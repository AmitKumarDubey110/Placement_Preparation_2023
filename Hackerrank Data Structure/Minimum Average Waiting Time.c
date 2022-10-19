#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

struct za {
    int when;
    int how_long;
};

int ctime(const void* a_in, const void* b_in) {
    const struct za* a = a_in;
    const struct za* b = b_in;
    if (a->when < b->when) return -1;
    if (a->when > b->when) return 1;
    return 0;
}

int za_cmp(struct za a, struct za b) {
    if (a.how_long < b.how_long) return -1;

    if (a.how_long > b.how_long) return 1;
    return 0;
}
void insert_heap_lt(struct za* root, int size) {
    int child = size - 1;
    int parent = (child - 1)/2;
    while (child > 0 && za_cmp(root[child], root[parent]) < 0) {
        struct za tmp = root[child];
        root[child] = root[parent];
        root[parent] = tmp;
        child = parent;
        parent = (child - 1)/2;
    }
}

struct za pop_heap_lt(struct za* root, int size) {
    struct za result = root[0];
    root[0] = root[size - 1];
    int parent = 0;
    int child = 1;
    while (child < size - 1) {
        int c2 = child + 1;
        if (c2 < size - 1 && za_cmp(root[c2], root[child]) < 0) {
            child = c2;
        } 
        if (za_cmp(root[child], root[parent]) < 0) {
            struct za tmp = root[child];
            root[child] = root[parent];
            root[parent] = tmp;
            parent = child;
            child = 2 * parent + 1;
        } else break;
    }
    return result;
}

int main() {
    int n;
    scanf("%d\n", &n);
    struct za zas[n];
    struct za zash[n];
    int hs = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d %d\n", &zas[i].when, &zas[i].how_long);
    }
    qsort(zas, n, sizeof(struct za), ctime);
    int zap = 0;
    long next_ready = zas[zap].when;
    long tt = 0;
    long tt1 = 0;
    while (zap < n || hs) {
        while (zap < n && zas[zap].when <= next_ready) {
            tt1 += next_ready - zas[zap].when;
            zash[hs++] = zas[zap];
            fprintf(stderr, "push: %d %d\n", zas[zap].when, zas[zap].how_long);
            insert_heap_lt(zash, hs);
            zap++;
        }
        if (!hs) {
            next_ready = zas[zap].when;
        } else {
            struct za cookme = pop_heap_lt(zash, hs--);
            tt1 += cookme.how_long * ((long)hs + 1);
          fprintf(stderr, "pop: %d %d\n", cookme.when, cookme.how_long);
            next_ready = next_ready + cookme.how_long;
            tt += next_ready - cookme.when;
        }
    }
    fprintf(stderr, "%ld %ld\n", tt, tt1);
    if (tt1 != tt) exit(-1);
    printf("%ld\n", tt / n);
    return 0;
}
