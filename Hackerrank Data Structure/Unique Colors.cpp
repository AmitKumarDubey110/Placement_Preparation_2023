#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
#define N 101000
typedef long long ll;
set<pi> S;
set<pi> ::iterator it;
int dis[N], rev[N], col[N], pa[N], fin[N];
ll Add[N * 4];
ll ans[N];
vector<int> v[N];
vector<int> C[N];
int cnt;
void dfs(int x, int p) {
    dis[x] = ++cnt;
    rev[cnt] = x;
    C[col[x]].push_back(x);
    for(int i = 0; i < v[x].size(); i ++) {
        int y = v[x][i];
        if(y == p) continue;
        pa[y] = x;
        dfs(y, x);
    }
    fin[x] = cnt;
}
pi A[N];

void build(int st, int en, int id) {
    Add[id] = 0;
    if(st == en) {
        return ;
    }
    int mid = (st + en) >> 1;
    build(st, mid, id * 2);
    build(mid + 1, en, id * 2 + 1);
    return ;
}

int n;

void push_down(int id) {
    if(Add[id]) {
        Add[id * 2] += Add[id];
        Add[id * 2 + 1] += Add[id];
        Add[id] = 0;
    }
    return ;
}

void add(int l, int r, int st, int en, int id, int val) {
    if(l > en || st > r) return ;
    if(l <= st && en <= r) {
        Add[id] += val;
        return ;
    }
    push_down(id);
    int mid = (st + en) >> 1;
    add(l, r, st, mid, id * 2, val);
    add(l, r, mid + 1, en, id * 2 + 1, val);
}

ll calc(int l, int st, int en, int id) {
    if(st == en) {
        return Add[id];
    }
    push_down(id);
    int mid = (st + en) >> 1;
    if(l <= mid) return calc(l, st, mid, id * 2);
    return calc(l, mid + 1, en, id * 2 + 1);
}
pi B[N];

void doit(int y) {
    int st = dis[y];
    int en = fin[y];
    it = S.lower_bound(pi(en + 1, 0));
    if(it == S.begin()) {
        add(st, en, 1, n, 1, -(en - st + 1));
        S.insert(pi(st, en));
        return ;
    }
    it --;
    pi bb = *it;
    if(bb.second < st) {
        add(st, en, 1, n, 1, -(en - st + 1));
        S.insert(pi(st, en));
        return ;
    }
    int cnt = 0;
    while(1) {
        pi aa = *it;
        if(aa.second < st) break;
        B[cnt ++] = aa;
        if(it == S.begin()) break;
        it --;
    }
    for(int i = 0; i < cnt; i ++) A[i] = B[cnt - 1- i];
    int num = en - st + 1;
    for(int i = 0; i < cnt; i ++) num -= (A[i].second - A[i].first + 1);
    for(int i = 1; i < cnt; i ++) {
        if(A[i].first > A[i - 1].second + 1) {
            add(A[i - 1].second + 1, A[i].first - 1, 1, n, 1, -num);
        }
        continue;
    }
    if(A[0].first >= st + 1) add(st, A[0].first - 1, 1, n, 1, -num);
    if(A[cnt - 1].second <= en - 1) add(A[cnt - 1].second + 1, en, 1, n, 1, -num);
    for(int i = 0; i < cnt; i ++) {
        it = S.find(pi(A[i].first, A[i].second));
        S.erase(it);
    }
    S.insert(pi(st, en));
}
int a[N];
int main() {
    //freopen("1.in", "r", stdin);
    scanf("%d", &n);
    for(int i = 1; i <= n; i ++) scanf("%d", &col[i]);
    for(int i = 1; i <= n; i ++) a[i - 1] = col[i];
    sort(a, a + n);
    int num = unique(a, a + n) - a;
    for(int i = 1; i <= n; i ++) col[i] = lower_bound(a, a + num, col[i]) - a + 1;
    for(int i = 1; i <= n; i ++) ans[i] = 1ll * num * n;
    for(int i = 1; i < n; i ++) {
        int x, y;
        scanf("%d%d", &x, &y);
        v[x].push_back(y);
        v[y].push_back(x);
    }
    if(n == 1) {
        puts("0");
        return 0;
    }
    dfs(1, 0);
    build(1, n, 1);
    for(int i = 1; i <= num; i ++) {
        S.clear();
        for(int j = C[i].size() - 1; j >= 0; j --) {
            int x = C[i][j];
            for(int k = 0; k < v[x].size(); k ++) {
                int y = v[x][k];
                if(y == pa[x]) continue;
                doit(y);
            }
            for(int k = 0; k < v[x].size(); k ++) {
                int y = v[x][k];
                if(y == pa[x]) continue;
                S.erase(pi(dis[y], fin[y]));
            }
            S.insert(pi(dis[x], fin[x]));
        }
        doit(1);
    }
    for(int i = 1; i <= n; i ++) ans[i] += calc(i, 1, n, 1);
    for(int i = 1; i <= n; i ++) printf("%lld\n", ans[dis[i]]);
    return 0;
}
