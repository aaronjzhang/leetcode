#include <vector>
#include <regex>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <list>
#include <unordered_map>
#include <map>
#include <algorithm>

inline uint64_t idx( uint64_t i, uint64_t j ) { return ( i << 32 ) | j; }
using namespace std;
int shortestSubarray(vector<int>& A, int K) {
	uint32_t size= A.size();
	vector<int> S(size+1,0);

	for( uint32_t i = 0; i < size+1; ++i )
	{
		S[i+1] = S[i] + A[i];
	}

	uint32_t res = size + 1;

	//vector<uint32_t> q(size);
	auto &q = A;
	uint32_t begin = 0;
	uint32_t end = 0;
	for( uint32_t i = 0; i < size; ++i )
	{
		while( end > begin && S[i] - S[q[begin]] >= K )
		{
			res = min( res, i - q[begin] );
			++begin;
		}

		while( end > begin && S[i] <= S[q[end-1]] )
		{
			--end;
		}
		q[end++] = i;
	}
	return res > size ? -1 : res;
}

int main( int argc, char *argv[] )
{
	if( argc < 2 )
	{
		printf("Usage: %s input.txt\n", argv[0]);
		return 1;
	}
	ifstream ifs(argv[1]);	
	if( !ifs.is_open() )
	{
		printf("Can't open file %s\n", argv[1]);
		return 1;
	}
	
	char line[1024*1024] = {0};
	ifs.getline( line, sizeof(line) );
	char *str = line + 1;		
	char *end = NULL;
	vector<int> A;
	while( ( end = index( str, ',' ) ) != NULL )
	{
		*end = 0;
		int n = atoi( str );
		A.push_back( n );
		str = end + 1;
	}
	str[strlen(str)-1] = 0;
	A.push_back( atoi(str) );

	ifs.getline( line, 100 );
	int K = atoi( line );

	int len = shortestSubarray( A, K );
	printf("shortest = %d\n", len );
}
