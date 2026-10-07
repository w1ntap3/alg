#include <stdio.h>
#include <stdlib.h>

#define HASAN_YIGIT_APA 31 // idk its my groupmate's name as a joke
#define DIVISION_COUNT 4

// make sure to read from stdin and print to stdout (fprintf(stdout, ...))
int main(void) {
  int side_len;
  // idk if we are supposed to do error checking of scanf when we are time
  // constrained lmao
  scanf("%d", &side_len);

  int (*orchard)[side_len][side_len] = malloc(sizeof(int[side_len][side_len]));

  for (int i = 0; i < side_len; i++) {
    for (int j = 0; j < side_len; j++) {
      scanf("%d", &(*orchard)[i][j]);
    }
  }

  /*
   * DIVISION LOGIC
   * I first lock the horizontal line on each supreme iteration
   * then i lock one vertical line, by choice, the northern one
   * then i divide all possible bottom vertical lines
   * so the three levels of iterations with hierarchy of hor->ver_n->ver_s
   */
  long long min_diff = 0;

  // calculate initial sums and then manipulate them by deltas
  // {Top-Left, Top-Right, Bottom-Left, Bottom-Right}
  long long dsums[DIVISION_COUNT] = {0, 0, 0, 0};

  for (int hor = 1; hor < side_len - 1; hor++) {
    for (int i = 0; i < DIVISION_COUNT; i++) {
      dsums[i] = 0;
    }

    for (int ver_n = 1; ver_n < side_len - 1; ver_n++) {
      // delta changes when northern vertical shifts (div N1 gains, div N2
      // loses)
      for (int row = 0; row < hor; row++) {
        dsums[0] += (*orchard)[row][ver_n];
        dsums[1] -= (*orchard)[row][ver_n];
      }

      for (int ver_s = 1; ver_s < side_len - 1; ver_s++) {
        // delta changes when southern vertical shifts (div N3 gains, div N4
        // loses)
        if (ver_s == 1) {
          dsums[2] = 0;
          dsums[3] = 0;

          for (int row = hor; row < side_len; row++) {
            for (int col = 0; col < ver_s; col++) {
              dsums[2] += (*orchard)[row][col];
            }
            for (int col = ver_s; col < side_len; col++) {
              dsums[3] += (*orchard)[row][col];
            }
          }
        } else {
          for (int row = hor; row < side_len; row++) {
            dsums[2] += (*orchard)[row][ver_s - 1];
            dsums[3] -= (*orchard)[row][ver_s - 1];
          }
        }

        // min/max determination + computation of the potential minimum
        // difference
        long long min = dsums[0];
        long long max = dsums[0];

        for (int d = 0; d < DIVISION_COUNT; d++) {
          if (dsums[d] > max)
            max = dsums[d];
        }
        for (int d = 0; d < DIVISION_COUNT; d++) {
          if (dsums[d] < min)
            min = dsums[d];
        }

        long long cur_diff = max - min;
        if (cur_diff < min_diff) {
          min_diff = cur_diff;
        }
      }
    }
  }

  fprintf(stdout, "%d\n", min_diff);

  return 0;
}
