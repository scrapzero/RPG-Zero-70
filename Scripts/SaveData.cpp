#include "SaveData.h"





const std::string NEquipmentAmount = "eggtabetaina";//N‚Íname‚Ì—ª
const std::string NhaveEquipmentKindLevel[400][3] = { "fksflad1","fksflad2","fksflad3","fksflad4","fksflad5","fksflad6","fksflad7","fksflad8","fksflad9","fksflad10","fksflad11","fksflad12","fksflad13","fksflad14","fksflad15","fksflad16","fksflad17","fksflad18","fksflad19","fksflad20","fksflad21","fksflad22","fksflad23","fksflad24","fksflad25","fksflad26","fksflad27","fksflad28","fksflad29","fksflad30","fksflad31","fksflad32","fksflad33","fksflad34","fksflad35","fksflad36","fksflad37","fksflad38","fksflad39","fksflad40","fksflad41","fksflad42","fksflad43","fksflad44","fksflad45","fksflad46","fksflad47","fksflad48","fksflad49","fksflad50","fksflad51","fksflad52","fksflad53","fksflad54","fksflad55","fksflad56","fksflad57","fksflad58","fksflad59","fksflad60","fksflad61","fksflad62","fksflad63","fksflad64","fksflad65","fksflad66","fksflad67","fksflad68","fksflad69","fksflad70","fksflad71","fksflad72","fksflad73","fksflad74","fksflad75","fksflad76","fksflad77","fksflad78","fksflad79","fksflad80","fksflad81","fksflad82","fksflad83","fksflad84","fksflad85","fksflad86","fksflad87","fksflad88","fksflad89","fksflad90","fksflad91","fksflad92","fksflad93","fksflad94","fksflad95","fksflad96","fksflad97","fksflad98","fksflad99","fksflad100","fksflad101","fksflad102","fksflad103","fksflad104","fksflad105","fksflad106","fksflad107","fksflad108","fksflad109","fksflad110","fksflad111","fksflad112","fksflad113","fksflad114","fksflad115","fksflad116","fksflad117","fksflad118","fksflad119","fksflad120","fksflad121","fksflad122","fksflad123","fksflad124","fksflad125","fksflad126","fksflad127","fksflad128","fksflad129","fksflad130","fksflad131","fksflad132","fksflad133","fksflad134","fksflad135","fksflad136","fksflad137","fksflad138","fksflad139","fksflad140","fksflad141","fksflad142","fksflad143","fksflad144","fksflad145","fksflad146","fksflad147","fksflad148","fksflad149","fksflad150","fksflad151","fksflad152","fksflad153","fksflad154","fksflad155","fksflad156","fksflad157","fksflad158","fksflad159","fksflad160","fksflad161","fksflad162","fksflad163","fksflad164","fksflad165","fksflad166","fksflad167","fksflad168","fksflad169","fksflad170","fksflad171","fksflad172","fksflad173","fksflad174","fksflad175","fksflad176","fksflad177","fksflad178","fksflad179","fksflad180","fksflad181","fksflad182","fksflad183","fksflad184","fksflad185","fksflad186","fksflad187","fksflad188","fksflad189","fksflad190","fksflad191","fksflad192","fksflad193","fksflad194","fksflad195","fksflad196","fksflad197","fksflad198","fksflad199","fksflad200","fksflad201","fksflad202","fksflad203","fksflad204","fksflad205","fksflad206","fksflad207","fksflad208","fksflad209","fksflad210","fksflad211","fksflad212","fksflad213","fksflad214","fksflad215","fksflad216","fksflad217","fksflad218","fksflad219","fksflad220","fksflad221","fksflad222","fksflad223","fksflad224","fksflad225","fksflad226","fksflad227","fksflad228","fksflad229","fksflad230","fksflad231","fksflad232","fksflad233","fksflad234","fksflad235","fksflad236","fksflad237","fksflad238","fksflad239","fksflad240","fksflad241","fksflad242","fksflad243","fksflad244","fksflad245","fksflad246","fksflad247","fksflad248","fksflad249","fksflad250","faakd1","faakd2","faakd3","faakd4","faakd5","faakd6","faakd7","faakd8","faakd9","faakd10","faakd11","faakd12","faakd13","faakd14","faakd15","faakd16","faakd17","faakd18","faakd19","faakd20","faakd21","faakd22","faakd23","faakd24","faakd25","faakd26","faakd27","faakd28","faakd29","faakd30","faakd31","faakd32","faakd33","faakd34","faakd35","faakd36","faakd37","faakd38","faakd39","faakd40","faakd41","faakd42","faakd43","faakd44","faakd45","faakd46","faakd47","faakd48","faakd49","faakd50","faakd51","faakd52","faakd53","faakd54","faakd55","faakd56","faakd57","faakd58","faakd59","faakd60","faakd61","faakd62","faakd63","faakd64","faakd65","faakd66","faakd67","faakd68","faakd69","faakd70","faakd71","faakd72","faakd73","faakd74","faakd75","faakd76","faakd77","faakd78","faakd79","faakd80","faakd81","faakd82","faakd83","faakd84","faakd85","faakd86","faakd87","faakd88","faakd89","faakd90","faakd91","faakd92","faakd93","faakd94","faakd95","faakd96","faakd97","faakd98","faakd99","faakd100","faakd101","faakd102","faakd103","faakd104","faakd105","faakd106","faakd107","faakd108","faakd109","faakd110","faakd111","faakd112","faakd113","faakd114","faakd115","faakd116","faakd117","faakd118","faakd119","faakd120","faakd121","faakd122","faakd123","faakd124","faakd125","faakd126","faakd127","faakd128","faakd129","faakd130","faakd131","faakd132","faakd133","faakd134","faakd135","faakd136","faakd137","faakd138","faakd139","faakd140","faakd141","faakd142","faakd143","faakd144","faakd145","faakd146","faakd147","faakd148","faakd149","faakd150","faakd151","faakd152","faakd153","faakd154","faakd155","faakd156","faakd157","faakd158","faakd159","faakd160","faakd161","faakd162","faakd163","faakd164","faakd165","faakd166","faakd167","faakd168","faakd169","faakd170","faakd171","faakd172","faakd173","faakd174","faakd175","faakd176","faakd177","faakd178","faakd179","faakd180","faakd181","faakd182","faakd183","faakd184","faakd185","faakd186","faakd187","faakd188","faakd189","faakd190","faakd191","faakd192","faakd193","faakd194","faakd195","faakd196","faakd197","faakd198","faakd199","faakd200","faakd201","faakd202","faakd203","faakd204","faakd205","faakd206","faakd207","faakd208","faakd209","faakd210","faakd211","faakd212","faakd213","faakd214","faakd215","faakd216","faakd217","faakd218","faakd219","faakd220","faakd221","faakd222","faakd223","faakd224","faakd225","faakd226","faakd227","faakd228","faakd229","faakd230","faakd231","faakd232","faakd233","faakd234","faakd235","faakd236","faakd237","faakd238","faakd239","faakd240","faakd241","faakd242","faakd243","faakd244","faakd245","faakd246","faakd247","faakd248","faakd249","faakd250","zqkpo1","zqkpo2","zqkpo3","zqkpo4","zqkpo5","zqkpo6","zqkpo7","zqkpo8","zqkpo9","zqkpo10","zqkpo11","zqkpo12","zqkpo13","zqkpo14","zqkpo15","zqkpo16","zqkpo17","zqkpo18","zqkpo19","zqkpo20","zqkpo21","zqkpo22","zqkpo23","zqkpo24","zqkpo25","zqkpo26","zqkpo27","zqkpo28","zqkpo29","zqkpo30","zqkpo31","zqkpo32","zqkpo33","zqkpo34","zqkpo35","zqkpo36","zqkpo37","zqkpo38","zqkpo39","zqkpo40","zqkpo41","zqkpo42","zqkpo43","zqkpo44","zqkpo45","zqkpo46","zqkpo47","zqkpo48","zqkpo49","zqkpo50","zqkpo51","zqkpo52","zqkpo53","zqkpo54","zqkpo55","zqkpo56","zqkpo57","zqkpo58","zqkpo59","zqkpo60","zqkpo61","zqkpo62","zqkpo63","zqkpo64","zqkpo65","zqkpo66","zqkpo67","zqkpo68","zqkpo69","zqkpo70","zqkpo71","zqkpo72","zqkpo73","zqkpo74","zqkpo75","zqkpo76","zqkpo77","zqkpo78","zqkpo79","zqkpo80","zqkpo81","zqkpo82","zqkpo83","zqkpo84","zqkpo85","zqkpo86","zqkpo87","zqkpo88","zqkpo89","zqkpo90","zqkpo91","zqkpo92","zqkpo93","zqkpo94","zqkpo95","zqkpo96","zqkpo97","zqkpo98","zqkpo99","zqkpo100","zqkpo101","zqkpo102","zqkpo103","zqkpo104","zqkpo105","zqkpo106","zqkpo107","zqkpo108","zqkpo109","zqkpo110","zqkpo111","zqkpo112","zqkpo113","zqkpo114","zqkpo115","zqkpo116","zqkpo117","zqkpo118","zqkpo119","zqkpo120","zqkpo121","zqkpo122","zqkpo123","zqkpo124","zqkpo125","zqkpo126","zqkpo127","zqkpo128","zqkpo129","zqkpo130","zqkpo131","zqkpo132","zqkpo133","zqkpo134","zqkpo135","zqkpo136","zqkpo137","zqkpo138","zqkpo139","zqkpo140","zqkpo141","zqkpo142","zqkpo143","zqkpo144","zqkpo145","zqkpo146","zqkpo147","zqkpo148","zqkpo149","zqkpo150","zqkpo151","zqkpo152","zqkpo153","zqkpo154","zqkpo155","zqkpo156","zqkpo157","zqkpo158","zqkpo159","zqkpo160","zqkpo161","zqkpo162","zqkpo163","zqkpo164","zqkpo165","zqkpo166","zqkpo167","zqkpo168","zqkpo169","zqkpo170","zqkpo171","zqkpo172","zqkpo173","zqkpo174","zqkpo175","zqkpo176","zqkpo177","zqkpo178","zqkpo179","zqkpo180","zqkpo181","zqkpo182","zqkpo183","zqkpo184","zqkpo185","zqkpo186","zqkpo187","zqkpo188","zqkpo189","zqkpo190","zqkpo191","zqkpo192","zqkpo193","zqkpo194","zqkpo195","zqkpo196","zqkpo197","zqkpo198","zqkpo199","zqkpo200","zqkpo201","zqkpo202","zqkpo203","zqkpo204","zqkpo205","zqkpo206","zqkpo207","zqkpo208","zqkpo209","zqkpo210","zqkpo211","zqkpo212","zqkpo213","zqkpo214","zqkpo215","zqkpo216","zqkpo217","zqkpo218","zqkpo219","zqkpo220","zqkpo221","zqkpo222","zqkpo223","zqkpo224","zqkpo225","zqkpo226","zqkpo227","zqkpo228","zqkpo229","zqkpo230","zqkpo231","zqkpo232","zqkpo233","zqkpo234","zqkpo235","zqkpo236","zqkpo237","zqkpo238","zqkpo239","zqkpo240","zqkpo241","zqkpo242","zqkpo243","zqkpo244","zqkpo245","zqkpo246","zqkpo247","zqkpo248","zqkpo249","zqkpo250","ffgssd1","ffgssd2","ffgssd3","ffgssd4","ffgssd5","ffgssd6","ffgssd7","ffgssd8","ffgssd9","ffgssd10","ffgssd11","ffgssd12","ffgssd13","ffgssd14","ffgssd15","ffgssd16","ffgssd17","ffgssd18","ffgssd19","ffgssd20","ffgssd21","ffgssd22","ffgssd23","ffgssd24","ffgssd25","ffgssd26","ffgssd27","ffgssd28","ffgssd29","ffgssd30","ffgssd31","ffgssd32","ffgssd33","ffgssd34","ffgssd35","ffgssd36","ffgssd37","ffgssd38","ffgssd39","ffgssd40","ffgssd41","ffgssd42","ffgssd43","ffgssd44","ffgssd45","ffgssd46","ffgssd47","ffgssd48","ffgssd49","ffgssd50","ffgssd51","ffgssd52","ffgssd53","ffgssd54","ffgssd55","ffgssd56","ffgssd57","ffgssd58","ffgssd59","ffgssd60","ffgssd61","ffgssd62","ffgssd63","ffgssd64","ffgssd65","ffgssd66","ffgssd67","ffgssd68","ffgssd69","ffgssd70","ffgssd71","ffgssd72","ffgssd73","ffgssd74","ffgssd75","ffgssd76","ffgssd77","ffgssd78","ffgssd79","ffgssd80","ffgssd81","ffgssd82","ffgssd83","ffgssd84","ffgssd85","ffgssd86","ffgssd87","ffgssd88","ffgssd89","ffgssd90","ffgssd91","ffgssd92","ffgssd93","ffgssd94","ffgssd95","ffgssd96","ffgssd97","ffgssd98","ffgssd99","ffgssd100","ffgssd101","ffgssd102","ffgssd103","ffgssd104","ffgssd105","ffgssd106","ffgssd107","ffgssd108","ffgssd109","ffgssd110","ffgssd111","ffgssd112","ffgssd113","ffgssd114","ffgssd115","ffgssd116","ffgssd117","ffgssd118","ffgssd119","ffgssd120","ffgssd121","ffgssd122","ffgssd123","ffgssd124","ffgssd125","ffgssd126","ffgssd127","ffgssd128","ffgssd129","ffgssd130","ffgssd131","ffgssd132","ffgssd133","ffgssd134","ffgssd135","ffgssd136","ffgssd137","ffgssd138","ffgssd139","ffgssd140","ffgssd141","ffgssd142","ffgssd143","ffgssd144","ffgssd145","ffgssd146","ffgssd147","ffgssd148","ffgssd149","ffgssd150","jfydufe1","jfydufe2","jfydufe3","jfydufe4","jfydufe5","jfydufe6","jfydufe7","jfydufe8","jfydufe9","jfydufe10","jfydufe11","jfydufe12","jfydufe13","jfydufe14","jfydufe15","jfydufe16","jfydufe17","jfydufe18","jfydufe19","jfydufe20","jfydufe21","jfydufe22","jfydufe23","jfydufe24","jfydufe25","jfydufe26","jfydufe27","jfydufe28","jfydufe29","jfydufe30","jfydufe31","jfydufe32","jfydufe33","jfydufe34","jfydufe35","jfydufe36","jfydufe37","jfydufe38","jfydufe39","jfydufe40","jfydufe41","jfydufe42","jfydufe43","jfydufe44","jfydufe45","jfydufe46","jfydufe47","jfydufe48","jfydufe49","jfydufe50","jfydufe51","jfydufe52","jfydufe53","jfydufe54","jfydufe55","jfydufe56","jfydufe57","jfydufe58","jfydufe59","jfydufe60","jfydufe61","jfydufe62","jfydufe63","jfydufe64","jfydufe65","jfydufe66","jfydufe67","jfydufe68","jfydufe69","jfydufe70","jfydufe71","jfydufe72","jfydufe73","jfydufe74","jfydufe75","jfydufe76","jfydufe77","jfydufe78","jfydufe79","jfydufe80","jfydufe81","jfydufe82","jfydufe83","jfydufe84","jfydufe85","jfydufe86","jfydufe87","jfydufe88","jfydufe89","jfydufe90","jfydufe91","jfydufe92","jfydufe93","jfydufe94","jfydufe95","jfydufe96","jfydufe97","jfydufe98","jfydufe99","jfydufe100","jfydufe101","jfydufe102","jfydufe103","jfydufe104","jfydufe105","jfydufe106","jfydufe107","jfydufe108","jfydufe109","jfydufe110","jfydufe111","jfydufe112","jfydufe113","jfydufe114","jfydufe115","jfydufe116","jfydufe117","jfydufe118","jfydufe119","jfydufe120","jfydufe121","jfydufe122","jfydufe123","jfydufe124","jfydufe125","jfydufe126","jfydufe127","jfydufe128","jfydufe129","jfydufe130","jfydufe131","jfydufe132","jfydufe133","jfydufe134","jfydufe135","jfydufe136","jfydufe137","jfydufe138","jfydufe139","jfydufe140","jfydufe141","jfydufe142","jfydufe143","jfydufe144","jfydufe145","jfydufe146","jfydufe147","jfydufe148","jfydufe149","jfydufe150","jfydufe151","jfydufe152","jfydufe153","jfydufe154","jfydufe155","jfydufe156","jfydufe157","jfydufe158","jfydufe159","jfydufe160","jfydufe161","jfydufe162","jfydufe163","jfydufe164","jfydufe165","jfydufe166","jfydufe167","jfydufe168","jfydufe169","jfydufe170","jfydufe171","jfydufe172","jfydufe173","jfydufe174","jfydufe175","jfydufe176","jfydufe177","jfydufe178","jfydufe179","jfydufe180","jfydufe181","jfydufe182","jfydufe183","jfydufe184","jfydufe185","jfydufe186","jfydufe187","jfydufe188","jfydufe189","jfydufe190","jfydufe191","jfydufe192","jfydufe193","jfydufe194","jfydufe195","jfydufe196","jfydufe197","jfydufe198","jfydufe199","jfydufe200","jfydufe201","jfydufe202","jfydufe203","jfydufe204","jfydufe205","jfydufe206","jfydufe207","jfydufe208","jfydufe209","jfydufe210","jfydufe211","jfydufe212","jfydufe213","jfydufe214","jfydufe215","jfydufe216","jfydufe217","jfydufe218","jfydufe219","jfydufe220","jfydufe221","jfydufe222","jfydufe223","jfydufe224","jfydufe225","jfydufe226","jfydufe227","jfydufe228","jfydufe229","jfydufe230","jfydufe231","jfydufe232","jfydufe233","jfydufe234","jfydufe235","jfydufe236","jfydufe237","jfydufe238","jfydufe239","jfydufe240","jfydufe241","jfydufe242","jfydufe243","jfydufe244","jfydufe245","jfydufe246","jfydufe247","jfydufe248","jfydufe249","jfydufe250","jfydufe251","jfydufe252","jfydufe253","jfydufe254","jfydufe255","jfydufe256","jfydufe257","jfydufe258","jfydufe259","jfydufe260","jfydufe261","jfydufe262","jfydufe263","jfydufe264","jfydufe265","jfydufe266","jfydufe267","jfydufe268","jfydufe269","jfydufe270","jfydufe271","jfydufe272","jfydufe273","jfydufe274","jfydufe275","jfydufe276","jfydufe277","jfydufe278","jfydufe279","jfydufe280","jfydufe281","jfydufe282","jfydufe283","jfydufe284","jfydufe285","jfydufe286","jfydufe287","jfydufe288","jfydufe289","jfydufe290","jfydufe291","jfydufe292","jfydufe293","jfydufe294","jfydufe295","jfydufe296","jfydufe297","jfydufe298","jfydufe299","jfydufe300"
};//900ŒÂ
const std::string nFood[100] = { "fksordi1","fksordi2","fksordi3","fksordi4","fksordi5","fksordi6","fksordi7","fksordi8","fksordi9","fksordi10","fksordi11","fksordi12","fksordi13","fksordi14","fksordi15","fksordi16","fksordi17","fksordi18","fksordi19","fksordi20","fksordi21","fksordi22","fksordi23","fksordi24","fksordi25","fksordi26","fksordi27","fksordi28","fksordi29","fksordi30","fksordi31","fksordi32","fksordi33","fksordi34","fksordi35","fksordi36","fksordi37","fksordi38","fksordi39","fksordi40","fksordi41","fksordi42","fksordi43","fksordi44","fksordi45","fksordi46","fksordi47","fksordi48","fksordi49","fksordi50","fksordi51","fksordi52","fksordi53","fksordi54","fksordi55","fksordi56","fksordi57","fksordi58","fksordi59","fksordi60","fksordi61","fksordi62","fksordi63","fksordi64","fksordi65","fksordi66","fksordi67","fksordi68","fksordi69","fksordi70","fksordi71","fksordi72","fksordi73","fksordi74","fksordi75","fksordi76","fksordi77","fksordi78","fksordi79","fksordi80","fksordi81","fksordi82","fksordi83","fksordi84","fksordi85","fksordi86","fksordi87","fksordi88","fksordi89","fksordi90","fksordi91","fksordi92","fksordi93","fksordi94","fksordi95","fksordi96","fksordi97","fksordi98","fksordi99","fksordi100"};
const std::string nTool[60] = { "pplsflad1","pplsflad2","pplsflad3","pplsflad4","pplsflad5","pplsflad6","pplsflad7","pplsflad8","pplsflad9","pplsflad10","pplsflad11","pplsflad12","pplsflad13","pplsflad14","pplsflad15","pplsflad16","pplsflad17","pplsflad18","pplsflad19","pplsflad20","pplsflad21","pplsflad22","pplsflad23","pplsflad24","pplsflad25","pplsflad26","pplsflad27","pplsflad28","pplsflad29","pplsflad30","pplsflad31","pplsflad32","pplsflad33","pplsflad34","pplsflad35","pplsflad36","pplsflad37","pplsflad38","pplsflad39","pplsflad40","pplsflad41","pplsflad42","pplsflad43","pplsflad44","pplsflad45","pplsflad46","pplsflad47","pplsflad48","pplsflad49","pplsflad50","pplsflad51","pplsflad52","pplsflad53","pplsflad54","pplsflad55","pplsflad56","pplsflad57","pplsflad58","pplsflad59","pplsflad60" };
const std::string nSorce[200] = { "oaosflad1","oaosflad2","oaosflad3","oaosflad4","oaosflad5","oaosflad6","oaosflad7","oaosflad8","oaosflad9","oaosflad10","oaosflad11","oaosflad12","oaosflad13","oaosflad14","oaosflad15","oaosflad16","oaosflad17","oaosflad18","oaosflad19","oaosflad20","oaosflad21","oaosflad22","oaosflad23","oaosflad24","oaosflad25","oaosflad26","oaosflad27","oaosflad28","oaosflad29","oaosflad30","oaosflad31","oaosflad32","oaosflad33","oaosflad34","oaosflad35","oaosflad36","oaosflad37","oaosflad38","oaosflad39","oaosflad40","oaosflad41","oaosflad42","oaosflad43","oaosflad44","oaosflad45","oaosflad46","oaosflad47","oaosflad48","oaosflad49","oaosflad50","oaosflad51","oaosflad52","oaosflad53","oaosflad54","oaosflad55","oaosflad56","oaosflad57","oaosflad58","oaosflad59","oaosflad60","oaosflad61","oaosflad62","oaosflad63","oaosflad64","oaosflad65","oaosflad66","oaosflad67","oaosflad68","oaosflad69","oaosflad70","oaosflad71","oaosflad72","oaosflad73","oaosflad74","oaosflad75","oaosflad76","oaosflad77","oaosflad78","oaosflad79","oaosflad80","oaosflad81","oaosflad82","oaosflad83","oaosflad84","oaosflad85","oaosflad86","oaosflad87","oaosflad88","oaosflad89","oaosflad90","oaosflad91","oaosflad92","oaosflad93","oaosflad94","oaosflad95","oaosflad96","oaosflad97","oaosflad98","oaosflad99","oaosflad100","oaosflad101","oaosflad102","oaosflad103","oaosflad104","oaosflad105","oaosflad106","oaosflad107","oaosflad108","oaosflad109","oaosflad110","oaosflad111","oaosflad112","oaosflad113","oaosflad114","oaosflad115","oaosflad116","oaosflad117","oaosflad118","oaosflad119","oaosflad120","oaosflad121","oaosflad122","oaosflad123","oaosflad124","oaosflad125","oaosflad126","oaosflad127","oaosflad128","oaosflad129","oaosflad130","oaosflad131","oaosflad132","oaosflad133","oaosflad134","oaosflad135","oaosflad136","oaosflad137","oaosflad138","oaosflad139","oaosflad140","oaosflad141","oaosflad142","oaosflad143","oaosflad144","oaosflad145","oaosflad146","oaosflad147","oaosflad148","oaosflad149","oaosflad150","oaosflad151","oaosflad152","oaosflad153","oaosflad154","oaosflad155","oaosflad156","oaosflad157","oaosflad158","oaosflad159","oaosflad160","oaosflad161","oaosflad162","oaosflad163","oaosflad164","oaosflad165","oaosflad166","oaosflad167","oaosflad168","oaosflad169","oaosflad170","oaosflad171","oaosflad172","oaosflad173","oaosflad174","oaosflad175","oaosflad176","oaosflad177","oaosflad178","oaosflad179","oaosflad180","oaosflad181","oaosflad182","oaosflad183","oaosflad184","oaosflad185","oaosflad186","oaosflad187","oaosflad188","oaosflad189","oaosflad190","oaosflad191","oaosflad192","oaosflad193","oaosflad194","oaosflad195","oaosflad196","oaosflad197","oaosflad198","oaosflad199","oaosflad200" };
const std::string NwearEquipmentLocate[5][2] = {"rhsrsrgs","sxfbxfg","rhsrsrgs2","sxfbxfg2" ,"rhsrsrgs3","sxfbxfg3","rhsrsrgs4","sxfbxfg4" ,"rhsrsrgs5","sxfbxfg5"};
const std::string Nmoney = "sida";
const std::string NitemSet[200] = { "fksffhdppap1","fksffhdppap2","fksffhdppap3","fksffhdppap4","fksffhdppap5","fksffhdppap6","fksffhdppap7","fksffhdppap8","fksffhdppap9","fksffhdppap10","fksffhdppap11","fksffhdppap12","fksffhdppap13","fksffhdppap14","fksffhdppap15","fksffhdppap16","fksffhdppap17","fksffhdppap18","fksffhdppap19","fksffhdppap20","fksffhdppap21","fksffhdppap22","fksffhdppap23","fksffhdppap24","fksffhdppap25","fksffhdppap26","fksffhdppap27","fksffhdppap28","fksffhdppap29","fksffhdppap30","fksffhdppap31","fksffhdppap32","fksffhdppap33","fksffhdppap34","fksffhdppap35","fksffhdppap36","fksffhdppap37","fksffhdppap38","fksffhdppap39","fksffhdppap40","fksffhdppap41","fksffhdppap42","fksffhdppap43","fksffhdppap44","fksffhdppap45","fksffhdppap46","fksffhdppap47","fksffhdppap48","fksffhdppap49","fksffhdppap50","fksffhdppap51","fksffhdppap52","fksffhdppap53","fksffhdppap54","fksffhdppap55","fksffhdppap56","fksffhdppap57","fksffhdppap58","fksffhdppap59","fksffhdppap60","fksffhdppap61","fksffhdppap62","fksffhdppap63","fksffhdppap64","fksffhdppap65","fksffhdppap66","fksffhdppap67","fksffhdppap68","fksffhdppap69","fksffhdppap70","fksffhdppap71","fksffhdppap72","fksffhdppap73","fksffhdppap74","fksffhdppap75","fksffhdppap76","fksffhdppap77","fksffhdppap78","fksffhdppap79","fksffhdppap80","fksffhdppap81","fksffhdppap82","fksffhdppap83","fksffhdppap84","fksffhdppap85","fksffhdppap86","fksffhdppap87","fksffhdppap88","fksffhdppap89","fksffhdppap90","fksffhdppap91","fksffhdppap92","fksffhdppap93","fksffhdppap94","fksffhdppap95","fksffhdppap96","fksffhdppap97","fksffhdppap98","fksffhdppap99","fksffhdppap100","fksffhdppap101","fksffhdppap102","fksffhdppap103","fksffhdppap104","fksffhdppap105","fksffhdppap106","fksffhdppap107","fksffhdppap108","fksffhdppap109","fksffhdppap110","fksffhdppap111","fksffhdppap112","fksffhdppap113","fksffhdppap114","fksffhdppap115","fksffhdppap116","fksffhdppap117","fksffhdppap118","fksffhdppap119","fksffhdppap120","fksffhdppap121","fksffhdppap122","fksffhdppap123","fksffhdppap124","fksffhdppap125","fksffhdppap126","fksffhdppap127","fksffhdppap128","fksffhdppap129","fksffhdppap130","fksffhdppap131","fksffhdppap132","fksffhdppap133","fksffhdppap134","fksffhdppap135","fksffhdppap136","fksffhdppap137","fksffhdppap138","fksffhdppap139","fksffhdppap140","fksffhdppap141","fksffhdppap142","fksffhdppap143","fksffhdppap144","fksffhdppap145","fksffhdppap146","fksffhdppap147","fksffhdppap148","fksffhdppap149","fksffhdppap150","fksffhdppap151","fksffhdppap152","fksffhdppap153","fksffhdppap154","fksffhdppap155","fksffhdppap156","fksffhdppap157","fksffhdppap158","fksffhdppap159","fksffhdppap160","fksffhdppap161","fksffhdppap162","fksffhdppap163","fksffhdppap164","fksffhdppap165","fksffhdppap166","fksffhdppap167","fksffhdppap168","fksffhdppap169","fksffhdppap170","fksffhdppap171","fksffhdppap172","fksffhdppap173","fksffhdppap174","fksffhdppap175","fksffhdppap176","fksffhdppap177","fksffhdppap178","fksffhdppap179","fksffhdppap180","fksffhdppap181","fksffhdppap182","fksffhdppap183","fksffhdppap184","fksffhdppap185","fksffhdppap186","fksffhdppap187","fksffhdppap188","fksffhdppap189","fksffhdppap190","fksffhdppap191","fksffhdppap192","fksffhdppap193","fksffhdppap194","fksffhdppap195","fksffhdppap196","fksffhdppap197","fksffhdppap198","fksffhdppap199","fksffhdppap200" };
const std::string NbringItemSet = "dfvwsdiw3d3";
const std::string NhaniwaLevel[10] = { "fkpophdppap1","fkpophdppap2","fkpophdppap3","fkpophdppap4","fkpophdppap5","fkpophdppap6","fkpophdppap7","fkpophdppap8","fkpophdppap9","fkpophdppap10"};
const std::string NrecipeStep[10] = { "fkewqp1","fkewqp2","fkewqp3","fkewqp4","fkewqp5","fkewqp6","fkewqp7","fkewqp8","fkewqp9","fkewqp10" };
const std::string NbringHaniwaKind[2] = {"adfvafba","svsvsfb"};
const std::string NRank = "sqqrvw";
const std::string NQuestClear[120] = { "oao[0]d1","oao[0]d2","oao[0]d3","oao[0]d4","oao[0]d5","oao[0]d6","oao[0]d7","oao[0]d8","oao[0]d9","oao[0]d10","oao[0]d11","oao[0]d12","oao[0]d13","oao[0]d14","oao[0]d15","oao[0]d16","oao[0]d17","oao[0]d18","oao[0]d19","oao[0]d20","oao[0]d21","oao[0]d22","oao[0]d23","oao[0]d24","oao[0]d25","oao[0]d26","oao[0]d27","oao[0]d28","oao[0]d29","oao[0]d30","oao[0]d31","oao[0]d32","oao[0]d33","oao[0]d34","oao[0]d35","oao[0]d36","oao[0]d37","oao[0]d38","oao[0]d39","oao[0]d40","oao[0]d41","oao[0]d42","oao[0]d43","oao[0]d44","oao[0]d45","oao[0]d46","oao[0]d47","oao[0]d48","oao[0]d49","oao[0]d50","oao[0]d51","oao[0]d52","oao[0]d53","oao[0]d54","oao[0]d55","oao[0]d56","oao[0]d57","oao[0]d58","oao[0]d59","oao[0]d60","oao[0]d61","oao[0]d62","oao[0]d63","oao[0]d64","oao[0]d65","oao[0]d66","oao[0]d67","oao[0]d68","oao[0]d69","oao[0]d70","oao[0]d71","oao[0]d72","oao[0]d73","oao[0]d74","oao[0]d75","oao[0]d76","oao[0]d77","oao[0]d78","oao[0]d79","oao[0]d80","oao[0]d81","oao[0]d82","oao[0]d83","oao[0]d84","oao[0]d85","oao[0]d86","oao[0]d87","oao[0]d88","oao[0]d89","oao[0]d90","oao[0]d91","oao[0]d92","oao[0]d93","oao[0]d94","oao[0]d95","oao[0]d96","oao[0]d97","oao[0]d98","oao[0]d99","oao[0]d100","oao[0]d101","oao[0]d102","oao[0]d103","oao[0]d104","oao[0]d105","oao[0]d106","oao[0]d107","oao[0]d108","oao[0]d109","oao[0]d110","oao[0]d111","oao[0]d112","oao[0]d113","oao[0]d114","oao[0]d115","oao[0]d116","oao[0]d117","oao[0]d118","oao[0]d119","oao[0]d120"};
const std::string NClearAmount[3][7] = { "eedppap1","eedppap2","eedppap3","eedppap4","eedppap5","eedppap6","eedppap7","eedppap8","eedppap9","eedppap10","eedppap11","eedppap12","eedppap13","eedppap14","eedppap15","eedppap16","eedppap17","eedppap18","eedppap19","eedppap20","eedppap21" };
const std::string NRankUpQuest[3][7] = { "we1","we2","we3","we4","we5","we6","we7","we8","we9","we10","we11","we12","we13","we14","we15","we16","we17","we18","we19","we20","we21"};
const std::string NHaniStatusUP[10][10] = { "aas1","aas2","aas3","aas4","aas5","aas6","aas7","aas8","aas9","aas10","aas11","aas12","aas13","aas14","aas15","aas16","aas17","aas18","aas19","aas20","aas21","aas22","aas23","aas24","aas25","aas26","aas27","aas28","aas29","aas30","aas31","aas32","aas33","aas34","aas35","aas36","aas37","aas38","aas39","aas40","aas41","aas42","aas43","aas44","aas45","aas46","aas47","aas48","aas49","aas50","aas51","aas52","aas53","aas54","aas55","aas56","aas57","aas58","aas59","aas60","aas61","aas62","aas63","aas64","aas65","aas66","aas67","aas68","aas69","aas70","aas71","aas72","aas73","aas74","aas75","aas76","aas77","aas78","aas79","aas80","wpoi1","wpoi2","wpoi3","wpoi4","wpoi5","wpoi6","wpoi7","wpoi8","wpoi9","wpoi10","wpoi11","wpoi12","wpoi13","wpoi14","wpoi15","wpoi16","wpoi17","wpoi18","wpoi19","wpoi20"};


