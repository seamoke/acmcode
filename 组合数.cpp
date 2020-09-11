#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <stack>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <unordered_map>
#include <queue>
#include <map>
#include <sstream>
#include <set>
#include <cstdlib>
#include <ctime>
#include <unordered_set>
#include <bitset>
#include <list>
#include <chrono>
#include <assert.h>
typedef long long ll;
using namespace std;
#pragma GCC optimize(3, "Ofast", "inline")
#define MAX_INF 0x3f3f3f3f
#define fir(i, a, b) for (int i = a; i <= b; i++)
ll pow(ll a, ll b, ll p)
{
	ll ans = 1;
	a %= p;
	while (b)
	{
		if (b & 1)
			ans = ans * a % p;
		a = a * a % p;
		b >>= 1;
	}
	return ans;
}
template <typename _Tp>
void read(_Tp &x)
{
    char ch;
    bool flag = 0;
    x = 0;
    while (ch = getchar(), !isdigit(ch))
        if (ch == '-')
            flag = 1;
    while (isdigit(ch))
        x = x * 10 + ch - '0', ch = getchar();
    if (flag)
        x = -x;
}
const int maxn = 1e5+ 20, N = 4e3+20, M = 4e6 + 10;
const int P=1000000007;
ll fac[maxn], invfac[maxn], mod,t[maxn];
	void init(int n, ll MOD){ // 线性求[1, n]的组合数和逆元
	    fac[0] = 1; mod = MOD;
	    for(int i = 1; i <= n; i++)
	        fac[i] = fac[i - 1] * i % mod;
	    invfac[n] = pow(fac[n], mod - 2, mod);
	    for(int i = n; i >= 1; i--)
	        invfac[i - 1] = invfac[i] * i % mod;
	}
	ll C(ll n, ll m){
	    return n >= m ? fac[n] * invfac[n - m] % mod * invfac[m] % mod: 0;
	}
int main()
{
    init(1e5+7,P);
    t[1]=0,t[2]=1;
    fir(i,3,maxn-1)
    t[i]=((i-1)*(t[i-1]+t[i-2]))%P;
    int T;
    cin>>T;
    while(T--)
    {
        int n,m;
        scanf("%d%d",&n,&m);
        printf("%lld\n",(t[m]*C(n,m)%P));
    }
}
