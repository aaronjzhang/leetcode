#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;
string addBinary( const string &a, const string &b )
{
	string result;
	int carry = 0;
	int num1, num2;
	for( int i = 1; a.length() >= i || b.length() >= i; i++ )
	{
		num1 = ( a.length() >= i ) ? a[a.length() - i] - '0' : 0;
		num2 = ( b.length() >= i ) ? b[b.length() - i] - '0' : 0;
		
		int sum = num1 + num2 + carry;
		carry = sum >> 1;
		
		char c = ( 1 & sum ) ? '1' : '0';
		result.insert( result.begin(), c );
	}
	
	if( carry )
	{
		result.insert( result.begin(), '1' );
	}

	return result;
}

int main()
{
	string out = addBinary( "101010101011010110101101011110101001011", "11110101010101110101010101010110101001001010101111011010101011110" );
	printf( "%s\n", out.c_str() );
}
