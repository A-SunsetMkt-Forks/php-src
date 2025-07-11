/*
  +----------------------------------------------------------------------+
  | TAR archive support for Phar                                         |
  +----------------------------------------------------------------------+
  | Copyright (c) The PHP Group                                          |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | https://www.php.net/license/3_01.txt                                 |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Authors: Dmitry Stogov <dmitry@php.net>                              |
  |          Gregory Beaver <cellog@php.net>                             |
  +----------------------------------------------------------------------+
*/

#include "phar_internal.h"
#include "ext/standard/php_string.h" /* For php_stristr() */

static uint32_t phar_tar_number(const char *buf, size_t len) /* {{{ */
{
	uint32_t num = 0;
	size_t i = 0;

	while (i < len && buf[i] == ' ') {
		++i;
	}

	while (i < len && buf[i] >= '0' && buf[i] <= '7') {
		num = num * 8 + (buf[i] - '0');
		++i;
	}

	return num;
}
/* }}} */

/* adapted from format_octal() in libarchive
 *
 * Copyright (c) 2003-2009 Tim Kientzle
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR(S) ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR(S) BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
static zend_result phar_tar_octal(char *buf, uint32_t val, size_t len) /* {{{ */
{
	char *p = buf;
	size_t s = len;

	p += len;		/* Start at the end and work backwards. */
	while (s-- > 0) {
		*--p = (char)('0' + (val & 7));
		val >>= 3;
	}

	if (val == 0) {
		return SUCCESS;
	}

	/* If it overflowed, fill field with max value. */
	while (len-- > 0) {
		*p++ = '7';
	}

	return FAILURE;
}
/* }}} */

static uint32_t phar_tar_checksum(char *buf, size_t len) /* {{{ */
{
	uint32_t sum = 0;
	char *end = buf + len;

	while (buf != end) {
		sum += (unsigned char)*buf;
		++buf;
	}
	return sum;
}
/* }}} */

bool phar_is_tar(char *buf, char *fname) /* {{{ */
{
	tar_header *header = (tar_header *) buf;
	uint32_t checksum = phar_tar_number(header->checksum, sizeof(header->checksum));
	bool is_tar;
	char save[sizeof(header->checksum)], *bname;

	/* assume that the first filename in a tar won't begin with <?php */
	if (!strncmp(buf, "<?php", sizeof("<?php")-1)) {
		return false;
	}

	memcpy(save, header->checksum, sizeof(header->checksum));
	memset(header->checksum, ' ', sizeof(header->checksum));
	is_tar = (checksum == phar_tar_checksum(buf, 512));
	memcpy(header->checksum, save, sizeof(header->checksum));
	if ((bname = strrchr(fname, PHP_DIR_SEPARATOR))) {
		fname = bname;
	}
	if (!is_tar && (bname = strstr(fname, ".tar")) && (bname[4] == '\0' || bname[4] == '.')) {
		/* probably a corrupted tar - so we will pretend it is one */
		return true;
	}
	return is_tar;
}
/* }}} */

zend_result phar_open_or_create_tar(char *fname, size_t fname_len, char *alias, size_t alias_len, int is_data, uint32_t options, phar_archive_data** pphar, char **error) /* {{{ */
{
	phar_archive_data *phar;
	zend_result ret = phar_create_or_parse_filename(fname, fname_len, alias, alias_len, is_data, options, &phar, error);

	if (FAILURE == ret) {
		return FAILURE;
	}

	if (pphar) {
		*pphar = phar;
	}

	phar->is_data = is_data;

	if (phar->is_tar) {
		return ret;
	}

	if (phar->is_brandnew) {
		phar->is_tar = 1;
		phar->is_zip = 0;
		return SUCCESS;
	}

	/* we've reached here - the phar exists and is a regular phar */
	if (error) {
		spprintf(error, 4096, "phar tar error: \"%s\" already exists as a regular phar and must be deleted from disk prior to creating as a tar-based phar", fname);
	}
	return FAILURE;
}
/* }}} */

static zend_result phar_tar_process_metadata(phar_entry_info *entry, php_stream *fp) /* {{{ */
{
	char *metadata;
	size_t save = php_stream_tell(fp), read;
	phar_entry_info *mentry;

	metadata = (char *) safe_emalloc(1, entry->uncompressed_filesize, 1);

	read = php_stream_read(fp, metadata, entry->uncompressed_filesize);
	if (read != entry->uncompressed_filesize) {
		efree(metadata);
		php_stream_seek(fp, save, SEEK_SET);
		return FAILURE;
	}

	phar_parse_metadata_lazy(metadata, &entry->metadata_tracker, entry->uncompressed_filesize, entry->is_persistent);

	if (zend_string_equals_literal(entry->filename, ".phar/.metadata.bin")) {
		if (phar_metadata_tracker_has_data(&entry->phar->metadata_tracker, entry->phar->is_persistent)) {
			efree(metadata);
			return FAILURE;
		}
		entry->phar->metadata_tracker = entry->metadata_tracker;
		entry->metadata_tracker.str = NULL;
		ZVAL_UNDEF(&entry->metadata_tracker.val);
	} else if (ZSTR_LEN(entry->filename) >= sizeof(".phar/.metadata/") + sizeof("/.metadata.bin") - 1 && NULL != (mentry = zend_hash_str_find_ptr(&entry->phar->manifest, ZSTR_VAL(entry->filename) + sizeof(".phar/.metadata/") - 1, ZSTR_LEN(entry->filename) - (sizeof("/.metadata.bin") - 1 + sizeof(".phar/.metadata/") - 1)))) {
		if (phar_metadata_tracker_has_data(&mentry->metadata_tracker, mentry->is_persistent)) {
			efree(metadata);
			return FAILURE;
		}
		/* transfer this metadata to the entry it refers */
		mentry->metadata_tracker = entry->metadata_tracker;
		entry->metadata_tracker.str = NULL;
		ZVAL_UNDEF(&entry->metadata_tracker.val);
	}

	efree(metadata);
	php_stream_seek(fp, save, SEEK_SET);
	return SUCCESS;
}
/* }}} */

