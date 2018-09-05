#include <vector>
#include <stdio.h>
#include <set>
#include <regex>

using namespace std;
struct Point{
	int x;
	int y;
	Point(): x(0),y(0){}
	Point( int a, int b):x(a),y(b){}
};

int maxPoints2( vector<Point>& points )
{
	if( points.size() == 0 ) return 0;
	
	vector< vector<int> > max_points( points.size(), vector<int>(points.size()) );
	max_points[0][0] = 1;
	int max = 1;
	for( size_t i = 1; i < points.size(); i++ )
	{
		for( int j = i - 1; j >= 0; j-- )
		{
			auto &cur = max_points[j][i];	
			long a = points[i].y - points[j].y;
			long b = points[j].x - points[i].x;
			long c = -1 * ( a * points[i].x + b * points[i].y );
			cur = max_points[j][j] + 1;
			int dup=0;
			int kj_max = cur;
			bool is_shot = false;
			int k = j - 1;
			for( ; k >= 0; k-- )
			{
				if( a * points[k].x + b * points[k].y + c == 0 )
				{
					if( points[k].x == points[j].x && 
							points[k].y == points[j].y )
					{
						dup++;
						continue;
					}
					int c = max_points[k][j] + 1 + dup;
					if( kj_max < c )
					{
						kj_max = c;
					}
					is_shot = true;
				}
			}
			cur = kj_max + ( is_shot ? 0 : dup);
			if( max < cur )
			{
				max = cur;
			}
		}

		max_points[i][i] = 1;
	}
	
	return max;
}
int main( int argc, char *argv[] )
{
	if( argc < 2 )
	{
		printf("usage: %s input.txt\n", argv[0]);
		return 1;
	}
	FILE *file = fopen( argv[1], "r" );		
	if( file == NULL )
	{
		printf("can't open input.txt\n");
		return 1;
	}

	char buf[1024*10+1] = {0};
	fread( buf, 1, 1024*10, file );

	printf( "%s\n", buf );
	vector<Point> points;
	regex e("\\[(-?\\d+),(-?\\d+)\\]");	
	smatch m;
	string s = buf;
	while( regex_search( s, m, e ) )
	{
		Point point( atoi( m[1].str().c_str() ), atoi( m[2].str().c_str()) );
		s = m.suffix().str();
		points.push_back( point );
	}

	int max = maxPoints2( points );
	printf("max points: %d\n", max );
	return 0;
}
