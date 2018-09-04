#include <stdio.h>
#include <string>
#include <regex>
#include <algorithm>
#include <cctype>

using namespace std;
regex rgx = regex("\\s*[+-]?(?:[0-9]*\\.[0-9]+|[0-9]+\\.[0-9]*|[0-9]+)(?:e[+-]?[0-9]+)?\\s*");
bool isNumber( string &str )
{
	return regex_match( str, rgx );
}

int main( int argc, char *argv[] )
{
	if( argc < 3 )
	{
		printf("usage: %s string expect\n", argv[0] );
	}

	string str = argv[1];
	bool valid = isNumber( str );
	printf("%s: %s %s\n", argv[1], valid ? "true" : "false", argv[2] );
}
