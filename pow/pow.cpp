class Solution {
public:
	double pow(double x, int n) {
		double result = 1.0;
		if ( n == 0 )
		{
			return result;
		}
		int m = ( n > 0 ) ? n : -1 * n;
		int sign = ( ( x < 0.0 ) && ( m % 2 ) ) ? -1 : 1;
		while( m ){
			double y = x  < 0.0 ?  -1.0 * x : x;
			int i = 1;
			for( ; ( 1 << i ) <= m; ++i ){
				y = y * y;
				if( y == 1.0 || y <= 1.0e-1023 || y >= 1.79e+308 )
				{
					break;
				}
			}
			m = m - ( 1 << ( i - 1 ) );
			result *= y;
			if ( result == 1.0 || result <= 1.0e-1023 || result >= 1.79e+308 )
			{
				break;
			}
		}
		return sign * ( ( n > 0 ) ? result : 1 / result );
	}
};
