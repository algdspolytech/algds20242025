#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Polinoms.h"

//инициализация очереди
void InitQueue(struct Queue* q)
{
	q->first = q->last = malloc(sizeof(struct monom));
	q->first = q->last = NULL;
}
//добавление в очередь
void Add2Queue(struct Queue* q, int coef, int pow)
{
	struct monom* p;

	p = malloc(sizeof(struct monom));
	p->coef = coef;
	p->pow = pow;
	p->next = NULL;
	if (q->last == NULL)
	{
		q->first = q->last = p;
		return;
	}
	if (q->first == NULL)
	{
		q->first = q->last = p;
		return;
	}
	q->last->next = p;
	q->last = p;
}



int atoistr(char* buf)
{
	char* buf1 = malloc(3 * sizeof(char));
	int i = 0;
	int j;

	while (buf[i] != '^')
	{
		i++;
	}

	for (j = 1; j < 4; j++)
	{
		if (buf[i + j] <= '9' && buf[i + j] >= '0')
		{
			buf1[j - 1] = buf[i + j];
		}
		else
		{
			break;
		}
	}

	return (atoi(buf1));
}

//чтение полинома из файла
void ReadPol(FILE* F, struct Queue* q)
{
	char* buf = malloc(10 * sizeof(char));
	int coef, pow;
	int i = 0;
	int j = 0;
	char ch;

	do
	{
		ch = fgetc(F);
		if (((ch == '-' || ch == '+') && i != 0) || ch == '\n' || ch == EOF)
		{
			if (strchr(buf, '*') != NULL)
			{
				if (strchr(buf, '^') != NULL && strchr(buf, 'x') != NULL)
				{
					coef = atoi(buf);
					pow = atoistr(buf);
				}
				else
				{
					coef = atoi(buf);
					pow = 1;
				}
			}
			else
			{
				if (buf[0] == '-')
				{
					if (strchr(buf, '^') != NULL)
					{
						coef = -1;
						pow = atoistr(buf);
					}
					else
					{
						if (strchr(buf, '^') == NULL && strchr(buf, 'x') != NULL)
						{
							coef = -1;
							pow = 1;
						}
						else
						{
							coef = atoi(buf);
							pow = 0;
						}
					}
				}
				if (buf[0] == '+')
				{
					if (strchr(buf, '^') != NULL)
					{
						coef = 1;
						pow = atoistr(buf);
					}
					else
					{
						if (strchr(buf, '^') == NULL && strchr(buf, 'x') != NULL)
						{
							coef = 1;
							pow = 1;
						}
						else
						{
							coef = atoi(buf);
							pow = 0;
						}
					}
				}
				if (buf[0] == 'x')
				{
					if (strchr(buf, '^') != NULL)
					{
						coef = 1;
						pow = atoistr(buf);
					}
					else
					{
						coef = 1;
						pow = 1;
					}
				}
			}
			Add2Queue(q, coef, pow);
			for (j = 0; j < 10; j++)
			{
				buf[j] = 's';
			}
			i = 0;
			buf[i] = ch;
			i++;
		}
		else
		{
			buf[i] = ch;
			i++;
		}
	} while (ch != '\n' && ch != EOF);
	free(buf);
}




void Sort(struct Queue* q)
{
	int size = 0;
	int i;
	int j;
	struct monom c;
	struct monom* p = q->first;

	//подсчёт количества элементов в очереди
	while (p != NULL)
	{
		size++;
		p = p->next;
	}
	//массив для хранения указателей на элементы очереди
	struct monom* arr = malloc(size * sizeof(struct monom));
	p = q->first;
	//заполняем массив указателями на элементы очереди
	for (i = 0; i < size; i++)
	{
		arr[i].pow = p->pow;
		arr[i].coef = p->coef;
		p = p->next;
	}
	//сортируем массив по степеням pow
	for (i = 0; i < size - 1; i++)
	{
		for (j = 0; j < size - i - 1; j++)
		{
			if (arr[j].pow > arr[j + 1].pow)
			{
				c = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = c;
			}
		}
	}
	//очищаем очередь
	while (q->first != NULL)
	{
		p = q->first;
		q->first = q->first->next;
		if (q->first == NULL)
		{
			q->last = NULL;
		}
		free(p);
	}
	//заполняем очередь отсортирорванными элементами
	for (i = 0; i < size; i++)
	{
		Add2Queue(q, arr[i].coef, arr[i].pow);
	}
}


