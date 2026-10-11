#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define DIVISION_COUNT 4

// make sure to read from stdin and print to stdout (fprintf(stdout, ...))
int main(void) {
  int side_len;

  if (scanf("%d", &side_len) != 1 || side_len < 2)
    return 1;

  int (*orchard)[side_len][side_len] = malloc(sizeof(int[side_len][side_len]));

  long long *col_top = calloc(side_len, sizeof(long long));
  long long *col_bottom = calloc(side_len, sizeof(long long));

  if (orchard == NULL || col_top == NULL || col_bottom == NULL) {
    free(orchard);
    free(col_top);
    free(col_bottom);
    return 1;
  }

  long long top_total = 0;
  long long bottom_total = 0;

  for (int i = 0; i < side_len; i++) {
    for (int j = 0; j < side_len; j++) {
      if (scanf("%d", &(*orchard)[i][j]) != 1) {
        free(orchard);
        free(col_top);
        free(col_bottom);
        return 1;
      }

      col_bottom[j] += (*orchard)[i][j];
      bottom_total += (*orchard)[i][j];
    }
  }

  /*
   * DIVISION LOGIC
   * Move the horizontal line one row at a time.
   * For each horizontal line, find the best vertical division
   * independently for the northern and southern halves.
   */

  long long min_diff = LLONG_MAX;

  // {Top-Left, Top-Right, Bottom-Left, Bottom-Right}
  long long dsums[DIVISION_COUNT] = {0, 0, 0, 0};

  for (int hor = 1; hor < side_len; hor++) {
    // Move one row from the bottom half to the top half.
    for (int col = 0; col < side_len; col++) {
      int value = (*orchard)[hor - 1][col];

      col_top[col] += value;
      col_bottom[col] -= value;

      top_total += value;
      bottom_total -= value;
    }

    long long left_top = 0;
    long long left_bottom = 0;

    long long best_top_diff = LLONG_MAX;
    long long best_bottom_diff = LLONG_MAX;

    long long best_top_left = 0;
    long long best_bottom_left = 0;

    // Try every vertical cut, keeping both sides nonempty.
    for (int col = 0; col < side_len - 1; col++) {
      left_top += col_top[col];
      left_bottom += col_bottom[col];

      long long top_diff = llabs(2 * left_top - top_total);
      long long bottom_diff = llabs(2 * left_bottom - bottom_total);

      if (top_diff < best_top_diff) {
        best_top_diff = top_diff;
        best_top_left = left_top;
      }

      if (bottom_diff < best_bottom_diff) {
        best_bottom_diff = bottom_diff;
        best_bottom_left = left_bottom;
      }
    }

    dsums[0] = best_top_left;
    dsums[1] = top_total - best_top_left;
    dsums[2] = best_bottom_left;
    dsums[3] = bottom_total - best_bottom_left;

    long long min = dsums[0];
    long long max = dsums[0];

    for (int d = 1; d < DIVISION_COUNT; d++) {
      if (dsums[d] > max)
        max = dsums[d];

      if (dsums[d] < min)
        min = dsums[d];
    }

    long long cur_diff = max - min;

    if (cur_diff < min_diff)
      min_diff = cur_diff;
  }

  fprintf(stdout, "%lld\n", min_diff);

  free(orchard);
  free(col_top);
  free(col_bottom);

  return 0;
}