zend_result phar_parse_tarfile(php_stream* fp, char *fname, size_t fname_len, char *alias, size_t alias_len, phar_archive_data** pphar, uint32_t compression, char **error) /* {{{ */
{
	char buf[512], *actual_alias = NULL, *p;
	phar_entry_info entry = {0};
	size_t pos = 0, read, totalsize;
	tar_header *hdr;
	uint32_t sum1, sum2, size, old;
	phar_archive_data *myphar, *actual;
	int last_was_longlink = 0;
	size_t linkname_len;

	if (error) {
		*error = NULL;
	}

	php_stream_seek(fp, 0, SEEK_END);
	totalsize = php_stream_tell(fp);
	php_stream_seek(fp, 0, SEEK_SET);
	read = php_stream_read(fp, buf, sizeof(buf));

	if (read != sizeof(buf)) {
		if (error) {
			spprintf(error, 4096, "phar error: \"%s\" is not a tar file or is truncated", fname);
		}
		php_stream_close(fp);
		return FAILURE;
	}

	hdr = (tar_header*)buf;
	old = (memcmp(hdr->magic, "ustar", sizeof("ustar")-1) != 0);

	myphar = (phar_archive_data *) pecalloc(1, sizeof(phar_archive_data), PHAR_G(persist));
	myphar->is_persistent = PHAR_G(persist);
	/* estimate number of entries, can't be certain with tar files */
	zend_hash_init(&myphar->manifest, 2 + (totalsize >> 12),
		zend_get_hash_value, destroy_phar_manifest_entry, (bool)myphar->is_persistent);
	zend_hash_init(&myphar->mounted_dirs, 5,
		zend_get_hash_value, NULL, (bool)myphar->is_persistent);
	zend_hash_init(&myphar->virtual_dirs, 4 + (totalsize >> 11),
		zend_get_hash_value, NULL, (bool)myphar->is_persistent);
	myphar->is_tar = 1;
	/* remember whether this entire phar was compressed with gz/bzip2 */
	myphar->flags = compression;

	entry.is_tar = 1;
	entry.is_crc_checked = 1;
	entry.phar = myphar;

	while (true) {
		phar_entry_info *newentry;

		pos = php_stream_tell(fp);
		hdr = (tar_header*) buf;
		sum1 = phar_tar_number(hdr->checksum, sizeof(hdr->checksum));
		if (sum1 == 0 && phar_tar_checksum(buf, sizeof(buf)) == 0) {
			break;
		}
		memset(hdr->checksum, ' ', sizeof(hdr->checksum));
		sum2 = phar_tar_checksum(buf, old?sizeof(old_tar_header):sizeof(tar_header));

		if (old && sum2 != sum1) {
			uint32_t sum3 = phar_tar_checksum(buf, sizeof(tar_header));
			if (sum3 == sum1) {
				/* apparently a broken tar which is in ustar format w/o setting the ustar marker */
				sum2 = sum3;
				old = 0;
			}
		}

		size = entry.uncompressed_filesize = entry.compressed_filesize =
			phar_tar_number(hdr->size, sizeof(hdr->size));

		/* skip global/file headers (pax) */
		if (!old && (hdr->typeflag == TAR_GLOBAL_HDR || hdr->typeflag == TAR_FILE_HDR)) {
			size = (size+511)&~511;
			goto next;
		}

		if (((!old && hdr->prefix[0] == 0) || old) && zend_strnlen(hdr->name, 100) == sizeof(".phar/signature.bin")-1 && !strncmp(hdr->name, ".phar/signature.bin", sizeof(".phar/signature.bin")-1)) {
			zend_off_t curloc;
			size_t sig_len;

			if (size > 511) {
				if (error) {
					spprintf(error, 4096, "phar error: tar-based phar \"%s\" has signature that is larger than 511 bytes, cannot process", fname);
				}
bail:
				php_stream_close(fp);
				phar_destroy_phar_data(myphar);
				return FAILURE;
			}
			curloc = php_stream_tell(fp);
			read = php_stream_read(fp, buf, size);
			if (read != size || read <= 8) {
				if (error) {
					spprintf(error, 4096, "phar error: tar-based phar \"%s\" signature cannot be read", fname);
				}
				goto bail;
			}
#ifdef WORDS_BIGENDIAN
# define PHAR_GET_32(buffer) \
	(((((unsigned char*)(buffer))[3]) << 24) \
		| ((((unsigned char*)(buffer))[2]) << 16) \
		| ((((unsigned char*)(buffer))[1]) <<  8) \
		| (((unsigned char*)(buffer))[0]))
#else
# define PHAR_GET_32(buffer) (uint32_t) *(buffer)
#endif
			myphar->sig_flags = PHAR_GET_32(buf);
			if (FAILURE == phar_verify_signature(fp, php_stream_tell(fp) - size - 512, myphar->sig_flags, buf + 8, size - 8, fname, &myphar->signature, &sig_len, error)) {
				if (error) {
					char *save = *error;
					spprintf(error, 4096, "phar error: tar-based phar \"%s\" signature cannot be verified: %s", fname, save);
					efree(save);
				}
				goto bail;
			}
			myphar->sig_len = sig_len;
			php_stream_seek(fp, curloc + 512, SEEK_SET);
			/* signature checked out, let's ensure this is the last file in the phar */
			if (((hdr->typeflag == '\0') || (hdr->typeflag == TAR_FILE)) && size > 0) {
				/* this is not good enough - seek succeeds even on truncated tars */
				php_stream_seek(fp, 512, SEEK_CUR);
				if ((uint32_t)php_stream_tell(fp) > totalsize) {
					if (error) {
						spprintf(error, 4096, "phar error: \"%s\" is a corrupted tar file (truncated)", fname);
					}
					php_stream_close(fp);
					phar_destroy_phar_data(myphar);
					return FAILURE;
				}
			}

			read = php_stream_read(fp, buf, sizeof(buf));

			if (read != sizeof(buf)) {
				if (error) {
					spprintf(error, 4096, "phar error: \"%s\" is a corrupted tar file (truncated)", fname);
				}
				php_stream_close(fp);
				phar_destroy_phar_data(myphar);
				return FAILURE;
			}

			hdr = (tar_header*) buf;
			sum1 = phar_tar_number(hdr->checksum, sizeof(hdr->checksum));

			if (sum1 == 0 && phar_tar_checksum(buf, sizeof(buf)) == 0) {
				break;
			}

			if (error) {
				spprintf(error, 4096, "phar error: \"%s\" has entries after signature, invalid phar", fname);
			}

			goto bail;
		}

		if (!last_was_longlink && hdr->typeflag == 'L') {
			last_was_longlink = 1;
			/* support the ././@LongLink system for storing long filenames */

			/* Check for overflow - bug 61065 */
			if (entry.uncompressed_filesize == UINT_MAX || entry.uncompressed_filesize == 0) {
				if (error) {
					spprintf(error, 4096, "phar error: \"%s\" is a corrupted tar file (invalid entry size)", fname);
				}
				php_stream_close(fp);
				phar_destroy_phar_data(myphar);
				return FAILURE;
			}
			entry.filename = zend_string_alloc(entry.uncompressed_filesize, myphar->is_persistent);
			if (myphar->is_persistent) {
				GC_MAKE_PERSISTENT_LOCAL(entry.filename);
			}
			ZSTR_VAL(entry.filename)[entry.uncompressed_filesize] = '\0';

			read = php_stream_read(fp, ZSTR_VAL(entry.filename), entry.uncompressed_filesize);
			if (read != entry.uncompressed_filesize) {
				zend_string_free(entry.filename);
				if (error) {
					spprintf(error, 4096, "phar error: \"%s\" is a corrupted tar file (truncated)", fname);
				}
				php_stream_close(fp);
				phar_destroy_phar_data(myphar);
				return FAILURE;
			}

			/* skip blank stuff */
			size = ((size+511)&~511) - size;

			/* this is not good enough - seek succeeds even on truncated tars */
			php_stream_seek(fp, size, SEEK_CUR);
			if ((uint32_t)php_stream_tell(fp) > totalsize) {
				zend_string_free(entry.filename);
				if (error) {
					spprintf(error, 4096, "phar error: \"%s\" is a corrupted tar file (truncated)", fname);
				}
				php_stream_close(fp);
				phar_destroy_phar_data(myphar);
				return FAILURE;
			}

			read = php_stream_read(fp, buf, sizeof(buf));

			if (read != sizeof(buf)) {
				zend_string_free(entry.filename);
				if (error) {
					spprintf(error, 4096, "phar error: \"%s\" is a corrupted tar file (truncated)", fname);
				}
				php_stream_close(fp);
				phar_destroy_phar_data(myphar);
				return FAILURE;
			}
			continue;
		} else if (!last_was_longlink && !old && hdr->prefix[0] != 0) {
			char name[256];
			int i, j;

			for (i = 0; i < 155; i++) {
				name[i] = hdr->prefix[i];
				if (name[i] == '\0') {
					break;
				}
			}
			name[i++] = '/';
			for (j = 0; j < 100; j++) {
				name[i+j] = hdr->name[j];
				if (name[i+j] == '\0') {
					break;
				}
			}

			uint32_t filename_len = i + j;

			if (name[filename_len - 1] == '/') {
				/* some tar programs store directories with trailing slash */
				filename_len--;
			}

			entry.filename = zend_string_init(name, filename_len, myphar->is_persistent);
			if (myphar->is_persistent) {
				GC_MAKE_PERSISTENT_LOCAL(entry.filename);
			}
		} else if (!last_was_longlink) {
			/* calculate strlen, which can be no longer than 100 */
			uint32_t filename_len;
			for (filename_len = 0; filename_len < 100; filename_len++) {
				if (hdr->name[filename_len] == '\0') {
					break;
				}
			}

			if (filename_len > 0 && hdr->name[filename_len - 1] == '/') {
				/* some tar programs store directories with trailing slash */
				filename_len--;
			}

			entry.filename = zend_string_init(hdr->name, filename_len, myphar->is_persistent);
			if (myphar->is_persistent) {
				GC_MAKE_PERSISTENT_LOCAL(entry.filename);
			}
		}
		last_was_longlink = 0;

		phar_add_virtual_dirs(myphar, ZSTR_VAL(entry.filename), ZSTR_LEN(entry.filename));

		if (sum1 != sum2) {
			if (error) {
				spprintf(error, 4096, "phar error: \"%s\" is a corrupted tar file (checksum mismatch of file \"%s\")", fname, ZSTR_VAL(entry.filename));
			}
			zend_string_release_ex(entry.filename, myphar->is_persistent);
			php_stream_close(fp);
			phar_destroy_phar_data(myphar);
			return FAILURE;
		}

		uint32_t entry_mode = phar_tar_number(hdr->mode, sizeof(hdr->mode));
		entry.tar_type = ((old & (hdr->typeflag == '\0')) ? TAR_FILE : hdr->typeflag);
		entry.offset = entry.offset_abs = pos; /* header_offset unused in tar */
		entry.fp_type = PHAR_FP;
		entry.flags = entry_mode & PHAR_ENT_PERM_MASK;
		entry.timestamp = phar_tar_number(hdr->mtime, sizeof(hdr->mtime));
		entry.is_persistent = myphar->is_persistent;

		if (old && entry.tar_type == TAR_FILE && S_ISDIR(entry_mode)) {
			entry.tar_type = TAR_DIR;
		}

		if (entry.tar_type == TAR_DIR) {
			entry.is_dir = 1;
		} else {
			entry.is_dir = 0;
		}

		entry.link = NULL;
		/* link field is null-terminated unless it has 100 non-null chars.
		 * Thus we cannot use strlen. */
		linkname_len = zend_strnlen(hdr->linkname, 100);
		if (entry.tar_type == TAR_LINK) {
			if (!zend_hash_str_exists(&myphar->manifest, hdr->linkname, linkname_len)) {
				if (error) {
					spprintf(error, 4096, "phar error: \"%s\" is a corrupted tar file - hard link to non-existent file \"%.*s\"", fname, (int)linkname_len, hdr->linkname);
				}
				zend_string_release_ex(entry.filename, myphar->is_persistent);
				php_stream_close(fp);
				phar_destroy_phar_data(myphar);
				return FAILURE;
			}
			entry.link = estrndup(hdr->linkname, linkname_len);
		} else if (entry.tar_type == TAR_SYMLINK) {
			entry.link = estrndup(hdr->linkname, linkname_len);
		}
		phar_set_inode(&entry);

		newentry = zend_hash_update_mem(&myphar->manifest, entry.filename, &entry, sizeof(phar_entry_info));
		ZEND_ASSERT(newentry != NULL);

		if (entry.is_persistent) {
			++entry.manifest_pos;
		}

		if (zend_string_starts_with_literal(entry.filename, ".phar/.metadata")) {
			if (FAILURE == phar_tar_process_metadata(newentry, fp)) {
				if (error) {
					spprintf(error, 4096, "phar error: tar-based phar \"%s\" has invalid metadata in magic file \"%s\"", fname, ZSTR_VAL(entry.filename));
				}
				php_stream_close(fp);
				phar_destroy_phar_data(myphar);
				return FAILURE;
			}
		}

		if (!actual_alias && zend_string_equals_literal(entry.filename, ".phar/alias.txt")) {
			/* found explicit alias */
			if (size > 511) {
				if (error) {
					spprintf(error, 4096, "phar error: tar-based phar \"%s\" has alias that is larger than 511 bytes, cannot process", fname);
				}
				php_stream_close(fp);
				phar_destroy_phar_data(myphar);
				return FAILURE;
			}

			read = php_stream_read(fp, buf, size);

			if (read == size) {
				buf[size] = '\0';
				if (!phar_validate_alias(buf, size)) {
					if (size > 50) {
						buf[50] = '.';
						buf[51] = '.';
						buf[52] = '.';
						buf[53] = '\0';
					}

					if (error) {
						spprintf(error, 4096, "phar error: invalid alias \"%s\" in tar-based phar \"%s\"", buf, fname);
					}

					php_stream_close(fp);
					phar_destroy_phar_data(myphar);
					return FAILURE;
				}

				actual_alias = pestrndup(buf, size, myphar->is_persistent);
				myphar->alias = actual_alias;
				myphar->alias_len = size;
				php_stream_seek(fp, pos, SEEK_SET);
			} else {
				if (error) {
					spprintf(error, 4096, "phar error: Unable to read alias from tar-based phar \"%s\"", fname);
				}

				php_stream_close(fp);
				phar_destroy_phar_data(myphar);
				return FAILURE;
			}
		}

		size = (size+511)&~511;

		if (((hdr->typeflag == '\0') || (hdr->typeflag == TAR_FILE)) && size > 0) {
next:
			/* this is not good enough - seek succeeds even on truncated tars */
			php_stream_seek(fp, size, SEEK_CUR);
			if ((uint32_t)php_stream_tell(fp) > totalsize) {
				if (error) {
					spprintf(error, 4096, "phar error: \"%s\" is a corrupted tar file (truncated)", fname);
				}
				php_stream_close(fp);
				phar_destroy_phar_data(myphar);
				return FAILURE;
			}
		}

		/* Only read next header if we're not yet at the end */
		if (php_stream_tell(fp) == totalsize) {
			break;
		}

		read = php_stream_read(fp, buf, sizeof(buf));

		if (read != sizeof(buf)) {
			if (error) {
				spprintf(error, 4096, "phar error: \"%s\" is a corrupted tar file (truncated)", fname);
			}
			php_stream_close(fp);
			phar_destroy_phar_data(myphar);
			return FAILURE;
		}
	}

	if (zend_hash_str_exists(&(myphar->manifest), ".phar/stub.php", sizeof(".phar/stub.php")-1)) {
		myphar->is_data = 0;
	} else {
		myphar->is_data = 1;
	}

	/* ensure signature set */
	if (!myphar->is_data && PHAR_G(require_hash) && !myphar->signature) {
		php_stream_close(fp);
		phar_destroy_phar_data(myphar);
		if (error) {
			spprintf(error, 0, "tar-based phar \"%s\" does not have a signature", fname);
		}
		return FAILURE;
	}

	myphar->fname = pestrndup(fname, fname_len, myphar->is_persistent);
#ifdef PHP_WIN32
	phar_unixify_path_separators(myphar->fname, fname_len);
#endif
	myphar->fname_len = fname_len;
	myphar->fp = fp;
	p = strrchr(myphar->fname, '/');

	if (p) {
		myphar->ext = memchr(p, '.', (myphar->fname + fname_len) - p);
		if (myphar->ext == p) {
			myphar->ext = memchr(p + 1, '.', (myphar->fname + fname_len) - p - 1);
		}
		if (myphar->ext) {
			myphar->ext_len = (myphar->fname + fname_len) - myphar->ext;
		}
	}

	phar_request_initialize();

	if (NULL == (actual = zend_hash_str_add_ptr(&(PHAR_G(phar_fname_map)), myphar->fname, fname_len, myphar))) {
		if (error) {
			spprintf(error, 4096, "phar error: Unable to add tar-based phar \"%s\" to phar registry", fname);
		}
		php_stream_close(fp);
		phar_destroy_phar_data(myphar);
		return FAILURE;
	}

	myphar = actual;

	if (actual_alias) {
		phar_archive_data *fd_ptr;

		myphar->is_temporary_alias = 0;

		if (NULL != (fd_ptr = zend_hash_str_find_ptr(&(PHAR_G(phar_alias_map)), actual_alias, myphar->alias_len))) {
			if (SUCCESS != phar_free_alias(fd_ptr, actual_alias, myphar->alias_len)) {
				if (error) {
					spprintf(error, 4096, "phar error: Unable to add tar-based phar \"%s\", alias is already in use", fname);
				}
				zend_hash_str_del(&(PHAR_G(phar_fname_map)), myphar->fname, fname_len);
				return FAILURE;
			}
		}

		zend_hash_str_add_ptr(&(PHAR_G(phar_alias_map)), actual_alias, myphar->alias_len, myphar);
	} else {
		phar_archive_data *fd_ptr;

		if (alias_len) {
			if (NULL != (fd_ptr = zend_hash_str_find_ptr(&(PHAR_G(phar_alias_map)), alias, alias_len))) {
				if (SUCCESS != phar_free_alias(fd_ptr, alias, alias_len)) {
					if (error) {
						spprintf(error, 4096, "phar error: Unable to add tar-based phar \"%s\", alias is already in use", fname);
					}
					zend_hash_str_del(&(PHAR_G(phar_fname_map)), myphar->fname, fname_len);
					return FAILURE;
				}
			}
			zend_hash_str_add_ptr(&(PHAR_G(phar_alias_map)), alias, alias_len, myphar);
			myphar->alias = pestrndup(alias, alias_len, myphar->is_persistent);
			myphar->alias_len = alias_len;
		} else {
			myphar->alias = pestrndup(myphar->fname, fname_len, myphar->is_persistent);
			myphar->alias_len = fname_len;
		}

		myphar->is_temporary_alias = 1;
	}

	if (pphar) {
		*pphar = myphar;
	}

	return SUCCESS;
}
/* }}} */

