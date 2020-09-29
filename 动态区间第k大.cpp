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
#include <fstream>
typedef long long ll;
using namespace std;
//#pragma GCC optimize(3, "Ofast", "inline")
#define MAX_INF 0x3f3f3f3f
ll mod = 1e9 + 7;
#define fir(i, a, b) for (int i = a; i <= b; i++)
#define mov(i) (1 << i)
const int maxn = 1e5 + 10;
struct SplNode
{
	int ch[2];
	int val;
	int size;
	int fa;
	int cnt;
	SplNode()
	{
		ch[2] = 0;
		val = size = fa = cnt = 0;
	}
};
SplNode spl[maxn * 50];
int cnt = 0;
int a[maxn];
int n, m;
struct Splay
{

	int root = 0;
	inline void newnode(int &now, int fa, int &val)
	{
		spl[now = ++cnt].val = val;
		spl[cnt].size = 1;
		spl[cnt].cnt = 1;
		spl[cnt].fa = fa;
		spl[cnt].ch[0] = spl[cnt].ch[1] = 0;
		if (!fa)
			spl[fa].ch[1] = now, root = now;
	}
	inline void update(int now)
	{
		int l = spl[now].ch[0];
		int x = spl[now].ch[1];
		spl[now].size = spl[l].size + spl[x].size + spl[now].cnt;
	}
	inline bool ident(int x, int f) { return spl[f].ch[1] == x; } //right:1,left:0
	inline void connect(int x, int f, int s)
	{
		spl[f].ch[s] = x;
		spl[x].fa = f;
	}
	inline void rotate(int x)
	{
		int f = spl[x].fa, ff = spl[f].fa, k = ident(x, f);
		connect(spl[x].ch[k ^ 1], f, k);
		connect(x, ff, ident(f, ff));
		connect(f, x, k ^ 1);
		update(f), update(x);
	}
	inline void splaying(int x, int goal)
	{
		while (spl[x].fa != goal)
		{
			int y = spl[x].fa, z = spl[y].fa;
			if (spl[y].fa != goal)
				rotate((spl[z].ch[1] == y) ^ (spl[y].ch[1] == x) ? x : y);
			rotate(x);
		}
		if (!goal)
			root = x;
		update(x);
	}
	inline int find(int val)
	{
		int u = root;
		if (u == 0)
			return -1;
		while (spl[u].ch[spl[u].val < val] && val != spl[u].val)
			u = spl[u].ch[spl[u].val < val];
		if (spl[u].val != val)
			return -1;
		splaying(u, 0);
		return u;
	}
	void ins(int val)
	{
		int fa = 0, now = root;
		while (now && val != spl[now].val)
		{
			fa = now;
			now = spl[now].ch[spl[now].val < val];
		}
		if (now)
			spl[now].cnt++;
		else
		{
			newnode(now, fa, val);
			connect(now, fa, val > spl[fa].val);
		}
		splaying(now, 0);
	}
	void del(int now)
	{
		splaying(now, 0);
		if (spl[now].cnt > 1)
			spl[now].cnt--, spl[now].size--;
		else if (!spl[now].ch[1])
			root = spl[root].ch[0], spl[root].fa = 0;
		else
		{
			int p = spl[now].ch[1];
			while (spl[p].ch[0])
				p = spl[p].ch[0];
			splaying(p, now);
			connect(spl[now].ch[0], p, 0);
			root = p;
			spl[p].fa = 0;
			update(root);
		}
	}
	void change(int pos, int val)
	{
		del(find(pos));
		ins(val);
	}
	void build(int l, int r, int fa)
	{
		ins(-2147483647);
		ins(2147483647);
		fir(i, l, r)
			ins(a[i]);
	}
	int getnum(int rank)
	{
		int now = root;//rank从1开始
		while (now)
		{
			int lsize = spl[spl[now].ch[0]].size;
			if (lsize + 1 <= rank && rank <= lsize + spl[now].cnt)
			{
				//	splaying(now, 0);
				break;
			}
			if (rank <= lsize)
				now = spl[now].ch[0];
			else
			{
				rank -= lsize + spl[now].cnt;
				now = spl[now].ch[1];
			}
		}
		return now;
	}
	int getrank(int val)
	{
		if (val == 2)
			int x = 1;
		int now = root;
		int rank = 0;
		while (now)
		{
			int& l = spl[now].ch[0], &r = spl[now].ch[1];
			if (val < spl[now].val)
				now = spl[now].ch[0];
			else if (spl[now].val < val)
				rank += spl[l].size + spl[now].cnt, now = r;
			else
			{
				rank += spl[l].size;
				break;
			}
		}
		return rank - 1;
	}
	vector<int> ans;
	void dfs(int now)
	{
		//	push_down(now);
		if (spl[now].ch[0])
			dfs(spl[now].ch[0]);
		//	if (spl[now].val >= 1 && spl[now].val <= n)
		ans.push_back(spl[now].val);
		if (spl[now].ch[1])
			dfs(spl[now].ch[1]);
	}
	void show()
	{
		ans.clear();
		dfs(root);
		for (int i = 0; i < ans.size() - 1; i++)
			printf("%d ", ans[i]);
		printf("%d\n", ans.back());
	}
};
#define left (i<<1)
#define right (i<<1|1)
struct node
{
	int l;
	int r;
	Splay s;
}seg[maxn * 4];
void build(int l, int r, int i)
{
	seg[i].l = l;
	seg[i].r = r;
	seg[i].s.build(l, r, 0);
	// seg[i].s.show();
	// cout<<l<<' '<<r<<endl;
	if (l == r)return;
	int mid = (l + r) >> 1;
	build(l, mid, left);
	build(mid + 1, r, right);
}
int query_rank(int l, int r, int i, int val)
{
	int ans = 0;
	if (l <= seg[i].l&&seg[i].r <= r)
	{
		return seg[i].s.getrank(val);
	}
	int mid = (seg[i].l + seg[i].r) >> 1;
	if (l <= mid)ans += query_rank(l, r, left, val);
	if (r > mid)ans += query_rank(l, r, right, val);
	return ans;
}
int query_val(int L, int R, int k)
{
	if (k > R - L + 1)return 2147483647;
	if (k <= 0)return -2147483647;
	int l = 0, r = 1e8;
	while (l < r)
	{
		int mid = (l + r + 1) >> 1;
		if (query_rank(L, R, 1, mid) + 1 <= k)l = mid;
		else r = mid - 1;
		//      cout<<mid<<':'<<query_rank(L,R,1,mid)+1<<endl;
	}
	return l;
}
void change(int l, int i, int val)
{
	seg[i].s.change(a[l], val);
	if (seg[i].l == seg[i].r)return;
	int mid = (seg[i].l + seg[i].r) >> 1;
	if (l <= mid)change(l, left, val);
	else change(l, right, val);
}
int getpre(int l, int r, int val)
{
	int pos = query_rank(l, r, 1, val) + 1;
	return query_val(l, r, pos - 1);
}
int getnext(int l, int r, int val)
{
	int pos = query_rank(l, r, 1, val + 1) + 1;
	// cout<<val<<':'<<pos<<endl;
	return query_val(l, r, pos);
}
int main()
{
	int debug = 0;
	if (debug)
	{
		freopen("in.txt", "r", stdin);
		freopen("out.txt", "w", stdout);
	}
	scanf("%d%d", &n, &m);
	fir(i, 1, n)scanf("%d", &a[i]);
	build(1, n, 1);
	while (m--)
	{
		int ch;
		scanf("%d", &ch);
		int l, r, pos, k;
		if (ch != 3)scanf("%d%d%d", &l, &r, &k);
		else scanf("%d%d", &pos, &k);
		if (ch == 1)printf("%d\n", query_rank(l, r, 1, k) + 1);//找到val的rank
		else if (ch == 2)printf("%d\n", query_val(l, r, k));//找到区间第K个数
		else if (ch == 3)change(pos, 1, k), a[pos] = k;//单点修改
		else if (ch == 4)printf("%d\n", getpre(l, r, k));//前驱
		else if (ch == 5)printf("%d\n", getnext(l, r, k));//后继
	}
}
