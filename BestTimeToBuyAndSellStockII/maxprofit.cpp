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

	int profit = 0;

	RandomAccessIterator it = first + 1;
	int buy = *first;
	bool selling = false;
	for( ; it != last; ++it )
	{
		if( !selling )
		{
			if( *it < buy )
			{
				buy = *it;
			}
			else
			{
				selling = true;
				profit = *it - buy;
			}
		}
		else
		{
			int new_profit = *it - buy;
			if( new_profit > profit )
			{
				profit = new_profit;
			}
			else
			{
				return profit + maxProfit( it, last );
			}
		}
	}

	return profit;
}
