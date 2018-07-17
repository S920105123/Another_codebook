/* 0-based or 1-based doesn't matter */
int N1, N2;
vector<int> G[MAXN1]; // For left subgraph only
int mat1[MAXN1], mat2[MAXN2], match;
bool vis1[MAXN1], vis2[MAXN2];
void init(int _N1, int _N2) {
	N1 = _N1;
	N2 = _N2;
	match = 0;
	for (int i = 0; i <= N2; i++) mat2[i] = -1;
	for (int i = 0; i <= N1; i++) {
		G[i].clear();
		mat1[i] = -1;
	}
}
bool dfs(int v) {
	vis1[v] = true;
	for (int i : G[v]) {
		if (vis2[i] || i == mat1[v]) continue;
		vis2[i] = true;
		if (mat2[i] == -1 || dfs(mat2[i])) {
			mat1[v] = i;
			mat2[i] = v;
			return true;
		}
	}
	return false;
}
int max_match() {
	bool update = true;
	while (update) {
		update = false;
		fill(vis1, vis1+N1+1, false);
		fill(vis2, vis2+N2+1, false);
		for (int i=0; i<=N1; i++) {
			if (!vis1[i] && mat1[i] == -1 && dfs(i)) {
				match++;
				update = true;
			}
		}
	}
	return match;
}
