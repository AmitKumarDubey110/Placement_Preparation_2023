#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIMIT 1000000007

typedef struct tree_node_list {
  struct tree_node *node;
  struct tree_node_list *next;
} tree_node_list;

typedef struct tree_node {
  struct tree_node *parent;
  uint32_t num;
  int32_t depth;
} tree_node;

typedef struct aux_info {
  uint32_t simple_sum;
  uint32_t level_sum;
  uint32_t marker;
} aux_info;

static void print_node(tree_node *node) {
  printf("(num: %ld, parent: %ld, depth: %ld) ", node->num,
         node->parent != NULL ? node->parent->num : 0, node->depth);
}

void print_tree(tree_node *nodes, size_t count) {
  for (int i = 0; i < count; i++) {
    tree_node *node = &nodes[i];
    print_node(node);
  }
  printf("\n");
}

static int order_tree(const void *lhs, const void *rhs) {
  tree_node *a = *((tree_node **)lhs);
  tree_node *b = *((tree_node **)rhs);
  return a->depth - b->depth;
}

static void add_depth(tree_node *node) {
  if (node->parent == NULL) {
    node->depth = 0;
  } else if (node->depth == -1) {
    add_depth(node->parent);
    node->depth = node->parent->depth + 1;
  }
}

int main() {
  long num_nodes, num_queries;
  scanf("%ld %ld", &num_nodes, &num_queries);
  tree_node *nodes = calloc(num_nodes, sizeof(tree_node));
  tree_node **order = calloc(num_nodes, sizeof(tree_node *));
  aux_info *info = calloc(num_nodes, sizeof(aux_info));
  for (long i = 0; i < num_nodes; ++i) {
    tree_node *node = &nodes[i];
    node->num = i + 1;
    node->depth = -1;
    order[i] = &nodes[i];
  }
  for (long i = 0; i < num_nodes - 1; i++) {
    long a, b;
    scanf("%ld %ld", &a, &b);
    tree_node *node_a = &nodes[a - 1];
    tree_node *node_b = &nodes[b - 1];
    if (node_b->parent == NULL) {
      node_b->parent = node_a;
    } else if (node_a->parent == NULL) {
      node_a->parent = node_b;
    } else {
      exit(1);
    }
  }
  for (long i = 0; i < num_nodes; ++i) {
    add_depth(&nodes[i]);
  }
  qsort(order, num_nodes, sizeof(tree_node *), order_tree);
  for (long i = 0; i < num_queries; ++i) {
    unsigned long k;
    scanf("%ld", &k);
    for (long j = 0; j < k; j++) {
      long node_num;
      scanf("%ld", &node_num);
      info[node_num - 1].marker = 1;
    }

    uint64_t total = 0;
    for (long j = num_nodes - 1; j >= 0; --j) {
      tree_node node = *order[j];
      uint64_t node_num = node.num;
      uint64_t node_index = node_num - 1;
      aux_info node_info = info[node_index];
      if (node_info.marker == 0 && node.depth == 0) {
        continue;
      }
      uint64_t node_simple_sum = node_info.simple_sum;
      uint64_t node_level_sum = node_info.level_sum;
      if (node_info.marker != 0) {
        // Add all the combintations made with this node and its children
        total = total + node_level_sum * node_num;
        if (total > LIMIT) {
          total = total % LIMIT;
        }
        node_simple_sum += node_num;
      } else if (node_simple_sum == 0) {
        continue;
      }
      // Increment the level
      node_level_sum += node_simple_sum;
      tree_node *parent = node.parent;
      if (parent != NULL) {
        uint64_t parent_index = parent->num - 1;
        aux_info parent_info = info[parent_index];
        uint64_t parent_simple_sum = parent_info.simple_sum;
        uint64_t parent_level_sum = parent_info.level_sum;
        // Add the combinations that this subtree makes with all sibling
        // subtrees processed so far
        total = (total + (parent_simple_sum * node_level_sum) +
                 (parent_level_sum * node_simple_sum));
        if (total > LIMIT) {
          total = total % LIMIT;
        }
        parent_simple_sum = parent_simple_sum + node_simple_sum;
        if (parent_simple_sum > LIMIT) {
          parent_simple_sum = parent_simple_sum % LIMIT;
        }
        parent_level_sum = parent_level_sum + node_level_sum;
        if (parent_level_sum > LIMIT) {
          parent_level_sum = parent_level_sum % LIMIT;
        }
        info[parent_index].simple_sum = parent_simple_sum;
        info[parent_index].level_sum = parent_level_sum;
      }
    }

    memset(info, 0, sizeof(aux_info) * num_nodes);
    long ans = total;
    printf("%ld\n", ans);
  }

  return 0;
}
