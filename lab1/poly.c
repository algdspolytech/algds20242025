#include "poly.h"
#pragma warning (disable: 4996)

int is_sign(char c) {
	if (c > 47 && c < 58)
		return 2;
	else if (c == '+')
		return 1;
	else if (c == '-')
		return -1;
	else if (c == 94)
		return 3;
	else if (c == 120)
		return 'x';
	return 0;

}

char* int_to_char(const int number) {
	int c = abs(number);
	int i = 0;

	char* my_string = NULL;
	if (c == 0) {
		my_string = (char*)realloc(my_string, 2 * sizeof(char));
		if (!my_string) {
			return NULL;
		}
		my_string[0] = '0';
		my_string[1] = '\0';
		return my_string;
	}
	while (c > 0) {
		my_string = (char*)realloc(my_string, (i + 1) * sizeof(char));
		if (!my_string) {
			return NULL;
		}
		char chr = (char)((c % 10) + 48);
		my_string[i] = chr;
		c = c / 10;
		i++;
	}
	my_string = (char*)realloc(my_string, (i + 1) * sizeof(char));
	if (!my_string) {
		return NULL;
	}
	my_string[i] = '\0';
	return my_string;
}

poly_t* initialize_poly() {
	poly_t *poly = (poly_t*)malloc(sizeof(poly_t));
	if (!poly) {
		return NULL;
	}
	poly->head = NULL;
	poly->tail = NULL;
	return poly;
}

monom_t* find(poly_t *poly, int degree) {
	monom_t *this_p = poly->head;
	while (this_p) {
		if (this_p->degree == degree) {
			return this_p;
		}
		this_p = this_p->next;
	}
	return NULL;
}

monom_t* new_monom_in_begin(poly_t* poly, int degree, int coeff) {
	if (!poly) {
		return NULL;
	}

	monom_t* is_here = find(poly, degree);
	if (is_here) {
		is_here->coeff += coeff;
		return is_here;
	}

	monom_t* new_monom = (monom_t*)malloc(sizeof(monom_t));
	if (!new_monom) {
		return NULL;
	}

	new_monom->degree = degree;
	new_monom->coeff = coeff;
	new_monom->next = poly->head;

	poly->head = new_monom;
	if (!poly->tail) {
		poly->tail = new_monom;
	}
	return new_monom;
}


monom_t* new_monom_in_end(poly_t *poly, int degree, int coeff) {
	if (!poly) {
		return NULL;
	}

	if (!poly->head) {
		return new_monom_in_begin(poly, degree, coeff);
	}

	monom_t* is_here = find(poly, degree);
	if (is_here) {
		is_here->coeff += coeff;
		return is_here;
	}

	monom_t* new_monom = (monom_t*)malloc(sizeof(monom_t));
	if (!new_monom) {
		return NULL;
	}

	new_monom->degree = degree;
	new_monom->coeff = coeff;
	new_monom->next = NULL;

	poly->tail->next = new_monom;
	poly->tail = new_monom;
	return new_monom;
}

monom_t* new_monom_after_current(poly_t *poly, monom_t *last, int degree, int coeff) {
	if (!poly) {
		return NULL;
	}

	monom_t* is_here = find(poly, degree);
	if (is_here) {
		is_here->coeff += coeff;
		return is_here;
	}

	if (!last) {
		return new_monom_in_end(poly, degree, coeff);
	}
	monom_t* new_monom = (monom_t*)malloc(sizeof(monom_t));
	if (!new_monom) {
		return NULL;
	}

	new_monom->degree = degree;
	new_monom->coeff = coeff;
	new_monom->next = last->next;
	last->next = new_monom;

	if (poly->tail == last) {
		poly->tail = new_monom;
	}
	return new_monom;
}

monom_t* find_after_which(poly_t* poly, int degree) {
	monom_t *this_p = poly->head;
	if (!this_p) {
		return NULL;
	}
	this_p = this_p->next;
	monom_t *previous = poly->head;

	while (this_p) {
		if (this_p->degree > degree) {
			return previous;
		}
		previous = this_p;
		this_p = this_p->next;
	}
	return previous;
}

poly_t* sort_poly(poly_t* poly) {
	if (!poly || !poly->head) {
		return poly;
	}
	monom_t *this_p = poly->head;

	poly_t* new_poly = initialize_poly();
	monom_t* check = new_monom_in_begin(new_poly, this_p->degree, this_p->coeff);
	if (!check) {
		return NULL;
	}

	this_p = this_p->next;
	while (this_p) {
		if (this_p->degree < new_poly->head->degree) {
			monom_t* check = new_monom_in_begin(new_poly, this_p->degree, this_p->coeff);
			if (!check) {
				return NULL;
			}
		}
		else if (this_p->degree > new_poly->tail->degree) {
			monom_t* check = new_monom_in_end(new_poly, this_p->degree, this_p->coeff);
			if (!check) {
				return NULL;
			}
		}
		else {
			monom_t* last = find_after_which(new_poly, this_p->degree);
			monom_t* check = new_monom_after_current(new_poly, last, this_p->degree, this_p->coeff);
			if (!check) {
				return NULL;
			}
		}
		this_p = this_p->next;
	}
	return new_poly;
}

