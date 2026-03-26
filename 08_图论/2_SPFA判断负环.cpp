//https://www.luogu.com.cn/problem/P3385(P3385 【模板】负环)

#include<iostream>
#include<queue>
#include<cstring>


using namespace std;

const int N = 3005;

int n,m,count_e;
int head[N];
struct Edge
{
	int to;
	int nxt;
	int w;
}edges[8000];

bool inq[N];
int cnt[N],dist[N];

void addEdge(int u,int v,int w)
{
	edges[count_e] = {v,head[u],w};
	head[u] = count_e++;
	return ;
}

bool SPFA(int s)
{
    //初始化距离数组
	memset(dist,0x3f3f3f3f,sizeof(dist));
	queue<int> que;
	que.push(s);    //将源点入队
	
    //初始化源点的距离为0
	dist[s] = 0;
	inq[s] = true;
	cnt[s] = 0;     //经过的边数

	while(que.empty() == false)
	{
		int u = que.front();
		que.pop();
		
		inq[u] = false;
		
		for(int k = head[u]; k != -1; k = edges[k].nxt)
		{
			int v = edges[k].to;
			if(dist[v] > dist[u] + edges[k].w)
			{
				dist[v] = dist[u] + edges[k].w;
				//更新边数
				cnt[v] = cnt[u] + 1;
				if(cnt[v] >= n) return true;
				
                //如果v不在队列中，入队
				if(inq[v] == false)
				{
					inq[v] = true;
					que.push(v);
				}
				
			}
		}	
	}
	
	return false;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	int T;
	cin >> T;
	
	while(T-- > 0)
	{
        //初始化图
		memset(head,-1,sizeof(head));
		memset(cnt,0,sizeof(cnt));
		memset(inq,0,sizeof(inq));	
		count_e = 0;
		
		cin >> n >> m;
		int u,v,w;
		for(int i = 1; i <= m; ++i)
		{
			cin >> u >> v >> w;
			if(w < 0) addEdge(u,v,w);
			else
			{
				addEdge(u,v,w);
				addEdge(v,u,w);
			} 
		} 
		
		//判断负环
		if(SPFA(1) == true) cout << "YES\n";
		else cout << "NO\n";
 		
	}
	
	
	return 0;
} 