#include<iostream>


using namespace std;

using ll = long long;

const int N = 1005;
ll arr[N][N];
ll prefixsum[N][N];     //前缀和数组prefixsum[i][j]表示以(1,1)为左上角，(i,j)为右下角的矩形区域内所有元素的和
void function1()
{
	int n,m,c;
	cin >> n >> m >> c;
	for(int i = 1; i <= n; ++i)
	{
		for(int j = 1; j <= m; ++j)
		{
			cin >> arr[i][j];
            //根据容斥原理计算前缀和：
            //prefixsum[i][j] = prefixsum[i-1][j] + prefixsum[i][j-1] - prefixsum[i-1][j-1] + arr[i][j]
			prefixsum[i][j] = prefixsum[i - 1][j] + prefixsum[i][j - 1] - prefixsum[i - 1][j - 1] + arr[i][j];
		}
	}
	
	ll maxn = -1e18;
	int x = -1,y = -1;
	for(int i = 1; i + c - 1 <= n; ++i)
	{
		for(int j = 1; j + c - 1 <= m; ++j)
		{
			if(prefixsum[i + c - 1][j + c - 1] - prefixsum[i - 1][j + c - 1] - prefixsum[i + c - 1][j - 1] + prefixsum[i - 1][j - 1] > maxn)
			{
                //根据容斥原理:
                //c*c的区域和 = prefixsum[i+c-1][j+c-1] - prefixsum[i-1][j+c-1] - prefixsum[i+c-1][j-1] + prefixsum[i-1][j-1]
				maxn = prefixsum[i + c - 1][j + c - 1] - prefixsum[i - 1][j + c - 1] - prefixsum[i + c - 1][j - 1] + prefixsum[i - 1][j - 1];
				x = i,y = j;
			}
		}
	}
	cout << x << ' ' << y << endl;
	return ;
}


//二维差分数组
//d[i][j]表示arr[i][j]与arr[i-1][j]、arr[i][j-1]、arr[i-1][j-1]的关系
//即d[i][j] = arr[i][j] - arr[i-1][j] - arr[i][j-1] + arr[i-1][j-1]
int d[N][N];  
int res[N][N];  
void function2()
{
	int n,m;
	cin >> n >> m;
	
	int x1,y1,x2,y2;
	for(int i = 1; i <= m; ++i)
	{
		cin >> x1 >> y1 >> x2 >> y2;
		d[x1][y1] += 1;
		d[x1][y2 + 1] -= 1;
		d[x2 + 1][y1] -= 1;
		d[x2 + 1][y2 + 1] += 1; 
	} 
	
	for(int i = 1; i <= n; ++i)
	{
		for(int j = 1; j <= n; ++j)
		{
			res[i][j] = d[i][j] + res[i - 1][j] + res[i][j - 1] - res[i - 1][j - 1];
			cout << res[i][j] << ' '; 
		}
		cout << '\n';
	}
	
	return ;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	function1();        //二维前缀和问题

    function2();        //二维差分问题

	return 0;
}