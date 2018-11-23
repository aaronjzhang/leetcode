#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <string>
#include <vector>

using namespace std;


bool isMatch( const string &str, const string &pattern )
{
	if( pattern.length() == 0 ) 
	{
		return str.length() == 0;
	}

	vector< vector<bool> > dp( str.length() + 1, vector<bool>(pattern.length(), false) );
	const char *s = str.c_str();
	const char *p = pattern.c_str();
	
	for( int i = str.length(); i >= 0; i-- )
	{
		for( int j = pattern.length() - 1; j >= 0; j-- )
		{
			if( p[j] == '*' )
			{
				if( (uint32_t)j == (pattern.length() - 1) )
				{
					dp[i][j] = true;
					continue;
				}

				if( (uint32_t)i < str.length() )
				{
					dp[i][j] = dp[i][j+1] || dp[i+1][j];
				}
				else
				{
					dp[i][j] = dp[i][j+1];
				}
			}

			if( s[i] != 0 )
			{
				if( p[j] == '?' || p[j] == s[i] )
				{
					if( (uint32_t)j < pattern.length() - 1 )
					{
						dp[i][j] = dp[i+1][j+1];
						continue;
					}

					if( (uint32_t)i == str.length() - 1 )
					{
						dp[i][j] = true;
					}
				}
			}
		}
	}

	return dp[0][0];
}

int main( int argc, char *argv[] )
{
	if( argc < 3 )
	{
		printf("Usage: %s str pattern\n", argv[0]);
		return 1;
	}

	bool match = isMatch( argv[1], argv[2] );
	printf("str:%s, pattern:%s, is match:%s\n", argv[1], argv[2], match ? "true":"false");
}