void SupPol(struct Queue* q1, struct Queue* q2, struct Queue* q3)
{
	struct monom* p1 = q1->first;
	struct monom* p2 = q2->first;
	int sum;

	while (p1 != NULL && p2 != NULL)
	{
		if (p1->pow > p2->pow)
		{
			Add2Queue(q3, p2->coef, p2->pow);
			p2 = p2->next;
		}
		else
		{
			if (p1->pow < p2->pow)
			{
				Add2Queue(q3, p1->coef, p1->pow);
				p1 = p1->next;
			}
			else
			{
				sum = p1->coef + p2->coef;
				if (sum != 0)
				{
					Add2Queue(q3, sum, p1->pow);
					p1 = p1->next;
					p2 = p2->next;
				}
				else
				{
					p1 = p1->next;
					p2 = p2->next;
				}
			}
		}
	}
	while (p1 != NULL)
	{
		Add2Queue(q3, p1->coef, p1->pow);
		p1 = p1->next;
	}
	while (p2 != NULL)
	{
		Add2Queue(q3, p2->coef, p2->pow);
		p2 = p2->next;
	}
}

void PrintPol(struct Queue* q)
{
	struct monom* p = q->first;

	while (p != NULL)
	{
		printf("%i  %i  ", p->coef, p->pow);
		p = p->next;
	}
	printf("\n");
}


void WritePol(FILE* F, struct Queue* q)
{
	struct monom* p = q->first;
	int i = 0;
	char str[10];
	char str1[10];

	while (p != NULL)
	{
		if (p->pow == 0 && p->coef == -1)
		{
			fputs("-1", F);
		}
		else if (p->pow == 0 && p->coef == 1 && i == 0)
		{
			fputs("1", F);
		}
		else if (p->pow == 0 && p->coef == 1 && i != 0)
		{
			fputs("+1", F);
		}
		else if ((p->pow == 0 && p->coef < 0) || (p->pow == 0 && p->coef > 0 && i == 0))
		{
			snprintf(str, sizeof(str), "%i", p->coef);
			fputs(str, F);
		}
		else if (p->pow == 0 && p->coef > 0 && i != 0)
		{
			snprintf(str, sizeof(str), "%i", p->coef);
			fputs("+", F);
			fputs(str, F);
		}
		else if (p->pow == 1 && p->coef == 1 && i == 0)
		{
			fputs("x", F);
		}
		else if (p->pow == 1 && p->coef == 1 && i != 0)
		{
			fputs("+x", F);
		}
		else if (p->pow == 1 && p->coef == -1)
		{
			fputs("-x", F);
		}
		else if ((p->pow == 1 && p->coef < 0) || (p->pow == 1 && p->coef > 0 && i == 0))
		{
			snprintf(str, sizeof(str), "%i", p->coef);
			fputs(str, F);
			fputs("*x", F);
		}
		else if (p->pow == 1 && p->coef > 0 && i != 0)
		{
			snprintf(str, sizeof(str), "%i", p->coef);
			fputs("+", F);
			fputs(str, F);
			fputs("*x", F);
		}
		else if (p->coef == 1 && p->pow != 0 && p->pow != 1 && i == 0)
		{
			snprintf(str, sizeof(str), "%i", p->pow);
			fputs("x^", F);
			fputs(str, F);
		}
		else if (p->coef == 1 && p->pow != 0 && p->pow != 1 && i != 0)
		{
			snprintf(str, sizeof(str), "%i", p->pow);
			fputs("+x^", F);
			fputs(str, F);
		}
		else if (p->coef == -1 && p->pow != 0 && p->pow != 1)
		{
			snprintf(str, sizeof(str), "%i", p->pow);
			fputs("-x^", F);
			fputs(str, F);
		}
		else if (p->coef == 0)
		{

		}
		else
		{
			if ((p->coef > 0 && i == 0) || (p->coef < 0))
			{
				snprintf(str, sizeof(str), "%i", p->pow);
				snprintf(str1, sizeof(str), "%i", p->coef);
				fputs(str1, F);
				fputs("*x^", F);
				fputs(str, F);
			}
			else
			{
				snprintf(str, sizeof(str), "%i", p->pow);
				snprintf(str1, sizeof(str), "%i", p->coef);
				fputs("+", F);
				fputs(str1, F);
				fputs("*x^", F);
				fputs(str, F);
			}
		}
		p = p->next;
		i++;
	}

}
//приведение подобных слагаемых в полиноме
void SimilarTerm(struct Queue* q)
{
	struct monom* p = q->first;
	struct monom* pnext;
	int c;
	int pw;
	int flag = 0;

	while (p != NULL)
	{
		pnext = p->next;
		c = p->coef;
		pw = p->pow;

		if (pnext == NULL)
		{
			break;
		}

		while ((pw == pnext->pow))
		{
			c += pnext->coef;
			if (pnext->next == NULL)
			{
				flag = 1;
				break;
			}
			pnext = pnext->next;
		}
		if (flag == 1)
		{
			p->coef = c;
			q->last = p;
			q->last->next = NULL;
			p = pnext->next;
		}
		else
		{
			p->next = pnext;
			p->coef = c;
			p = p->next;
		}
	}
}

