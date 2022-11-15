#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>


#define floor_log2_X86(self) (__builtin_clz(self) ^ 31U)
#define floor_log2 floor_log2_X86

void heap_sort(unsigned *self, unsigned *weights, unsigned length) {
    unsigned
        at = length >> 1,
        member,
        node;

    for (self--; at; self[node >> 1] = member) {
        member = self[at];

        for (node = at-- << 1; node <= length; node <<= 1) {
            node |= (node < length) && (weights[self[node]] < weights[self[node | 1]]);
            if (weights[self[node]] < weights[member])
                break ;
            self[node >> 1] = self[node];
        }
    }
    for (; length > 1; self[at >> 1] = member) {
        member = self[length];
        self[length--] = self[1];

        for (at = 2; at <= length; at <<= 1) {
            at |= (at < length) && (weights[self[at]] < weights[self[at | 1]]);
            if (weights[self[at]] < weights[member])
                break ;
            self[at >> 1] = self[at];
        }
    }
}

void compress(unsigned length, unsigned values[length]) {
    unsigned
        at,
        order[length];

    unsigned long sum = 0x0000000100000000UL;
    for (at = 0; at < (length >> 1); sum += 0x0000000200000002UL)
        ((unsigned long *)order)[at++] = sum;
    order[length - 1] = length - 1;

    heap_sort(order, values, length);

    unsigned roots[length], seen = 1, max = 0, others;
    for (roots[at = 0] = -1U; at < length; roots[seen++] = at - 1) {
        for (others = at; (at < length) && values[order[at]] == values[order[others]]; at++);

        if (max < (at - others))
            max = (at - others);
    }

    unsigned
        indices[max + 1],
        ranks[seen];

    memset(indices, 0, sizeof(indices));
    for (at = 0; ++at < seen; indices[roots[at] - roots[at - 1]]++);
    for (at = max; at--; indices[at] += indices[at + 1]);
    for (at = seen; --at; ranks[--indices[roots[at] - roots[at - 1]]] = at);

    for (; at < (seen - 1); at++)
        for (others = roots[ranks[at] - 1]; ++others <= roots[ranks[at]]; values[order[others]] = at);
}


static inline unsigned nearest_common_ancestor(
    unsigned depth,
    unsigned base_cnt,
    unsigned vertex_cnt,
    unsigned base_ids[vertex_cnt],
    unsigned bases[base_cnt][depth],
    unsigned char depths[base_cnt],
    unsigned weights[vertex_cnt],
    unsigned lower,
    unsigned upper
) {
    if (upper < (lower + weights[lower]))
        return lower;

    if (depths[upper] > depths[lower])
        upper = bases[base_ids[upper]][depths[upper] - depths[lower] - 1];

    if (upper < lower)
        return upper;

    unsigned *others = bases[base_ids[upper]];
    for (; depth > 1; depth >>= 1)
        if (others[depth >> 1] > lower) {
            others += depth >> 1;
            depth += depth & 1U;
        }

    return others[others[0] > lower];
}

typedef union {
    unsigned long packd;
    struct {
        int low, high;
    };
} range_t;

typedef struct {
    unsigned
        *members,
        *colors,
        *indices,
        *locations;
} colored_tree_t;


unsigned long query_all(colored_tree_t *self, unsigned at, range_t other) {
    unsigned
        color = self->colors[at],
        length = self->indices[color + 1] - self->indices[color],
        *base = &self->members[self->indices[color]];

    if (other.high < base[0] || other.low > base[length - 1])
        return 0;

    if (self->colors[other.low] != color) {
        if (at < other.low) {
            base += self->locations[at] - self->indices[color];
            length = self->indices[color + 1] - self->locations[at];
        } else
            length = self->locations[at] - self->indices[color]; // at > other.low

        for (; length > 1; length >>= 1)
            if (base[length >> 1] < other.low) {
                base += length >> 1;
                length += length & 1;
            }

        base += (base[0] < other.low);
    } else
        base += (self->locations[other.low] - self->indices[color]);

    if (base[0] > other.high)
        return 0;

    unsigned *ceil;
    if (self->colors[other.high] != color) {
        ceil = (at > base[0] && at < other.high) ? &self->members[self->locations[at]] : base;

        for (length = self->indices[color + 1] - self->locations[ceil[0]]; length > 1; length >>= 1)
            if (ceil[length >> 1] <= other.high) {
                ceil += length >> 1;
                length += length & 1;
            }

        ceil -= (ceil[0] > other.high);
    } else
        ceil = &self->members[self->locations[other.high]];


    return ceil - base + 1 - (at >= other.low && at <= other.high);
}

