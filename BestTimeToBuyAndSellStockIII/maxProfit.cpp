#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <vector>
template<class RandomAccessIterator>
int maxprofit( RandomAccessIterator first, RandomAccessIterator last )
{
	size_t count = last - first;
	if( count <= 1 )
	{
		return 0;
	}

	//profits1[i] {i|0,1,2...n} represents max profit of [*first, *(first + 1), *(first+2), ..., *(first+n)] with one transaction. 
	std::vector<int> profits1; 

	//profits2[i] {i|0,1,2,...,n} represents max profit of [*(last-i-1), *(last-i-2),...,*(last-1)] with one transaction.
	std::vector<int> profits2; 

	int min_price = *first;
	int max_price = *(last-1);

	profits1.push_back(0);
	profits2.push_back( 0 );

	int max_profit1 = 0;
	int max_profit2 = 0;
	
	int profit = 0;
	RandomAccessIterator it;
	for( int i = 1; i < count; ++i )
	{
		it = first + i;
		profit = *it - min_price;
		max_profit1 = ( profit > max_profit1 ) ? profit : max_profit1;
		profits1.push_back( max_profit1 );
		min_price = ( *it < min_price ) ? *it : min_price;
	
		it = last - i - 1;
		profit = max_price - *it;
		max_profit2 = ( profit > max_profit2 ) ? profit : max_profit2;
		profits2.push_back( max_profit2 );
		max_price = ( *it > max_price ) ? *it : max_price;
	}

	int	max_profit = 0;
	for( size_t i = 0; i < count; i++ )
	{
		int profit = profits1[i] + profits2[count-i-1];
		max_profit = ( profit > max_profit ) ? profit : max_profit;
	}

	return max_profit;
}

int main()
{
	int a[] = { 1,2,4};
	int max_profit = maxprofit( a, a + 3 );
	printf("%d\n", max_profit);
}

