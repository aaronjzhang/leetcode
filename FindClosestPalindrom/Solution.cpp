#include <string>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

string nearestPalindromic( string &n )
{
	n.erase( 0, n.find_first_not_of( '0' ) );
	size_t len = n.size();
	if( len == 0 )
	{
		return "1";
	}

	uint64_t n_ul = stoul( n );
	if( n_ul == 10 || n_ul == 11 )
	{
		return "9";
	}
	string pre_half = n.substr( 0, (len+1)/2 );
	uint64_t pre_half_ul = stoul( pre_half );
	string candidate1 = to_string( pre_half_ul + 1 );
	int m = len - (len+1)/2 - 1;
	for( int i = m; i >= 0; --i )
	{
		candidate1.append( 1, candidate1[i] );
	}

	string candidate2 = to_string( pre_half_ul - 1 );

	if( candidate2.size() < pre_half.size() )
	{
		candidate2.append( len - candidate2.length() - 1, '9' );
	}
	else
	{
		for( int i = m; i >= 0; --i )
		{
			candidate2.append( 1, candidate2[i] );	
		}
	}
	string candidate3 = n;
	size_t i = 0;
	size_t j = len - 1;
	for( ; i < j; i++,j-- )
	{
		candidate3[j] = candidate3[i];
	}
	
	uint64_t cand1_ul = stoul( candidate1 );
	uint64_t cand2_ul = stoul( candidate2 );
	uint64_t cand3_ul = stoul( candidate3 );

	std::vector< uint64_t > candidates_ul = { cand1_ul, cand2_ul, cand3_ul };
	std::vector< size_t > diffs = { cand1_ul - n_ul,n_ul - cand2_ul, ( n_ul > cand3_ul ) ? n_ul - cand3_ul : cand3_ul - n_ul };
	std::vector< string > candidates = { candidate1, candidate2, candidate3 };	

	int size = ( cand3_ul == n_ul ) ? 2 : 3;
	int min_pos = 0;
	for( int pos = 1; pos < size; pos++ )
	{
		if( diffs[pos] < diffs[min_pos] )
		{
			min_pos = pos;
			continue;
		}

		if( diffs[pos] == diffs[min_pos] && candidates_ul[pos] < candidates_ul[min_pos] )
		{
			min_pos = pos;
		}
	}
	
	return candidates[min_pos];
}

int main( int argc, char *argv[] )
{
	if( argc < 2 )
	{
		printf("Usage: %s number\n", argv[0]);
	}

	string n(argv[1]);

	string palindromic = nearestPalindromic( n );
	printf( "%s --> %s\n", argv[1], palindromic.c_str() );
}