CMySaveData::CMySaveData(bool kari) {
	if (kari == false) {
		data = new CData("savedata.txt");
		otherData = new CData("karisavedata.txt");
	}
	else
	{
		data = new CData("karisavedata.txt");
		otherData = new CData("savedata.txt");
	}


	data->ReadAll();
	EquipmentAmount = data->GetInt(NEquipmentAmount);

	for (int i = 0; i < EquipmentAmount; i++) {
		haveEquipmentKindLevel[i][0] = data->GetInt(NhaveEquipmentKindLevel[i][0]);
		haveEquipmentKindLevel[i][1] = data->GetInt(NhaveEquipmentKindLevel[i][1]);
		haveEquipmentKindLevel[i][2] = data->GetInt(NhaveEquipmentKindLevel[i][2]);
	}

	for (int i = 0; i < 5; i++) {
		wearEquipmentLocate[i][0] = data->GetInt(NwearEquipmentLocate[i][0]);
		wearEquipmentLocate[i][1] = data->GetInt(NwearEquipmentLocate[i][1]);
	}
	money = data->GetInt(Nmoney);

	for (int i = 0; i < 200; i++) {
		sorce[i] = data->GetInt(nSorce[i]);
	}
	for (int i = 0; i < 60; i++) {
		tool[i] = data->GetInt(nTool[i]);
	}
	for (int i = 0; i < 100; i++) {
		food[i] = data->GetInt(nFood[i]);
	}

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			itemSet[i][j].first = data->GetInt(NitemSet[i * 20 + j*2]);
			itemSet[i][j].second = data->GetInt(NitemSet[i * 20 + j * 2 +1]);
		}
	}

	for (int i = 0; i < 10; i++) {
		recipeStep[i] = data->GetInt(NrecipeStep[i]);
	}

	bringItemSet = data->GetInt(NbringItemSet);

	for (int i = 0; i < 10; i++) {
		haniwaLevel[i] = data->GetInt(NhaniwaLevel[i]);
	}

	for (int i = 0; i < 2; i++) {
		bringHaniwaKind[i] = data->GetInt(NbringHaniwaKind[i]);
	}
	Rank = data->GetInt(NRank);


	for (int i = 0; i < 120; i++) {
		questClear[i] = data->GetInt(NQuestClear[i]);
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 7; j++) {
			clearAmount[i][j] = data->GetInt(NClearAmount[i][j]);
			rankUpQuest[i][j] = data->GetInt(NRankUpQuest[i][j]);
		}
	}

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			haniStatusPlus[i][j] = data->GetInt(NHaniStatusUP[i][j]);
		}
	}

	EquipmentAmount = this->EquipmentAmount;



	if (EquipmentAmount==0) {
		EquipmentAmount = 7;
		for (int i = 0; i < 7; i++) {
			haveEquipmentKindLevel[i][0] = i;
			haveEquipmentKindLevel[i][1] = 1;
			haveEquipmentKindLevel[i][2] = 0;
		}
		for (int i = 0; i < 5; i++) {
			wearEquipmentLocate[0][0] =0;
			wearEquipmentLocate[0][1] =0;
			if (i > 0) {
				wearEquipmentLocate[i][0] = i+2;
				wearEquipmentLocate[i][1] = 0;
			}

		}

		for (int i = 0; i < 10; i++) {
			recipeStep[i] = 1;
		}

		for (int i = 0; i < 200; i++) {
			sorce[i] = 0;
		}
		for (int i = 0; i < 60; i++) {
			tool[i] = 0;
		}
		for (int i = 0; i < 100; i++) {
			food[i] = 0;
		}
		sorce[1] = 100;
		sorce[3] = 100;
		tool[0] = 1;
		food[0] = 50;
		food[2] = 100;
		money = 1000;

	
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				itemSet[i][j].first = 1;
				itemSet[i][j].second = 0;
			}
		}
		itemSet[0][0].second = 1;
		bringItemSet = 0;

		for (int i = 0; i < 10; i++) {
			haniwaLevel[i] = 1;
		}

		for (int i = 0; i < 2; i++) {
			bringHaniwaKind[i] = i + 1;
		}
		Rank = 1;

		for (int i = 0; i < 120; i++) {
			questClear[i] = false;
		}

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 7; j++) {
				clearAmount[i][j] = 0;
				rankUpQuest[i][j] = false;
			}
		}


		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				haniStatusPlus[i][j] = 0;
			}
		}

	}



}