void MultiplicationPol(struct Queue* q1, struct Queue* q2, struct Queue* q3)
{
	struct monom* p1 = q1->first;
	struct monom* p2 = q2->first;

	while (p1 != NULL)
	{
		p2 = q2->first;
		while (p2 != NULL)
		{
			Add2Queue(q3, p1->coef * p2->coef, p1->pow + p2->pow);
			p2 = p2->next;
		}
		p1 = p1->next;
	}
	printf("\n");
	Sort(q3);

	SimilarTerm(q3);
}

void DerPol(struct Queue* q1)
{
	struct monom* p1 = q1->first;

	while (p1 != NULL)
	{
		if (p1->pow == 0)
		{
			q1->first = p1->next;
		}
		else
		{
			p1->coef = p1->coef * p1->pow;
			p1->pow = p1->pow - 1;
		}
		p1 = p1->next;
	}
}


void main(void)
{
	FILE* F;
	struct Queue q1, q2, q3, q4;

	if ((F = fopen("input.txt", "r")) == NULL)
	{
		printf("The file input.txt was not opened\n");
	}

	InitQueue(&q1);
	ReadPol(F, &q1);
	PrintPol(&q1);
	printf("\n");

	InitQueue(&q2);
	ReadPol(F, &q2);
	fclose(F);
	PrintPol(&q2);
	printf("\n");


	Sort(&q1);
	SimilarTerm(&q1);
	PrintPol(&q1);
	printf("\n");
	Sort(&q2);
	SimilarTerm(&q2);
	PrintPol(&q2);
	printf("\n");

	InitQueue(&q3);
	SupPol(&q1, &q2, &q3);
	PrintPol(&q3);
	printf("\n");

	FILE* F1 = fopen("output.txt", "w");
	if (F1)
	{
		WritePol(F1, &q3);
	}

	InitQueue(&q4);
	MultiplicationPol(&q1, &q2, &q4);
	PrintPol(&q4);

	fputs("\n", F1);
	WritePol(F1, &q4);

	printf("\n");
	DerPol(&q1);
	PrintPol(&q1);

	fputs("\n", F1);
	WritePol(F1, &q1);
	fclose(F1);

	RunTests();
}