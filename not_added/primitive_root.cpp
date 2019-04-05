int generator (int p) {
	// Return primitive root of p
	// Exist is p is 2, 4 or odd prime power or 2 * odd prime power
	// O(ANS * log^2(p))
    vector<int> fact;
    int phi = p-1,  n = phi;
    for (int i=2; i*i<=n; ++i) {
    	if (n % i == 0) {
            fact.push_back (i);
            while (n % i == 0)
                n /= i;
        }
	}
    if (n > 1) fact.push_back(n);

    for (int res=2; res<=p; ++res) {
        bool ok = true;
        for (size_t i=0; i<fact.size() && ok; ++i)
            ok &= powmod (res, phi / fact[i], p) != 1;
        if (ok)  return res;
    }
    return -1;
}
