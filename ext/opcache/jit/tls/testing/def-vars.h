/* Declare a few additional TLS variables to fill any surplus space,
 * so _tsrm_ls_cache is allocated in the dynamic section. */

#define DEF_VAR(prefix, num) __thread void* prefix##num
#define DEF_VARS(prefix) \
	DEF_VAR(prefix, 0000); \
	DEF_VAR(prefix, 0001); \
	DEF_VAR(prefix, 0002); \
	DEF_VAR(prefix, 0003); \
	DEF_VAR(prefix, 0004); \
	DEF_VAR(prefix, 0005); \
	DEF_VAR(prefix, 0006); \
	DEF_VAR(prefix, 0007); \
	DEF_VAR(prefix, 0008); \
	DEF_VAR(prefix, 0009); \
	DEF_VAR(prefix, 0010); \
	DEF_VAR(prefix, 0011); \
	DEF_VAR(prefix, 0012); \
	DEF_VAR(prefix, 0013); \
	DEF_VAR(prefix, 0014); \
	DEF_VAR(prefix, 0015); \
	DEF_VAR(prefix, 0016); \
	DEF_VAR(prefix, 0017); \
	DEF_VAR(prefix, 0018); \
	DEF_VAR(prefix, 0019); \
	DEF_VAR(prefix, 0020); \
	DEF_VAR(prefix, 0021); \
	DEF_VAR(prefix, 0022); \
	DEF_VAR(prefix, 0023); \
	DEF_VAR(prefix, 0024); \
	DEF_VAR(prefix, 0025); \
	DEF_VAR(prefix, 0026); \
	DEF_VAR(prefix, 0027); \
	DEF_VAR(prefix, 0028); \
	DEF_VAR(prefix, 0029); \
	DEF_VAR(prefix, 0030); \
	DEF_VAR(prefix, 0031); \
	DEF_VAR(prefix, 0032); \
	DEF_VAR(prefix, 0033); \
	DEF_VAR(prefix, 0034); \
	DEF_VAR(prefix, 0035); \
	DEF_VAR(prefix, 0036); \
	DEF_VAR(prefix, 0037); \
	DEF_VAR(prefix, 0038); \
	DEF_VAR(prefix, 0039); \
	DEF_VAR(prefix, 0040); \
	DEF_VAR(prefix, 0041); \
	DEF_VAR(prefix, 0042); \
	DEF_VAR(prefix, 0043); \
	DEF_VAR(prefix, 0044); \
	DEF_VAR(prefix, 0045); \
	DEF_VAR(prefix, 0046); \
	DEF_VAR(prefix, 0047); \
	DEF_VAR(prefix, 0048); \
	DEF_VAR(prefix, 0049); \
	DEF_VAR(prefix, 0050); \
	DEF_VAR(prefix, 0051); \
	DEF_VAR(prefix, 0052); \
	DEF_VAR(prefix, 0053); \
	DEF_VAR(prefix, 0054); \
	DEF_VAR(prefix, 0055); \
	DEF_VAR(prefix, 0056); \
	DEF_VAR(prefix, 0057); \
	DEF_VAR(prefix, 0058); \
	DEF_VAR(prefix, 0059); \
	DEF_VAR(prefix, 0060); \
	DEF_VAR(prefix, 0061); \
	DEF_VAR(prefix, 0062); \
	DEF_VAR(prefix, 0063); \
	DEF_VAR(prefix, 0064); \
	DEF_VAR(prefix, 0065); \
	DEF_VAR(prefix, 0066); \
	DEF_VAR(prefix, 0067); \
	DEF_VAR(prefix, 0068); \
	DEF_VAR(prefix, 0069); \
	DEF_VAR(prefix, 0070); \
	DEF_VAR(prefix, 0071); \
	DEF_VAR(prefix, 0072); \
	DEF_VAR(prefix, 0073); \
	DEF_VAR(prefix, 0074); \
	DEF_VAR(prefix, 0075); \
	DEF_VAR(prefix, 0076); \
	DEF_VAR(prefix, 0077); \
	DEF_VAR(prefix, 0078); \
	DEF_VAR(prefix, 0079); \
	DEF_VAR(prefix, 0080); \
	DEF_VAR(prefix, 0081); \
	DEF_VAR(prefix, 0082); \
	DEF_VAR(prefix, 0083); \
	DEF_VAR(prefix, 0084); \
	DEF_VAR(prefix, 0085); \
	DEF_VAR(prefix, 0086); \
	DEF_VAR(prefix, 0087); \
	DEF_VAR(prefix, 0088); \
	DEF_VAR(prefix, 0089); \
	DEF_VAR(prefix, 0090); \
	DEF_VAR(prefix, 0091); \
	DEF_VAR(prefix, 0092); \
	DEF_VAR(prefix, 0093); \
	DEF_VAR(prefix, 0094); \
	DEF_VAR(prefix, 0095); \
	DEF_VAR(prefix, 0096); \
	DEF_VAR(prefix, 0097); \
	DEF_VAR(prefix, 0098); \
	DEF_VAR(prefix, 0099); \
	DEF_VAR(prefix, 0100); \
	DEF_VAR(prefix, 0101); \
	DEF_VAR(prefix, 0102); \
	DEF_VAR(prefix, 0103); \
	DEF_VAR(prefix, 0104); \
	DEF_VAR(prefix, 0105); \
	DEF_VAR(prefix, 0106); \
	DEF_VAR(prefix, 0107); \
	DEF_VAR(prefix, 0108); \
	DEF_VAR(prefix, 0109); \
	DEF_VAR(prefix, 0110); \
	DEF_VAR(prefix, 0111); \
	DEF_VAR(prefix, 0112); \
	DEF_VAR(prefix, 0113); \
	DEF_VAR(prefix, 0114); \
	DEF_VAR(prefix, 0115); \
	DEF_VAR(prefix, 0116); \
	DEF_VAR(prefix, 0117); \
	DEF_VAR(prefix, 0118); \
	DEF_VAR(prefix, 0119); \
	DEF_VAR(prefix, 0120); \
	DEF_VAR(prefix, 0121); \
	DEF_VAR(prefix, 0122); \
	DEF_VAR(prefix, 0123); \
	DEF_VAR(prefix, 0124); \
	DEF_VAR(prefix, 0125); \
	DEF_VAR(prefix, 0126); \
	DEF_VAR(prefix, 0127); \
	DEF_VAR(prefix, 0128); \
	DEF_VAR(prefix, 0129); \
	DEF_VAR(prefix, 0130); \
	DEF_VAR(prefix, 0131); \
	DEF_VAR(prefix, 0132); \
	DEF_VAR(prefix, 0133); \
	DEF_VAR(prefix, 0134); \
	DEF_VAR(prefix, 0135); \
	DEF_VAR(prefix, 0136); \
	DEF_VAR(prefix, 0137); \
	DEF_VAR(prefix, 0138); \
	DEF_VAR(prefix, 0139); \
	DEF_VAR(prefix, 0140); \
	DEF_VAR(prefix, 0141); \
	DEF_VAR(prefix, 0142); \
	DEF_VAR(prefix, 0143); \
	DEF_VAR(prefix, 0144); \
	DEF_VAR(prefix, 0145); \
	DEF_VAR(prefix, 0146); \
	DEF_VAR(prefix, 0147); \
	DEF_VAR(prefix, 0148); \
	DEF_VAR(prefix, 0149); \
	DEF_VAR(prefix, 0150); \
	DEF_VAR(prefix, 0151); \
	DEF_VAR(prefix, 0152); \
	DEF_VAR(prefix, 0153); \
	DEF_VAR(prefix, 0154); \
	DEF_VAR(prefix, 0155); \
	DEF_VAR(prefix, 0156); \
	DEF_VAR(prefix, 0157); \
	DEF_VAR(prefix, 0158); \
	DEF_VAR(prefix, 0159); \
	DEF_VAR(prefix, 0160); \
	DEF_VAR(prefix, 0161); \
	DEF_VAR(prefix, 0162); \
	DEF_VAR(prefix, 0163); \
	DEF_VAR(prefix, 0164); \
	DEF_VAR(prefix, 0165); \
	DEF_VAR(prefix, 0166); \
	DEF_VAR(prefix, 0167); \
	DEF_VAR(prefix, 0168); \
	DEF_VAR(prefix, 0169); \
	DEF_VAR(prefix, 0170); \
	DEF_VAR(prefix, 0171); \
	DEF_VAR(prefix, 0172); \
	DEF_VAR(prefix, 0173); \
	DEF_VAR(prefix, 0174); \
	DEF_VAR(prefix, 0175); \
	DEF_VAR(prefix, 0176); \
	DEF_VAR(prefix, 0177); \
	DEF_VAR(prefix, 0178); \
	DEF_VAR(prefix, 0179); \
	DEF_VAR(prefix, 0180); \
	DEF_VAR(prefix, 0181); \
	DEF_VAR(prefix, 0182); \
	DEF_VAR(prefix, 0183); \
	DEF_VAR(prefix, 0184); \
	DEF_VAR(prefix, 0185); \
	DEF_VAR(prefix, 0186); \
	DEF_VAR(prefix, 0187); \
	DEF_VAR(prefix, 0188); \
	DEF_VAR(prefix, 0189); \
	DEF_VAR(prefix, 0190); \
	DEF_VAR(prefix, 0191); \
	DEF_VAR(prefix, 0192); \
	DEF_VAR(prefix, 0193); \
	DEF_VAR(prefix, 0194); \
	DEF_VAR(prefix, 0195); \
	DEF_VAR(prefix, 0196); \
	DEF_VAR(prefix, 0197); \
	DEF_VAR(prefix, 0198); \
	DEF_VAR(prefix, 0199); \
	DEF_VAR(prefix, 0200); \
	DEF_VAR(prefix, 0201); \
	DEF_VAR(prefix, 0202); \
	DEF_VAR(prefix, 0203); \
	DEF_VAR(prefix, 0204); \
	DEF_VAR(prefix, 0205); \
	DEF_VAR(prefix, 0206); \
	DEF_VAR(prefix, 0207); \
	DEF_VAR(prefix, 0208); \
	DEF_VAR(prefix, 0209); \
	DEF_VAR(prefix, 0210); \
	DEF_VAR(prefix, 0211); \
	DEF_VAR(prefix, 0212); \
	DEF_VAR(prefix, 0213); \
	DEF_VAR(prefix, 0214); \
	DEF_VAR(prefix, 0215); \
	DEF_VAR(prefix, 0216); \
	DEF_VAR(prefix, 0217); \
	DEF_VAR(prefix, 0218); \
	DEF_VAR(prefix, 0219); \
	DEF_VAR(prefix, 0220); \
	DEF_VAR(prefix, 0221); \
	DEF_VAR(prefix, 0222); \
	DEF_VAR(prefix, 0223); \
	DEF_VAR(prefix, 0224); \
	DEF_VAR(prefix, 0225); \
	DEF_VAR(prefix, 0226); \
	DEF_VAR(prefix, 0227); \
	DEF_VAR(prefix, 0228); \
	DEF_VAR(prefix, 0229); \
	DEF_VAR(prefix, 0230); \
	DEF_VAR(prefix, 0231); \
	DEF_VAR(prefix, 0232); \
	DEF_VAR(prefix, 0233); \
	DEF_VAR(prefix, 0234); \
	DEF_VAR(prefix, 0235); \
	DEF_VAR(prefix, 0236); \
	DEF_VAR(prefix, 0237); \
	DEF_VAR(prefix, 0238); \
	DEF_VAR(prefix, 0239); \
	DEF_VAR(prefix, 0240); \
	DEF_VAR(prefix, 0241); \
	DEF_VAR(prefix, 0242); \
	DEF_VAR(prefix, 0243); \
	DEF_VAR(prefix, 0244); \
	DEF_VAR(prefix, 0245); \
	DEF_VAR(prefix, 0246); \
	DEF_VAR(prefix, 0247); \
	DEF_VAR(prefix, 0248); \
	DEF_VAR(prefix, 0249); \
	DEF_VAR(prefix, 0250); \
	DEF_VAR(prefix, 0251); \
	DEF_VAR(prefix, 0252); \
	DEF_VAR(prefix, 0253); \
	DEF_VAR(prefix, 0254); \
	DEF_VAR(prefix, 0255); \
	DEF_VAR(prefix, 0256); \
	DEF_VAR(prefix, 0257); \
	DEF_VAR(prefix, 0258); \
	DEF_VAR(prefix, 0259); \
	DEF_VAR(prefix, 0260); \
	DEF_VAR(prefix, 0261); \
	DEF_VAR(prefix, 0262); \
	DEF_VAR(prefix, 0263); \
	DEF_VAR(prefix, 0264); \
	DEF_VAR(prefix, 0265); \
	DEF_VAR(prefix, 0266); \
	DEF_VAR(prefix, 0267); \
	DEF_VAR(prefix, 0268); \
	DEF_VAR(prefix, 0269); \
	DEF_VAR(prefix, 0270); \
	DEF_VAR(prefix, 0271); \
	DEF_VAR(prefix, 0272); \
	DEF_VAR(prefix, 0273); \
	DEF_VAR(prefix, 0274); \
	DEF_VAR(prefix, 0275); \
	DEF_VAR(prefix, 0276); \
	DEF_VAR(prefix, 0277); \
	DEF_VAR(prefix, 0278); \
	DEF_VAR(prefix, 0279); \
	DEF_VAR(prefix, 0280); \
	DEF_VAR(prefix, 0281); \
	DEF_VAR(prefix, 0282); \
	DEF_VAR(prefix, 0283); \
	DEF_VAR(prefix, 0284); \
	DEF_VAR(prefix, 0285); \
	DEF_VAR(prefix, 0286); \
	DEF_VAR(prefix, 0287); \
	DEF_VAR(prefix, 0288); \
	DEF_VAR(prefix, 0289); \
	DEF_VAR(prefix, 0290); \
	DEF_VAR(prefix, 0291); \
	DEF_VAR(prefix, 0292); \
	DEF_VAR(prefix, 0293); \
	DEF_VAR(prefix, 0294); \
	DEF_VAR(prefix, 0295); \
	DEF_VAR(prefix, 0296); \
	DEF_VAR(prefix, 0297); \
	DEF_VAR(prefix, 0298); \
	DEF_VAR(prefix, 0299); \
	DEF_VAR(prefix, 0300); \
	DEF_VAR(prefix, 0301); \
	DEF_VAR(prefix, 0302); \
	DEF_VAR(prefix, 0303); \
	DEF_VAR(prefix, 0304); \
	DEF_VAR(prefix, 0305); \
	DEF_VAR(prefix, 0306); \
	DEF_VAR(prefix, 0307); \
	DEF_VAR(prefix, 0308); \
	DEF_VAR(prefix, 0309); \
	DEF_VAR(prefix, 0310); \
	DEF_VAR(prefix, 0311); \
	DEF_VAR(prefix, 0312); \
	DEF_VAR(prefix, 0313); \
	DEF_VAR(prefix, 0314); \
	DEF_VAR(prefix, 0315); \
	DEF_VAR(prefix, 0316); \
	DEF_VAR(prefix, 0317); \
	DEF_VAR(prefix, 0318); \
	DEF_VAR(prefix, 0319); \
	DEF_VAR(prefix, 0320); \
	DEF_VAR(prefix, 0321); \
	DEF_VAR(prefix, 0322); \
	DEF_VAR(prefix, 0323); \
	DEF_VAR(prefix, 0324); \
	DEF_VAR(prefix, 0325); \
	DEF_VAR(prefix, 0326); \
	DEF_VAR(prefix, 0327); \
	DEF_VAR(prefix, 0328); \
	DEF_VAR(prefix, 0329); \
	DEF_VAR(prefix, 0330); \
	DEF_VAR(prefix, 0331); \
	DEF_VAR(prefix, 0332); \
	DEF_VAR(prefix, 0333); \
	DEF_VAR(prefix, 0334); \
	DEF_VAR(prefix, 0335); \
	DEF_VAR(prefix, 0336); \
	DEF_VAR(prefix, 0337); \
	DEF_VAR(prefix, 0338); \
	DEF_VAR(prefix, 0339); \
	DEF_VAR(prefix, 0340); \
	DEF_VAR(prefix, 0341); \
	DEF_VAR(prefix, 0342); \
	DEF_VAR(prefix, 0343); \
	DEF_VAR(prefix, 0344); \
	DEF_VAR(prefix, 0345); \
	DEF_VAR(prefix, 0346); \
	DEF_VAR(prefix, 0347); \
	DEF_VAR(prefix, 0348); \
	DEF_VAR(prefix, 0349); \
	DEF_VAR(prefix, 0350); \
	DEF_VAR(prefix, 0351); \
	DEF_VAR(prefix, 0352); \
	DEF_VAR(prefix, 0353); \
	DEF_VAR(prefix, 0354); \
	DEF_VAR(prefix, 0355); \
	DEF_VAR(prefix, 0356); \
	DEF_VAR(prefix, 0357); \
	DEF_VAR(prefix, 0358); \
	DEF_VAR(prefix, 0359); \
	DEF_VAR(prefix, 0360); \
	DEF_VAR(prefix, 0361); \
	DEF_VAR(prefix, 0362); \
	DEF_VAR(prefix, 0363); \
	DEF_VAR(prefix, 0364); \
	DEF_VAR(prefix, 0365); \
	DEF_VAR(prefix, 0366); \
	DEF_VAR(prefix, 0367); \
	DEF_VAR(prefix, 0368); \
	DEF_VAR(prefix, 0369); \
	DEF_VAR(prefix, 0370); \
	DEF_VAR(prefix, 0371); \
	DEF_VAR(prefix, 0372); \
	DEF_VAR(prefix, 0373); \
	DEF_VAR(prefix, 0374); \
	DEF_VAR(prefix, 0375); \
	DEF_VAR(prefix, 0376); \
	DEF_VAR(prefix, 0377); \
	DEF_VAR(prefix, 0378); \
	DEF_VAR(prefix, 0379); \
	DEF_VAR(prefix, 0380); \
	DEF_VAR(prefix, 0381); \
	DEF_VAR(prefix, 0382); \
	DEF_VAR(prefix, 0383); \
	DEF_VAR(prefix, 0384); \
	DEF_VAR(prefix, 0385); \
	DEF_VAR(prefix, 0386); \
	DEF_VAR(prefix, 0387); \
	DEF_VAR(prefix, 0388); \
	DEF_VAR(prefix, 0389); \
	DEF_VAR(prefix, 0390); \
	DEF_VAR(prefix, 0391); \
	DEF_VAR(prefix, 0392); \
	DEF_VAR(prefix, 0393); \
	DEF_VAR(prefix, 0394); \
	DEF_VAR(prefix, 0395); \
	DEF_VAR(prefix, 0396); \
	DEF_VAR(prefix, 0397); \
	DEF_VAR(prefix, 0398); \
	DEF_VAR(prefix, 0399); \
	DEF_VAR(prefix, 0400); \
	DEF_VAR(prefix, 0401); \
	DEF_VAR(prefix, 0402); \
	DEF_VAR(prefix, 0403); \
	DEF_VAR(prefix, 0404); \
	DEF_VAR(prefix, 0405); \
	DEF_VAR(prefix, 0406); \
	DEF_VAR(prefix, 0407); \
	DEF_VAR(prefix, 0408); \
	DEF_VAR(prefix, 0409); \
	DEF_VAR(prefix, 0410); \
	DEF_VAR(prefix, 0411); \
	DEF_VAR(prefix, 0412); \
	DEF_VAR(prefix, 0413); \
	DEF_VAR(prefix, 0414); \
	DEF_VAR(prefix, 0415); \
	DEF_VAR(prefix, 0416); \
	DEF_VAR(prefix, 0417); \
	DEF_VAR(prefix, 0418); \
	DEF_VAR(prefix, 0419); \
	DEF_VAR(prefix, 0420); \
	DEF_VAR(prefix, 0421); \
	DEF_VAR(prefix, 0422); \
	DEF_VAR(prefix, 0423); \
	DEF_VAR(prefix, 0424); \
	DEF_VAR(prefix, 0425); \
	DEF_VAR(prefix, 0426); \
	DEF_VAR(prefix, 0427); \
	DEF_VAR(prefix, 0428); \
	DEF_VAR(prefix, 0429); \
	DEF_VAR(prefix, 0430); \
	DEF_VAR(prefix, 0431); \
	DEF_VAR(prefix, 0432); \
	DEF_VAR(prefix, 0433); \
	DEF_VAR(prefix, 0434); \
	DEF_VAR(prefix, 0435); \
	DEF_VAR(prefix, 0436); \
	DEF_VAR(prefix, 0437); \
	DEF_VAR(prefix, 0438); \
	DEF_VAR(prefix, 0439); \
	DEF_VAR(prefix, 0440); \
	DEF_VAR(prefix, 0441); \
	DEF_VAR(prefix, 0442); \
	DEF_VAR(prefix, 0443); \
	DEF_VAR(prefix, 0444); \
	DEF_VAR(prefix, 0445); \
	DEF_VAR(prefix, 0446); \
	DEF_VAR(prefix, 0447); \
	DEF_VAR(prefix, 0448); \
	DEF_VAR(prefix, 0449); \
	DEF_VAR(prefix, 0450); \
	DEF_VAR(prefix, 0451); \
	DEF_VAR(prefix, 0452); \
	DEF_VAR(prefix, 0453); \
	DEF_VAR(prefix, 0454); \
	DEF_VAR(prefix, 0455); \
	DEF_VAR(prefix, 0456); \
	DEF_VAR(prefix, 0457); \
	DEF_VAR(prefix, 0458); \
	DEF_VAR(prefix, 0459); \
	DEF_VAR(prefix, 0460); \
	DEF_VAR(prefix, 0461); \
	DEF_VAR(prefix, 0462); \
	DEF_VAR(prefix, 0463); \
	DEF_VAR(prefix, 0464); \
	DEF_VAR(prefix, 0465); \
	DEF_VAR(prefix, 0466); \
	DEF_VAR(prefix, 0467); \
	DEF_VAR(prefix, 0468); \
	DEF_VAR(prefix, 0469); \
	DEF_VAR(prefix, 0470); \
	DEF_VAR(prefix, 0471); \
	DEF_VAR(prefix, 0472); \
	DEF_VAR(prefix, 0473); \
	DEF_VAR(prefix, 0474); \
	DEF_VAR(prefix, 0475); \
	DEF_VAR(prefix, 0476); \
	DEF_VAR(prefix, 0477); \
	DEF_VAR(prefix, 0478); \
	DEF_VAR(prefix, 0479); \
	DEF_VAR(prefix, 0480); \
	DEF_VAR(prefix, 0481); \
	DEF_VAR(prefix, 0482); \
	DEF_VAR(prefix, 0483); \
	DEF_VAR(prefix, 0484); \
	DEF_VAR(prefix, 0485); \
	DEF_VAR(prefix, 0486); \
	DEF_VAR(prefix, 0487); \
	DEF_VAR(prefix, 0488); \
	DEF_VAR(prefix, 0489); \
	DEF_VAR(prefix, 0490); \
	DEF_VAR(prefix, 0491); \
	DEF_VAR(prefix, 0492); \
	DEF_VAR(prefix, 0493); \
	DEF_VAR(prefix, 0494); \
	DEF_VAR(prefix, 0495); \
	DEF_VAR(prefix, 0496); \
	DEF_VAR(prefix, 0497); \
	DEF_VAR(prefix, 0498); \
	DEF_VAR(prefix, 0499); \
	DEF_VAR(prefix, 0500); \
	DEF_VAR(prefix, 0501); \
	DEF_VAR(prefix, 0502); \
	DEF_VAR(prefix, 0503); \
	DEF_VAR(prefix, 0504); \
	DEF_VAR(prefix, 0505); \
	DEF_VAR(prefix, 0506); \
	DEF_VAR(prefix, 0507); \
	DEF_VAR(prefix, 0508); \
	DEF_VAR(prefix, 0509); \
	DEF_VAR(prefix, 0510); \
	DEF_VAR(prefix, 0511); \
	DEF_VAR(prefix, 0512); \
	DEF_VAR(prefix, 0513); \
	DEF_VAR(prefix, 0514); \
	DEF_VAR(prefix, 0515); \
	DEF_VAR(prefix, 0516); \
	DEF_VAR(prefix, 0517); \
	DEF_VAR(prefix, 0518); \
	DEF_VAR(prefix, 0519); \
	DEF_VAR(prefix, 0520); \
	DEF_VAR(prefix, 0521); \
	DEF_VAR(prefix, 0522); \
	DEF_VAR(prefix, 0523); \
	DEF_VAR(prefix, 0524); \
	DEF_VAR(prefix, 0525); \
	DEF_VAR(prefix, 0526); \
	DEF_VAR(prefix, 0527); \
	DEF_VAR(prefix, 0528); \
	DEF_VAR(prefix, 0529); \
	DEF_VAR(prefix, 0530); \
	DEF_VAR(prefix, 0531); \
	DEF_VAR(prefix, 0532); \
	DEF_VAR(prefix, 0533); \
	DEF_VAR(prefix, 0534); \
	DEF_VAR(prefix, 0535); \
	DEF_VAR(prefix, 0536); \
	DEF_VAR(prefix, 0537); \
	DEF_VAR(prefix, 0538); \
	DEF_VAR(prefix, 0539); \
	DEF_VAR(prefix, 0540); \
	DEF_VAR(prefix, 0541); \
	DEF_VAR(prefix, 0542); \
	DEF_VAR(prefix, 0543); \
	DEF_VAR(prefix, 0544); \
	DEF_VAR(prefix, 0545); \
	DEF_VAR(prefix, 0546); \
	DEF_VAR(prefix, 0547); \
	DEF_VAR(prefix, 0548); \
	DEF_VAR(prefix, 0549); \
	DEF_VAR(prefix, 0550); \
	DEF_VAR(prefix, 0551); \
	DEF_VAR(prefix, 0552); \
	DEF_VAR(prefix, 0553); \
	DEF_VAR(prefix, 0554); \
	DEF_VAR(prefix, 0555); \
	DEF_VAR(prefix, 0556); \
	DEF_VAR(prefix, 0557); \
	DEF_VAR(prefix, 0558); \
	DEF_VAR(prefix, 0559); \
	DEF_VAR(prefix, 0560); \
	DEF_VAR(prefix, 0561); \
	DEF_VAR(prefix, 0562); \
	DEF_VAR(prefix, 0563); \
	DEF_VAR(prefix, 0564); \
	DEF_VAR(prefix, 0565); \
	DEF_VAR(prefix, 0566); \
	DEF_VAR(prefix, 0567); \
	DEF_VAR(prefix, 0568); \
	DEF_VAR(prefix, 0569); \
	DEF_VAR(prefix, 0570); \
	DEF_VAR(prefix, 0571); \
	DEF_VAR(prefix, 0572); \
	DEF_VAR(prefix, 0573); \
	DEF_VAR(prefix, 0574); \
	DEF_VAR(prefix, 0575); \
	DEF_VAR(prefix, 0576); \
	DEF_VAR(prefix, 0577); \
	DEF_VAR(prefix, 0578); \
	DEF_VAR(prefix, 0579); \
	DEF_VAR(prefix, 0580); \
	DEF_VAR(prefix, 0581); \
	DEF_VAR(prefix, 0582); \
	DEF_VAR(prefix, 0583); \
	DEF_VAR(prefix, 0584); \
	DEF_VAR(prefix, 0585); \
	DEF_VAR(prefix, 0586); \
	DEF_VAR(prefix, 0587); \
	DEF_VAR(prefix, 0588); \
	DEF_VAR(prefix, 0589); \
	DEF_VAR(prefix, 0590); \
	DEF_VAR(prefix, 0591); \
	DEF_VAR(prefix, 0592); \
	DEF_VAR(prefix, 0593); \
	DEF_VAR(prefix, 0594); \
	DEF_VAR(prefix, 0595); \
	DEF_VAR(prefix, 0596); \
	DEF_VAR(prefix, 0597); \
	DEF_VAR(prefix, 0598); \
	DEF_VAR(prefix, 0599); \
	DEF_VAR(prefix, 0600); \
	DEF_VAR(prefix, 0601); \
	DEF_VAR(prefix, 0602); \
	DEF_VAR(prefix, 0603); \
	DEF_VAR(prefix, 0604); \
	DEF_VAR(prefix, 0605); \
	DEF_VAR(prefix, 0606); \
	DEF_VAR(prefix, 0607); \
	DEF_VAR(prefix, 0608); \
	DEF_VAR(prefix, 0609); \
	DEF_VAR(prefix, 0610); \
	DEF_VAR(prefix, 0611); \
	DEF_VAR(prefix, 0612); \
	DEF_VAR(prefix, 0613); \
	DEF_VAR(prefix, 0614); \
	DEF_VAR(prefix, 0615); \
	DEF_VAR(prefix, 0616); \
	DEF_VAR(prefix, 0617); \
	DEF_VAR(prefix, 0618); \
	DEF_VAR(prefix, 0619); \
	DEF_VAR(prefix, 0620); \
	DEF_VAR(prefix, 0621); \
	DEF_VAR(prefix, 0622); \
	DEF_VAR(prefix, 0623); \
	DEF_VAR(prefix, 0624); \
	DEF_VAR(prefix, 0625); \
	DEF_VAR(prefix, 0626); \
	DEF_VAR(prefix, 0627); \
	DEF_VAR(prefix, 0628); \
	DEF_VAR(prefix, 0629); \
	DEF_VAR(prefix, 0630); \
	DEF_VAR(prefix, 0631); \
	DEF_VAR(prefix, 0632); \
	DEF_VAR(prefix, 0633); \
	DEF_VAR(prefix, 0634); \
	DEF_VAR(prefix, 0635); \
	DEF_VAR(prefix, 0636); \
	DEF_VAR(prefix, 0637); \
	DEF_VAR(prefix, 0638); \
	DEF_VAR(prefix, 0639); \
	DEF_VAR(prefix, 0640); \
	DEF_VAR(prefix, 0641); \
	DEF_VAR(prefix, 0642); \
	DEF_VAR(prefix, 0643); \
	DEF_VAR(prefix, 0644); \
	DEF_VAR(prefix, 0645); \
	DEF_VAR(prefix, 0646); \
	DEF_VAR(prefix, 0647); \
	DEF_VAR(prefix, 0648); \
	DEF_VAR(prefix, 0649); \
	DEF_VAR(prefix, 0650); \
	DEF_VAR(prefix, 0651); \
	DEF_VAR(prefix, 0652); \
	DEF_VAR(prefix, 0653); \
	DEF_VAR(prefix, 0654); \
	DEF_VAR(prefix, 0655); \
	DEF_VAR(prefix, 0656); \
	DEF_VAR(prefix, 0657); \
	DEF_VAR(prefix, 0658); \
	DEF_VAR(prefix, 0659); \
	DEF_VAR(prefix, 0660); \
	DEF_VAR(prefix, 0661); \
	DEF_VAR(prefix, 0662); \
	DEF_VAR(prefix, 0663); \
	DEF_VAR(prefix, 0664); \
	DEF_VAR(prefix, 0665); \
	DEF_VAR(prefix, 0666); \
	DEF_VAR(prefix, 0667); \
	DEF_VAR(prefix, 0668); \
	DEF_VAR(prefix, 0669); \
	DEF_VAR(prefix, 0670); \
	DEF_VAR(prefix, 0671); \
	DEF_VAR(prefix, 0672); \
	DEF_VAR(prefix, 0673); \
	DEF_VAR(prefix, 0674); \
	DEF_VAR(prefix, 0675); \
	DEF_VAR(prefix, 0676); \
	DEF_VAR(prefix, 0677); \
	DEF_VAR(prefix, 0678); \
	DEF_VAR(prefix, 0679); \
	DEF_VAR(prefix, 0680); \
	DEF_VAR(prefix, 0681); \
	DEF_VAR(prefix, 0682); \
	DEF_VAR(prefix, 0683); \
	DEF_VAR(prefix, 0684); \
	DEF_VAR(prefix, 0685); \
	DEF_VAR(prefix, 0686); \
	DEF_VAR(prefix, 0687); \
	DEF_VAR(prefix, 0688); \
	DEF_VAR(prefix, 0689); \
	DEF_VAR(prefix, 0690); \
	DEF_VAR(prefix, 0691); \
	DEF_VAR(prefix, 0692); \
	DEF_VAR(prefix, 0693); \
	DEF_VAR(prefix, 0694); \
	DEF_VAR(prefix, 0695); \
	DEF_VAR(prefix, 0696); \
	DEF_VAR(prefix, 0697); \
	DEF_VAR(prefix, 0698); \
	DEF_VAR(prefix, 0699); \
	DEF_VAR(prefix, 0700); \
	DEF_VAR(prefix, 0701); \
	DEF_VAR(prefix, 0702); \
	DEF_VAR(prefix, 0703); \
	DEF_VAR(prefix, 0704); \
	DEF_VAR(prefix, 0705); \
	DEF_VAR(prefix, 0706); \
	DEF_VAR(prefix, 0707); \
	DEF_VAR(prefix, 0708); \
	DEF_VAR(prefix, 0709); \
	DEF_VAR(prefix, 0710); \
	DEF_VAR(prefix, 0711); \
	DEF_VAR(prefix, 0712); \
	DEF_VAR(prefix, 0713); \
	DEF_VAR(prefix, 0714); \
	DEF_VAR(prefix, 0715); \
	DEF_VAR(prefix, 0716); \
	DEF_VAR(prefix, 0717); \
	DEF_VAR(prefix, 0718); \
	DEF_VAR(prefix, 0719); \
	DEF_VAR(prefix, 0720); \
	DEF_VAR(prefix, 0721); \
	DEF_VAR(prefix, 0722); \
	DEF_VAR(prefix, 0723); \
	DEF_VAR(prefix, 0724); \
	DEF_VAR(prefix, 0725); \
	DEF_VAR(prefix, 0726); \
	DEF_VAR(prefix, 0727); \
	DEF_VAR(prefix, 0728); \
	DEF_VAR(prefix, 0729); \
	DEF_VAR(prefix, 0730); \
	DEF_VAR(prefix, 0731); \
	DEF_VAR(prefix, 0732); \
	DEF_VAR(prefix, 0733); \
	DEF_VAR(prefix, 0734); \
	DEF_VAR(prefix, 0735); \
	DEF_VAR(prefix, 0736); \
	DEF_VAR(prefix, 0737); \
	DEF_VAR(prefix, 0738); \
	DEF_VAR(prefix, 0739); \
	DEF_VAR(prefix, 0740); \
	DEF_VAR(prefix, 0741); \
	DEF_VAR(prefix, 0742); \
	DEF_VAR(prefix, 0743); \
	DEF_VAR(prefix, 0744); \
	DEF_VAR(prefix, 0745); \
	DEF_VAR(prefix, 0746); \
	DEF_VAR(prefix, 0747); \
	DEF_VAR(prefix, 0748); \
	DEF_VAR(prefix, 0749); \
	DEF_VAR(prefix, 0750); \
	DEF_VAR(prefix, 0751); \
	DEF_VAR(prefix, 0752); \
	DEF_VAR(prefix, 0753); \
	DEF_VAR(prefix, 0754); \
	DEF_VAR(prefix, 0755); \
	DEF_VAR(prefix, 0756); \
	DEF_VAR(prefix, 0757); \
	DEF_VAR(prefix, 0758); \
	DEF_VAR(prefix, 0759); \
	DEF_VAR(prefix, 0760); \
	DEF_VAR(prefix, 0761); \
	DEF_VAR(prefix, 0762); \
	DEF_VAR(prefix, 0763); \
	DEF_VAR(prefix, 0764); \
	DEF_VAR(prefix, 0765); \
	DEF_VAR(prefix, 0766); \
	DEF_VAR(prefix, 0767); \
	DEF_VAR(prefix, 0768); \
	DEF_VAR(prefix, 0769); \
	DEF_VAR(prefix, 0770); \
	DEF_VAR(prefix, 0771); \
	DEF_VAR(prefix, 0772); \
	DEF_VAR(prefix, 0773); \
	DEF_VAR(prefix, 0774); \
	DEF_VAR(prefix, 0775); \
	DEF_VAR(prefix, 0776); \
	DEF_VAR(prefix, 0777); \
	DEF_VAR(prefix, 0778); \
	DEF_VAR(prefix, 0779); \
	DEF_VAR(prefix, 0780); \
	DEF_VAR(prefix, 0781); \
	DEF_VAR(prefix, 0782); \
	DEF_VAR(prefix, 0783); \
	DEF_VAR(prefix, 0784); \
	DEF_VAR(prefix, 0785); \
	DEF_VAR(prefix, 0786); \
	DEF_VAR(prefix, 0787); \
	DEF_VAR(prefix, 0788); \
	DEF_VAR(prefix, 0789); \
	DEF_VAR(prefix, 0790); \
	DEF_VAR(prefix, 0791); \
	DEF_VAR(prefix, 0792); \
	DEF_VAR(prefix, 0793); \
	DEF_VAR(prefix, 0794); \
	DEF_VAR(prefix, 0795); \
	DEF_VAR(prefix, 0796); \
	DEF_VAR(prefix, 0797); \
	DEF_VAR(prefix, 0798); \
	DEF_VAR(prefix, 0799); \
	DEF_VAR(prefix, 0800); \
	DEF_VAR(prefix, 0801); \
	DEF_VAR(prefix, 0802); \
	DEF_VAR(prefix, 0803); \
	DEF_VAR(prefix, 0804); \
	DEF_VAR(prefix, 0805); \
	DEF_VAR(prefix, 0806); \
	DEF_VAR(prefix, 0807); \
	DEF_VAR(prefix, 0808); \
	DEF_VAR(prefix, 0809); \
	DEF_VAR(prefix, 0810); \
	DEF_VAR(prefix, 0811); \
	DEF_VAR(prefix, 0812); \
	DEF_VAR(prefix, 0813); \
	DEF_VAR(prefix, 0814); \
	DEF_VAR(prefix, 0815); \
	DEF_VAR(prefix, 0816); \
	DEF_VAR(prefix, 0817); \
	DEF_VAR(prefix, 0818); \
	DEF_VAR(prefix, 0819); \
	DEF_VAR(prefix, 0820); \
	DEF_VAR(prefix, 0821); \
	DEF_VAR(prefix, 0822); \
	DEF_VAR(prefix, 0823); \
	DEF_VAR(prefix, 0824); \
	DEF_VAR(prefix, 0825); \
	DEF_VAR(prefix, 0826); \
	DEF_VAR(prefix, 0827); \
	DEF_VAR(prefix, 0828); \
	DEF_VAR(prefix, 0829); \
	DEF_VAR(prefix, 0830); \
	DEF_VAR(prefix, 0831); \
	DEF_VAR(prefix, 0832); \
	DEF_VAR(prefix, 0833); \
	DEF_VAR(prefix, 0834); \
	DEF_VAR(prefix, 0835); \
	DEF_VAR(prefix, 0836); \
	DEF_VAR(prefix, 0837); \
	DEF_VAR(prefix, 0838); \
	DEF_VAR(prefix, 0839); \
	DEF_VAR(prefix, 0840); \
	DEF_VAR(prefix, 0841); \
	DEF_VAR(prefix, 0842); \
	DEF_VAR(prefix, 0843); \
	DEF_VAR(prefix, 0844); \
	DEF_VAR(prefix, 0845); \
	DEF_VAR(prefix, 0846); \
	DEF_VAR(prefix, 0847); \
	DEF_VAR(prefix, 0848); \
	DEF_VAR(prefix, 0849); \
	DEF_VAR(prefix, 0850); \
	DEF_VAR(prefix, 0851); \
	DEF_VAR(prefix, 0852); \
	DEF_VAR(prefix, 0853); \
	DEF_VAR(prefix, 0854); \
	DEF_VAR(prefix, 0855); \
	DEF_VAR(prefix, 0856); \
	DEF_VAR(prefix, 0857); \
	DEF_VAR(prefix, 0858); \
	DEF_VAR(prefix, 0859); \
	DEF_VAR(prefix, 0860); \
	DEF_VAR(prefix, 0861); \
	DEF_VAR(prefix, 0862); \
	DEF_VAR(prefix, 0863); \
	DEF_VAR(prefix, 0864); \
	DEF_VAR(prefix, 0865); \
	DEF_VAR(prefix, 0866); \
	DEF_VAR(prefix, 0867); \
	DEF_VAR(prefix, 0868); \
	DEF_VAR(prefix, 0869); \
	DEF_VAR(prefix, 0870); \
	DEF_VAR(prefix, 0871); \
	DEF_VAR(prefix, 0872); \
	DEF_VAR(prefix, 0873); \
	DEF_VAR(prefix, 0874); \
	DEF_VAR(prefix, 0875); \
	DEF_VAR(prefix, 0876); \
	DEF_VAR(prefix, 0877); \
	DEF_VAR(prefix, 0878); \
	DEF_VAR(prefix, 0879); \
	DEF_VAR(prefix, 0880); \
	DEF_VAR(prefix, 0881); \
	DEF_VAR(prefix, 0882); \
	DEF_VAR(prefix, 0883); \
	DEF_VAR(prefix, 0884); \
	DEF_VAR(prefix, 0885); \
	DEF_VAR(prefix, 0886); \
	DEF_VAR(prefix, 0887); \
	DEF_VAR(prefix, 0888); \
	DEF_VAR(prefix, 0889); \
	DEF_VAR(prefix, 0890); \
	DEF_VAR(prefix, 0891); \
	DEF_VAR(prefix, 0892); \
	DEF_VAR(prefix, 0893); \
	DEF_VAR(prefix, 0894); \
	DEF_VAR(prefix, 0895); \
	DEF_VAR(prefix, 0896); \
	DEF_VAR(prefix, 0897); \
	DEF_VAR(prefix, 0898); \
	DEF_VAR(prefix, 0899); \
	DEF_VAR(prefix, 0900); \
	DEF_VAR(prefix, 0901); \
	DEF_VAR(prefix, 0902); \
	DEF_VAR(prefix, 0903); \
	DEF_VAR(prefix, 0904); \
	DEF_VAR(prefix, 0905); \
	DEF_VAR(prefix, 0906); \
	DEF_VAR(prefix, 0907); \
	DEF_VAR(prefix, 0908); \
	DEF_VAR(prefix, 0909); \
	DEF_VAR(prefix, 0910); \
	DEF_VAR(prefix, 0911); \
	DEF_VAR(prefix, 0912); \
	DEF_VAR(prefix, 0913); \
	DEF_VAR(prefix, 0914); \
	DEF_VAR(prefix, 0915); \
	DEF_VAR(prefix, 0916); \
	DEF_VAR(prefix, 0917); \
	DEF_VAR(prefix, 0918); \
	DEF_VAR(prefix, 0919); \
	DEF_VAR(prefix, 0920); \
	DEF_VAR(prefix, 0921); \
	DEF_VAR(prefix, 0922); \
	DEF_VAR(prefix, 0923); \
	DEF_VAR(prefix, 0924); \
	DEF_VAR(prefix, 0925); \
	DEF_VAR(prefix, 0926); \
	DEF_VAR(prefix, 0927); \
	DEF_VAR(prefix, 0928); \
	DEF_VAR(prefix, 0929); \
	DEF_VAR(prefix, 0930); \
	DEF_VAR(prefix, 0931); \
	DEF_VAR(prefix, 0932); \
	DEF_VAR(prefix, 0933); \
	DEF_VAR(prefix, 0934); \
	DEF_VAR(prefix, 0935); \
	DEF_VAR(prefix, 0936); \
	DEF_VAR(prefix, 0937); \
	DEF_VAR(prefix, 0938); \
	DEF_VAR(prefix, 0939); \
	DEF_VAR(prefix, 0940); \
	DEF_VAR(prefix, 0941); \
	DEF_VAR(prefix, 0942); \
	DEF_VAR(prefix, 0943); \
	DEF_VAR(prefix, 0944); \
	DEF_VAR(prefix, 0945); \
	DEF_VAR(prefix, 0946); \
	DEF_VAR(prefix, 0947); \
	DEF_VAR(prefix, 0948); \
	DEF_VAR(prefix, 0949); \
	DEF_VAR(prefix, 0950); \
	DEF_VAR(prefix, 0951); \
	DEF_VAR(prefix, 0952); \
	DEF_VAR(prefix, 0953); \
	DEF_VAR(prefix, 0954); \
	DEF_VAR(prefix, 0955); \
	DEF_VAR(prefix, 0956); \
	DEF_VAR(prefix, 0957); \
	DEF_VAR(prefix, 0958); \
	DEF_VAR(prefix, 0959); \
	DEF_VAR(prefix, 0960); \
	DEF_VAR(prefix, 0961); \
	DEF_VAR(prefix, 0962); \
	DEF_VAR(prefix, 0963); \
	DEF_VAR(prefix, 0964); \
	DEF_VAR(prefix, 0965); \
	DEF_VAR(prefix, 0966); \
	DEF_VAR(prefix, 0967); \
	DEF_VAR(prefix, 0968); \
	DEF_VAR(prefix, 0969); \
	DEF_VAR(prefix, 0970); \
	DEF_VAR(prefix, 0971); \
	DEF_VAR(prefix, 0972); \
	DEF_VAR(prefix, 0973); \
	DEF_VAR(prefix, 0974); \
	DEF_VAR(prefix, 0975); \
	DEF_VAR(prefix, 0976); \
	DEF_VAR(prefix, 0977); \
	DEF_VAR(prefix, 0978); \
	DEF_VAR(prefix, 0979); \
	DEF_VAR(prefix, 0980); \
	DEF_VAR(prefix, 0981); \
	DEF_VAR(prefix, 0982); \
	DEF_VAR(prefix, 0983); \
	DEF_VAR(prefix, 0984); \
	DEF_VAR(prefix, 0985); \
	DEF_VAR(prefix, 0986); \
	DEF_VAR(prefix, 0987); \
	DEF_VAR(prefix, 0988); \
	DEF_VAR(prefix, 0989); \
	DEF_VAR(prefix, 0990); \
	DEF_VAR(prefix, 0991); \
	DEF_VAR(prefix, 0992); \
	DEF_VAR(prefix, 0993); \
	DEF_VAR(prefix, 0994); \
	DEF_VAR(prefix, 0995); \
	DEF_VAR(prefix, 0996); \
	DEF_VAR(prefix, 0997); \
	DEF_VAR(prefix, 0998); \
	DEF_VAR(prefix, 0999); \
	DEF_VAR(prefix, 1000); \
	DEF_VAR(prefix, 1001); \
	DEF_VAR(prefix, 1002); \
	DEF_VAR(prefix, 1003); \
	DEF_VAR(prefix, 1004); \
	DEF_VAR(prefix, 1005); \
	DEF_VAR(prefix, 1006); \
	DEF_VAR(prefix, 1007); \
	DEF_VAR(prefix, 1008); \
	DEF_VAR(prefix, 1009); \
	DEF_VAR(prefix, 1010); \
	DEF_VAR(prefix, 1011); \
	DEF_VAR(prefix, 1012); \
	DEF_VAR(prefix, 1013); \
	DEF_VAR(prefix, 1014); \
	DEF_VAR(prefix, 1015); \
	DEF_VAR(prefix, 1016); \
	DEF_VAR(prefix, 1017); \
	DEF_VAR(prefix, 1018); \
	DEF_VAR(prefix, 1019); \
	DEF_VAR(prefix, 1020); \
	DEF_VAR(prefix, 1021); \
	DEF_VAR(prefix, 1022); \
	DEF_VAR(prefix, 1023); \
	DEF_VAR(prefix, 1024);
