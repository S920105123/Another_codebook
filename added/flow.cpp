struct Edge{
    int to,cap,rev;
    Edge(int a,int b,int c) {
    	to = a; cap = b; rev = c;
	}
};
// IMPORETANT, MAXV != MAXN
vector<Edge> G[MAXV];
int V, flow[MAXV];
void init(int _V){
    V = _V;
    for(int i=0; i<=V; i++) G[i].clear();
}
void add_edge(int f,int t,int c, bool directed){
	int s1 = G[f].size(), s2 = G[t].size();
    G[f].push_back(Edge(t,c,s2));
	G[t].push_back(Edge(f,c*!directed,s1));
}
int dfs(int v, int t) {
    if(v == t) return flow[t];
    for(Edge &e : G[v]){
        if(e.cap==0||flow[e.to]!=-1) continue;
        flow[e.to] = min(flow[v], e.cap);
        int f = dfs(e.to, t);
        if (f!=0) {
            e.cap -= f;
            G[e.to][e.rev].cap += f;
            return f;
        }
    }
    return 0;
}
int max_flow(int s,int t){
    int ans = 0, add = 0;
    do {
    	fill(flow,flow+V+1,-1);
    	flow[s] = INF;
    	add = dfs(s, t);
    	ans += add;
	} while (add != 0);
    return ans;
}
