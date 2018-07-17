struct Kosaraju {
    // Vertex i belong to which SCC, call findSCC to build.
    int SCCof[MAXV+5],V,cnt;
    bool vis[MAXV+5];
    vector<int> *G,*Grev;
    stack<int> stk;
    void dfs(vector<int> *Gcur, int v) {
        for (auto u : Gcur[v]) {
            if (!vis[u]) {
                vis[u]=true;
                dfs(Gcur,u);
            }
        }
        if (Gcur==G) stk.push(v);
        else SCCof[v]=cnt;
    }
    int findSCC(int _V, vector<int> *_G, vector<int> *_Grev) {
        // G: Adjacency list of graph. Grev: Reverse graph of G.
        // No need for init, return # of SCC, 1-based
        V=_V; G=_G; Grev=_Grev;
        for (int i=1;i<=V;i++) vis[i]=0;
        for (int i=1;i<=V;i++) {
            if (!vis[i]) {
                vis[i]=true;
                dfs(G,i);
            }
        }
        cnt=0;
        for (int i=1;i<=V;i++) vis[i]=0;
        while (!stk.empty()) {
            int v=stk.top();
            stk.pop();
            if (!vis[v]) {
                cnt++;
                vis[v]=true;
                dfs(Grev,v);
            }
        }
        return cnt;
    }
    void compress(vector<int> *Gtar) {
        // Pack SCC into one vertex, store into Gtar
        // Call findSCC before this, 1-based
        for (int i=1;i<=V;i++)
            for (auto j : G[i])
                if (SCCof[i]!=SCCof[j])
                    Gtar[SCCof[i]].push_back(SCCof[j]);
    }
};
