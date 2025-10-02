#include "mergesort.h"

static void merge_into(int *dst, const int *left, int nL, const int *right, int nR) {
  int i = 0, j = 0, k = 0;
  while( i < nL && j < nR){
    if(left[i] <= right[j]) {
      dst[k++] = left[i++];
    }else {
      dst[k++] = right[j++];
    }
  }
  while (i <nL) dst[k++] = left[i++];
  while (j < nR) dst[k++] = right[j++];
}
    
void mergesort(int size, int values[]) {
  if (size <= 1 || values == NULL) return;
  int mid = size /2;
  int nL = mid;
  int nR = size -mid;

  int *left = (int *)calloc(nL, sizeof(int));
  int *right = (int *)calloc(nR, sizeof(int));
  if (!left || !right) {
    free(left);
    free(right);
    return;
  }

  for(int i = 0; i < nL; i++) {
    left[i] = values[i];
  }
  for(int j = 0; j < nR; j++) {
    right[j] = values[mid + j];
  }

  mergesort(nL, left);
  mergesort(nR, right);
  merge_into(values, left, nL, right, nR);

  free(left);
  free(right);
}
