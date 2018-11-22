#include <string>
#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <bitset>
#include <cmath>
#include <cctype>
#include <vector>
#include <algorithm>

using namespace std;

int strongPasswordChecker( string &s )
{
	size_t size = s.length();
	printf("size = %ld  ", size );
	vector<int> repeats;	
	int replacement = 3;
	bool has_lower = false;
	bool has_upper = false;
	bool has_digit = false;

	int repeat = 1;
	for( size_t i = 0; i < size; ++i )
	{
		if( !has_lower && islower( s[i] ) )
		{
			has_lower = true;
			--replacement;
		}

		if( !has_upper && isupper( s[i] ) )
		{
			has_upper = true;
			--replacement;
		}

		if( !has_digit && isdigit( s[i] ) )
		{
			has_digit = true;
			--replacement;
		}

		if( i > 0 && s[i] == s[i-1]  )
		{
			++repeat;
			continue;
		}
		if( repeat > 2 )
		{
			repeats.push_back(repeat);
		}
		repeat = 1;
	}
	
	if( repeat > 2 )
	{
		repeats.push_back(repeat);
	}
	if( replacement == 0 && repeats.size() == 0 && size >= 6 && size <= 20 )
	{
		return 0;
	}

	if( size < 6 )
	{
		int insert_count = 6 - size;
		return max( insert_count, replacement );	
	}
	
	int min_changes = 0;
	int remove_count = size - 20;
	if( size > 20 )
	{
		sort( repeats.begin(), repeats.end() );
		while( !repeats.empty() )
		{
			if( replacement > 0 )
			{
				int q = repeats.back() / 3;
				if( replacement >= q )
				{
					min_changes += q;
					replacement -= q;
					repeats.pop_back();
				}
				else
				{
					min_changes += replacement;
					repeats.back() -= 3 * replacement;
					replacement = 0;
				}
				continue;
			}

			if( remove_count == 0 )
			{
				min_changes += repeats.back() / 3;
				repeats.pop_back();
				continue;
			}
		
			for( int i = 0; i < 3; i++ )
			{
				for( auto it = repeats.begin(); it != repeats.end(); )
				{
					if( remove_count == 0 )
					{
						break;
					}

					if( *it % 3 == i )
					{
						if( remove_count >= i+1 )
						{
							*it -= (i+1);
							remove_count -= (i+1);
							min_changes += (i+1);
						}
						else
						{
							*it -= remove_count;
							min_changes += remove_count;
							remove_count = 0;
						}
					}

					if( *it < 3 )
					{
						it = repeats.erase( it );
						continue;
					}
					++it;
				}
			}
		}

		min_changes += ( replacement + remove_count );
		return min_changes;
	}

	int all_repeat = 0;
	for( auto repeat : repeats )
	{
		all_repeat += repeat / 3;
	}

	return max( all_repeat, replacement );
}

int main( int argc, char *argv[] )
{
	if( argc < 2 )
	{
		return 1;
	}

	printf("%s\n", argv[1]);
	string s(argv[1]);
	printf("%d\n", strongPasswordChecker( s ) );
}
