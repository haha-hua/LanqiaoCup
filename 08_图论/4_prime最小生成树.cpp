//题目链接:https://www.luogu.com.cn/problem/P3366(P3366 【模板】最小生成树)

#include<iostream>
#include<queue>
#include<cstring>

using namespace std;

const int N = 5005;
const int M = 400006;

int n,m;
int count_e,head[N];
struct Edge
{
	int to;
	int nxt;
	int w;
}edges[M];

struct Node
{
	int s;
	int u;
	
	bool operator<(const Node& other) const
	{
		return s > other.s;
	}
	
};
bool ins[N];

void addEdge(int u,int v,int w)
{
	edges[count_e] = {v,head[u],w};
	head[u] = count_e++;
	return ;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	memset(head,-1,sizeof(head));
	cin >> n >> m;	
	
	int u,v,w;
	for(int i = 1; i <= m; ++i)
	{
		cin >> u >> v >> w;
		addEdge(u,v,w);
		addEdge(v,u,w);
	}
	
	int cnt = 0,ans = 0; 
	priority_queue<Node> que;   //s,u
	que.push({0,1});            //待选的边的权重，待选的点
	
	while(que.empty() == false && cnt < n)  //当优先队列不空且生成树的点数小于n时，继续循环
	{
		Node cur = que.top();
		que.pop();
		
		if(ins[cur.u] == true) continue;        //如果这个点已经在生成树中，跳过
		ins[cur.u] = true;                      //将这个点加入生成树
		ans += cur.s;
		++cnt;                          //加入生成树的点数加1
        
        //将这个点的所有邻边加入优先队列
		for(int k = head[cur.u]; k != -1; k = edges[k].nxt)
		{
			int v = edges[k].to;
            //如果这个点不在生成树中，将这个边加入优先队列
			if(ins[v] == false)que.push({edges[k].w,v});
		}
	}
	
	
	if(cnt != n) cout << "orz\n";
	else cout << ans << endl;
	
	return 0;
}