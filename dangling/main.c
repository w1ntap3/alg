#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_NEIGHBOURS 3
#define READ_BUFFER_SIZE (1 << 16)

static char read_buffer[READ_BUFFER_SIZE];
static size_t read_len = 0;
static size_t read_pos = 0;

static int read_char(void) {
  if (read_pos == read_len) {
    read_len = fread(read_buffer, 1, READ_BUFFER_SIZE, stdin);
    read_pos = 0;

    if (read_len == 0)
      return -1;
  }

  return (unsigned char)read_buffer[read_pos++];
}

static int read_int(int *value) {
  int c = read_char();

  while (c == ' ' || c == '\n' || c == '\r' || c == '\t')
    c = read_char();

  if (c < '0' || c > '9')
    return 0;

  int number = 0;

  while (c >= '0' && c <= '9') {
    number = number * 10 + (c - '0');
    c = read_char();
  }

  *value = number;
  return 1;
}

int main(void) {
  int node_count;
  int root;

  if (read_int(&node_count) != 1 || node_count < 1)
    return 1;

  if (read_int(&root) != 1 || root < 0 || root >= node_count)
    return 1;

  int *keys = malloc(node_count * sizeof(int));
  int *degrees = calloc(node_count, sizeof(int));
  int (*adjacency)[MAX_NEIGHBOURS] = malloc(node_count * sizeof(int[MAX_NEIGHBOURS]));

  if (keys == NULL || degrees == NULL || adjacency == NULL) {
    free(keys);
    free(degrees);
    free(adjacency);
    return 1;
  }

  for (int i = 0; i < node_count; i++) {
    if (read_int(&keys[i]) != 1) {
      free(keys);
      free(degrees);
      free(adjacency);
      return 1;
    }
  }

  for (int i = 0; i + 1 < node_count; i++) {
    int a;
    int b;

    if (read_int(&a) != 1 || read_int(&b) != 1 || a < 0 || a >= node_count ||
        b < 0 || b >= node_count || a == b) {
      free(keys);
      free(degrees);
      free(adjacency);
      return 1;
    }

    if (degrees[a] >= MAX_NEIGHBOURS || degrees[b] >= MAX_NEIGHBOURS) {
      free(keys);
      free(degrees);
      free(adjacency);
      return 1;
    }

    adjacency[a][degrees[a]++] = b;
    adjacency[b][degrees[b]++] = a;
  }

  long long min_cost = LLONG_MAX;
  long long max_cost = LLONG_MIN;

  for (int leaf = 0; leaf < node_count; leaf++) {
    if (degrees[leaf] > 1 || (leaf == root && degrees[leaf] == 1))
      continue;

    long long cost = keys[leaf];
    int cur = leaf;
    int prev = -1;

    while (cur != root) {
      int parent = -1;

      for (int k = 0; k < degrees[cur]; k++) {
        if (adjacency[cur][k] != prev) {
          parent = adjacency[cur][k];
          break;
        }
      }

      if (parent == -1 || degrees[parent] > 2)
        break;

      cost += keys[parent];
      prev = cur;
      cur = parent;
    }

    if (cost < min_cost)
      min_cost = cost;

    if (cost > max_cost)
      max_cost = cost;
  }

  fprintf(stdout, "%lld %lld\n", min_cost, max_cost);

  free(keys);
  free(degrees);
  free(adjacency);

  return 0;
}
