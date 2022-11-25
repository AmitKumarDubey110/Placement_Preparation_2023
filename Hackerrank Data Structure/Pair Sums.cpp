#include <bits/stdc++.h>
using namespace std;

#define ll long long

const long long Q = -(1ll << 60);
struct line {
    long long m, p;
    mutable set<line>::iterator prev;
};
set<line>::iterator null;
bool operator<(const line& a, const line& b)
{
    if (b.p != Q && a.p != Q) {
        return a.m < b.m;
    }
    if (b.p == Q) {
        if (a.prev == null)
            return true;
        bool ok = true;
        if ((a.prev->m - a.m) < 0)
            ok = !ok;
        if (ok) {
            return (a.p - a.prev->p) < (a.prev->m - a.m) * b.m;
        }
        else {
            return (a.p - a.prev->p) > (a.prev->m - a.m) * b.m;
        }
    }
    else {
        if (b.prev == null)
            return false;
        bool ok = true;
        if ((b.prev->m - b.m) < 0)
            ok = !ok;
        if (ok) {
            return !((b.p - b.prev->p) < a.m * (b.prev->m - b.m));
        }
        else {
            return !((b.p - b.prev->p) > a.m * (b.prev->m - b.m));
        }
    }
}
class convex_hull {
public:
    set<line> convex;
    set<line>::iterator next(set<line>::iterator ii)
    {
        set<line>::iterator gg = ii;
        gg++;
        return gg;
    }
    set<line>::iterator prev(set<line>::iterator ii)
    {
        set<line>::iterator gg = ii;
        gg--;
        return gg;
    }
    bool bad(set<line>::iterator jj)
    {
        set<line>::iterator ii, kk;
        if (jj == convex.begin())
            return false;
        kk = next(jj);
        if (kk == convex.end())
            return false;
        ii = prev(jj);
        line a = *ii, c = *kk, b = *jj;
        bool ok = true;
        if ((b.m - a.m) < 0)
            ok = !ok;
        if ((b.m - c.m) < 0)
            ok = !ok;
        if (ok) {
            return (c.p - b.p) * (b.m - a.m) <= (a.p - b.p) * (b.m - c.m);
        }
        else {
            return (c.p - b.p) * (b.m - a.m) >= (a.p - b.p) * (b.m - c.m);
        }
    }
    void del(set<line>::iterator ii)
    {
        set<line>::iterator jj = next(ii);
        if (jj != convex.end()) {
            jj->prev = ii->prev;
        }
        convex.erase(ii);
    }
    void add(long long m, long long p)
    {
        null = convex.end();
        line g;
        g.m = m;
        g.p = p;
        set<line>::iterator ii = convex.find(g);
        if (ii != convex.end()) {
            if (ii->p >= p)
                return;
            del(ii);
        }
        convex.insert(g);
        ii = convex.find(g);
        set<line>::iterator jj = next(ii);
        if (jj != convex.end())
            jj->prev = ii;
        if (ii != convex.begin()) {
            ii->prev = prev(ii);
        }
        else {
            ii->prev = convex.end();
        }
        if (bad(ii)) {
            del(ii);
            return;
        }
        jj = next(ii);
        while (jj != convex.end() && bad(jj)) {
            del(jj);
            jj = next(ii);
        }
        if (ii != convex.begin()) {
            jj = prev(ii);
            while (ii != convex.begin() && bad(jj)) {
                del(jj);
                jj = prev(ii);
            }
        }
    }
    long long query(long long x)
    {
        null = convex.end();
        line y;
        y.m = x;
        y.p = Q;
        set<line>::iterator ii = convex.lower_bound(y);
        ii--;
        return ii->m * x + ii->p;
    }
};

ll a[500000], p1[500001], p2[500001], ans=LLONG_MIN;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n;
	cin >> n;
	if(n<=0) {
		for(int i=0; i<n; ++i) {
			cin >> a[i];
			p1[i+1]=p1[i]+a[i];
	        p2[i+1]=p2[i]+a[i]*a[i];
	    }
	    for(int i=0; i<n; ++i)
            for(int j=i+1; j<=n; ++j)
ans=max((p1[j]-p1[i])*(p1[j]-p1[i])-p2[j]+p2[i], ans);
	} else {
		convex_hull h;
		for(int i=0; i<n; ++i) {
			cin >> a[i];
			p1[i+1]=p1[i]+a[i];
	        p2[i+1]=p2[i]+a[i]*a[i];
	        h.add(-2*p1[i], p1[i]*p1[i]+p2[i]);
ans=max(p1[i+1]*p1[i+1]+h.query(p1[i+1])-p2[i+1], ans);
		}
	}
	cout << ans/2;
}
