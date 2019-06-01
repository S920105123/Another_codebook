// In this template value is on the edge, everything is 1-based
int N;
vector<Edge> G[MAXN+5];
 
// Preprocess info, setup in dfs1
int heavy[MAXN+5], pa_w[MAXN+5], sz[MAXN+5];
int pa[MAXN+5], dep[MAXN+5], recorder[MAXN+5]; // Which node record edge i.
 
// HLD info, setup in build, 1-based
// pos: position of node i in seg tree.
// head: For NODE i, points to head of the chain.
int chain_no, border, pos[MAXN+5], head[MAXN+5];
 
void dfs1(int v, int p) {
    pa[v] = p;
    sz[v] = 1;
    dep[v] = dep[p] + 1;
    heavy[v] = -1;
    
    for (const Edge &e : G[v]) {
        if (e.to == p) continue;
        dfs1(e.to, v);
        pa_w[e.to] = e.w;
        recorder[e.id] = e.to;
        sz[v] += sz[e.to];
        if (heavy[v] == -1 || sz[e.to] > sz[heavy[v]]) {
            heavy[v] = e.to;
        }
    }
}
 
void build(int v, int chain_head) {
    pos[v] = ++border;
    head[v] = chain_head;
    tree.update(pos[v], pa_w[v], 1, N, 1);
    
    if (heavy[v] != -1) build(heavy[v], chain_head);
    for (const Edge &e : G[v]) {
        if (e.to == pa[v] || e.to == heavy[v]) continue;
        build(e.to, e.to);
    }
}
 
void init_HLD() {
    /* Only init used data, be careful. */
    /* Does not init G!!!!! */
    border = dep[1] = pa_w[1] = 0;
    dfs1(1, 1);
    build(1, 1);
}
 
int query_up(int a, int b) {
    int ans = 0;
    while (head[a] != head[b]) {
    	if (dep[head[a]] < dep[head[b]]) swap(a, b);
    	ans = max(ans, tree.query(pos[head[a]], pos[a], 1, N, 1));
    	a = pa[head[a]];
	}
	
    if (a == b) return ans;
    if (dep[a] < dep[b]) swap(a, b);
    // Query range is pos[b] if value is on node.
    ans = max(ans, tree.query(pos[b] + 1, pos[a], 1, N, 1));
    return ans;
}
