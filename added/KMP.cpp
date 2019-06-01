vector<int> lps; // longest prefix suffix, 0-based
int match(const string &text, const string &pat) {
	/* Init is included */
	lps.resize(pat.size());	
	/* DP */
	lps[0] = 0;
	for (int i=1; i<pat.size(); i++) {
		int len = lps[i-1];
		while (true) {
			if (pat[i] == pat[len]) {
				lps[i] = len + 1;
				break;
			}
			if (len <= 0) {
				lps[i] = 0;
				break;
			}	
			len = lps[len - 1];
		}
	}		
	/* Match */
	int i = 0, j = 0;
	while (i < text.size() && j < pat.size()) {
		if (text[i] == pat[j]) i++, j++;
		else if (j == 0) i++;
		else j = lps[j - 1];
	}
	if (j >= pat.size()) return i - j;
	return -1;
}
