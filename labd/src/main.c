#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000

int elements[MAX_N];

void read_input(uint32_t *B, int *N, const char *file_name) {
  FILE *file = fopen(file_name, "r");
  fscanf(file, "%u", B);
  fscanf(file, "%d", N);
  for (int i = 0; i < *N; i++) {
    fscanf(file, "%d", &elements[i]);
  }
  fclose(file);
}

// решил при помощи алгоритма поиска с возвратом

void find_answer(uint32_t B, int N, const char *output_file) {
  int found = 0;
  // массив с элементами в текущей сумме
  int *idx = calloc(N, sizeof(int));
  int size = 0;
  int current_sum = 0;

  for (int i = 0; i < N; i++) {
    current_sum += elements[i];

    if (current_sum > B) {
      current_sum -= elements[i];
    } else {
      idx[size] = i;
      size++;
    }

    if (current_sum == B) {
      found = 1;
      FILE *file = fopen(output_file, "w");
      for (int j = 0; j < size; j++) {
        fprintf(file, "%d ", elements[idx[j]]);
      }
      fprintf(file, "\n");
      fclose(file);
      break;
    }

    // возврат к предпоследнему значению
    if (i == N - 1 && size > 0) {
      i = idx[size - 1];
      current_sum -= elements[idx[size - 1]];
      idx[size - 1] = 0;
      size--;
      if (i == N - 1 && size > 0) {
        i = idx[size - 1];
        current_sum -= elements[idx[size - 1]];
        idx[size - 1] = 0;
        size--;
      }
    }
  }

  if (!found) {
    FILE *file = fopen(output_file, "w");
    fprintf(file, "0\n");
    fclose(file);
  }

  free(idx);
}

void check_answer(const char *file_name, int res) {
  FILE *file = fopen(file_name, "r");
  int number;
  int sum = 0;
  while (fscanf(file, "%d", &number) == 1) {
    sum += number;
  }
  fclose(file);
  assert(res == sum);
}

int main() {
  uint32_t B;
  int N;

  // тест на общую работоспособность
  read_input(&B, &N, "res/input1.txt");
  find_answer(B, N, "res/output1.txt");
  check_answer("res/output1.txt", B);
  // тест на возвращение назад и игнорирование элементов, приводящих к неверному
  // результату
  read_input(&B, &N, "res/input2.txt");
  find_answer(B, N, "res/output2.txt");
  check_answer("res/output2.txt", B);
  // тест для B, которое больше суммы всех чисел
  read_input(&B, &N, "res/input3.txt");
  find_answer(B, N, "res/output3.txt");
  check_answer("res/output3.txt", 0);
  // тест для B, которое меньше всех чисел
  read_input(&B, &N, "res/input4.txt");
  find_answer(B, N, "res/output4.txt");
  check_answer("res/output4.txt", 0);

  return 0;
}
