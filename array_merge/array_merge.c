#include "array_merge.h"
#include <stdlib.h>

extern void mergesort(int size, int values[]);

int* array_merge(int num_arrays, int* sizes, int** values) {
  // Handle invalid input
  if( num_arrays <= 0 || sizes == NULL || values == NULL){
    int* out = (int*)malloc(sizeof(int));
    if (out) out[0] = 0;
    return out;
  }

  // Calculate total number of elements across all arrays
  long long total_ll = 0;
  for(int i = 0; i < num_arrays; i++) {
    int sz = sizes[i];
    if(sz > 0) total_ll += sz;
  }

  // Return empty result if no elements
  if(total_ll <=0) {
    int* out = (int*)malloc(sizeof(int));
    if(out) out[0] = 0;
    return out;
  }

  // Convert to int and allocate flat array to hold all elements
  int total = (int)total_ll;
  int* flat = (int*)malloc((size_t)total * sizeof(int));
  if(!flat) {
    int* out = (int*)malloc(sizeof(int));
    if (out) out[0] = 0;
    return out;
  }

  // Copy all array elements into flat array
  int pos = 0;
  for (int i = 0; i < num_arrays; i++) {
    int sz = sizes[i];
    if (sz <=0) continue;
    int* arr = values[i];
    if(!arr) continue;
    for (int j = 0; j < sz; j++) {
      flat[pos++] = arr[j];
    }
  }

  total = pos;

  // Return empty result if no valid elements found
  if(total == 0) {
    free(flat);
    int* out = (int*)malloc(sizeof(int));
    if (out) out[0] = 0;
    return out;
  }

  // Sort all elements
  mergesort(total, flat);

  // Count unique elements
  int k = 1;
  for (int i = 1; i < total; i++) {
    if (flat[i] != flat[i-1]) k++;
  }

  // Allocate output array: [count, unique_values...]
  int* out = (int*)malloc((size_t)(k + 1) * sizeof(int));
  if(!out) {
    free(flat);
    int* fail = (int*)malloc(sizeof(int));
    if(fail) fail[0] = 0;
    return fail;
  }

  // Store count at index 0
  out[0] = k;

  // Copy unique elements to output
  int write = 1;
  out[write++] = flat[0];
  for (int i = 1; i < total; i++) {
    if(flat[i] != flat[i-1]) {
      out[write++] = flat[i];
    }
  }

  free(flat);
  return out;
}
