struct Suffix_array {
	/* isa: inverse sa, or rank, build can be used many times */
	/* MAXL: Maximum length of string, lcp[i]: LCP(sa[i], sa[i-1]) */
	string text;
	int sa[MAXL+5], isa[MAXL+5], lcp[MAXL+5], cnt[MAXL+128];
	void build(const string &_text) {
		text = _text + '\0';
		int sz = text.size(), lim = 128;
		for (int i = 0; i < lim; i++) cnt[i] = 0;
		for (int i = 0; i < sz; i++) cnt[ isa[i] = text[i] ]++;
		for (int i = 1; i < lim; i++) cnt[i] += cnt[i - 1];
		for (int i = 0; i < sz; i++) sa[ --cnt[text[i]] ] = i;
	
		lim = sz + 1;
		int *rank = isa, *nxtsa = lcp, *nxtrank = lcp;
		for (int len = 1; len <= sz; len <<= 1) {
			int num = 0;
			for (int i = sz - len; i < sz; i++) nxtsa[num++] = i;
			for (int i = 0; i < sz; i++) if (sa[i] >= len) nxtsa[num++] = sa[i] - len;
			
			for (int i = 0; i < lim; i++) cnt[i] = 0;
			for (int i = 0; i < sz; i++) cnt[ rank[i] ]++;
			for (int i = 1; i < lim; i++) cnt[i] += cnt[i - 1];
			for (int i = sz-1; i >= 0; i--) sa[ --cnt[rank[nxtsa[i]]] ] = nxtsa[i];
			
			num = 0;
			nxtrank[sa[0]] = num++;
			for (int i = 1; i < sz; i++) {
				bool cond = rank[sa[i]] == rank[sa[i-1]] && sa[i] + len < sz;
				cond = cond && sa[i-1] + len < sz && rank[sa[i]+len] == rank[sa[i-1]+len];
				if (cond) nxtrank[sa[i]] = num - 1;
				else nxtrank[sa[i]] = num++;
			}
			
			if (num >= sz) break;
			lim = num;
			swap(rank, nxtrank);
			nxtsa = nxtrank;
		}
		for (int i=0; i<sz; i++) isa[sa[i]] = i;
		
		/* LCP */
		int len = 0;
		lcp[0] = -1; // Undefined
		for (int i=0; i<sz; i++) {
			if (isa[i] == 0) continue;
			len = max(0, len-1);
			int j = sa[isa[i]-1];
			while (text[i+len] == text[j+len]) len++;
			lcp[isa[i]] = len;
		}
	}
} sa;


int main() {
	//ios_base::sync_with_stdio(0); cin.tie(0);
	
}

