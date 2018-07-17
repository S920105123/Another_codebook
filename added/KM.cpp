template<class T>
struct KM_n_3
{
    T G[maxn][maxn];
    T lx[maxn], ly[maxn], y_slack[maxn];
    int x_match[maxn], y_match[maxn];
    int px[maxn], py[maxn];  
    int y_par[maxn]; 
    int n;

    void toggle(int y){
        x_match[py[y]] = y;
        y_match[y] = py[y];
        if(px[y_match[y]]!=-2) toggle(px[y_match[y]]);
    }

    /* n = |L| = |R|, id of nodes start with 1*/
    int init(int _n){
        n = _n;
        for(int i=0; i<=n; i++){
            for(int j=0; j<=n; j++)
                G[i][j] = 0;
        }
    }

    int add_edge(int a, int b, T c){ G[a][b] = c; }

    int dfs(int x){
        for(int y=1; y<=n; y++){
            if(py[y]) continue;
            T slack = lx[x] + ly[y] - G[x][y];
            if(slack==0){
                py[y] = x;
                if(y_match[y]==0){
                    toggle(y);
                    return true;
                }
                else{
                    if(px[y_match[y]]) continue;
                    px[ y_match[y] ] = y;
                    if(dfs(y_match[y])) return 1;
                }
            }
            else if(y_slack[y] > slack){
                y_slack[y] = slack;
                y_par[y] = x;
            }
        }
        return false;
    }

    void update(vector<int>& Y){
        Y.clear();
        T d = INF;
        for(int i=1; i<=n; i++) if(!py[i]) d = min(d, y_slack[i]);

        for(int i=1; i<=n; i++){
            if(px[i]) lx[i] -= d;
            if(py[i]) ly[i] += d;
            else{
                y_slack[i] -= d;
                if(y_slack[i]==0) Y.push_back(i);
            }
        }
    }

    T km(){
        for(int i=0; i<=n; i++) x_match[i] = y_match[i] = 0;
        for(int i=1; i<=n; i++){
            lx[i] = G[i][1], ly[i] = 0;
            for(int j=1; j<=n; j++)
                lx[i] = max(lx[i], G[i][j]);
        }

        for(int i=1; i<=n; i++){
            for(int j=0; j<=n; j++) y_slack[j] = INF;
            for(int j=0; j<=n; j++) px[j] = py[j] = 0;
            px[i] = -2;
            if(dfs(i)) continue;

            // adjust labeling until finding an augmenting path
            bool find = false;
            while(!find){
                vector<int> Y;
                update(Y);
                for(auto y:Y){
                    if(find) break;
                    py[y] = y_par[y];
                    if(y_match[y]==0){
                        toggle(y);
                        find = true;
                    }
                    else{
                        px[ y_match[y] ] = y;
                        if(dfs(y_match[y])) find = true;
                    }
                }
            }
        }

        T ans = 0;
        for(int x=1; x<=n; x++) ans += G[x][x_match[x]];
        return ans;
    }

    void dump(vector<pair<int,int>>& ans){
        for(int i=1; i<=n; i++) if(G[i][x_match[i]]!=0){
            ans.push_back({i, x_match[i]});
        }
    }
} 
