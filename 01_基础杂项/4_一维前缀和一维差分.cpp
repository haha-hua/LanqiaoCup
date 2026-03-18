#include<iostream>


using namespace std;


void function1()
{
	const int N = 100005;
	int n,m,x;
	int prefixsum[N] = {};      //前缀和数组，prefixsum[i]表示前i个数的和
	
	cin >> n;
	for(int i = 1; i <= n; ++i)
	{
		cin >> x;
		prefixsum[i] = prefixsum[i - 1] + x;    //初始化
	}
	
	cin >> m;
	
	int l = 0,r = 0;
	for(int i = 1; i <= m; ++i)
	{
		cin >> l >> r;          
		cout << prefixsum[r] - prefixsum[l - 1] << '\n';        
        //[l,r]区间和 = prefixsum[r] - prefixsum[l-1]
	}
	
	return ;
}

//function2需要的参数和变量
const int N = 5000005;
int n,p;
int arr[N] = {};
int d[N] = {};	        //差分数组，d[i]表示arr[i]与arr[i-1]的差值，即d[i] = arr[i] - arr[i-1]
void function2()
{
	cin >> n >> p;
	
	for(int i = 1; i <= n; ++i) cin >> arr[i];
	
	int l,r,val;
	for(int i = 1; i <= p; ++i)
	{
		cin >> l >> r >> val;
        //差分数组的更新：对于区间[l,r]加上val，相当于在d[l]加上val，在d[r+1]减去val
        //这样在后续计算前缀和时，区间[l,r]的每个元素都会增加val，而其他元素不受影响
		d[l] += val;
		d[r + 1] -= val;
	}
	
	int minn = 1e9;
	int sum = 0;
	for(int i = 1; i <= n; ++i)
	{
        //计算前缀和：sum表示当前元素的增量，初始为0，每次加上d[i]，就得到了arr[i]的最终值
		sum += d[i];
		minn = min(minn,sum + arr[i]);
	}
	
	cout << minn << endl;
	return ;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	function1(); //解决一维前缀和问题
	
	function2(); //解决一维差分问题
	
	return 0;
}