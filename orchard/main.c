#include <stdio.h>

#define DIVISION_COUNT 4

// make sure to read from stdin and print to stdout (fprintf(stdout, ...))
int main(void) {
  int side_len;
  // idk if we are supposed to do error checking of scanf when we are time
  // constrained lmao
  scanf("%d", &side_len);

  int orchard[side_len][side_len];
  for (int i = 0; i < side_len; i++) {
    for (int j = 0; j < side_len; j++) {
      scanf("%d", &orchard[i][j]);
    }
  }

  // TODO: COMMENT THIS OUT WHEN SUBMITTING
  for (int i = 0; i < side_len; i++) {
    fprintf(stdout, "[");
    for (int j = 0; j < side_len; j++) {
      fprintf(stdout, "%d%s", orchard[i][j], j == side_len - 1 ? "" : ", ");
    }
    fprintf(stdout, "]\n");
  }

  /*
   * DIVISION LOGIC
   * I first lock the horizontal line on each supreme iteration
   * then i lock one vertical line, by choice, the northern one
   * then i divide all possible bottom vertical lines
   * so the three levels of iterations with hierarchy of hor->ver_n->ver_s
   */

  int min_diff;

  // calculate initial sums and then manipulate them by deltas
  int dsums[DIVISION_COUNT] = {0, 0, 0, 0};
  dsums[0] = orchard[0][0];
  for (int col = 1; col < side_len; col++) {
    dsums[1] += orchard[0][col];
  }
  for (int row = 1; row < side_len; row++) {
    dsums[2] += orchard[row][0];
  }
  for (int row = 1; row < side_len; row++) {
    for (int col = 1; col < side_len; col++) {
      dsums[3] += orchard[row][col];
    }
  }

  for (int hor = 1; hor < side_len - 1; hor++) {
    for (int ver_n = 1; ver_n < side_len - 1; ver_n++) {
      // delta changes when northern vertical shifts (div N1 gains, div N2
      // loses)
      for (int row = 0; row < hor - 1; row++) {
        dsums[0] += orchard[row][ver_n - 1];
        dsums[1] -= orchard[row][ver_n - 1];
      }
      for (int ver_s = 1; ver_s < side_len - 1; ver_s++) {
        // delta changes when southern vertical shifts (div N3 gains, div N4
        // loses)
        for (int row = hor; row < side_len; row++) {
          dsums[2] += orchard[row][ver_s + 1];
          dsums[3] -= orchard[row][ver_s + 1];
        }

        // min/max determination + computation of the potential minimum
        // difference
        int min = dsums[0];
        int max = dsums[0];

        for (int d = 0; d < DIVISION_COUNT; d++) {
          if (dsums[d] > max)
            max = dsums[d];
        }
        for (int d = 0; d < DIVISION_COUNT; d++) {
          if (dsums[d] < min)
            min = dsums[d];
        }

        int cur_diff = max - min;
        if (cur_diff < min_diff) {
          min_diff = cur_diff;
        }
      }
    }
  }

  fprintf(stdout, "%d\n", min_diff);
  return 0;
}
