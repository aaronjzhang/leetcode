#include <stdio.h>
#include <algorithm>
#include <vector>

typedef std::vector<int> IntArray;
typedef std::vector< IntArray > DyadicArray;

template<class RandomAccessIterator>
DyadicArray nSum( RandomAccessIterator first, RandomAccessIterator last, int target, int n )
{
	DyadicArray result;
	if( n == 2 )
	{
		RandomAccessIterator it = first;
		for( ; it != last; ++it )
		{
			if( it != first )
			{
				if( std::binary_search( first, it, *it ) )
				{
					continue;
				}
			}

			int target_new = target - *it;
			if( std::binary_search( it+1, last, target_new ) )
			{
				IntArray array;
				array.push_back( *it );
				array.push_back( target_new );
				result.push_back( array );
			}
		}
		return result;
	}
	else
	{
		RandomAccessIterator it = first;
		for( ; it != last; ++it )
		{

			if( it != first )
			{
				if( std::binary_search( first, it, *it ) )
				{
					continue;
				}
			}

			int target_new = target - *it;
			DyadicArray tupleArray = nSum( it + 1, last, target_new, n - 1 );
			if( !tupleArray.empty() )
			{
				DyadicArray::iterator dyadic_array_it = tupleArray.begin();
				for( ; dyadic_array_it != tupleArray.end(); ++dyadic_array_it )
				{
					dyadic_array_it->insert( dyadic_array_it->begin(), *it );
					result.push_back( *dyadic_array_it );
				}
			}
		}
	}

	return result;
}

DyadicArray fourSum( IntArray &num, int target )
{
	DyadicArray result;
	if( num.size() < 4 )
	{
		return result;
	}

	std::sort( num.begin(), num.end() );
	return nSum( num.begin(), num.end(), target, 4 );
}

int main()
{
	int intarray[] = { 1, 0 , -1, 0, -2, 2 };
	IntArray array;
	array.insert( array.begin(), intarray, intarray + 6 );
	
	DyadicArray quadrupltes = fourSum( array, 0 );

	if( quadrupltes.empty() )
	{
		printf("no result!\n");
		return 0;
	}

	DyadicArray::iterator it = quadrupltes.begin();
	for( ; it != quadrupltes.end(); ++it )
	{
		IntArray::iterator IntArray_it = it->begin();
		for( ; IntArray_it != it->end(); ++IntArray_it )
		{
			printf( "%d ", *IntArray_it );
		}

		printf("\n");
	}
}