void CMySaveData::WriteSaveData() {

	data->Set(NEquipmentAmount, EquipmentAmount);
	


	for (int i = 0; i < EquipmentAmount; i++) {
		data->Set(NhaveEquipmentKindLevel[i][0], haveEquipmentKindLevel[i][0]);
		data->Set(NhaveEquipmentKindLevel[i][1], haveEquipmentKindLevel[i][1]);
		data->Set(NhaveEquipmentKindLevel[i][2], haveEquipmentKindLevel[i][2]);
	}

	for (int i = 0; i < 5; i++) {
		data->Set(NwearEquipmentLocate[i][0], wearEquipmentLocate[i][0]);
		data->Set(NwearEquipmentLocate[i][1], wearEquipmentLocate[i][1]);
	}

	for (int i = 0; i < 200; i++) {
		data->Set(nSorce[i], sorce[i]);
	}
	for (int i = 0; i < 60; i++) {
		data->Set(nTool[i], tool[i]);
	}
	for (int i = 0; i < 100; i++) {
		data->Set(nFood[i], food[i]);
	}

	data->Set(Nmoney, money);

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			data->Set(NitemSet[i * 20 + j * 2], itemSet[i][j].first);
			data->Set(NitemSet[i * 20 + j * 2 + 1], itemSet[i][j].second);
		}
	}

	for (int i = 0; i < 10; i++) {
		data->Set(NrecipeStep[i], recipeStep[i]);
	}

	data->Set(NbringItemSet,bringItemSet);

	for (int i = 0; i < 10; i++) {
		data->Set(NhaniwaLevel[i], haniwaLevel[i]);
	}

	for (int i = 0; i < 2; i++) {
		data->Set(NbringHaniwaKind[i], bringHaniwaKind[i]);
	}
	data->Set(NRank, Rank);
	for (int i = 0; i < 120; i++) {
		data->Set(NQuestClear[i], questClear[i]);
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 7; j++) {
			data->Set(NClearAmount[i][j], clearAmount[i][j]);
			data->Set(NRankUpQuest[i][j], rankUpQuest[i][j]);
		}
	}

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			data->Set(NHaniStatusUP[i][j], haniStatusPlus[i][j]);
		}
	}

	data->WriteAll();
}

