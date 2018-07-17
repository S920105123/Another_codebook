const int maxn = 100;
const int maxkind = 26;
const int maxlen = 100;
const int maxsize = maxn*maxlen + 10;
struct AC{
    int ch[maxsize][maxkind], f[maxsize], last[maxsize], val[maxsize];
    int root, memid;
    AC(){ clear(): }
    void newNode(){
        memset(ch[memid], 0, sizeof(ch[memid]));
        f[memid] = last[memid] = val[memid] = 0;
        return memid++;
    }
    void clear(){
        memid = 0;
        root = newNode();
    }
    void insert(const char* s,int v){
        int tmp =  root;
        for(int i=0; s[i]; i++){
            int id(ID[s[i]]);
            if(!ch[tmp][id]) ch[tmp][id] = newNode();
            tmp = ch[tmp][id];
        }
        val[tmp] = v;
    }
    void getfail(){
        queue<int> Q;
        f[root] = 0;
        for(int i=0; i<maxkind; i++) if(ch[root][i]){
            int u = ch[root][i];
            f[u] = last[u] = 0;
            Q.push(u);
        }
        while(!Q.empty()){
            int x = Q.front(); Q.pop();
            for(int i=0; i<maxkind; i++) if(ch[x][i]){
                int tmp = f[x], u = ch[x][i];
                while(tmp && !ch[tmp][i]) tmp = f[tmp];
                f[u] = ch[tmp][i];
                last[u] = val[f[u]]? f[u]:last[f[u]];
                Q.push(u);
            }
        }
    }
    void find(const char *s){
        int tmp = root;
        for(int i=0; s[i]; i++){
            int id = ID(s[i]);
            while(tmp && !ch[tmp][id]) tmp = f[tmp];
            tmp = ch[tmp][id];
            if(val[id])// find
            if(last[id]) //find
        }
    }
};
