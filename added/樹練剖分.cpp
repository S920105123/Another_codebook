vector<int> G[maxn];
int pa[maxn], maxson[maxn], son[maxn];
int dep[maxn];
int link[maxn], linkpa[maxn];
int linkcnt = 0;
void dfs(int x,int p){
    pa[x] = p;
    dep[x] = dep[p]+1;
    son[x] = 1, maxson[x] = -1;
    for(int i=0; i<G[x].size(); i++)if(G[x][i]!=p){
        dfs(G[x][i], x);
        son[x] += son[ G[x][i] ];
        if(maxson[x]==-1 || son[G[x][i]]>son[maxson[x]]) maxson[x] = G[x][i];
    }
}
void build_link(int x, int plink){
    link[x] = ++linkcnt;
    linkpa[x] = plink;

    if(maxson[x]!=-1) build_link(maxson[x], plink);
    for(int i=0; i<G[x].size(); i++){
        int u = G[x][i];
        if(u==maxson[x] || u==pa[x] ) continue;
        build_link(u, u);
    }
}
ll cal(int a,int b,int type){

    ll ans = 0;
    int ta = linkpa[a], tb = linkpa[b];
    while(linkpa[a]!=linkpa[b]){
        int A, B;

        if(dep[ ta ] <= dep[ tb ]){
            swap(a , b);
            swap(ta, tb);
        }
        A = link[ta];
        B = link[a];

            // if(type==1) T.add(1, n, 1, A, B);
            // else ans += T.query(1, n, 1, A, B);
        a = pa[linkpa[a]];
        ta = linkpa[a];
    }

    if(a==b) return ans;
    if(dep[a] > dep[b]) swap(a, b);

    int A = link[a] + 1, B = link[b];
        // if(type==1) T.add(1, n, 1, link[a]+1, link[b]);
        // else ans += T.query(1, n, 1, link[a]+1, link[b]);
    if(type==0) return ans;
}
