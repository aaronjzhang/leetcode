#include <stdio.h>
#include <algorithm>
#include <vector>
#include <math.h>
#include <stdint.h>

template<class RandomAccessIterator>
int nClosest( RandomAccessIterator first, RandomAccessIterator last, int target, int n)
{
	if( n == 1 )
	{
		RandomAccessIterator up = std::upper_bound( first, last, target );
		if( up == last )
		{
			return *( last - 1 );
		}
		
		if( abs( target - *up ) < abs( target - *( up - 1 ) ) )
		{
			return *up;
		}

		return *(up - 1);
	}
	else
	{
		RandomAccessIterator it = first;
		int result = 0;

		/**
		if( last - first <= n )
		{
			for( ; it != last; ++it )
			{
				result += *it;
			}
			return result;
		}
		*/

		uint32_t min = -1;
		for( ; it != last; ++it )
		{
			int target_new = target - *it;
			int closest = nClosest( it + 1, last, target_new, n - 1 );
			uint32_t distance = abs( *it + closest - target );
			if( distance < min )
			{
				min = distance;
				result = *it + closest;
			}
		}

		for( it = first; it != last; ++it )
		{
			printf("%d ", *it );
		}
		printf("target:%d result:%d n:%d\n", target, result, n );
		return result;
	}
}

int main()
{
	int array[] = { -4, -1, 1, 2 };
	int n = nClosest( array, array + sizeof(array)/sizeof(int), 1, 3 );
	printf( "%d\n", n );
}