struct _phar_pass_tar_info {
	php_stream *old;
	php_stream *new;
	bool free_fp;
	bool free_ufp;
	char **error;
};

static int phar_tar_writeheaders_int(phar_entry_info *entry, void *argument) /* {{{ */
{
	tar_header header;
	size_t pos;
	struct _phar_pass_tar_info *fp = (struct _phar_pass_tar_info *)argument;
	char padding[512];

	if (entry->is_mounted) {
		return ZEND_HASH_APPLY_KEEP;
	}

	if (entry->is_deleted) {
		if (entry->fp_refcount <= 0) {
			return ZEND_HASH_APPLY_REMOVE;
		} else {
			/* we can't delete this in-memory until it is closed */
			return ZEND_HASH_APPLY_KEEP;
		}
	}

	phar_add_virtual_dirs(entry->phar, ZSTR_VAL(entry->filename), ZSTR_LEN(entry->filename));
	memset((char *) &header, 0, sizeof(header));

	if (ZSTR_LEN(entry->filename) > 100) {
		char *boundary;
		if (ZSTR_LEN(entry->filename) > 256) {
			if (fp->error) {
				spprintf(fp->error, 4096, "tar-based phar \"%s\" cannot be created, filename \"%s\" is too long for tar file format", entry->phar->fname, ZSTR_VAL(entry->filename));
			}
			return ZEND_HASH_APPLY_STOP;
		}
		boundary = ZSTR_VAL(entry->filename) + ZSTR_LEN(entry->filename) - 101;
		while (*boundary && *boundary != '/') {
			++boundary;
		}
		if (!*boundary || ((boundary - ZSTR_VAL(entry->filename)) > 155)) {
			if (fp->error) {
				spprintf(fp->error, 4096, "tar-based phar \"%s\" cannot be created, filename \"%s\" is too long for tar file format", entry->phar->fname, ZSTR_VAL(entry->filename));
			}
			return ZEND_HASH_APPLY_STOP;
		}
		memcpy(header.prefix, ZSTR_VAL(entry->filename), boundary - ZSTR_VAL(entry->filename));
		memcpy(header.name, boundary + 1, ZSTR_LEN(entry->filename) - (boundary + 1 - ZSTR_VAL(entry->filename)));
	} else {
		memcpy(header.name, ZSTR_VAL(entry->filename), ZSTR_LEN(entry->filename));
	}

	phar_tar_octal(header.mode, entry->flags & PHAR_ENT_PERM_MASK, sizeof(header.mode)-1);

	if (FAILURE == phar_tar_octal(header.size, entry->uncompressed_filesize, sizeof(header.size)-1)) {
		if (fp->error) {
			spprintf(fp->error, 4096, "tar-based phar \"%s\" cannot be created, filename \"%s\" is too large for tar file format", entry->phar->fname, ZSTR_VAL(entry->filename));
		}
		return ZEND_HASH_APPLY_STOP;
	}

	if (FAILURE == phar_tar_octal(header.mtime, entry->timestamp, sizeof(header.mtime)-1)) {
		if (fp->error) {
			spprintf(fp->error, 4096, "tar-based phar \"%s\" cannot be created, file modification time of file \"%s\" is too large for tar file format", entry->phar->fname, ZSTR_VAL(entry->filename));
		}
		return ZEND_HASH_APPLY_STOP;
	}

	/* calc checksum */
	header.typeflag = entry->tar_type;

	if (entry->link) {
		if (strlcpy(header.linkname, entry->link, sizeof(header.linkname)) >= sizeof(header.linkname)) {
			if (fp->error) {
				spprintf(fp->error, 4096, "tar-based phar \"%s\" cannot be created, link \"%s\" is too long for format", entry->phar->fname, entry->link);
			}
			return ZEND_HASH_APPLY_STOP;
		}
	}

	memcpy(header.magic, "ustar", sizeof("ustar")-1);
	memcpy(header.version, "00", sizeof("00")-1);
	memcpy(header.checksum, "        ", sizeof("        ")-1);
	entry->crc32 = phar_tar_checksum((char *)&header, sizeof(header));

	if (FAILURE == phar_tar_octal(header.checksum, entry->crc32, sizeof(header.checksum)-1)) {
		if (fp->error) {
			spprintf(fp->error, 4096, "tar-based phar \"%s\" cannot be created, checksum of file \"%s\" is too large for tar file format", entry->phar->fname, ZSTR_VAL(entry->filename));
		}
		return ZEND_HASH_APPLY_STOP;
	}

	/* write header */
	entry->header_offset = php_stream_tell(fp->new);

	if (sizeof(header) != php_stream_write(fp->new, (char *) &header, sizeof(header))) {
		if (fp->error) {
			spprintf(fp->error, 4096, "tar-based phar \"%s\" cannot be created, header for  file \"%s\" could not be written", entry->phar->fname, ZSTR_VAL(entry->filename));
		}
		return ZEND_HASH_APPLY_STOP;
	}

	pos = php_stream_tell(fp->new); /* save start of file within tar */

	/* write contents */
	if (entry->uncompressed_filesize) {
		if (FAILURE == phar_open_entry_fp(entry, fp->error, 0)) {
			return ZEND_HASH_APPLY_STOP;
		}

		if (-1 == phar_seek_efp(entry, 0, SEEK_SET, 0, 0)) {
			if (fp->error) {
				spprintf(fp->error, 4096, "tar-based phar \"%s\" cannot be created, contents of file \"%s\" could not be written, seek failed", entry->phar->fname, ZSTR_VAL(entry->filename));
			}
			return ZEND_HASH_APPLY_STOP;
		}

		if (SUCCESS != php_stream_copy_to_stream_ex(phar_get_efp(entry, 0), fp->new, entry->uncompressed_filesize, NULL)) {
			if (fp->error) {
				spprintf(fp->error, 4096, "tar-based phar \"%s\" cannot be created, contents of file \"%s\" could not be written", entry->phar->fname, ZSTR_VAL(entry->filename));
			}
			return ZEND_HASH_APPLY_STOP;
		}

		memset(padding, 0, 512);
		php_stream_write(fp->new, padding, ((entry->uncompressed_filesize +511)&~511) - entry->uncompressed_filesize);
	}

	if (entry->fp_refcount) {
		/* open file pointers refer to this fp, do not free the stream */
		switch (entry->fp_type) {
			case PHAR_FP:
				fp->free_fp = 0;
				break;
			case PHAR_UFP:
				fp->free_ufp = 0;
			default:
				break;
		}
	}

	entry->is_modified = 0;

	if (entry->fp_type == PHAR_MOD && entry->fp != entry->phar->fp && entry->fp != entry->phar->ufp) {
		if (!entry->fp_refcount) {
			php_stream_close(entry->fp);
		}
		entry->fp = NULL;
	}

	entry->fp_type = PHAR_FP;

	/* note new location within tar */
	entry->offset = entry->offset_abs = pos;
	return ZEND_HASH_APPLY_KEEP;
}
/* }}} */

