#include "stack.h"

void push(Stack st, int element) {
  if (element >= 0) {
    for (int i = 0; i < st.size; i++) {
      if (st.values[i] == -1) {
        st.values[i] = element;
        break;
      }
    }
  }
}

int pop(Stack st) {
  for (int i = 1; i < st.size; i++) {
    if (st.values[i] == -1) {
      int res = st.values[i - 1];
      st.values[i - 1] = -1;
      return res;
    }
    if (i + 1 == st.size) {
      int res = st.values[i];
      st.values[i] = -1;
      return res;
    }
  }
  return -1;
}