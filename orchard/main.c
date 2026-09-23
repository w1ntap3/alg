#include <stdint.h>
#include <stdio.h>

// make sure to read from stdin and print to stdout (fprintf(stdout, ...))
int main(void) {
  int16_t side_len;
  // idk if we are supposed to do error checking of scanf when we are time
  // constrained lmao
  scanf("%hu", &side_len);

  int32_t orchard[side_len][side_len];
  for (int16_t i = 0; i < side_len; i++) {
    for (int16_t j = 0; j < side_len; j++) {
      scanf("%d", &orchard[i][j]);
    }
  }

  // TODO: COMMENT THIS OUT WHEN SUBMITTING
  for (int16_t i = 0; i < side_len; i++) {
    fprintf(stdout, "[");
    for (int16_t j = 0; j < side_len; j++) {
      fprintf(stdout, "%d%s", orchard[i][j], j == side_len - 1 ? "" : ", ");
    }
    fprintf(stdout, "]\n");
  }

  /*
   * DIVISION LOGIC
   * I first lock the horizontal line on each supreme iteration
   * then i lock one vertical line, by choice, the northern one
   * then i divide all possible bottom vertical lines
   * so the three levels of iterations with hierarchy of hor->ver1->ver2
   */

  for (int16_t hor = 1; hor < side_len - 1; hor++) {
    for (int16_t ver1 = 1; ver1 < side_len - 1; ver1++) {
      for (int16_t ver2 = 1; ver2 < side_len - 1; ver2++) {
      }
    }
  }
  return 0;
}
