#include <stdio.h>
#include <string>
#include <vector>
#include <string.h>

bool match( const char *s, const char *p, std::vector< std::vector<int> > &dp )
{
	auto pstart = p;

	for( ; *p; )
	{
		if( *p == '*' )
		{
			if( p == pstart || *(p-1) == '*' )
			{
				return false;
			}
			
			if( *s == 0 )
			{
				++p;
				continue;
			}

			int i = strlen(s)-1;
			int j = strlen(p)-1;
			if( dp[i][j] == -1 )
			{
				dp[i][j] = match( s, p + 1, dp );	
			}
			if( dp[i][j] )
			{
				return true;
			}

			if( *(p-1) == '.' || *(p-1) == *s )
			{
				++s;
			}
			else
			{
				++p;
			}

			continue;
		}

		if( *(p + 1) && *(p+1) == '*' )
		{
			++p;
			continue;
		}

		if( *s && ( *p == '.' || *p == *s ) )
		{
			++s;
			++p;
		}
		else
		{
			return false;
		}
	}

	return *s == 0;
}

int main( int argc, char **argv )
{
	if( argc < 3 )
	{
		printf("match string pattern\n");
		return 0;
	}

	std::vector< std::vector<int> > dp(strlen(argv[1]),std::vector<int>(strlen(argv[2]),-1) );
	bool is_match = match( argv[1], argv[2], dp );
	printf("is match: %s\n", is_match ? "true" : "false" );
	return 0;
}
