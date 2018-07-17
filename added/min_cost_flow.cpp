#include <bits/stdc++.h>
#define IOS ios_base::sync_with_stdio(0); cin.tie(0)
#define MAXV 4000
#define MAXE 8000
#define INF (INT_MAX)/2
#define LL_MAX 0x7FFFFFFFFFFFFFFF
#define pb push_back
#define PII pair<int,int>
#define LL long long
#define sp ' '
#define endl '\n'
using namespace std;

template<class T>
struct Min_cost_flow {
    // 0-based
    struct Edge {
        int fr,to;
		T cap,cost;
    };
    // IMPORETANT
    // MAXV is the number of vertices in the graph
    // Not the N in the problem statement!!
    int V,E;
    vector<Edge> es;
    vector<int> G[MAXV+5];

    void init(int _V) {
        V=_V;
        E=0;
        for (int i=0;i<=V;i++) G[i].clear();
        es.clear();
    }
    int add_edge(int fr, int to, T cap, T cost) {
        es.pb({fr,to,cap,cost});
        es.pb({to,fr,0,-cost});
        G[fr].push_back(E);
        G[to].push_back(E^1);
        E+=2;
        return E-2;
    }
    bool SPFA(int s, int t, T &ans_flow, T &ans_cost) {
		queue<int> que;
        int pre[MAXV+5];
		T dist[MAXV+5],flow[MAXV+5];
        bool inque[MAXV+5];
        for (int i=0;i<=V;i++) {
            dist[i]=INF;
            inque[i]=false;
        }
        dist[s]=0;
        flow[s]=INF;
        inque[s]=true;
        que.push(s);
        while (!que.empty()) {
            int v=que.front(); que.pop();
            inque[v]=false;
            for (int idx : G[v]) {
                Edge &e=es[idx];
                if (e.cap>0 && dist[e.fr]+e.cost<dist[e.to]) {
                    flow[e.to]=min(flow[e.fr],e.cap);
                    dist[e.to]=dist[e.fr]+e.cost;
                    pre[e.to]=idx;
                    if (!inque[e.to]) que.push(e.to),inque[e.to]=true;
                }
            }
        }
        if (dist[t]==INF) return false;
        //if (dist[t]>=0) return false;
        // Add above line -> min cost > max flow (priority)
        // Without        -> max flow > min cost

        int v=t;
        ans_flow+=flow[t];
        ans_cost+=(dist[t]*flow[t]);
        while (v!=s) {
            es[pre[v]].cap-=flow[t];
            es[pre[v]^1].cap+=flow[t];
            v=es[pre[v]].fr;
        }
        return true;
    }
    pair<T,T> min_cost_flow(int s, int t) {
        T ans_flow=0, ans_cost=0;
        while (SPFA(s,t,ans_flow,ans_cost));
        return make_pair(ans_flow,ans_cost);
    }
};
