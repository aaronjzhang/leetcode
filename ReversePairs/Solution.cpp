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
#include <bitset>
#include <iterator>
using namespace std;


vector<int> aux;
template<typename RandomAccessIt>
inline int merge( RandomAccessIt begin, RandomAccessIt mid, RandomAccessIt end )
{
	int count = 0;
	auto it = begin;
	auto rb = mid;
	for( ; it < mid && rb < end; )
	{
		if( *it > *rb * 2L )
		{
			count += (mid - it);
			++rb;
			continue;
		}
		++it;
	}
	
	it = begin;
	rb = mid;
	auto aux_it = aux.begin();
	while( it < mid && rb < end )
	{
		if( *it < *rb )
		{
			*aux_it++ = *it++;
		}
		else
		{
			*aux_it++ = *rb++;
		}
	}

	while( it != mid )
	{
		*aux_it++ = *it++;	
	}
	while( rb != end )
	{
		*aux_it++ = *rb++;
	}
	int size = end - begin;
	copy( aux.begin(), aux.begin() + size, begin ); 
	return count;
}

template<typename RandomAccessIt>
inline int reversePairs( RandomAccessIt begin, RandomAccessIt end )
{
	int size = distance( begin, end );
	if( size == 1 )
	{
		return 0;
	}

	int count = 0;
	auto mid = begin + ( size >> 1 );
	count += reversePairs( begin, mid );	
	count += reversePairs( mid, end );
	count += merge( begin, mid, end );
	return count;
}

int reversePairs2( vector<int> nums )
{
	if( nums.size() < 1 )
	{
		return 0;
	}
	aux.resize(nums.size(),0);
	return reversePairs( nums.begin(), nums.end() );
}

int reversePairs( vector<int> &nums )
{
	int size = nums.size();
	int count = 0;
	if( size < 2 )
	{
		return count;
	}
	vector<int64_t> post_nums;
	post_nums.push_back( nums.back()*2L );
	for( int i = size - 2; i >= 0; --i )
	{
		auto lower = lower_bound( post_nums.begin(), post_nums.end(), nums[i] );	
		count += ( lower - post_nums.begin() );
		auto it = lower_bound( post_nums.begin(), post_nums.end(), 2L*nums[i] );
		post_nums.insert( it, 2L*nums[i] );
		
	}
	return count;
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
	vector<int> nums;
	while( ( end = index( str, ',' ) ) != NULL )
	{
		*end = 0;
		int n = atoi( str );
		nums.push_back( n );
		str = end + 1;
	}
	str[strlen(str)-1] = 0;
	nums.push_back( atoi(str) );
	ifs.close();

	int size = 0;
	if( argc > 2 )
	{
		size = reversePairs2( nums );
	}
	else
	{
		size = reversePairs( nums );
	}
	printf( "%d \n", size );
}
