#include <stdio.h>
#include <algorithm>
#include <vector>
#include <math.h>
#include <stdint.h>

template<class RandomAccessIterator>
int nClosest( RandomAccessIterator first, RandomAccessIterator last, int target, int n)
{
	int result = 0;
	if( n == 1 )
	{
		RandomAccessIterator up = std::upper_bound( first, last, target );
		if( up == last )
		{
			result = *( last - 1 );
			goto ret;
		}
		
		if( up == first )
		{
			result = *up;
			goto ret;
		}

		if( abs( target - *up ) < abs( target - *( up - 1 ) ) )
		{
			result = *up;
			goto ret;
		}

		result =*(up - 1);
		goto ret;
	}
	else
	{
		RandomAccessIterator it = first;

		if( last - first <= n )
		{
			for( ; it != last; ++it )
			{
				result += *it;
			}
			goto ret;
		}

		uint32_t min = -1;
		for( ; it != last - n + 1; ++it )
		{
			int target_new = target - *it;
			int closest = nClosest( it + 1, last, target_new, n - 1 );
			uint32_t distance = abs( *it + closest - target );
			if( distance < min )
			{
				min = distance;
				result = *it + closest;
			}
			if( distance == 0 )
			{
				goto ret;
			}
		}
		goto ret;
	}

ret:
	//printf( "[%d, %d] target:%d result:%d n:%d\n", *first, *(last-1), target, result, n );
	return result;
}

int main()
{
//	int array[] = {43,75,-90,47,-49,72,17,-31,-68,-22,-21,-30,65,88,-75,23,97,-61,53,87,-3,33,20,51,-79,43,80,-9,34,-89,-7,93,43,55,-94,29,-32,-49,25,72,-6,35,53,63,6,-62,-96,-83,-73,66,-11,96,-90,-27,78,-51,79,35,-63,85,-82,-15,100,-82,1,-4,-41,-21,11,12,12,72,-82,-22,37,47,-18,61,60,55,22,-6,26,-60,-42,-92,68,45,-1,-26,5,-56,-1,73,92,-55,-20,-43,-56,-15,7,52,35,-90,63,41,-55,-58,46,-84,-92,17,-66,-23,96,-19,-44,77,67,-47,-48,99,51,-25,19,0,-13,-88,-10,-67,14,7,89,-69,-83,86,-70,-66,-38,-50,66,0,-67,-91,-65,83,42,70,-6,52,-21,-86,-87,-44,8,49,-76,86,-3,87,-32,81,-58,37,-55,19,-26,66,-89,-70,-69,37,0,19,-65,38,7,3,1,-96,96,-65,-52,66,5,-3,-87,-16,-96,57,-74,91,46,-79,0,-69,55,49,-96,80,83,73,56,22,58,-44,-40,-45,95,99,-97,-22,-33,-92,-51,62,20,70,90};
	int array[] = {-16,-2,17,-16,3,-7,-13,20,-4,12,5,13,-7,0,5,4,-17,-16,9,1,8,-6,0,-8,16,10,-6,9,-4,12,16,5,19,2,-9,-17,-8,-17,7,-10,2,20,-18,-20,-14,-6,6,17,-10,-8,18,-15,7,-9,13,13,-13,3,18,10,12,16,-6,-19,-6,-13,8,-5,16,5,8,-3,-9,-9,-5,14,14,-13,-18,13,15,-3,9,14,18,-14,-14,1,20,-4,-6,0,3,15,20,20,9,13,-8,-1,-2,6};	
	size_t count = sizeof(array)/sizeof(int);

	std::sort( array, array + count );
	printf("[ ");
	for( int i = 0; i < count - 1; i++ )
	{
		printf("%d, ", array[i] );
	}

	printf("%d ]\n", *(array + count - 1) );
	int n = nClosest( array, array + count, -58, 3 );
	printf( "%d\n", n );
}