static int phar_tar_writeheaders(zval *zv, void *argument) /* {{{ */
{
	return phar_tar_writeheaders_int(Z_PTR_P(zv), argument);
}
/* }}} */

static int phar_tar_setmetadata(const phar_metadata_tracker *tracker, phar_entry_info *entry, char **error) /* {{{ */
{
	/* Copy the metadata from tracker to the new entry being written out to temporary files */
	const zend_string *serialized_str;
	phar_metadata_tracker_copy(&entry->metadata_tracker, tracker, entry->is_persistent);
	phar_metadata_tracker_try_ensure_has_serialized_data(&entry->metadata_tracker, entry->is_persistent);
	serialized_str = entry->metadata_tracker.str;

	/* If there is no data, this will replace the metadata file (e.g. .phar/.metadata.bin) with an empty file */
	entry->uncompressed_filesize = entry->compressed_filesize = serialized_str ? ZSTR_LEN(serialized_str) : 0;

	if (entry->fp && entry->fp_type == PHAR_MOD) {
		php_stream_close(entry->fp);
	}

	entry->fp_type = PHAR_MOD;
	entry->is_modified = 1;
	entry->fp = php_stream_fopen_tmpfile();
	entry->offset = entry->offset_abs = 0;
	if (entry->fp == NULL) {
		spprintf(error, 0, "phar error: unable to create temporary file");
		return -1;
	}
	if (serialized_str && ZSTR_LEN(serialized_str) != php_stream_write(entry->fp, ZSTR_VAL(serialized_str), ZSTR_LEN(serialized_str))) {
		spprintf(error, 0, "phar tar error: unable to write metadata to magic metadata file \"%s\"", ZSTR_VAL(entry->filename));
		zend_hash_del(&entry->phar->manifest, entry->filename);
		return ZEND_HASH_APPLY_STOP;
	}

	return ZEND_HASH_APPLY_KEEP;
}
/* }}} */