char* read_poly_from_file(FILE *file) {
	char *poly = NULL;
	char c;
	int length = 0;

	while ((c = fgetc(file)) != EOF && c != '\n') {
		poly = (char *)realloc(poly, (length + 1) * sizeof(char));
		if (!poly) {
			return NULL;
		}
		poly[length] = c;
		length++;
	}

	if (length > 0) {
		poly = (char *)realloc(poly, (length + 1) * sizeof(char));
		if (!poly) {
			return NULL;
		}
		poly[length] = '\0';
	}
	else {
		free(poly);
		return NULL;
	}
	return poly;
}

poly_t* read_poly_from_str(char* str) {
	int degree = 0;
	int coeff = 0;
	int sign = 0;
	bool was_x = false;

	if (str[0] == '\0') {
		return NULL;
	}

	poly_t* new_poly = initialize_poly();
	for (int i = 0; str[i] != '\0'; i++) {
		if (is_sign(str[i]) == 1 || is_sign(str[i]) == -1) {
			if (sign != 0) {
				if (was_x == false) degree = 0;
				if (was_x == true && degree == 0) degree = 1;
				if (was_x == true && coeff == 0) coeff = 1;
				monom_t* check = new_monom_in_end(new_poly, degree, sign*coeff);
				if (check == NULL) {
					return NULL;
				}
			}
			degree = 0, coeff = 0, sign = is_sign(str[i]), was_x = false;;
		}
		else {
			if (sign == 0) sign = 1;
			if (str[i] == 'x') was_x = true;
			if (is_sign(str[i]) == 2 && was_x == false) coeff = coeff * 10 + (int)(str[i] - '0');
			if (is_sign(str[i]) == 2 && was_x == true) degree = degree * 10 + (int)(str[i] - '0');
		}
	}
	if (was_x == false) degree = 0;
	if (was_x == true && degree == 0) degree = 1;
	if (was_x == true && coeff == 0) coeff = 1;
	monom_t* check = new_monom_in_end(new_poly, degree, sign*coeff);

	return new_poly;
}

int StrLength(char const* str) {
	int length = 0;
	while (str[length] != '\0') {
		length++;
	}
	return length;
}

void print_text(char* paragraph) {
	if (!paragraph)
		printf("It's NULL!\n");
	else {
		int i = 0;
		while (*(paragraph + i) != '\0') {
			printf("%c", *(paragraph + i));
			i++;
		}
		printf("\n");
	}
}

char* poly_in_str(poly_t* poly) {
	if (!poly) {
		return NULL;
	}
	monom_t *this_p = poly->head;
	if (!this_p) {
		return NULL;
	}
	char* str = NULL;
	size_t length = 0;
	while (this_p) {
		char* degree = int_to_char(this_p->degree);
		char* coeff = int_to_char(this_p->coeff);
		if (!degree || !coeff) {
			return NULL;
		}

		if ((this_p->coeff < 0 || this_p != poly->head)) {
			str = (char*)realloc(str, (length + 1) * sizeof(char));
			if (!str) {
				return NULL;
			}
			char sign = '-';
			if (this_p->coeff > 0) {
				sign = '+';
			}

			str[length] = sign;
			length += 1;
		}

		size_t len_coeff = StrLength(coeff);
		if ((this_p->coeff != 1 && this_p->coeff != -1) || this_p->degree == 0) {
			str = (char*)realloc(str, (length + len_coeff) * sizeof(char));
			if (!str) {
				free(coeff);
				return NULL;
			}
			for (int i = 0; i < len_coeff; i++) {
				str[length + i] = coeff[len_coeff - i - 1];
			}
			length += len_coeff;
		}
		free(coeff);
		size_t len_degree = StrLength(degree);
		if (this_p->degree == 0) {
			this_p = this_p->next;
			free(degree);
			continue;
		}
		if (this_p->coeff != 1 && this_p->coeff != -1) {
			str = (char*)realloc(str, (length + 1) * sizeof(char));
			if (!str) {
				free(degree);
				return NULL;
			}
			str[length] = '*';
			length += 1;
		}
		str = (char*)realloc(str, (length + 1) * sizeof(char));
		if (!str) {
			free(degree);
			return NULL;
		}
		str[length] = 'x';
		length += 1;
		if (this_p->degree == 1) {
			free(degree);
			this_p = this_p->next;
			continue;
		}
		str = (char*)realloc(str, (length + 1) * sizeof(char));
		if (!str) {
			free(degree);
			return NULL;
		}
		str[length] = '^';
		length += 1;

		str = (char*)realloc(str, (length + len_degree) * sizeof(char));
		if (!str) {
			free(degree);
			return NULL;
		}
		for (int i = 0; i < len_degree; i++) {
			str[length + i] = degree[len_degree - i - 1];
		}
		length += len_degree;
		free(degree);
		this_p = this_p->next;
	}
	str = (char*)realloc(str, (length + 1) * sizeof(char));
	str[length] = '\0';
	return str;
}

