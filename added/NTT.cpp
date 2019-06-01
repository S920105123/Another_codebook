const LL mod = 998244353;
const LL p_root = 3;
const LL root_pw = 1LL << 23;

// Do NTT under mod. invert=true to do iNTT.
// mod MUST be a prime, if mod=c*2^k+1, then
// p_root is any primitive root of mod
// root_pw=2^k, and n(size) MUST <= 2^k
// n MUST be power of 2.
// mod=2013265921, root_pw=1LL<<27, p_root=31

void ntt(LL a[], int n, bool invert) {
    LL root = qpow(p_root, (mod-1)/root_pw, mod);
	LL root_1 = mod_inv(root, mod);

	for (int i = 1, j = 0; i < n; i++) {
		LL bit = n >> 1;
		for (; j & bit; bit >>= 1)
			j ^= bit;
		j ^= bit;

		if (i < j)
			swap(a[i], a[j]);
	}

	for (int len = 2; len <= n; len <<= 1) {
		LL wlen = invert ? root_1 : root;
		for (int i = len; i < root_pw; i <<= 1)
			wlen = wlen * wlen % mod;

		for (int i = 0; i < n; i += len) {
			LL w = 1;
			for (int j = 0; j < len / 2; j++) {
				LL u = a[i+j], v = a[i+j+len/2] * w % mod;
				a[i+j] = u + v < mod ? u + v : u + v - mod;
				a[i+j+len/2] = u - v >= 0 ? u - v : u - v + mod;
				w = w * wlen % mod;
			}
		}
	}

	if (invert) {
		LL n_1 = mod_inv(n, mod);
		for (int i = 0; i < n; i++) {
			a[i] = a[i] * n_1 % mod;
		}
	}
}
