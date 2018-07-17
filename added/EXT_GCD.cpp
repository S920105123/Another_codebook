#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair < LL, LL> ii;

ii exd_gcd( LL a, LL b) {
    if (a % b == 0) return ii(0, 1);
    ii T = exd_gcd(b, a % b);
    return ii( T.second, T.first - a / b * T.second);
}
LL mod_inv(LL x) { // P is mod number, gcd(x,P) must be 1
    return (exd_gcd(x,P).first%P+P)%P;
}
