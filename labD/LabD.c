#include <stdio.h>
#include "LabD.h"

int readFile(const char* filename, int* B, int* N, int* A, int* flagArr)
{
	FILE* file = fopen(filename, "r");
	if (!file)
	{
		printf("File is empty or not opening.\n");
		return 0;
	}


	fscanf_s(file, "%d", B);
	fscanf_s(file, "%d", N);
	for (int i = 0;i < *N;i++)
	{
		fscanf_s(file, "%d", &A[i]);
		flagArr[i] = 0;
	}

	fclose(file);

	return 1;
}

void Write(const char* filename, int* res, int* flag, int* resSize)
{
	FILE* file = fopen(filename, "w");
	if (!file)
	{
		printf("File is empty or not opening.\n");
		return 0;
	}

	if (*flag == 0)
	{
		fprintf(file, "0");
		return;
	}

	int i = 0;
	for (int i = 0; i < *resSize; i++)
	{
		fprintf(file, "%d ", res[i]);
	}
	fclose(file);
}

void sum_size(int* B, int* N, int* A, int dp[], int presum, int* flag, int* res, int* resSize)
{
	if (*flag == 1 || presum > *B)
	{

		return;
	}
	if ((presum == *B) && (*B != 0))
	{
		*resSize = 0;
		for (int i = 0;i < *N;i++)
		{
			if (dp[i] == 1)
			{
				res[*resSize] = A[i];
				(*resSize)++;
			}
		}
		*flag = 1;
		return;
	}

	for (int i = 0;i < *N;i++)
	{
		if (dp[i] == 0)
		{
			dp[i] = 1;
			presum += A[i];
		}
		else continue;
		sum_size(B, N, A, dp, presum, flag, res, resSize);
		dp[i] = 0;
		presum -= A[i];
	}

}