unsigned long count_pairs(
    unsigned cnt,
    unsigned length,
    unsigned long pairs[cnt][cnt],
    unsigned *overlapping,
    colored_tree_t *tree,
    range_t self,
    range_t other
) {
    unsigned long count = 0;
    for (; (self.low % length) && (self.low <= self.high); count += query_all(tree, self.low++, other));
    for (; ((self.high + 1) % length) && (self.low <= self.high); count += query_all(tree, self.high--, other));

    if (self.low <= self.high) {
        for (; (other.low % length) && (other.low <= other.high); count += query_all(tree, other.low++, self));
        for (; ((other.high + 1) % length) && (other.low <= other.high); count += query_all(tree, other.high--, self));

        if (other.low <= other.high) {
            self.low   /= length;
            self.high  /= length;
            other.low  /= length;
            other.high /= length;

            if (self.low > other.low) {
                self.packd  ^= other.packd;
                other.packd ^= self.packd;
                self.packd  ^= other.packd;
            }

            unsigned high = (self.high < other.low) ? self.high : (other.low - 1);

            count +=
                pairs[high][other.high]
                    - pairs[high][other.low - 1UL]
                    - pairs[self.low - 1UL][other.high]
                    + pairs[self.low - 1UL][other.low - 1UL];

            self.low = high + 1;

            if (self.high > other.high) {
                self.packd  ^= other.packd;
                other.packd ^= self.packd;
                self.packd  ^= other.packd;
            }

            if (self.low <= self.high)
                count +=
                    (overlapping[self.high] - overlapping[self.low - 1UL])
                        + ((
                        pairs[self.high][self.high]
                            - pairs[self.high][self.low - 1UL]
                            - pairs[self.low - 1UL][self.high]
                            + pairs[self.low - 1UL][self.low - 1UL]
                    ) << 1) + (
                        pairs[self.high][other.high]
                            - pairs[self.high][self.high]
                            - pairs[self.low - 1UL][other.high]
                            + pairs[self.low - 1UL][self.high]
                    );
        }
    }

    return count;
}

