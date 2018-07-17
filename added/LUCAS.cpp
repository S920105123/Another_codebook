struct Lucas {
	// P is mod number, must be prime
	LL fac[MAXP+5],P;
	void init(LL _P) {
		P=_P;
		LL i;
		fac[0] =1;
		for(i =1; i <= MAXP; i++) {
			fac[i] = fac[i-1]*i % P;
		}
	}
	LL qpow(LL a, LL p) {
	    if (p<=0) return 1;
	    LL tmp=qpow(a,p/2);
	    if (p&1) return tmp*tmp%P*a%P;
	    return tmp*tmp%P;
	}
	LL C(LL n, LL k) {
		if(k > n) return 0;
		return fac[n]*qpow(fac[k]*fac[n-k]%P, P-2) % P;
	}
	LL lucas(LL n, LL k ) {
		if(k ==0) return 1;
		else return (C(n%P, k%P)*lucas(n/P, k/P))%P;
	}
};