static int phar_tar_setupmetadata(zval *zv, void *argument) /* {{{ */
{
	struct _phar_pass_tar_info *i = (struct _phar_pass_tar_info *)argument;
	char **error = i->error;
	phar_entry_info *entry = (phar_entry_info *)Z_PTR_P(zv), *metadata, newentry = {0};

	if (zend_string_starts_with_literal(entry->filename, ".phar/.metadata")) {
		if (zend_string_equals_literal(entry->filename, ".phar/.metadata.bin")) {
			return phar_tar_setmetadata(&entry->phar->metadata_tracker, entry, error);
		}
		/* search for the file this metadata entry references */
		if (ZSTR_LEN(entry->filename) >= sizeof(".phar/.metadata/") + sizeof("/.metadata.bin") - 1 && !zend_hash_str_exists(&entry->phar->manifest, ZSTR_VAL(entry->filename) + sizeof(".phar/.metadata/") - 1, ZSTR_LEN(entry->filename) - (sizeof("/.metadata.bin") - 1 + sizeof(".phar/.metadata/") - 1))) {
			/* this is orphaned metadata, erase it */
			return ZEND_HASH_APPLY_REMOVE;
		}
		/* we can keep this entry, the file that refers to it exists */
		return ZEND_HASH_APPLY_KEEP;
	}

	if (!entry->is_modified) {
		return ZEND_HASH_APPLY_KEEP;
	}

	/* now we are dealing with regular files, so look for metadata */
	zend_string *lookfor = zend_strpprintf_unchecked(0, ".phar/.metadata/%S/.metadata.bin", entry->filename);

	if (!phar_metadata_tracker_has_data(&entry->metadata_tracker, entry->is_persistent)) {
		zend_hash_del(&entry->phar->manifest, lookfor);
		zend_string_efree(lookfor);
		return ZEND_HASH_APPLY_KEEP;
	}

	if (NULL != (metadata = zend_hash_find_ptr(&entry->phar->manifest, lookfor))) {
		int ret;
		ret = phar_tar_setmetadata(&entry->metadata_tracker, metadata, error);
		zend_string_efree(lookfor);
		return ret;
	}

	newentry.filename = lookfor;
	newentry.phar = entry->phar;
	newentry.tar_type = TAR_FILE;
	newentry.is_tar = 1;

	if (NULL == (metadata = zend_hash_add_mem(&entry->phar->manifest, lookfor, &newentry, sizeof(phar_entry_info)))) {
		zend_string_efree(lookfor);
		spprintf(error, 0, "phar tar error: unable to add magic metadata file to manifest for file \"%s\"", ZSTR_VAL(entry->filename));
		return ZEND_HASH_APPLY_STOP;
	}

	return phar_tar_setmetadata(&entry->metadata_tracker, metadata, error);
}
/* }}} */

