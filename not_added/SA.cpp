/* rank: inverse sa */
/* MAXL: Maximum length of string, lcp[i]: LCP(sa[i], sa[i-1]) */
string text;
int sa[MAXL], isa[MAXL], lcp[MAXL], cnt[MAXL+ALPHA];
void build(const vector<int> &_text) {
	text = _text + '\0'; // Must add this, must >= 0
	int sz = text.size(), lim = ALPHA; // Takes ALPHA time, note when #TC is large
	for (int i = 0; i < lim; i++) cnt[i] = 0;
	for (int i = 0; i < sz; i++) cnt[ isa[i] = text[i] ]++;
	for (int i = 1; i < lim; i++) cnt[i] += cnt[i - 1];
	for (int i = sz - 1; i >= 0; i--) sa[ --cnt[text[i]] ] = i;

	lim = max(sz, ALPHA);
	int *rk = isa, *nsa = lcp, *nrk = lcp;
	for (int len = 1; len < sz; len <<= 1) {
		int num = 0;
		for (int i = sz - len; i < sz; i++) nsa[num++] = i;
		for (int i = 0; i < sz; i++) if (sa[i] >= len) nsa[num++] = sa[i] - len;
		
		for (int i = 0; i < lim; i++) cnt[i] = 0;
		for (int i = 0; i < sz; i++) cnt[ rk[i] ]++;
		for (int i = 1; i < lim; i++) cnt[i] += cnt[i - 1];
		for (int i = sz-1; i >= 0; i--) sa[ --cnt[rk[nsa[i]]] ] = nsa[i];
		
		num = 0;
		nrk[sa[0]] = num++;
		for (int i = 1; i < sz; i++) {
			bool cond = rk[sa[i]] == rk[sa[i-1]] && sa[i] + len < sz;
			cond = cond && sa[i-1] + len < sz && rk[sa[i]+len] == rk[sa[i-1]+len];
			if (cond) nrk[sa[i]] = num - 1;
			else nrk[sa[i]] = num++;
		}
		
		if (num >= sz) break;
		lim = num;
		swap(rk, nrk);
		nsa = nrk;
	}
	for (int i=0; i<sz; i++) isa[sa[i]] = i;
	
	/* LCP */
	int len = 0;
	lcp[0] = 0; // Undefined
	for (int i=0; i<sz; i++) {
		if (isa[i] == 0) continue;
		len = max(0, len-1);
		int j = sa[isa[i]-1];
		while (text[i+len] == text[j+len]) len++;
		lcp[isa[i]] = len;
	}
}
