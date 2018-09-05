思路: 动态规划

假设有一组points {p1,p2,p3...pn}, 我们用二维数组max_points保存直线(pj,pi)的max points, j < i, max_points[j][i]表示直线(pj,pi)上的max points.
现在增加一个点pn+1, 直线会增加{(pi,pn+1) | i = 0,1,2...n-1}, 现在我们就需要计算这些直线的max points.
对于任意一个新增的直线 (pi,pn+1), 如果它和某直线(pj,pi)共线，那么max_points[i][n+1] = max_points[j][i] + 1. 因此遍历点(p0,p1,p2...pi-1)就可以计算出max_points[i][n+1]，同样的方法计算其他点到pn+1的max_points.
如果没有重复的点，上面非常完美, 然而不幸的是，这其中允许重复的点。
假设pj和pi重复，pj,pi,pn+1三个点必然属于同一直线, 因此不能简单的认为max_points[j][i]也属于max_points[i][n+1],它必须找到其他的一个点pk(k<j),pk!=pj,pk,pi,pn+1属于同一直线,max_points[i][n+1]=max_points[k][i]+前面重复点的个数。如果没有找到pk，max_points[i][n+1]应该就要等于2(pi和pn+1)+pi重复点的个数.