void phar_tar_flush(phar_archive_data *phar, zend_string *user_stub, bool is_default_stub, char **error) /* {{{ */
{
	static const char newstub[] = "<?php // tar-based phar archive stub file\n__HALT_COMPILER();";
	static const char halt_stub[] = "__HALT_COMPILER();";

	phar_entry_info entry = {0};
	php_stream *oldfile, *newfile;
	bool must_close_old_file = false;
	size_t signature_length;
	struct _phar_pass_tar_info pass;
	char *buf, *signature, sigbuf[8];

	entry.flags = PHAR_ENT_PERM_DEF_FILE;
	entry.timestamp = time(NULL);
	entry.is_modified = 1;
	entry.is_crc_checked = 1;
	entry.is_tar = 1;
	entry.tar_type = '0';
	entry.phar = phar;
	entry.fp_type = PHAR_MOD;
	entry.fp = NULL;
	entry.filename = NULL;

	if (phar->is_persistent) {
		if (error) {
			spprintf(error, 0, "internal error: attempt to flush cached tar-based phar \"%s\"", phar->fname);
		}
		return;
	}

	if (phar->is_data) {
		goto nostub;
	}

	/* set alias */
	if (!phar->is_temporary_alias && phar->alias_len) {
		entry.fp = php_stream_fopen_tmpfile();
		if (entry.fp == NULL) {
			spprintf(error, 0, "phar error: unable to create temporary file");
			return;
		}
		if (phar->alias_len != php_stream_write(entry.fp, phar->alias, phar->alias_len)) {
			if (error) {
				spprintf(error, 0, "unable to set alias in tar-based phar \"%s\"", phar->fname);
			}
			php_stream_close(entry.fp);
			return;
		}

		entry.uncompressed_filesize = phar->alias_len;

		entry.filename = ZSTR_INIT_LITERAL(".phar/alias.txt", false);
		zend_hash_update_mem(&phar->manifest, entry.filename, &entry, sizeof(phar_entry_info));
		/* At this point the entry is saved into the manifest. The manifest destroy
			routine will care about any resources to be freed. */
	} else {
		zend_hash_str_del(&phar->manifest, ".phar/alias.txt", sizeof(".phar/alias.txt")-1);
	}

	/* set stub */
	if (user_stub && !is_default_stub) {
		char *pos = php_stristr(ZSTR_VAL(user_stub), halt_stub, ZSTR_LEN(user_stub), sizeof(halt_stub) - 1);

		if (pos == NULL) {
			if (error) {
				spprintf(error, 0, "illegal stub for tar-based phar \"%s\"", phar->fname);
			}
			return;
		}

		size_t len = pos - ZSTR_VAL(user_stub) + strlen(halt_stub);
		const char end_sequence[] = " ?>\r\n";
		size_t end_sequence_len = strlen(end_sequence);

		entry.fp = php_stream_fopen_tmpfile();
		if (entry.fp == NULL) {
			spprintf(error, 0, "phar error: unable to create temporary file");
			return;
		}
		entry.uncompressed_filesize = len + end_sequence_len;

		if (
			len != php_stream_write(entry.fp, ZSTR_VAL(user_stub), len)
			|| end_sequence_len != php_stream_write(entry.fp, end_sequence, end_sequence_len)
		) {
			if (error) {
				spprintf(error, 0, "unable to create stub from string in new tar-based phar \"%s\"", phar->fname);
			}
			php_stream_close(entry.fp);
			return;
		}

		entry.filename = ZSTR_INIT_LITERAL(".phar/stub.php", false);
		zend_hash_update_mem(&phar->manifest, entry.filename, &entry, sizeof(phar_entry_info));
	} else {
		/* Either this is a brand new phar (add the stub), or the default stub is required (overwrite the stub) */
		entry.fp = php_stream_fopen_tmpfile();
		if (entry.fp == NULL) {
			spprintf(error, 0, "phar error: unable to create temporary file");
			return;
		}
		if (sizeof(newstub)-1 != php_stream_write(entry.fp, newstub, sizeof(newstub)-1)) {
			php_stream_close(entry.fp);
			if (error) {
				spprintf(error, 0, "unable to %s stub in%star-based phar \"%s\", failed", user_stub ? "overwrite" : "create", user_stub ? " " : " new ", phar->fname);
			}
			return;
		}

		entry.uncompressed_filesize = entry.compressed_filesize = sizeof(newstub) - 1;
		entry.filename = ZSTR_INIT_LITERAL(".phar/stub.php", false);

		if (!is_default_stub) {
			if (!zend_hash_exists(&phar->manifest, entry.filename)) {
				if (NULL == zend_hash_add_mem(&phar->manifest, entry.filename, &entry, sizeof(phar_entry_info))) {
					php_stream_close(entry.fp);
					zend_string_efree(entry.filename);
					if (error) {
						spprintf(error, 0, "unable to create stub in tar-based phar \"%s\"", phar->fname);
					}
					return;
				}
			} else {
				php_stream_close(entry.fp);
				zend_string_efree(entry.filename);
			}
		} else {
			zend_hash_update_mem(&phar->manifest, entry.filename, &entry, sizeof(phar_entry_info));
		}
	}
nostub:
	if (phar->fp && !phar->is_brandnew) {
		oldfile = phar->fp;
		must_close_old_file = false;
		php_stream_rewind(oldfile);
	} else {
		oldfile = php_stream_open_wrapper(phar->fname, "rb", 0, NULL);
		must_close_old_file = oldfile != NULL;
	}

	newfile = php_stream_fopen_tmpfile();
	if (!newfile) {
		if (error) {
			spprintf(error, 0, "unable to create temporary file");
		}
		if (must_close_old_file) {
			php_stream_close(oldfile);
		}
		return;
	}

	pass.old = oldfile;
	pass.new = newfile;
	pass.error = error;
	pass.free_fp = 1;
	pass.free_ufp = 1;

	if (phar_metadata_tracker_has_data(&phar->metadata_tracker, phar->is_persistent)) {
		phar_entry_info *mentry;
		if (NULL != (mentry = zend_hash_str_find_ptr(&(phar->manifest), ".phar/.metadata.bin", sizeof(".phar/.metadata.bin")-1))) {
			if (ZEND_HASH_APPLY_KEEP != phar_tar_setmetadata(&phar->metadata_tracker, mentry, error)) {
				if (must_close_old_file) {
					php_stream_close(oldfile);
				}
				return;
			}
		} else {
			phar_entry_info newentry = {0};

			newentry.filename = ZSTR_INIT_LITERAL(".phar/.metadata.bin", false);
			newentry.phar = phar;
			newentry.tar_type = TAR_FILE;
			newentry.is_tar = 1;

			if (NULL == (mentry = zend_hash_add_mem(&phar->manifest, newentry.filename, &newentry, sizeof(phar_entry_info)))) {
				zend_string_efree(newentry.filename);
				spprintf(error, 0, "phar tar error: unable to add magic metadata file to manifest for phar archive \"%s\"", phar->fname);
				if (must_close_old_file) {
					php_stream_close(oldfile);
				}
				return;
			}

			if (ZEND_HASH_APPLY_KEEP != phar_tar_setmetadata(&phar->metadata_tracker, mentry, error)) {
				zend_hash_del(&phar->manifest, newentry.filename);
				if (must_close_old_file) {
					php_stream_close(oldfile);
				}
				return;
			}
		}
	}

	zend_hash_apply_with_argument(&phar->manifest, phar_tar_setupmetadata, (void *) &pass);

	if (error && *error) {
		if (must_close_old_file) {
			php_stream_close(oldfile);
		}

		/* on error in the hash iterator above, error is set */
		php_stream_close(newfile);
		return;
	}

	zend_hash_apply_with_argument(&phar->manifest, phar_tar_writeheaders, (void *) &pass);

	/* add signature for executable tars or tars explicitly set with setSignatureAlgorithm */
	if (!phar->is_data || phar->sig_flags) {
		if (FAILURE == phar_create_signature(phar, newfile, &signature, &signature_length, error)) {
			if (error) {
				char *save = *error;
				spprintf(error, 0, "phar error: unable to write signature to tar-based phar: %s", save);
				efree(save);
			}

			if (must_close_old_file) {
				php_stream_close(oldfile);
			}

			php_stream_close(newfile);
			return;
		}

		entry.fp = php_stream_fopen_tmpfile();
		if (entry.fp == NULL) {
			spprintf(error, 0, "phar error: unable to create temporary file");
			return;
		}
#ifdef WORDS_BIGENDIAN
# define PHAR_SET_32(destination, source) do { \
        uint32_t swapped = (((((unsigned char*)&(source))[3]) << 24) \
            | ((((unsigned char*)&(source))[2]) << 16) \
            | ((((unsigned char*)&(source))[1]) << 8) \
            | (((unsigned char*)&(source))[0])); \
        memcpy(destination, &swapped, 4); \
    } while (0);
#else
# define PHAR_SET_32(destination, source) memcpy(destination, &source, 4)
#endif
		PHAR_SET_32(sigbuf, phar->sig_flags);
		PHAR_SET_32(sigbuf + 4, signature_length);

		if (8 != php_stream_write(entry.fp, sigbuf, 8) || signature_length != php_stream_write(entry.fp, signature, signature_length)) {
			efree(signature);
			if (error) {
				spprintf(error, 0, "phar error: unable to write signature to tar-based phar %s", phar->fname);
			}

			if (must_close_old_file) {
				php_stream_close(oldfile);
			}
			php_stream_close(newfile);
			return;
		}

		ALLOCA_FLAG(use_heap);
		ZSTR_ALLOCA_INIT(entry.filename, ".phar/signature.bin", sizeof(".phar/signature.bin")-1, use_heap);
		efree(signature);
		entry.uncompressed_filesize = entry.compressed_filesize = signature_length + 8;
		/* throw out return value and write the signature */
		phar_tar_writeheaders_int(&entry, &pass);
		ZSTR_ALLOCA_FREE(entry.filename, use_heap);

		if (error && *error) {
			if (must_close_old_file) {
				php_stream_close(oldfile);
			}
			/* error is set by writeheaders */
			php_stream_close(newfile);
			return;
		}
	} /* signature */

	/* add final zero blocks */
	buf = (char *) ecalloc(1024, 1);
	php_stream_write(newfile, buf, 1024);
	efree(buf);

	if (must_close_old_file) {
		php_stream_close(oldfile);
	}

	/* on error in the hash iterator above, error is set */
	if (error && *error) {
		php_stream_close(newfile);
		return;
	}

	if (phar->fp && pass.free_fp) {
		php_stream_close(phar->fp);
	}

	if (phar->ufp) {
		if (pass.free_ufp) {
			php_stream_close(phar->ufp);
		}
		phar->ufp = NULL;
	}

	phar->is_brandnew = 0;
	php_stream_rewind(newfile);

	if (phar->donotflush) {
		/* deferred flush */
		phar->fp = newfile;
	} else {
		phar->fp = php_stream_open_wrapper(phar->fname, "w+b", IGNORE_URL|STREAM_MUST_SEEK|REPORT_ERRORS, NULL);
		if (!phar->fp) {
			phar->fp = newfile;
			if (error) {
				spprintf(error, 0, "unable to open new phar \"%s\" for writing", phar->fname);
			}
			return;
		}

		if (phar->flags & PHAR_FILE_COMPRESSED_GZ) {
			php_stream_filter *filter;
			/* to properly compress, we have to tell zlib to add a zlib header */
			zval filterparams;

			array_init(&filterparams);
/* this is defined in zlib's zconf.h */
#ifndef MAX_WBITS
#define MAX_WBITS 15
#endif
			add_assoc_long(&filterparams, "window", MAX_WBITS + 16);
			filter = php_stream_filter_create("zlib.deflate", &filterparams, php_stream_is_persistent(phar->fp));
			zend_array_destroy(Z_ARR(filterparams));

			if (!filter) {
				/* copy contents uncompressed rather than lose them */
				php_stream_copy_to_stream_ex(newfile, phar->fp, PHP_STREAM_COPY_ALL, NULL);
				php_stream_close(newfile);
				if (error) {
					spprintf(error, 4096, "unable to compress all contents of phar \"%s\" using zlib, PHP versions older than 5.2.6 have a buggy zlib", phar->fname);
				}
				return;
			}

			php_stream_filter_append(&phar->fp->writefilters, filter);
			php_stream_copy_to_stream_ex(newfile, phar->fp, PHP_STREAM_COPY_ALL, NULL);
			php_stream_filter_flush(filter, 1);
			php_stream_filter_remove(filter, 1);
			php_stream_close(phar->fp);
			/* use the temp stream as our base */
			phar->fp = newfile;
		} else if (phar->flags & PHAR_FILE_COMPRESSED_BZ2) {
			php_stream_filter *filter;

			filter = php_stream_filter_create("bzip2.compress", NULL, php_stream_is_persistent(phar->fp));
			php_stream_filter_append(&phar->fp->writefilters, filter);
			php_stream_copy_to_stream_ex(newfile, phar->fp, PHP_STREAM_COPY_ALL, NULL);
			php_stream_filter_flush(filter, 1);
			php_stream_filter_remove(filter, 1);
			php_stream_close(phar->fp);
			/* use the temp stream as our base */
			phar->fp = newfile;
		} else {
			php_stream_copy_to_stream_ex(newfile, phar->fp, PHP_STREAM_COPY_ALL, NULL);
			/* we could also reopen the file in "rb" mode but there is no need for that */
			php_stream_close(newfile);
		}
	}
}
/* }}} */
