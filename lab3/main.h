#ifndef MAIN_H
#define MAIN_H

#include <stdbool.h>

#define MAX_TASKS 1000  // Максимальное количество задач

#ifdef __cplusplus
extern "C" {
#endif
	
	// Структура для представления задачи
	typedef struct {
		int cost;
		int id;
	} Task;

	// Функции для обработки задач
	bool read_tasks(const char* filename, Task* tasks, int* task_count, int* K);
	bool process_schedule(const Task* tasks, int task_count, int K, int* result_schedule);
	void write_schedule(const char* filename, const int* schedule, int task_count);


#ifdef __cplusplus
}
#endif

#endif 