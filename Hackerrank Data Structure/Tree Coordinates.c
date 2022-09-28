#include <stdio.h>
#include <string.h>

void descending(unsigned length, unsigned *weights, unsigned *self) {
    unsigned at, member, node = length >> 1;

    for (self--; node; self[at >> 1] = member) {
        member = self[node];
        for (at = node-- << 1; at < length && weights[self[
                 at |= weights[self[at | 1]] < weights[self[at]]
             ]] < weights[member]; 
             at <<= 1
        ) self[at >> 1] = self[at];     

        if (at == length && weights[self[at]] < weights[member])
            member ^= self[at], self[at] ^= member, member ^= self[at];
    }
    for (; length > 1; self[at >> 1] = member) {
        member = self[length];
        self[length--] = self[1];
        for (at = 2; at < length && weights[self[
                at |= weights[self[at | 1]] < weights[self[at]]
             ]] < weights[member]; 
             at <<= 1
        ) self[at >> 1] = self[at];

        if (at == length && weights[self[at]] < weights[member])
            node = self[at], self[at] = member, member = node;
    }
}
// Submitted by Samy Vilar <samy_vilar> on 07/07/2019
typedef struct {
    unsigned 
        *weights,
        *depths,        
        *bases,
        *base_indices,
        *ancestral_bases;
} tree_t;

