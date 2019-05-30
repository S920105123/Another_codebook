struct AC {
	int N; // link: suffix link, next: DFA link
	int pa[MAXN], dep[MAXN], link[MAXN], next[MAXN][ALPHA];
	int trie[MAXN][ALPHA], tag[MAXN], nocc[MAXN];
	// next and link always exist, others exist iff values != -1.
	// nocc: next occurrence, first node with tag != -1 along suffix link
	
	int new_node(int p) {
		pa[N] = p;
		dep[N] = N == 0 ? 0 : dep[p] + 1;
		link[N] = tag[N] = nocc[N] = -1;
		for (int i = 0; i < ALPHA; i++) {
			next[N][i] = 0;
			trie[N][i] = -1;
		}
		return N++;
	}
	void init() {
		// Init -> add all strings -> build
		N = 0;
		new_node(0);
	}
	void add_string(int id, const string &s) {
		int v = 0;
		for (int i = 0; i < s.size(); i++) {
			int to = s[i] - 'A';
			if (trie[v][to] == -1) {
				trie[v][to] = next[v][to] = new_node(v);
			}
			v = trie[v][to];
		}
		tag[v] = id;
	}
	void build() {
		queue<int> Q;
		link[0] = 0;
		
		Q.push(0);
		while (!Q.empty()) {
			int v = Q.front();
			Q.pop();
			
//			cout << "Link " << v << " is " << link[v] << '\n';
//			for (int i = 0; i < ALPHA; i++) {
//				cout << "Next " << v << " " << (char)(i + 'A') << " is " << next[link[v]][i] << '\n';
//			}
			for (int to = 0; to < ALPHA; to++) {
				if (trie[v][to] != -1) {
					int u = trie[v][to];
					link[u] = v == 0 ? 0 : next[link[v]][to];
					nocc[u] = tag[link[u]] != -1 ? link[u] : nocc[link[u]];
					for (int j = 0; j < ALPHA; j++) {
						if (trie[u][j] == -1) {
							next[u][j] = next[link[u]][j];
						}
					}
					Q.push(u);
				}
			}
		}
	}
} ac;
