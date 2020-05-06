#include <map>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <cassert>
#include <string>
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <stack>
#include <numeric>
#include <regex>
using std::vector;
using std::string;

class Solution {
public:
    bool repeatedSubstringPattern(const string& s) {
        /*
         std::regex repeated("\(\\w+\)\\1+");
        return std::regex_match(s, repeated);
        */
        const int len = s.size();
        std::string ss = s.substr(1, len-1) + s.substr(0, len-1);
        return ss.find(s) != std::string::npos;
    }
}; 
int main() {
    std::string a = "gcdzzvyyqqrcfxjneckbdfjgeaztbdknqaanfrcxrrbbvqlknuybtghqirazuzuwbollodhebmkvjvcuarhmczfzbnavmhppjlivahjnwcyzgzptyrjjlbbkejjekworvdbsgnisalrhnzbwywadgbxcexjetwyqrgdxhszdwqcplkydsncctpplhrbhewyevgykzikrdcuznnfpngskxseoikwkbsnfscaxknkhvppcrswvawphuqdazitsczglhfykvqclmyipzbnbsifniuohgcrkgjrzjioipewwbgkuvksomjqgigsnsndsqjtvlwhgyqchkroscetciiivjjpwiblwiygcrwzbvrjxuocjwyrgtsrwwggauybxzjzfckqfhrwlxrldflxmvpnvloqbowxobgkadmaigmrcerkxppfnkzmcrdrzogqbengfeaulhkwprigrssxnvxvparcckpgveqqlljfopngrnfmjpmkcuxnjozdeeieuxxutudqzzogufklymjqbcuxoiupsshvetyylpgjcfctdqizvxecscwmcvevcauofvahhbdjxgxgstwvfyqesjabtushtdvxtvpaiefcqhaizabrjfcbjefulxwfliccezhzdljgffkkkcwxyiymoizuvmnebnsiksqnjfbhxfwwkioobeycgrlyjzusiwhnwyfiecoyqxwgsfbrortiwjijkybpxyxdgkepbsvgfdrhmqpsofhmdyzxdhukndasyhjpzsrggldhfsrwntzoudasorkkklgdqeqslocoyqqzxpkegfachwvwdlfepeiqapdtuxjvbhuktbeoigbpujijdvnzjzlvdrpmuuhynyjnvxnywalrppabfgokdpgkrejpsecqdvsajztallucbhiwkiafqytehcrophrpharrlcwpcwipcngbzihxqzxsdmlvmblfqqxhvxgwlhrdtngwikjffqcjzmnitszpxohdxlrisjadqacptzdvdbsuocxtwtsapvheebjqresbmhpspkeosfsoarbffpyoetohcauevbtdvaiviqsnvyfumltrxjorrydsqfnjsdtghcvutyvswmfdijmrsekksuiaivholmqadchznmiwpfezyhttavmljoaqmlrtxsiyvongfscjfdbhzhruzpmhfzduvjvhgtiiabyqcmyijnynyhutsfxyrafyduqhcqbmigqlgzaiocypgsjflrlcwbvgafpekfkxtbrvgouprkzieqvcpmbcwljrlpeakgxcufxnwdsnqgzqiqpslhmozsafrkwyiynmbennqtmxpuilpkvsvlfaishylytxbsiligzifmyhpuiuabonlrtpihzzmxpxxdoftbciqmanynnqugbauaxkzffrkzflbtpczecbsufdrijrhquuitvfepnklccvtlabupupeljccrvibwncellcnjhugbmmhxeeqrhghmsslemrdhmwyczgaohtfmemrbzsohfbdxchwnotbqfxehkrluinlgoimlbvqkzliyrhyyonhiyjkpsrylzsiyqndsuldvkhjwgeivaoombyskwxcakaeasrwkwcxzkqkdncevgyhaxfuyjjdqlkpglpxuorlxohnpeeuzwifejhqmzhvirachcsaavzbqsbheiycwqramnnvnthdsvnpwdqlfdvgyaaeyvfazsosisbctjehtethdlinresiauqwlciheneshdtexddiicntnylccedcordbdnsamzzctyhovvqowlaegqaezwqbivzkynhuukdduzafyfadstpkqevgnvvxvtcatzezkhualbqaysegqtqsqagpsnyntravascpcqqozrbofcoepqlnsotbqqekwffhviulfggwkkqubbtypwnbnvplqwuxxiccsacoqvzwlfttrkkglrpohxfhuhaznoiaefbykdfzujknmwxetbutyrmgyngpdqhjpxvyfasgiwolzaxxlxujthexbnxbehrdrdkohbxatpfqywtbumqksdkgpopidxaihrdqluopvjtjanprzdulmgfmftrtaxyisstbwqdbgslzrumxjxrtzsgbknnjhsyzzjrdpcxqajhrgvnibjhpztgfhmmpyxxaboelsdtaicmtiigyccybubxlllnpbsfrhqygupszvdlrnzxtjfvlpcrpdxgshuoyhkykpuqmobbexzebqrowgqctkggarqxgdljeoxviieyoydtzpydrwidqujcwgptppvyrtfnthchefbwnyknouthlyswcfzhogxrsrkkwrqxfwfftomhwedpaceillrfnnudatzlppimcvwponqdrqrihqubrkphcwfinpzoukbeibtylvqpssdikbpczjeprytsjjwtjhnjingwptfpgrbeolrjjohuazawobhadduyzsvhnmpbthcdpskhhrsnjzugshemigdhsesuaztbctmprsobistxghinlssegojmzouualrvpoxptvzlfjgtfzaklkoyvklzbaetxhspireyuwxwjxnprjvdghoiynxcalcsycxffcrjyssygrcdmlpwiltwwspvpmyhcbmavneckchhtmhtdxkrznegbpvprlkssrasqggubefsfnkdctmbebjacrfganbczajnfuwkyctuujevtypluoyshvandnptmcszbrhieioxpsoozbcdhhlmdibedjvdrrrybcksxzdcrjxjqowcovyzprxhsuxjpcufmrxsrnpsbtlpiblpbiacdtxgznlozzvlhxknyvzwdpzbqqtexwmdzirpnavkkvdlwcodfqwfuuywlstipvlwzqurezstkdumxmnvhnglrvotkxuhfingbplqoapoytwztahmvfalewmxgbvmyngkadsgmuwbfvlyrgzmndvvbegixruffkmodbvqmjfeuyzpgvemfbphzemoclrshgmcbjcppoydyojvfyzxajewnipkdrxmgdstpamxlmtxbunngnymdvngiqjimkettqysbexxljojmwjkhplsgvidgyuotigpraetcquwldmezfwovokhwzyczsstxpnqzrhckmuwveykuiuderjzsevcrflpqvqbzsnjxaacqvbisghwfvscqtpthqowqzbhrgkomhyaddphkjryfzgwodsghsiwhqwvkiiqlfpjfxpcvextjnrbbyqnhzrdlqfjhavvjhyxifxuthkogexfmfbcnimesoyjvhyvfmlooajmedzitmdkxdiobvvfdlnsnmgzdfkhgpaspmyoabjeqgfrwqgeuuhwazdcdnvzeyizivkoraeltoudxtgyeznedcsixehgkcadazebxzbjvcszbjjtgmahfnnoghpmfbaphmrtovqojfrorhduoftngxczmnpakpvyukwzdeqvivakwmgjgefkgccmepewhdavbmviqmgfmwqywhpscezazpasosyifruciakidbefuhptjrgyjrjfmzkolzmbtnhkzpskpyxpbadosnuglpnhwjsmmdujjyyloknsghwqorjxiuxknbagewwdlvnrrtlhoduufxlknqvfdltksparmtrixqwxzqzslcaytfnfitinuguedbjmjylicamwvrgxolyuhhxcbviwbfdufhjqzcrzxyyllxqbigjklbhafpmrvaygedmjqxeqmhpagpisuavzbizvilzbukqemjzqnkzsqcxhbqtlxqhzateftdywdqcscjuckhlmizpizjjyjldvmhtdqzwuajrwvtswiirlhbkscjyqvzyxpfomzsqzdosuhhbjstjexokfujhcimqmxodnhmezbsoutoufgaohbynsbemzkmgtboicgjapqkkchysylisflwrkfmmnwjenhpwgjujfbxlamhvjorawpytbdusrlgephcbgbmunqppmeezykhxgihwvvvnhwewvlsrevrgaqgyhsedrnqgsbguwzgkudigfqekldckontfcnesncexenocioxtymisotvxyelevwkmikftudalpqbqzozbudsxdfojjivpfrsefjvtyhmevwtgpnrzzhsjxyxbmrtbkmytshrlqilnrxtngwujljctnalsnwsymdyhdwicrnqjqjsvxowagbunjjvbcfstnacdmjohpttasngjjdsijnaexfohrnpeyvikqrybmvzjhrhjifnbtbyvzvoqlzqwmzobdmsuhnwdffravrqudpetaeronqzzyuecxlvywphpcbhdaxbhlxaatfrdlurzicxjqmjrpddkuiwlelamuikvrxpthxzjzwjabpxaskmcczeprqbmegykxqgkfjybxlfcgtvznpszzxxsituyjblfiyzcmxpnyvwedebmqguviiigzrxzdoozcsessogougvpmriaurueirfjuewhzrixbuuohkgigqqcxcformwykhfzfmlssspqgdicewmtppfvsjhtneubvjusmbccelbryzvuomiqkgcfovherggkmmtghjyfsszfsiwhtytyhpuaenqzoiepabdzvhlxaenuoleihwvkuzkjjbbzozfqhzmkkhezvbnwamzvgbltptzexdzudkqvyctpvagwmttywcuzyngqwxnbdpakuvreifbwyikuzrnzcntkunzwrbsbzhiclsqqkclaetqkiapdmbfqyfpkihpfembsxyrtuqupmqrgthtnkghuucqhnxyuucthbczxbxftdaoyirdfxszcumitfzzzukxfetovixeoypijkhxzeldpybsnkmrhjpmczflpvzxdevufovbdkbnfqemljfyaxrrwpwzbhwwiwgvmjanmoznyxjnfmfdopcaiuvksjmmnrvdjtywjtfalxypxwgzarsaggjfibxhcowpsfvkwmiagorfpnlluycelnngrpgnywdpfyxtczyifiyihfugwkikmnvubjzefufneiiwilfazezulwepvmtvygcoduaxmeehgexprxtwcmfqpwystrbmvzdlflmjhcocyiqlfsjydhtpwpogqmtemmlpfhjyfhcfvovhdjrjijmzszfgxiinutlfsnbiqnpdikztysnspvusyhqqqbfetlwrrboamkxccdhwhwrmnginsaeefrlwodbczyutpapqtiruscyymbpcgycytfnkxxpcxinhgiuvrurrveuekknfyvmjhivpbfgdikqikmnohduaxcmndqqazusugaaewlgujbjyklkcobxscaivpnnyqnfkafxdmoqfinojztevofjmjwurwmqduhklymwoxoetyxibhrmpegyiwmxmaqorpykjladzppythuwcgtsivwjceghnylwizbtpdhqogpuwyqmkvndyiqbmydfvgazabquwftghwesasejxgsaaxvtdfwpxrbyyplvsigwfcmsdkmkcdkgrpuheoxbdgruitsodxshnaxizebwlfuvpkukypsaiozivbjxlnyuwcwvggnjlsnblrzsgjtsjdyadqemxcqkncljtmygdbzrfpapsgfbtyibjxgsqtsxtxicgrxdhlawlwzdlnxgjtojyejtkkpqdjysgyuperosctuyuhcwmheoeadqrofsrrjtfksxwcbsliyvylkgyfmhxwldmyieybkfxfxugxlneikswlnicqzwxnkkweardfzyrxmkqcnmarroedzqhyuyinsjsfbqbcncoopxpmktljdyoibsgrtthnsntipnntdswggfzmenapjqdlqcvskfodegqrvuiuncqbksnivfaygxatfdqcvukflbcmelomvfpicohivzdglhzeabvlddgidytlrocvrbhfivalqlrzhbhcuptltnckjgnrohjwkqoinfgycnayrqrqwkqzmuoqxhcjankevwhlpwibjvfvdnfbaeiqgtyufgchxehzaleiicwbbminjxbilrungfjdygasvztrxiedvdlfcgbgutqqbuvpovuvvqcristdobriozyvylhhonxsastorkruuvtjluhvwypbtbcxuysrzznuuwmnrpkafnvzeewsibovfimthqigrkjibesianqwskwdritimugwovjkpuahnfmhsfljvrltjnbotjpwjzxnetxhljtwucvlwakazrorzrsbvfhadpqpotqyjqhwvyvwndqdysuuotfsoejokortfpgqybpwlmpjwydydjczdedvkuacyrnstazrrzaincaiahdnyizvdrmudfwlhmwxcsctrbqljvtekmcjcrtgyhtfgpaloqgfwuuezlcjsfneyhwaonekhneiqfcpjvrpphrvtzotpajhsevjeyewjutwpnpzhulbulussazygaiprppogjfainxqliqwxxfzelpjijcwzhhewznzyuerxguctggyrzitwrigvbjtreametaiaossuvtofeqgubmgucdgjmipilupqirkpiinczfhgeqtywxfrdpupgomdqcamdjwsmwtrpkhkwghizsfanlbfljsumcbwbzdtpasmiejjjcacykihkevsgzlslavsowfsfasnnsfhuundiyghflprbpnjjovikkmeitiymwmdlhtdicbxrpqeacexeriwlntqudtwymcoktnxoayytglijxxvrtwyyyxxsqgqkjhgfhcjqhqchwfqemiheddfqrnvqsgiukfseligagbchtkscnmbmrbvaecuahxwzffbvzmnktnzxvembdnjumzhcyxtappiqpnoipmpazjimxdofrwyxtetunxhdtuqvnygqsgkgerunawbhllyxirmbftbkzhjwelomogmzimlpjklhgzrvxjerzkgwkddgdxfwypxkmjleirdaacbxcasgiuwzgjzsfmeitetmozvtvukglclkvafaywacryevzjjvdmiwfpmprtsoanypmojtekfduumpuufkrfeeakwwphvqjgkvjsthnrhjxhpmpracaruxvsrdwbfhabwwhazosfqgriykenckywhqxyaqtkgdvuvjnvlpjxfmguxtgyhypvlhqnscfqbmcsalavqrgutbeejiulbcrwrmphbgenntnimmimzyvcvopinntmnqdakbhuzxexsrmnqlgxyupcjoeohpqpsgbbqjxyeoevpbovlelwwmdrikudjtmzstgkojvgikuupeeagzaqnsmuxiscqydocsodevsyiflybaqvcszgqxzsbtcsmzjdnwjoxcekytjtzskpytvqvtagibgaxgauxjedibdeijpmeedqupyswmptexhdbsqvuuhqqkpwfqpgncedzomsxiyvbiurykgjcgltsbawqdnbxcrryflmzgqgyjuwxlktzdxogtxmwczdefzxaztrmhughjtoyilliaghqqnlynvtgguinyquxtpuuycpzfofqxmmlnnmnjigidirzqgmjmkrsxgrjrquyfeyrfuuqdamomxxgghzynnlemcowhqpuuetusxwvjnitorwjztmykwhscowstsfojslrclnwoelmoguqtfmknvgjvezgmiliqabftvmxvrjeixqjvddlyqzlxdwplnxcomsvmiixlotkbstxhfkfwxilblujxropyybqvpvfpceehdbvvfzcnqnceogkgiqjrmsfdmauurxpvmgihqqyjxpifitgwokbgxvhfmvagfegbevtqztmoaaktdvinimilioihdugvifhcyenvfldosukxxulutuezajmwfskuggrumeuzklfnxtqmcyerdhobrrollwsinxfiiwcemxrpzqqpkyddfihubhgaydfzgxrcuojcfqiigxcysdhmrvgaxxdwywsykowozpgdvbhcyrxqsrzkodzadojhbynxgfczwkziqgbrpucmbduiblwtfizncsaoxptltfuamramamoyckdisptuzdzhprfltzbqmodytuyqvqdyqnpzkyggwfznzcrthstgasjphzzrzksbvkzneafsfitxcssaihvlgkhvbkogheqdqzrscgrykoxtctccsidkuetlymldxdlmzyixcxcdekpfhelspcjvcmbmvybbeusrnwtxhsxnztjxvgwnxtfixbvhzkjaqrusrinmpdhcuvykxlkibocstdbitibilfkjeupswavaplmqgoiumccurmgipmppknpgrtowqudhbpnvfwzzojilkoeywrqdqgfjjnvrvxfrvplsqrgfihyqizudqlhtluugzqlorxbwdxqklsnqbrbvymzevyoteqouvvlwexhyuwkfdmcgaykubecejepmdxfvypuhlbmytxmwcpfnwwpdggvgsdmghdxfpqhhwkcyqslewpzubdymifegfakqdhjhwekwpfqwqagdqzvfnkkwtlfnlvmpmwssrmgquwhcqpodutmjeerbcpysobphetitiugdriqnrjsdsxkgqyczfozjotakgemuczogjbfwylqqdbtvzktvwhcanyqvxqyttwrzatjomjjorbipjvpvtxdlopgajcielcqjypmvljovozgbpdhhtaeehjahcvvmhwudggpjhxhjdxvzixzjvjooosceqfcyebqmodfdtnjpvymvdjpygbaamsjsjrtwinsrafgbjsrslrcazpumbsmuuaisdiacjlysrhdlfjbqxlkdtaihdfbpzixgrvprgtesxwgpgmhxvnemykoiqrlwzclghcmywcghltqhfziokgkbvynlmckiznavxgmywgkkfacuetrlqgmufeqvflunxlnwyawzkmoconujmovkgnksabofkytdmtubriyxvhkltgnddfiejyjrziwfqwcgarqhxicutzekyhwsgphmhmiyttxenpbgbqfuixzypanchvzqovsjanjsrjatdmugavtneptptdqejharuckmcgirvnrdahjlhvacsfsozyecgsmhtoggjmdaeejmznmnatqwtoljrzcivxcjfdikymjmycabrzhdlzjxmnqgzobbszkqhobvhrutiaftetzixxwqzpmdefvacupqjeimtmtefdnxtzqmocqveljxfukjivzwupfxivviuecxihshaxyuvitjflimwbdtstxiutljvjskajqicpfndrpwlqxduelxrxxz";
    std::cout << Solution().repeatedSubstringPattern(a) << std::endl;
    return 0;
}