int main() {
    unsigned at, vertex_cnt;
    unsigned short query_cnt;
    scanf("%u %hu", &vertex_cnt, &query_cnt);

    unsigned colors[vertex_cnt + 1];
    for (at = 0; at < vertex_cnt; scanf("%u", &colors[at++]));
    colors[at] = 0xFFFFFFFFU;
    compress(at + 1, colors);

    unsigned ancestors[at + 1];
    {
        unsigned ancestor, descendant;
        for (memset(ancestors, 0xFFU, sizeof(ancestors)); --at; ancestors[descendant] = ancestor) {
            scanf("%u %u", &ancestor, &descendant);
            --ancestor;
            if (ancestors[--descendant] != 0xFFFFFFFFU) {
                unsigned root = descendant, next;
                for (; ancestor != 0xFFFFFFFFU; ancestor = next) {
                    next = ancestors[ancestor];
                    ancestors[ancestor] = root;
                    root = ancestor;
                }
                for (; ancestors[descendant] != 0xFFFFFFFFU; descendant = next) {
                    next = ancestors[descendant];
                    ancestors[descendant] = ancestor;
                    ancestor = descendant;
                }
            }
        }

        for (ancestor = 0xFFFFFFFFU; at != 0xFFFFFFFFU; at = descendant) {
            descendant = ancestors[at];
            ancestors[at] = ancestor;
            ancestor = at;
        }
    }

    unsigned
        others,
        ids[vertex_cnt + 1],
        weights[vertex_cnt],
        bases[vertex_cnt + 1],
        history[vertex_cnt];

    unsigned char
        base_depths[vertex_cnt],
        dist = 0;

    {
        unsigned
            history[vertex_cnt],
            indices[vertex_cnt + 1],
            descendants[vertex_cnt];

        memset(indices, 0, sizeof(indices));
        for (ancestors[vertex_cnt] = (at = vertex_cnt); at; indices[ancestors[at--]]++);
        for (; ++at <= vertex_cnt; indices[at] += indices[at - 1]);
        for (; --at; descendants[--indices[ancestors[at]]] = at);

        history[0] = 0;
        memset(weights, 0, sizeof(weights));
        for (at = 1; at--; )
            if (weights[history[at]])
                for (others = indices[history[at]];
                     others < indices[history[at] + 1];
                     weights[history[at]] += weights[descendants[others++]]);
            else {
                weights[history[at]] = 1;
                memcpy(
                    &history[at + 1],
                    &descendants[indices[history[at]]],
                    (indices[history[at] + 1] - indices[history[at]]) * sizeof(descendants[0])
                );
                at += indices[history[at] + 1] - indices[history[at]] + 1;
            }

        unsigned
            orig_ancestors[vertex_cnt + 1],
            orig_colors[vertex_cnt + 1],
            orig_weights[vertex_cnt];

        memcpy(orig_ancestors, ancestors, sizeof(ancestors));
        memcpy(orig_weights, weights, sizeof(weights));
        memcpy(orig_colors, colors, sizeof(colors));

        base_depths[0] = (bases[0] = (ids[0] = 0));
        bases[vertex_cnt] = (ids[vertex_cnt] = vertex_cnt);
        for (at = 1; at--;) {
            unsigned
                id = ids[history[at]],
                base = bases[id++],
                branches = indices[history[at] + 1] - indices[history[at]];

            heap_sort(&descendants[indices[history[at]]], orig_weights, branches);
            memcpy(&history[at], &descendants[indices[history[at]]], branches * sizeof(descendants[0]));

            for (others = (at += branches); branches--; base = id) {
                ids[history[--others]] = id;

                ancestors[id] = ids[orig_ancestors[history[others]]];
                weights[id] = orig_weights[history[others]];
                colors[id] = orig_colors[history[others]];

                bases[id] = base;
                base_depths[id] = base_depths[ancestors[id]] + (base == id);

                if (dist < base_depths[id])
                    dist = base_depths[id];

                id += weights[id];
            }
        }
    }

    unsigned base_ids[vertex_cnt + 1];
    for (base_ids[0] = (others = (at = 0)); others < vertex_cnt; base_ids[others] = base_ids[at] + 1)
        for (at = others; bases[at] == bases[others]; base_ids[others++] = base_ids[at]);

    unsigned ancestral_bases[base_ids[vertex_cnt]][dist];
    for (ancestors[0] = 0; others--; ancestral_bases[base_ids[others]][0] = ancestors[others]);
    while ((++others + 1) < dist)
        for (at = 0; ++at < base_ids[vertex_cnt];
             ancestral_bases[at][others + 1] = ancestors[bases[ancestral_bases[at][others]]]);

    unsigned
        indexed_colors[colors[vertex_cnt] + 2],
        members[vertex_cnt + 1];

    memset(indexed_colors, 0, sizeof(indexed_colors));
    for (at = vertex_cnt + 1; at--; indexed_colors[colors[at]]++);
    for (; ++at < colors[vertex_cnt]; indexed_colors[at + 1] += indexed_colors[at]);
    for (at = vertex_cnt + 1; at--; members[--indexed_colors[colors[at]]] = at);
    indexed_colors[colors[vertex_cnt] + 1] = indexed_colors[colors[vertex_cnt]];

    unsigned
        levels = floor_log2(vertex_cnt) + 1,
        block_cnt = (vertex_cnt / levels) + 1,
        locations[vertex_cnt + 1],
        overlapping[block_cnt];

    unsigned long (*pairs)[block_cnt][block_cnt] = calloc(
        (1 + block_cnt) * (1 + block_cnt),
        sizeof(pairs[0][0][0])
    );
    pairs = (void *)&pairs[0][1][1];

    for (at = vertex_cnt + 1; at--; locations[members[at]] = at);

    memset(overlapping, 0, sizeof(overlapping));
    for (at = 0; (indexed_colors[at + 1] - indexed_colors[at]) > 1; at++) {
        others = indexed_colors[at];

        unsigned
            block_bases[indexed_colors[at + 1] - others + 1],
            cnt = 1;

        for (block_bases[0] = members[others]; at == colors[members[++others]]; )
            if ((members[others] / levels) != (block_bases[cnt - 1] / levels))
                block_bases[cnt++] = members[others];

        block_bases[cnt] = members[others];
        for (others = 0; others < cnt; others++) {
            unsigned long density = locations[block_bases[others + 1]] - locations[block_bases[others]];
            overlapping[block_bases[others] / levels] += density * (density - 1);

            unsigned block = others;
            for (; ++block < cnt; pairs[0][block_bases[others] / levels][block_bases[block] / levels]
                += density * (locations[block_bases[block + 1]] - locations[block_bases[block]]));
        }
    }

    for (at = 0; ++at < block_cnt; overlapping[at] += overlapping[at - 1])
        pairs[0][0][at] += pairs[0][0][at - 1];

    for (at = 0; ++at < block_cnt; )
        for (others = 0; ++others < block_cnt; pairs[0][at][others] += pairs[0][at][others - 1]);

    for (at = 0; ++at < block_cnt; )
        for (others = 0; others < block_cnt; others++)
            pairs[0][at][others] += pairs[0][at - 1][others];

    colored_tree_t *tree = &(colored_tree_t) {
        .members = members,
        .colors = colors,
        .indices = indexed_colors,
        .locations = locations
    };


    while (query_cnt--) {
        range_t left, right;
        scanf("%u %u %u %u", &left.low, &left.high, &right.low, &right.high);
        left.packd -= 0x0000000100000001UL;
        right.packd -= 0x0000000100000001UL;

        left.low = ids[left.low];
        left.high = ids[left.high];

        right.low = ids[right.low];
        right.high = ids[right.high];

        if (left.high < left.low)
            left.packd = (left.packd << 32) | (left.packd >> 32);

        if (right.high < right.low)
            right.packd = (right.packd << 32) | (right.packd >> 32);

        if (right.high < left.low) {
            left.packd  ^= right.packd;
            right.packd ^= left.packd;
            left.packd  ^= right.packd;
        }

        struct {
            range_t members[32];
            unsigned cnt;
        }
            a = {.cnt = 0},
            b = {.cnt = 0};

        unsigned common = nearest_common_ancestor(
            dist, base_ids[vertex_cnt], vertex_cnt,
            base_ids, ancestral_bases,
            base_depths, weights,
            left.low, left.high
        );

        for (at = left.low; bases[at] != bases[common]; at = ancestral_bases[base_ids[at]][0])
            a.members[a.cnt++].packd = bases[at] | ((unsigned long)at << 32);

        for (others = left.high; bases[others] != bases[common]; others = ancestral_bases[base_ids[others]][0])
            a.members[a.cnt++].packd = bases[others] | ((unsigned long)others << 32);

        a.members[a.cnt++].packd = common | ((unsigned long)((at != common) ? at : others) << 32);

        common = nearest_common_ancestor(
            dist, base_ids[vertex_cnt], vertex_cnt,
            base_ids, ancestral_bases,
            base_depths, weights,
            right.low, right.high
        );

        for (at = right.low; bases[at] != bases[common]; at = ancestral_bases[base_ids[at]][0])
            b.members[b.cnt++].packd = bases[at] | ((unsigned long)at << 32);

        for (others = right.high; bases[others] != bases[common]; others = ancestral_bases[base_ids[others]][0])
            b.members[b.cnt++].packd = bases[others] | ((unsigned long)others << 32);

        b.members[b.cnt++].packd = common | ((unsigned long)((at != common) ? at : others) << 32);

        unsigned long total = 0;
        for (at = 0; at < a.cnt; at++)
            for (others = 0; others < b.cnt;
                 total += count_pairs(
                     block_cnt, levels, pairs[0], overlapping, tree,
                     a.members[at], b.members[others++]
                 )
            );

        printf("%lu\n", total);
    }

    return 0;
}
