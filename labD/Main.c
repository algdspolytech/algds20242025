#include <stdio.h>
#include "labD.h"
int main()
{

	int N, B, resSize;
	int A[MAX_N], dp[MAX_N], res[MAX_N];
	int flag = 0;
	if (!readFile("input.txt", &B, &N, &A, &dp))
	{
		return 1;
	}
	sum_size(&B, &N, &A, &dp, 0, &flag, &res, &resSize);
	Write("output.txt", &res, &flag, &resSize);
	printf_s("%d", resSize);
	return 0;
}