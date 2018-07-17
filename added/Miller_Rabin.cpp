LL mod_mul(LL a, LL b, LL mod) {
//	return (__int128)a*b%mod;
	/* In case __int128 doesn't work(32* multi to avoid ovf) */
	LL x=0,y=a%mod;
    while(b > 0){
        if (b&1) x = (x+y)%mod;
        y = (y*2)%mod;
        b >>= 1;
    }
    return x%mod;
}
LL qpow(LL a, LL p, LL mod) {
	if (p<=0) return 1;
	LL temp = qpow(a,p/2,mod);
	temp = mod_mul(temp,temp,mod);
	if (p&1) return mod_mul(temp,a,mod);
	return temp;
}
bool MRtest(LL a, LL d, LL n) {
	LL x = qpow(a,d,n);
	if (x==1 || x==n-1) return true;
	while (d != n-1) {
		x = mod_mul(x,x,n);
		d *= 2;
		if (x==n-1) return true;
		if (x==1) return false;
	}
	return false;
}
bool is_prime(LL n) {
	if (n==2) return true;
	if (n<2 || n%2==0) return false;
	LL table[7] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022}, d=n-1;
	while (d%2 != 0) d>>=1; // n-1 = d * 2^r, d is odd.
	for (int i=0; i<7; i++) {
		LL a = table[i] % n;
		if (a==0 || a==1 || a==n-1) continue;
		if (!MRtest(a,d,n)) {
			return false;
		}
	}
	return true;
}
