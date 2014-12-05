#include <stdio.h>
#include <algorithm>
#include <vector>


typedef std::vector<int> IntArray;
typedef std::vector< IntArray > DyadicArray;

template<class RandomAccessIterator>
DyadicArray nSum( RandomAccessIterator first, RandomAccessIterator last, int target, int n )
{
	DyadicArray result;

	int min = 0;
	int max = 0;;

	for( int i = 0; i < n; ++i )
	{
		min += *(first + i );
		max += *(last - i - 1 );
	}

	if( target < min || target > max )
	{
		return result;
	}

	if( n == 2 )
	{
		printf( "%d, %d, %d \n", *first, *(last-1), target ); 	

		RandomAccessIterator it = first;
		for( ; it != last; ++it )
		{
			int target_new = target - *it;
			if( std::binary_search( it + 1, last, target_new ) )
			{
				if( it != first )
				{
					if( std::binary_search( first, it, *it ) )
					{
						continue;
					}
				}

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
	int intarray[] = { -472,-466,-463,-445,-443,-429,-428,-427,-383,-372,-345,-344,-318,-314,-302,-299,-285,-283,-267,-236,-235,-232,-230,-225,-207,-205,-185,-184,-155,-151,-144,-128,-127,-124,-110,-110,-101,-95,-93,-63,-43,-25,-25,2,4,19,20,28,31,31,40,75,79,92,113,114,119,157,157,161,161,181,191,198,209,215,228,229,235,237,243,254,254,260,274,274,292,303,304,316,320,324,336,368,378,383,389,402,406,446,462,496 };
	IntArray array;
	array.insert( array.begin(), intarray, intarray + sizeof(intarray)/sizeof(int) );
	
	DyadicArray quadrupltes = fourSum( array, 1000);

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




