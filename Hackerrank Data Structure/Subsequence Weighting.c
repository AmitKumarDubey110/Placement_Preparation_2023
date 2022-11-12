#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct treap {
    int x, p;
    long long y;
    struct treap *l, *r;
}* Treap;

Treap td = NULL;

Treap newTreap(int x, long long y) {
    Treap t;
    if (td) {
        t = td;
        td = td->r;
    }
    else
        t = (Treap) malloc(sizeof(struct treap));
    t->x = x;
    t->y = y;
    t->p = rand();
    t->l = t->r = NULL;
    return t;
}

void dump(Treap t) {
    if (t) {
        dump(t->l);
        dump(t->r);
        t->r = td;
        td = t;
    }
}

Treap merge(Treap l, Treap r) {
    if (!l)
        return r;
    if (!r)
        return l;
    if (l->p > r->p) {
        l->r = merge(l->r, r);
        return l;
    }
    r->l = merge(l, r->l);
    return r;
}

void split(Treap t, Treap *l, Treap *r, long long v, int d) {
    if (!t)
        *l = *r = NULL;
    else if (d ? (t->x < v) : (t->y <= v)) {
        split(t->r, &t->r, r, v, d);
        *l = t;
    }
    else {
        split(t->l, l, &t->l, v, d);
        *r = t;
    }
}

Treap rightmost(Treap t) {
    if (t) {
        while (t->r)
            t = t->r;
    }
    return t;
}

Treap leftmost(Treap t) {
    if (t) {
        while (t->l)
            t = t->l;
    }
    return t;
}

long long solve() {
    int n, i;
    long long v;
    scanf("%d", &n);
    int a[n], w[n];
    for (i = -1; ++i < n; scanf("%d", a + i));
    for (i = -1; ++i < n; scanf("%d", w + i));
    Treap r = newTreap(0, 0), l, m;
    for (i = -1; ++i < n;) {
        split(r, &l, &r, a[i], 1);
        m = rightmost(l);
        v = w[i] + m->y;
        split(r, &m, &r, v, 0);
        if (m) {
            dump(m);
            m = newTreap(a[i], v);
        }
        else {
            m = leftmost(r);
            if (!m || m->x > a[i])
                m = newTreap(a[i], v);
            else
                m = NULL;
        }
        l = merge(l, m);
        r = merge(l, r);
    }
    v = rightmost(r)->y;
    dump(r);
    return v;
}

int main() {
    srand(time(NULL));
    int t;
    scanf("%d", &t);
    while (t--)
        printf("%lld\n", solve());
    return 0;
}