void CMySaveData::WriteSaveDataToOther() {

	otherData->Set(NEquipmentAmount, EquipmentAmount);

	

	for (int i = 0; i < EquipmentAmount; i++) {
		otherData->Set(NhaveEquipmentKindLevel[i][0], haveEquipmentKindLevel[i][0]);
		otherData->Set(NhaveEquipmentKindLevel[i][1], haveEquipmentKindLevel[i][1]);
		otherData->Set(NhaveEquipmentKindLevel[i][2], haveEquipmentKindLevel[i][2]);
	}

	for (int i = 0; i < 5; i++) {
		otherData->Set(NwearEquipmentLocate[i][0], wearEquipmentLocate[i][0]);
		otherData->Set(NwearEquipmentLocate[i][1], wearEquipmentLocate[i][1]);
	}

	for (int i = 0; i < 200; i++) {
		otherData->Set(nSorce[i], sorce[i]);
	}
	for (int i = 0; i < 60; i++) {
		otherData->Set(nTool[i], tool[i]);
	}
	for (int i = 0; i < 100; i++) {
		otherData->Set(nFood[i], food[i]);
	}
	otherData->Set(Nmoney, money);

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			otherData->Set(NitemSet[i * 20 + j * 2], itemSet[i][j].first);
			otherData->Set(NitemSet[i * 20 + j * 2 + 1], itemSet[i][j].second);
		}
	}

	for (int i = 0; i < 10; i++) {
		otherData->Set(NhaniwaLevel[i], haniwaLevel[i]);
	}

	for (int i = 0; i < 2; i++) {
		otherData->Set(NbringHaniwaKind[i], bringHaniwaKind[i]);
	}

	otherData->Set(NbringItemSet, bringItemSet);


	for (int i = 0; i < 10; i++) {
		otherData->Set(NrecipeStep[i], recipeStep[i]);
	}

	otherData->Set(NRank, Rank);

	for (int i = 0; i < 120; i++) {
		otherData->Set(NQuestClear[i], questClear[i]);
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 7; j++) {
			otherData->Set(NClearAmount[i][j], clearAmount[i][j]);
			otherData->Set(NRankUpQuest[i][j], rankUpQuest[i][j]);
		}
	}

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			otherData->Set(NHaniStatusUP[i][j], haniStatusPlus[i][j]);
		}
	}

	otherData->WriteAll();
}


