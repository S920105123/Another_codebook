struct Blossom {
	#define MAXN 505 // Max solvable problem, DON'T CHANGE
	// 1-based, IMPORTANT
	vector<int> g[MAXN];
	int parent[MAXN], match[MAXN], belong[MAXN], state[MAXN];
	int n;
	int lca(int u, int v) {
		static int cases = 0, used[MAXN] = {};
		for (++cases; ; swap(u, v)) {
			if (u == 0)
				continue;
			if (used[u] == cases)
				return u;
			used[u] = cases;
			u = belong[parent[match[u]]];
		}
	}
	void flower(int u, int v, int l, queue<int> &q) {
		while (belong[u] != l) {
			parent[u] = v, v = match[u];
			if (state[v] == 1)
				q.push(v), state[v] = 0;
			belong[u] = belong[v] = l, u = parent[v];
		}
	}
	bool bfs(int u) {
		for (int i = 0; i <= n; i++)
			belong[i] = i;
		memset(state, -1, sizeof(state[0])*(n+1));
		queue<int> q;
		q.push(u), state[u] = 0;
		while (!q.empty()) {
			u = q.front(), q.pop();
			for (int i = 0; i < g[u].size(); i++) {
				int v = g[u][i];
				if (state[v] == -1) {
					parent[v] = u, state[v] = 1;
					if (match[v] == 0) {
						for (int prev; u; v = prev, u = parent[v]) {
							prev = match[u];
							match[u] = v;
							match[v] = u;
						}
						return 1;
					}
					q.push(match[v]), state[match[v]] = 0;
				} else if (state[v] == 0 && belong[v] != belong[u]) {
					int l = lca(u, v);
					flower(v, u, l, q);
					flower(u, v, l, q);
				}
			}
		}
		return 0;
	}
	int blossom() {
		memset(parent, 0, sizeof(parent[0])*(n+1));
		memset(match, 0, sizeof(match[0])*(n+1));
		int ret = 0;
		for (int i = 1; i <= n; i++) {
			if (match[i] == 0 && bfs(i))
				ret++;
		}
		return ret;
	}
	void addEdge(int x, int y) {
		g[x].push_back(y), g[y].push_back(x);
	}
	void init(int _n) {
		n = _n;
		for (int i = 0; i <= n; i++)
			g[i].clear();
	}
} algo;
