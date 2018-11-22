#include <string>
#include <vector>
#include <unordered_set>
#include <queue>
#include <stdio.h>
#include <stdint.h>
#include <limits.h>

using namespace std;
bool is_ladder( const string &word1, const string &word2 )
{
	size_t ladder = 0;
	for( size_t i = 0; i < word1.length(); i++ )
	{
		if( word1[i] != word2[i] )
		{
			ladder++;
		}
	}

	return ladder == 1;
}
vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
	vector< vector<string> > ans;
	size_t end_pos = ULONG_MAX;
	size_t begin_pos = ULONG_MAX;
	for( size_t i = 0; i < wordList.size(); i++ )
	{
		if( beginWord == wordList[i] )
		{
			begin_pos = i;
			continue;
		}

		if( endWord == wordList[i] )
		{
			end_pos = i;
		}
	}

	if( end_pos == ULONG_MAX )
	{
		return ans;
	}

	if( begin_pos == ULONG_MAX )
	{
		wordList.push_back( beginWord );
		begin_pos = wordList.size() - 1;
	}

	size_t size = wordList.size();

	unordered_map<size_t, unordered_set<size_t> > adj_table;
	for( size_t i = 0; i < size; i++ )
	{
		unordered_set<size_t> adjs;
		if( adj_table.find( i ) == adj_table.end() )
		{
			adj_table[i] = adjs;
		}
		for( size_t j = i + 1; j < size; j++ )
		{
			if( adj_table.find( j ) == adj_table.end() )
			{
				adj_table[j] = adjs;
			}
			if( is_ladder( wordList[i], wordList[j] ) )
			{
				adj_table[i].insert( j );
				adj_table[j].insert( i );
			}
		}
	}

	queue< vector<size_t> > paths;
	unordered_set<size_t> visited;	
	unordered_set<size_t> tmp_visited;	

	paths.push( { begin_pos}  );
	visited.insert( begin_pos );

	size_t min_size = -1;
	while( !paths.empty() )
	{
		auto path = paths.front();
		paths.pop();
		if( path.back() == end_pos )
		{
			min_size = path.size();
			vector< string > ladders;
			for( auto i : path )
			{
				ladders.push_back( wordList[i] );
			}
			ans.push_back( ladders );
			continue;
		}
		if( path.size() >= min_size )
		{
			continue;
		}
		if( paths.empty() || path.size() == paths.back().size() )
		{
			visited.insert( tmp_visited.begin(), tmp_visited.end() );
			tmp_visited.clear();
		}
		size_t i = path.back();
		for( size_t j : adj_table[i] )
		{
			if( visited.find(j) == visited.end() )
			{
				vector<size_t> new_path = path;
				new_path.push_back( j );
				paths.push( new_path );
				if( end_pos != j )
				{
					tmp_visited.insert( j );
				}
			}
		}

	}
	return ans;
}

