--TEST--
MHash: mhash_keygen_s2k() test
--SKIPIF--
<?php if(!function_exists('mhash')) { die('skip mhash compatibility layer not available'); } ?>
--FILE--
<?php

$supported_hash_al = array(
"MHASH_MD5"        => "8690154eaf9432cde9347aa15094b9c046eb06e6a0940c5479aa7a6367ae68b5e0e0745e5709fede2d9fe9739d9aad413759faa73acced821077b4ddb2788064e371eb53b3a9d55ed2839aab2655c82cfedbe83a208461c799d9d77ae481061c81539b01",
"MHASH_SHA1"       => "dd315c70061d07455d53c2fb0b08df0c61aa665c1ab1a701fa10955423248ba832a5ade406b39b78630aba3d1688e622494a0eae279d4ece9ad4bdf76e878fcb084a33c9153c2b48131d30a75b00a7c05b91f1ffeabf59bb1271c4d8a11990b84baf6d49",
"MHASH_HAVAL256"   => "0ede47009f87d5e9a24ecf5077d60c483657a5d98404ab2bb780f5872c90caf61c0d67645a848e55fee107296f4169c95b4e61f0aeeefab2648554c1171fb0a2fc32aa5aeed3d5c155d334367d4959622cdadefe43ae17bd1a75f9d4fef77bf192be5b78",
"MHASH_HAVAL224"   => "5c4aff3d825ad608f608c8eae779ee3868610bc60a98f3d770b311a6677c797fc2dadcab71dde0c0191e068397ab297f0de5cbbc6cbcd0c78ca8470c42401f6b77e81dc2ba8d51930ff982760335324fb850ac2d30b73514004c096d60472d320e0ec349",
"MHASH_HAVAL192"   => "22e0c27126023c852ef94107bb2f1ee132b064178b9dcbfb1c32e658760b8f70bdc5b1c52599031628c2433bee2b0870ab7a38aeb21215134ec1088975b9a96487642971ef9eb3d987baf9765fd9e6d64d494e1719aa84afe7e0a0784c74979ebab1c787",
"MHASH_HAVAL160"   => "d6e5f0ef07f3facced646eedb6364758ecde6dc6fb061e00a496f5ceb723f78ea135884d9682226ded69c11d8431240ef97cad583c4f29593bbf3dd3cab0b8792eb3d86022ca6002ebd0d9b4429909d4af85bed2b5a96b3e47b9b8cac919c1177ec40d7e",
"MHASH_RIPEMD160"  => "e4d5db469af29f78e2b90dc735c9cf020a1d5b19a6674458677794d4dca144d426c562aff98d8e866a8a924299ebf6b0ea9a1637f987a1fb5de9b647edc35b1447605e1babc3084be7a003931117eb33432d4142e225df044b033f3ff64bb4a18682a4f9",
"MHASH_GOST"       => "c044f669bd7e8643953d77c682fd179242d9df157dadf873be4d9601e4647c018234689359e7220ab0492a6240d184c478634073dea87f79be7f86fd4e2564f7d709b68a46440a121250e00fc7d57d45a9c07ee23a704ff4148c0dad7077ec527b194d87",
"MHASH_TIGER"      => "470aca9d7bc9ea67e46402332f26f6b15532fe6037231cce297912d32f5142f6276b2358e7f1ccba8b116ec0c0c2a46845f7a5042f0ee41906c0db9ba9b80f82181720314d2a70981bba79da4bc9c4564d95f8d709d5604fd48d369797a218a862196f48",
"MHASH_CRC32"      => "481c40148c26185f9a59ef18e86f51c5d2d0315b46711d22ae08c1ccdd669fe956c817380815e3a545f6ee453c9da48d1d994dbc3ac8ba85a572108412f06b2a16b1489cda75b118e82f7d9bdfdb68336957bbf19e4a3f76750d6985a53dd557229dfcf3",
"MHASH_CRC32B"     => "65ab6cb5fb7d3ea67f5da92a9bd746b6628a13368fcbcd43af49092e9c6a960fd030a5ce3c1f0ddb512ec698be96e77969748db66278b0fd837d24d8c898f50bd70993b48cc8accf4b44c54431e91385ddf04c7560a1a7368fc9e6f763457c90b07f04f1"
);

foreach ($supported_hash_al as $hash=>$wanted) {
    $passwd = str_repeat($hash, 10);
    $salt = str_repeat($hash, 2);
    $result = mhash_keygen_s2k(constant($hash), $passwd, $salt, 100);
    if (!strcmp(bin2hex($result), $wanted)) {
        echo "$hash\nok\n";
    } else {
        echo "$hash: ";
        var_dump($wanted);
        echo "$hash: ";
        var_dump(bin2hex($result));
    }
    echo "\n";
}
?>
--EXPECTF--
Deprecated: Constant MHASH_MD5 is deprecated in %s on line %d

Deprecated: Function mhash_keygen_s2k() is deprecated since 8.1 in %s on line %d
MHASH_MD5
ok


Deprecated: Constant MHASH_SHA1 is deprecated in %s on line %d

Deprecated: Function mhash_keygen_s2k() is deprecated since 8.1 in %s on line %d
MHASH_SHA1
ok


Deprecated: Constant MHASH_HAVAL256 is deprecated in %s on line %d

Deprecated: Function mhash_keygen_s2k() is deprecated since 8.1 in %s on line %d
MHASH_HAVAL256
ok


Deprecated: Constant MHASH_HAVAL224 is deprecated in %s on line %d

Deprecated: Function mhash_keygen_s2k() is deprecated since 8.1 in %s on line %d
MHASH_HAVAL224
ok


Deprecated: Constant MHASH_HAVAL192 is deprecated in %s on line %d

Deprecated: Function mhash_keygen_s2k() is deprecated since 8.1 in %s on line %d
MHASH_HAVAL192
ok


Deprecated: Constant MHASH_HAVAL160 is deprecated in %s on line %d

Deprecated: Function mhash_keygen_s2k() is deprecated since 8.1 in %s on line %d
MHASH_HAVAL160
ok


Deprecated: Constant MHASH_RIPEMD160 is deprecated in %s on line %d

Deprecated: Function mhash_keygen_s2k() is deprecated since 8.1 in %s on line %d
MHASH_RIPEMD160
ok


Deprecated: Constant MHASH_GOST is deprecated in %s on line %d

Deprecated: Function mhash_keygen_s2k() is deprecated since 8.1 in %s on line %d
MHASH_GOST
ok


Deprecated: Constant MHASH_TIGER is deprecated in %s on line %d

Deprecated: Function mhash_keygen_s2k() is deprecated since 8.1 in %s on line %d
MHASH_TIGER
ok


Deprecated: Constant MHASH_CRC32 is deprecated in %s on line %d

Deprecated: Function mhash_keygen_s2k() is deprecated since 8.1 in %s on line %d
MHASH_CRC32
ok


Deprecated: Constant MHASH_CRC32B is deprecated in %s on line %d

Deprecated: Function mhash_keygen_s2k() is deprecated since 8.1 in %s on line %d
MHASH_CRC32B
ok