void CMySaveData::SetWearEquipmentLocate(int equipmentKind, int locate1, int locate2) {
	wearEquipmentLocate[equipmentKind][0] = locate1;
	wearEquipmentLocate[equipmentKind][1] = locate2;

}

void CMySaveData::SetEquipmentAmount(int Amount){
	EquipmentAmount = Amount;
}

void CMySaveData::SetHaveEquipmentNumLevel(int dataNum,int eKind, int eNum, int eLevel) {
	haveEquipmentKindLevel[dataNum][0] = eKind;
	haveEquipmentKindLevel[dataNum][1] = eNum;
	haveEquipmentKindLevel[dataNum][2] = eLevel;
}

void CMySaveData::SetItem(int kind, int num, int amount)
{
	switch (kind) {
	case 0: sorce[num] = amount; break;
	case 1:tool[num] = amount; break;
	case 2:food[num] = amount; break;
	}

}

void CMySaveData::SetMoney(int amount)
{
	money = amount;
}

void CMySaveData::SetItemSet(int setNum, int conNum, int kind, int num)
{
	itemSet[setNum][conNum].first = kind;
	itemSet[setNum][conNum].second = num;
}


int CMySaveData::GetEquipmentAmountSaveData(){
	return EquipmentAmount;
}

int CMySaveData::GetHaveEquipmentKindLevelSaveData(int num, int what) {
	return haveEquipmentKindLevel[num][what];
}

int CMySaveData::GetWearEquipmentLocateSaveData(int equipKind,int which){
	return wearEquipmentLocate[equipKind][which];
}

int CMySaveData::GetMoneySaveData(){
	return money;
}

int CMySaveData::GetItem(int kind, int num)
{
	switch (kind)
	{
		case 0: return sorce[num]; break;
		case 1: return tool[num]; break;
		case 2: return food[num]; break;
		default:break;
	}

}

int CMySaveData::GetSetItem(int setNum, int conNum, bool first)
{
	if (first) {
		return itemSet[setNum][conNum].first;
	}
	else {
		return itemSet[setNum][conNum].second;
	}
}

