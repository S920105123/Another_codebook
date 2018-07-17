#include <bits/stdc++.h>
using namespace std;
const int maxn = 100+10;
const int INF = 2147483647;
template<class T>
struct Dinic{
    struct Edge{
        int f,to;
        T c;
        Edge(int _f,int _to,T _c):f(_f),to(_to),c(_c){}
    };

	// IMPORETANT
    // maxn is the number of vertices in the graph
    // Not the N in the problem statement!!
    vector<int> G[maxn];
    vector<Edge> es;
    int level[maxn],st, end, n;
    int cur[maxn];

    void init(int _n){
        n = _n;
        es.clear();
        for(int i=0; i<=n; i++) G[i].clear();
    }

    void addEdge(int f,int t,T c, bool directed=false){
        es.push_back(Edge(f,t,c)); G[f].push_back(es.size()-1);
        es.push_back(Edge(t,f,directed?0:c)); G[t].push_back(es.size()-1);
    }

    bool BFS(int s,int t){
        queue<int> Q;
        for(int i=0; i<=n; i++) level[i] = 0;
        level[s] = 1;
        Q.push(s);
        while(!Q.empty()){
            int x = Q.front(); Q.pop();
            for(int i=0; i<G[x].size(); i++){
                Edge e = es[ G[x][i] ];
                if(e.c==0 || level[e.to]) continue;
                level[e.to] = level[x] + 1;
                Q.push(e.to);
            }
        }
        return level[t]!=0;
    }

    T DFS(int s,T cur_flow){ // can't exceed c
        if(s==end) return cur_flow;

        T ans = 0, temp, total = 0;

        for(int& i=cur[s]; i<G[s].size(); i++){
            Edge &e = es[ G[s][i] ];
            if(e.c==0 || level[e.to]!=level[s]+1) continue;
            temp = DFS(e.to, min(e.c, cur_flow));
            if(temp!=0){
                e.c -= temp;
                es[G[s][i]^1].c += temp;
                cur_flow -= temp;
                total += temp;
                if(cur_flow==0) break;
            }
        }
        return total;
    }

    T maxFlow(int s,int t){
    	/* If you want to incrementally doing maxFlow, 
		   you need to add the result manually.
		   This function returns difference in that case. */
        T ans = 0;
        st = s, end = t;
        while(BFS(s,t)){
            while(true){
                memset(cur, 0, sizeof(cur));
                T temp = DFS(s,INF);
                if(temp==0) break;
                ans += temp;
            }
        }
        return ans;
    }
};

