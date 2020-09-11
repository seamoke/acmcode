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
const int maxn = 10000 + 20, N = 4e3+20, M = 4e6 + 10;
struct node
{
    int v;
    int next;
    ll cost;
    int val;
};
int head[N], flow[N], pre[N];
bool flag[N];
ll dis[N];
int n, m, s, t, tot = 1;
ll maxflow = 0, mincost = 0;
node e[M];
void add(int u, int v, int val, ll c)
{
    e[++tot] = {v, head[u], c, val};
    head[u] = tot;
    e[++tot] = {u, head[v], -c, 0};
    head[v] = tot;
}
bool spfa()
{
    fir(i, 0, N - 1)
        dis[i] = 1e18; //最大费用为-1e18,也可边权取负跑最短路
    memset(flow, MAX_INF, sizeof(flow));
    memset(flag, true, sizeof(flag));
    queue<int> p;
    p.push(s);
    dis[s] = 0;
    pre[t] = -1;
    while (!p.empty())
    {
        int x = p.front();
        p.pop();
        flag[x] = true;
        for (int i = head[x]; i; i = e[i].next)
        {
            int y = e[i].v;
            if (e[i].val && dis[y] > dis[x] + e[i].cost) //最大费用为<
            {
                dis[y] = dis[x] + e[i].cost;
                pre[y] = i;
                flow[y] = min(flow[x], e[i].val);
                if (flag[y])
                {
                    p.push(y);
                    flag[y] = false;
                }
            }
        }
    }
    return pre[t] != -1;
}
void updata()
{
    int x = t;
    while (x != s)
    {
        int i = pre[x];
        e[i].val -= flow[t];
        e[i ^ 1].val += flow[t];
        x = e[i ^ 1].v;
    }
    mincost += flow[t] * dis[t];
    maxflow += flow[t];
}
void work()
{
    mincost = 0;
    maxflow = 0;
    while (spfa())
        updata();
    printf("%lld\n", -mincost);
}
void init(int _s, int _t)
{
    memset(head, 0, sizeof(head));
    s = _s;
    t = _t;
    tot = 1;
}
int a[maxn];
int main()
{
    int n, k;
    int T;
    cin >> T;
    while (T--)
    {
        cin >> n >> k;
        fir(i, 1, n)
            read(a[i]);
		int ss=0,cs=1,ct=n*2+2,tt=n*2+3;
        init(ss,tt);
        add(0, 1, k, 0);
		add(ct,tt,k,0);
        fir(i, 1, n)
        {
            int t1 = i + 1;
            add(cs, t1, 1, 0);
            add(t1, t1 + n, 1, -a[i]);
            add(t1 + n, ct, 1, 0);
            fir(j, i + 1,min(n,i+105))
            {
                if (a[j] >= a[i])
                {
                    int t2 = j + 1;
                    add(t1 + n, t2, 1, 0);
                }
            }
        }
        work();
    }
}
