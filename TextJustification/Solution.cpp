#include <cstdio>
#include <string>
#include <vector>
#include <regex>
#include <fstream>

using namespace std;
vector<string> fullJustify(vector<string>& words, size_t maxWidth) 
{
	vector< string > ans;
	vector< string > aline; 
	size_t size = 0;
	while( !words.empty() )
	{
		if( size + aline.size() + words.front().size() <= maxWidth )
		{
			aline.push_back( words.front() );
			size += words.front().size();
			words.erase( words.begin() );	
		}
		else
		{
			string sline;
			if( aline.size() > 1 )
			{
				size_t q = (maxWidth - size) / ( aline.size() - 1 );
				int r = (maxWidth - size) % ( aline.size() - 1 );
				for( auto &word : aline )
				{
					sline += word;
					if( sline.size() < maxWidth )
					{
						size_t space_cnt = q + (( r-- > 0 ) ? 1 : 0);
						sline.append( space_cnt, ' ' );
					}
				}
			}
			else
			{
				sline += aline.front();
				sline.append( maxWidth - sline.size(), ' ' );
			}

			ans.push_back( sline );
			aline.clear();
			size = 0;
		}
	}

	string sline;
	for( auto &word : aline )
	{
		sline += word;	
		if( sline.size() < maxWidth )
		{
			sline += " ";
		}
	}
	if( sline.size() < maxWidth )
	{
		sline.append( maxWidth - sline.size(), ' ');
	}
	ans.push_back( sline );
	return ans;
}
int main( int argc, char *argv[] )
{
	if( argc < 2 )
	{
		printf("Usage: %s input.txt", argv[0]);
		return 1;
	}
	
	ifstream ifs( argv[1] );
	if( !ifs.is_open() )
	{
		return 1;
	}

	char cline[10*1024] = {0};
	ifs.getline( cline, sizeof(cline) - 1 );
	printf( "%s\n", cline );
	
	string sline = cline;
	vector<string> words;	
	regex e("\"(\\w+\\.?)\"");
	
	smatch m;
	while( regex_search( sline, m, e ) )
	{
		words.push_back( m[1].str() );
		sline = m.suffix().str();
	}

	ifs.getline( cline, sizeof(cline) - 1 );
	printf( "%s\n\n", cline );
	sline = cline;
	regex e1("(\\d+)");
	int maxWidth = 0;
	if( regex_search( sline, m, e1 ) )
	{
		maxWidth = stoi( m[1].str() );
	}

	//printf("maxWidth: %d\n", maxWidth );
	ifs.close();

	vector<string> ans = fullJustify( words, maxWidth );
	for( auto &line : ans )
	{
		printf( "\"%s\"\n", line.c_str() );
	}
	return 0;
}


