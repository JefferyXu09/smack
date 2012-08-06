#include <stdio.h>
#include <stdlib.h>
#include "smack.h"

#define RESET 0
#define SET 1

typedef struct {
  short data;
  int count;
  char status;
} elem;

int arraySize;

void __SMACK_GlobalInvariant() {
  __SMACK_invariant(arraySize > 0);
  __SMACK_invariant(__SMACK_allocated(&arraySize));
  __SMACK_invariant(__SMACK_size(&arraySize) == 4);
  __SMACK_invariant(__SMACK_offsetOf(&arraySize) == 0);
  TYPES(__SMACK_invariant(__SMACK_typeOf(&arraySize, TYPEP(int))));
}

void __SMACK_anno_resetArray(elem *array) {
  TYPES(__SMACK_requires(__SMACK_forall(__SMACK_x,
                                        __SMACK_ARRAY_COUNT(array, sizeof(elem), arraySize),
                                        __SMACK_typeOf(__SMACK_x, TYPEP(elem)))));
  __SMACK_requires(__SMACK_size(array) == arraySize * sizeof(elem));
  __SMACK_requires(__SMACK_offsetOf(array) == 0);
  __SMACK_requires(__SMACK_allocated(array));
  __SMACK_requires(__SMACK_OBJNOALIAS(array, &arraySize));
  __SMACK_ensures(__SMACK_forall(__SMACK_x, __SMACK_ARRAY_COUNT(array, sizeof(elem), arraySize), (((elem*)__SMACK_x)->status) == RESET));
  INFER(__SMACK_modifies(__SMACK_addOffsetToSet(__SMACK_ARRAY_COUNT(array, sizeof(elem), arraySize), __SMACK_OFFSET(elem, status))));
  INLINE(__SMACK_inline());
}
void resetArray(elem *array) {
  int i = 0;

  for (i = 0; i < arraySize; i++) {
    // *** loop invariants
    __SMACK_invariant(0 <= i);
    __SMACK_invariant(i <= arraySize);
    __SMACK_invariant(__SMACK_forall(__SMACK_x, __SMACK_ARRAY_COUNT(array, sizeof(elem), i), (((elem*)__SMACK_x)->status) == RESET));
    INFER(__SMACK_modifies(__SMACK_union(__SMACK_addOffsetToSet(__SMACK_ARRAY_COUNT(array, sizeof(elem), __SMACK_new(i)),
                                                                __SMACK_OFFSET(elem, status)),
                                         __SMACK_set(&i))));
    // ***

    array[i].status = RESET;
  }
}

void __SMACK_anno_setArray(elem *array) {
  TYPES(__SMACK_requires(__SMACK_forall(__SMACK_x,
                                        __SMACK_ARRAY_COUNT(array, sizeof(elem), arraySize),
                                        __SMACK_typeOf(__SMACK_x, TYPEP(elem)))));
  __SMACK_requires(__SMACK_size(array) == arraySize * sizeof(elem));
  __SMACK_requires(__SMACK_offsetOf(array) == 0);
  __SMACK_requires(__SMACK_allocated(array));
  __SMACK_requires(__SMACK_OBJNOALIAS(array, &arraySize));
  __SMACK_ensures(__SMACK_forall(__SMACK_x, __SMACK_ARRAY_COUNT(array, sizeof(elem), arraySize), (((elem*)__SMACK_x)->status) == SET));
  INFER(__SMACK_modifies(__SMACK_addOffsetToSet(__SMACK_ARRAY_COUNT(array, sizeof(elem), arraySize), __SMACK_OFFSET(elem, status))));
  INLINE(__SMACK_inline());
}
void setArray(elem *array) {
  int i = 0;

  for (i = arraySize - 1; i >= 0; i--) {
    // *** loop invariants
    __SMACK_invariant(-1 <= i);
    __SMACK_invariant(i < arraySize);
    __SMACK_invariant(__SMACK_forall(__SMACK_x, __SMACK_array(array + i + 1, sizeof(elem), array + arraySize), (((elem*)__SMACK_x)->status) == SET));
    INFER(__SMACK_modifies(__SMACK_union(__SMACK_addOffsetToSet(__SMACK_array(array + __SMACK_new(i) + 1, sizeof(elem), array + arraySize),
                                                                __SMACK_OFFSET(elem, status)),
                                         __SMACK_set(&i))));
    // ***

    array[i].status = SET;
  }
}

void __SMACK_anno_initializeCount(elem *array) {
  TYPES(__SMACK_requires(__SMACK_forall(__SMACK_x,
                                        __SMACK_ARRAY_COUNT(array, sizeof(elem), arraySize),
                                        __SMACK_typeOf(__SMACK_x, TYPEP(elem)))));
  __SMACK_requires(__SMACK_size(array) == arraySize * sizeof(elem));
  __SMACK_requires(__SMACK_offsetOf(array) == 0);
  __SMACK_requires(__SMACK_allocated(array));
  __SMACK_requires(__SMACK_OBJNOALIAS(array, &arraySize));
  __SMACK_ensures(__SMACK_forall(__SMACK_x, __SMACK_ARRAY_COUNT(array, sizeof(elem), arraySize), (((elem*)__SMACK_x)->count) == 0));
  INFER(__SMACK_modifies(__SMACK_addOffsetToSet(__SMACK_ARRAY_COUNT(array, sizeof(elem), arraySize), __SMACK_OFFSET(elem, count))));
  INLINE(__SMACK_inline());
}
void initializeCount(elem *array) {
  int i = 0;

  for (i = 0; i < arraySize; i++) {
    // *** loop invariants
    __SMACK_invariant(0 <= i);
    __SMACK_invariant(i <= arraySize);
    __SMACK_invariant(__SMACK_forall(__SMACK_x, __SMACK_ARRAY_COUNT(array, sizeof(elem), i), (((elem*)__SMACK_x)->count) == 0));
    INFER(__SMACK_modifies(__SMACK_union(__SMACK_addOffsetToSet(__SMACK_ARRAY_COUNT(array, sizeof(elem), __SMACK_new(i)),
                                                                __SMACK_OFFSET(elem, count)),
                                         __SMACK_set(&i))));
    // ***

    array[i].count = 0;
  }
}

int main() {
  int i = 0;
  elem *arrayOne;
  elem *arrayTwo;

  __SMACK_assume(arraySize > 0);

  arrayOne = (elem*)malloc(arraySize * sizeof(elem));
  arrayTwo = (elem*)malloc(arraySize * sizeof(elem));

  resetArray(arrayOne);
  setArray(arrayTwo);
  initializeCount(arrayTwo);

  for (i = 0; i < arraySize; i++) {
    // *** loop invariants
    __SMACK_invariant(0 <= i);
    __SMACK_invariant(i <= arraySize);
    INFER(__SMACK_modifies(__SMACK_set(&i)));
    // ***

    __SMACK_assert(arrayOne[i].status == RESET);
    __SMACK_assert(arrayTwo[i].status == SET);
    __SMACK_assert(arrayTwo[i].count == 0);
  }

  initializeCount(arrayOne);
  setArray(arrayOne);
  resetArray(arrayTwo);

  for (i = arraySize - 1; i >= 0; i--) {
    // *** loop invariants
    __SMACK_invariant(-1 <= i);
    __SMACK_invariant(i < arraySize);
    INFER(__SMACK_modifies(__SMACK_set(&i)));
    // ***

    __SMACK_assert(arrayOne[i].count != 0 || arrayOne[i].status != SET || arrayTwo[i].status != RESET);
  }

  free(arrayOne);
  free(arrayTwo);
  return 0;
}