int main()
{
	//vector< string > wordlist = { "hot","dot","dog","lot","log","cog" };
	//vector< string > wordlist = { "hot","dot","dog","lot","log","cot" };
	//vector< string > wordlist = { "hot","dog","dot"};
	//vector< string > wordlist = { "hot","cog","dog","tot","hog","hop","pot","dot" };
	vector< string > wordlist = { "kid","tag","pup","ail","tun","woo","erg","luz","brr","gay","sip","kay","per","val","mes","ohs","now","boa","cet","pal","bar","die","war","hay","eco","pub","lob","rue","fry","lit","rex","jan","cot","bid","ali","pay","col","gum","ger","row","won","dan","rum","fad","tut","sag","yip","sui","ark","has","zip","fez","own","ump","dis","ads","max","jaw","out","btu","ana","gap","cry","led","abe","box","ore","pig","fie","toy","fat","cal","lie","noh","sew","ono","tam","flu","mgm","ply","awe","pry","tit","tie","yet","too","tax","jim","san","pan","map","ski","ova","wed","non","wac","nut","why","bye","lye","oct","old","fin","feb","chi","sap","owl","log","tod","dot","bow","fob","for","joe","ivy","fan","age","fax","hip","jib","mel","hus","sob","ifs","tab","ara","dab","jag","jar","arm","lot","tom","sax","tex","yum","pei","wen","wry","ire","irk","far","mew","wit","doe","gas","rte","ian","pot","ask","wag","hag","amy","nag","ron","soy","gin","don","tug","fay","vic","boo","nam","ave","buy","sop","but","orb","fen","paw","his","sub","bob","yea","oft","inn","rod","yam","pew","web","hod","hun","gyp","wei","wis","rob","gad","pie","mon","dog","bib","rub","ere","dig","era","cat","fox","bee","mod","day","apr","vie","nev","jam","pam","new","aye","ani","and","ibm","yap","can","pyx","tar","kin","fog","hum","pip","cup","dye","lyx","jog","nun","par","wan","fey","bus","oak","bad","ats","set","qom","vat","eat","pus","rev","axe","ion","six","ila","lao","mom","mas","pro","few","opt","poe","art","ash","oar","cap","lop","may","shy","rid","bat","sum","rim","fee","bmw","sky","maj","hue","thy","ava","rap","den","fla","auk","cox","ibo","hey","saw","vim","sec","ltd","you","its","tat","dew","eva","tog","ram","let","see","zit","maw","nix","ate","gig","rep","owe","ind","hog","eve","sam","zoo","any","dow","cod","bed","vet","ham","sis","hex","via","fir","nod","mao","aug","mum","hoe","bah","hal","keg","hew","zed","tow","gog","ass","dem","who","bet","gos","son","ear","spy","kit","boy","due","sen","oaf","mix","hep","fur","ada","bin","nil","mia","ewe","hit","fix","sad","rib","eye","hop","haw","wax","mid","tad","ken","wad","rye","pap","bog","gut","ito","woe","our","ado","sin","mad","ray","hon","roy","dip","hen","iva","lug","asp","hui","yak","bay","poi","yep","bun","try","lad","elm","nat","wyo","gym","dug","toe","dee","wig","sly","rip","geo","cog","pas","zen","odd","nan","lay","pod","fit","hem","joy","bum","rio","yon","dec","leg","put","sue","dim","pet","yaw","nub","bit","bur","sid","sun","oil","red","doc","moe","caw","eel","dix","cub","end","gem","off","yew","hug","pop","tub","sgt","lid","pun","ton","sol","din","yup","jab","pea","bug","gag","mil","jig","hub","low","did","tin","get","gte","sox","lei","mig","fig","lon","use","ban","flo","nov","jut","bag","mir","sty","lap","two","ins","con","ant","net","tux","ode","stu","mug","cad","nap","gun","fop","tot","sow","sal","sic","ted","wot","del","imp","cob","way","ann","tan","mci","job","wet","ism","err","him","all","pad","hah","hie","aim","ike","jed","ego","mac","baa","min","com","ill","was","cab","ago","ina","big","ilk","gal","tap","duh","ola","ran","lab","top","gob","hot","ora","tia","kip","han","met","hut","she","sac","fed","goo","tee","ell","not","act","gil","rut","ala","ape","rig","cid","god","duo","lin","aid","gel","awl","lag","elf","liz","ref","aha","fib","oho","tho","her","nor","ace","adz","fun","ned","coo","win","tao","coy","van","man","pit","guy","foe","hid","mai","sup","jay","hob","mow","jot","are","pol","arc","lax","aft","alb","len","air","pug","pox","vow","got","meg","zoe","amp","ale","bud","gee","pin","dun","pat","ten","mob" };
	string beginWord = "cet";
	string endWord = "ism";

	unordered_set<string> words;
	for( auto &word : wordlist )
	{
		words.insert( word );
	}
	auto all_ladders = findLadders( beginWord, endWord, words);
	
	for( auto &ladders : all_ladders )
	{
		for( auto &word : ladders )
		{
			printf( "%s, ", word.c_str() );
		}
		printf("\n");
	}
	return 0;
}
