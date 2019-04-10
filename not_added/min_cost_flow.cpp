// 0-based
#define fi first
#define se second
struct Edge {
    int to,cap;
	int cost,rev;
};
static const int MAXV = 605;

int V,E;
vector<Edge> G[MAXV];

void init(int _V) {
    V=_V;
    for (int i=0;i<=V;i++) G[i].clear();
}
void add_edge(int fr, int to, int cap, int cost) {
	int a = G[fr].size(), b = G[to].size();
    G[fr].push_back({to,cap,cost,b});
    G[to].push_back({fr,0,-cost,a});
}
bool SPFA(int s, int t, int &ans_flow, int &ans_cost) {
	queue<int> que;
    PII pre[MAXV];
	int flow[MAXV], dist[MAXV];
	bool inque[MAXV];
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
        for (int i=0;i<G[v].size();i++) {
        	const Edge &e = G[v][i];
            if (e.cap>0 && dist[v]+e.cost<dist[e.to]) {
                flow[e.to]=min(flow[v],e.cap);
                dist[e.to]=dist[v]+e.cost;
                pre[e.to]={v,i};
                if (!inque[e.to]) que.push(e.to),inque[e.to]=true;
            }
        }
    }
    if (dist[t]==INF) return false;
    //if (dist[t]>=0) return false;
    // Add above line -> min cost > max flow (priority)
    // Without        -> max flow > min cost

    int v=t,f=flow[t];
    ans_flow+=flow[t];
    ans_cost+=(dist[t]*flow[t]);
    while (v!=s) {
    	Edge &e = G[pre[v].fi][pre[v].se];
        e.cap-=f;
        G[v][e.rev].cap+=f;
        v=pre[v].fi;
    }
    return true;
}
pair<int,int> min_cost_flow(int s, int t) {
    int ans_flow=0, ans_cost=0;
    while (SPFA(s,t,ans_flow,ans_cost));
    return make_pair(ans_flow,ans_cost);
}