void free_poly(poly_t* poly) {
	if (poly) {
		if (poly->head) {
			monom_t* this_p = poly->head;
			while (this_p) {
				monom_t* del = this_p;
				this_p = this_p->next;
				free(del);
			}
		}
		free(poly);
	}
}

poly_t* diff_poly(poly_t* poly) {
	monom_t *this_p = poly->head;
	poly_t* new_poly = initialize_poly();
	if (!new_poly) {
		return NULL;
	}

	int coeff;
	int degree;
	while (this_p) {
		coeff = this_p->coeff * this_p->degree;
		degree = this_p->degree - 1;
		if (degree != -1 && coeff != 0) {
			monom_t* check = new_monom_in_end(new_poly, degree, coeff);
			if (!check) {
				return NULL;
			}
		}

		this_p = this_p->next;
	}
	return new_poly;
}

poly_t* copy_poly(poly_t* poly) {
	poly_t* new_poly = initialize_poly();
	if (!new_poly) {
		return NULL;
	}
	monom_t *this_p = poly->head;
	while (this_p) {
		monom_t* check = new_monom_in_end(new_poly, this_p->degree, this_p->coeff);
		if (!check) {
			return NULL;
		}
		this_p = this_p->next;
	}
	return new_poly;
}

poly_t* sum_poly(poly_t* poly1, poly_t* poly2) {
	if ((!poly1 || !poly1->head) && (!poly2 || !poly2->head)) {
		return NULL;
	}
	else if (!poly1 || !poly1->head) {
		return poly2;
	}
	else if (!poly2 || !poly2->head) {
		return poly1;
	}
	monom_t *this_p = poly2->head;
	poly_t* new_poly = copy_poly(poly1);
	if (!new_poly) {
		return NULL;
	}

	while (this_p) {
		monom_t* finding = find(new_poly, this_p->degree);
		if (!finding) {
			monom_t* check = new_monom_in_end(new_poly, this_p->degree, this_p->coeff);
			if (!check) {
				return NULL;
			}
		}
		else {
			finding->coeff = finding->coeff + this_p->coeff;
		}
		this_p = this_p->next;
	}
	return new_poly;
}

poly_t* mul_poly(poly_t* poly1, poly_t* poly2) {
	if ((!poly1 || !poly1->head) && (!poly2 || !poly2->head)) {
		return NULL;
	}
	else if (!poly1 || !poly1->head) {
		return poly2;
	}
	else if (!poly2 || !poly2->head) {
		return poly1;
	}
	monom_t *this_p1 = poly1->head;
	monom_t *this_p2 = poly2->head;
	poly_t* new_poly = initialize_poly();
	if (!new_poly) {
		return NULL;
	}

	int degree;
	int coeff;
	while (this_p1) {
		monom_t *this_p2 = poly2->head;
		while (this_p2) {
			degree = this_p1->degree + this_p2->degree;
			coeff = this_p1->coeff * this_p2->coeff;
			if (coeff == 0) {
				this_p2 = this_p2->next;
				continue;
			}
			monom_t* finding = find(new_poly, degree);
			if (!finding) {
				monom_t* check = new_monom_in_end(new_poly, degree, coeff);
				if (!check) {
					return NULL;
				}
			}
			else {
				finding->coeff = finding->coeff + coeff;
			}
			this_p2 = this_p2->next;
		}
		this_p1 = this_p1->next;
	}
	if (!new_poly || !(new_poly->head)) {
		return NULL;
	}
	return new_poly;
}

void print_coeffs(poly_t* list) {
	monom_t *this_p = list->head;

	printf("[");
	while (this_p) {
		printf("[%i, %i]", this_p->coeff, this_p->degree);
		this_p = this_p->next;
	}

	printf("]\n");
}

poly_t* create_poly_from_data(int* degrees, int* coeffs, int num_monoms) {
	poly_t *new_poly = initialize_poly();
	if (!new_poly) {
		return NULL;
	}

	for (int i = 0; i < num_monoms; i++) {
		monom_t* is_in = find(new_poly, degrees[i]);
		if (!is_in) {
			monom_t* check = new_monom_in_end(new_poly, degrees[i], coeffs[i]);
			if (!check) {
				return NULL;
			}
		}
		else {
			is_in->coeff += coeffs[i];
		}
	}
	return new_poly;
}

void output(char *filename, poly_t* poly1, poly_t* poly2, poly_t* poly3) {
	char *line1 = poly_in_str(poly1);
	char *line2 = poly_in_str(poly2);
	char *line3 = poly_in_str(poly3);

	FILE *file = fopen(filename, "w");
	if (!file) {
		printf("Opening Error\n");
		return;
	}

	fprintf(file, "%s\n%s\n%s\n", line1, line2, line3);
	fclose(file);

	free(line1);
	free(line2);
	free(line3);
}