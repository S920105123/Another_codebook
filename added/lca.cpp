// adj[u] : adjacency list of u
// par[u][i] : (2^i)-th parent pf u
int LOG = 20;
int time = 0;
void dfs(int u, int p) {
    par[u][0] = p;
    timer_in[u] = ++timer;
    for (int v : adj[u]) if (v!=p) dfs(v, u);
    time_out[u] = ++timer;
}
bool anc(int x, int y) {
     return time_in[x] <= time_in[y]
            && time_out[y] <= time_out[x];
}
int lca(int x, int y) {
    if (anc(y, x)) return y;
    for (int j = LOG; j >= 0; j--) {
        if (!anc(par[y][j], x)) y = par[y][j];
    }
    return par[y][0];
}
int main() {
    int root = 1;// set root node
    dfs(root, root);

    for (int j = 1; j <= LOG; j++)
        for (int i = 1; i <= n; i++)
            pair[i][j] = par[par[i][j - 1]][j - 1];
    return 0;
}
