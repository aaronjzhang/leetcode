#include <stdio.h>
#include <algorithm>
#include <vector>

template<class RandomAccessIterator>
int maxProfit( RandomAccessIterator first, RandomAccessIterator last )
{
	if( last - first <= 1 )
	{
		return 0;
	}

	int max_profit = 0;

	RandomAccessIterator it = first + 1;
	int min_price = *first;
	for( ; it != last; ++it )
	{
		int new_profit = *it - min_price;
		if( new_profit > max_profit )
		{
			max_profit = new_profit;
			continue;
		}
		if( *it < min_price )
		{
			min_price = *it;
		}
	}

	return max_profit;
}