unsigned calc_dist(tree_t *self, unsigned low, unsigned high) {        
    if (high < low) 
        low ^= high, high ^= low, low ^= high;

    if (low <= high && high < (low + self->weights[low])) 
        return self->depths[high] - self->depths[low];
        
    unsigned *candidates = &self->ancestral_bases[self->base_indices[self->bases[high]]];
    unsigned short length = self->base_indices[self->bases[high] + 1] - self->base_indices[self->bases[high]];
    
    for (; length > 1; length >>= 1)
        if (candidates[length >> 1] < low) {
            candidates += length >> 1;
            length += length & 1;
        }   

    return self->depths[low] + self->depths[high] - (self->depths[*candidates] << 1);
}
// Submitted by Samy Vilar <samy_vilar> on 07/07/2019
int main() {
    unsigned vertex_cnt, point_cnt;
    scanf("%u %u", &vertex_cnt, &point_cnt);

    unsigned 
        at, others, tail, next,
        ancestors[vertex_cnt];
    
    for (at = vertex_cnt >> 1; at--; ((unsigned long *)ancestors)[at] = 0x100000001UL * vertex_cnt);    
    for (ancestors[at += vertex_cnt] = vertex_cnt; at--; ancestors[others] = tail)
        if (ancestors[(scanf("%u %u", &others, &tail), --tail, --others)] != vertex_cnt)
            for (next = tail, tail = others, others = next; ancestors[others] != vertex_cnt; others = next) {
                next = ancestors[others];
                ancestors[others] = tail;
                tail = others;
            }    

    unsigned
        indices[vertex_cnt + 2],
        descendants[vertex_cnt];                       

    memset(indices, 0, sizeof(indices));
    for (at = vertex_cnt; at--; *(unsigned long *)&indices[ancestors[at]] += 0x100000001UL);
    for (; ++at < (vertex_cnt >> 1); ((unsigned long *)indices)[at + 1] += ((unsigned long *)indices)[at]);        
    for (at = vertex_cnt; at--; descendants[--indices[ancestors[at]]] = at);
        
    unsigned 
        history[vertex_cnt],
        weights[vertex_cnt + 1];

    at += vertex_cnt;
    for (history[at] = descendants[at], tail = 0; tail < at; tail++) {        
        history[tail] = history[at];
        at -= (indices[history[tail] + 1] - indices[history[tail]]) - 1;
        memcpy(
            &history[at], 
            &descendants[indices[history[tail]]], 
            (indices[history[tail] + 1] - indices[history[tail]]) * sizeof(history[0])
        );
    }        
    for (at = vertex_cnt >> 1; at--; ((unsigned long *)weights)[at] = 0x100000001UL);
    for (*(unsigned long *)&weights[(at = vertex_cnt) - 1] = 1UL; --at; 
        weights[ancestors[history[at]]] += weights[history[at]]);    

    unsigned        
        depths[vertex_cnt],
        bases[vertex_cnt],
        ids[vertex_cnt + 1],
        base_indices[vertex_cnt + 1];    

    memcpy(bases, weights, vertex_cnt * sizeof(weights[0]));
    
    weights[0] = vertex_cnt;                        
    for (ids[history[0]] = (depths[0] = (at = 0)); at < tail; at++) {
        others = indices[history[at]];
        descending(indices[history[at] + 1] - others, bases, &descendants[others]);                                    
        for (next = ids[history[at]] + 1; others < indices[history[at] + 1]; next += weights[next]) {
            ids[descendants[others]] = next;            
            ancestors[next] = ids[history[at]];                        
            depths[next] = depths[ancestors[next]] + 1;
            weights[next] = bases[descendants[others++]];
        }        
    }        
    
    memset(base_indices, 0, sizeof(base_indices));        
    for (bases[0] = (at = 0); ++at < vertex_cnt; ) 
        if ((ancestors[at] + 1) == at)
            bases[at] = bases[ancestors[at]];
        else 
            base_indices[(bases[at] = at) + 1] = base_indices[bases[ancestors[at]] + 1] + 1;        
        
    for (at = 0; ++at < vertex_cnt; base_indices[at] += base_indices[at - 1]);
    base_indices[at] += base_indices[at - 1];

    unsigned ancestral_bases[base_indices[at]];
    for (others = base_indices[at--]; others; at--)
        if (base_indices[at] < others) 
            for (ancestral_bases[--others] = ancestors[at]; others > base_indices[at]; others--)
                ancestral_bases[others - 1] = ancestors[bases[ancestral_bases[others]]];         

    unsigned 
        x_points[point_cnt],
        y_points[point_cnt];
    
    for (at = point_cnt; at--; x_points[at] = ids[x_points[at] - 1]) {
        scanf("%u %u", &x_points[at], &y_points[at]);                
        y_points[at] = ids[y_points[at] - 1];
    }

    memset(indices, 0, sizeof(indices));
    for (at = vertex_cnt; --at; *(unsigned long *)&indices[ancestors[at]] += 0x100000001UL);
    for (; ++at <= (vertex_cnt >> 1); ((unsigned long *)indices)[at] += ((unsigned long *)indices)[at - 1]);
    for (at = vertex_cnt; --at; descendants[--indices[ancestors[at]]] = at);

    // Submitted by Samy Vilar <samy_vilar> on 07/07/2019

    unsigned mass[vertex_cnt + 1];
    {
        unsigned 
            centroids[vertex_cnt],
            id = 0;

        ancestors[0] = (centroids[0] = (mass[0] = vertex_cnt));
        for (history[0] = 0, at = 1; at--; weights[next] = 0, ids[next] = id++) {
            for (tail = (next = history[at]); (weights[next] << 1) < mass[history[at]]; next = ancestors[tail = next]);
            for (others = indices[next]; others < indices[next + 1]; others++)
                if ((weights[descendants[others]] << 1) > mass[history[at]] && descendants[others] != tail)
                    others = indices[next = descendants[others]] - 1;

            centroids[next] = centroids[history[at]];                   
            for (mass[next] = mass[history[at]]; others-- > indices[next]; )
                if (weights[descendants[others]]) {                                      
                    centroids[history[at] = descendants[others]] = next;                                        
                    mass[history[at++]] = weights[descendants[others]];
                }      

            for (others = next; weights[ancestors[others]]; weights[others = ancestors[others]] -= weights[next]);        
            if (others != next) {
                centroids[history[at] = ancestors[next]] = next;                
                mass[history[at++]] = weights[others];
            }
        }       
        for (at = vertex_cnt >> 1; at--; ((unsigned long *)weights)[at] = 0x100000001UL);
        for (weights[(at = vertex_cnt) - 1] = 1; --at; weights[ancestors[at]] += weights[at]);            
                    
        memset(indices, 0, sizeof(indices));
        for (at = vertex_cnt; at--; *(unsigned long *)&indices[centroids[at]] += 0x100000001UL);
        for (; ++at < (vertex_cnt >> 1); ((unsigned long *)indices)[at + 1] += ((unsigned long *)indices)[at]);        
        for (at = vertex_cnt; at--; descendants[--indices[centroids[at]]] = at);        
        memcpy(ancestors, centroids, vertex_cnt * sizeof(centroids[0]));
    }    

    unsigned x_indices[vertex_cnt + 2];
    {                        
        unsigned buffers[2][point_cnt];

        memset(x_indices, 0, sizeof(x_indices));
        for (at = point_cnt; at--; *(unsigned long *)&x_indices[ids[x_points[at]]] += 0x100000001UL);
        for (; ++at < (vertex_cnt >> 1); ((unsigned long *)x_indices)[at + 1] += ((unsigned long *)x_indices)[at]);                    
        for (at = point_cnt; at--; buffers[1][x_indices[ids[x_points[at]]]] = y_points[at])
            buffers[0][--x_indices[ids[x_points[at]]]] = x_points[at];         

        memcpy(x_points, buffers[0], sizeof(x_points));
        memcpy(y_points, buffers[1], sizeof(y_points));
    }
    
    // Submitted by Samy Vilar <samy_vilar> on 07/07/2019    

    tree_t *tree_props = &(tree_t) {
        .weights = weights,
        .depths = depths,        
        .bases = bases,
        .base_indices = base_indices,
        .ancestral_bases = ancestral_bases
    };

    union path_t {
        unsigned long packd;
        struct {
            unsigned branch;
            int dist;
        };
    } furthest[vertex_cnt],
      second[vertex_cnt],
      candidate;
            
    for (at = vertex_cnt; at--; furthest[at].packd = 0x8000000000000000UL | vertex_cnt);        
    memcpy(second, furthest, sizeof(furthest));
    
    // Submitted by Samy Vilar <samy_vilar> on 07/07/2019

    int max_seen = 0; 
    
    mass[ids[vertex_cnt] = vertex_cnt] = 0;
    ancestors[descendants[vertex_cnt - 1]] = 0xFFFFFFFFU;    
    
    unsigned x_dist, at_x = vertex_cnt;

    while (at_x--) {                                
        for (others = x_indices[ids[at_x] + mass[at_x]]; others-- > x_indices[ids[at_x]]; ) 
            for (tail = y_points[others]; tail != 0xFFFFFFFFU && furthest[tail].dist != 0x80000000U; tail = ancestors[tail]) 
                second[tail].packd = (furthest[tail].packd = vertex_cnt | 0x8000000000000000UL);                
            
        while (++others < x_indices[ids[at_x] + 1])
            for (next = y_points[others], candidate.branch = vertex_cnt; next != 0xFFFFFFFFU; next = ancestors[candidate.branch = next]) {
                candidate.dist = calc_dist(tree_props, next, y_points[others]);                

                if ((ids[candidate.branch] <  ids[furthest[next].branch] || 
                     ids[candidate.branch] >= (ids[furthest[next].branch] + mass[furthest[next].branch]))
                        && max_seen < (candidate.dist + furthest[next].dist))                          
                    max_seen = candidate.dist + furthest[next].dist;
                else if ((ids[candidate.branch] < ids[second[next].branch] || 
                          ids[candidate.branch] >= (ids[second[next].branch] + mass[second[next].branch]))
                            && max_seen < ((candidate.dist + second[next].dist)))
                    max_seen = candidate.dist + second[next].dist;        
                
                if (furthest[next].dist < candidate.dist) {
                    if (furthest[next].branch != candidate.branch) 
                        second[next].packd = furthest[next].packd;

                    furthest[next].packd = candidate.packd;                    
                } else if (second[next].dist < candidate.dist && furthest[next].branch != candidate.branch) 
                    second[next].packd = candidate.packd;                
            }                                          
           
        // Submitted by Samy Vilar <samy_vilar> on 07/07/2019

        for (others = indices[at_x]; others < indices[at_x + 1]; others++) {
            for (at = x_indices[ids[descendants[others]]]; 
                 at < x_indices[ids[descendants[others]] + mass[descendants[others]]]; 
                 at++
            ) {
                x_dist = calc_dist(tree_props, at_x, x_points[at]);                 

                for (next = y_points[at], tail = vertex_cnt; next != 0xFFFFFFFFU; next = ancestors[tail = next])
                    if (ids[tail] <   ids[furthest[next].branch] || 
                        ids[tail] >= (ids[furthest[next].branch] + mass[furthest[next].branch])) 
                    {                
                        candidate.dist = furthest[next].dist + x_dist + calc_dist(tree_props, next, y_points[at]);
                        if (max_seen < candidate.dist)
                            max_seen = candidate.dist;
                    } else if (ids[tail] <   ids[second[next].branch] || 
                               ids[tail] >= (ids[second[next].branch] + mass[second[next].branch])) 
                    {                    
                        candidate.dist = second[next].dist + x_dist + calc_dist(tree_props, next, y_points[at]);
                        if (max_seen < candidate.dist)
                            max_seen = candidate.dist;
                    }
            }            
            while (at-- > x_indices[ids[descendants[others]]]) {
                x_dist = calc_dist(tree_props, at_x, x_points[at]);   

                candidate.branch = vertex_cnt;
                for (next = y_points[at]; next != 0xFFFFFFFFU; next = ancestors[candidate.branch = next]) {
                    candidate.dist = x_dist + calc_dist(tree_props, next, y_points[at]);                    

                    if (furthest[next].dist < candidate.dist) {
                        if (furthest[next].branch != candidate.branch) 
                            second[next].packd = furthest[next].packd;                            
                                                
                        furthest[next].packd = candidate.packd;                        
                    } else if (second[next].dist < candidate.dist && furthest[next].branch != candidate.branch) 
                        second[next].packd = candidate.packd;                    
                }            
            }
        }
    }
    
    printf("%u", max_seen);
    return 0;
}
