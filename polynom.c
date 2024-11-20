#include "l1_polynom.h"
#pragma warning (disable: 4996)

int is_sign(char sym) {
    if (sym > 47 && sym < 58)
        return 2;
    else if (sym == '+')
        return 1;
    else if (sym == '-')
        return -1;
    else if (sym == 94)
        return 3;
    else if (sym == 120)
        return 'x';
    return 0;
}

char* int_to_char(const int number) {
    int abs_num = abs(number);
    int iter = 0;

    char* result_str = NULL;
    if (abs_num == 0) {
        result_str = (char*)realloc(result_str, 2 * sizeof(char));
        if (!result_str) {
            return NULL;
        }
        result_str[0] = '0';
        result_str[1] = '\0';
        return result_str;
    }
    while (abs_num > 0) {
        result_str = (char*)realloc(result_str, (iter + 1) * sizeof(char));
        if (!result_str) {
            return NULL;
        }
        char digit_char = (char)((abs_num % 10) + 48);
        result_str[iter] = digit_char;
        abs_num = abs_num / 10;
        iter++;
    }
    result_str = (char*)realloc(result_str, (iter + 1) * sizeof(char));
    if (!result_str) {
        return NULL;
    }
    result_str[iter] = '\0';
    return result_str;
}

poly_t* initialize_poly() {
    poly_t* poly_inst = (poly_t*)malloc(sizeof(poly_t));
    if (!poly_inst) {
        return NULL;
    }
    poly_inst->head = NULL;
    poly_inst->tail = NULL;
    return poly_inst;
}

monom_t* find(poly_t* poly_inst, int degree) {
    monom_t* mon = poly_inst->head;
    while (mon) {
        if (mon->degree == degree) {
            return mon;
        }
        mon = mon->next;
    }
    return NULL;
}

monom_t* new_monom_in_begin(poly_t* poly_inst, int degree, int coeff) {
    if (!poly_inst) {
        return NULL;
    }

    monom_t* mon_present = find(poly_inst, degree);
    if (mon_present) {
        mon_present->coeff += coeff;
        return mon_present;
    }

    monom_t* new_monom = (monom_t*)malloc(sizeof(monom_t));
    if (!new_monom) {
        return NULL;
    }

    new_monom->degree = degree;
    new_monom->coeff = coeff;
    new_monom->next = poly_inst->head;

    poly_inst->head = new_monom;
    if (!poly_inst->tail) {
        poly_inst->tail = new_monom;
    }
    return new_monom;
}

monom_t* new_monom_in_end(poly_t* poly_inst, int degree, int coeff) {
    if (!poly_inst) {
        return NULL;
    }

    if (!poly_inst->head) {
        return new_monom_in_begin(poly_inst, degree, coeff);
    }

    monom_t* mon_present = find(poly_inst, degree);
    if (mon_present) {
        mon_present->coeff += coeff;
        return mon_present;
    }

    monom_t* new_monom = (monom_t*)malloc(sizeof(monom_t));
    if (!new_monom) {
        return NULL;
    }

    new_monom->degree = degree;
    new_monom->coeff = coeff;
    new_monom->next = NULL;

    poly_inst->tail->next = new_monom;
    poly_inst->tail = new_monom;
    return new_monom;
}

monom_t* new_monom_after_current(poly_t* poly_inst, monom_t* last_monom, int degree, int coeff) {
    if (!poly_inst) {
        return NULL;
    }

    monom_t* mon_present = find(poly_inst, degree);
    if (mon_present) {
        mon_present->coeff += coeff;
        return mon_present;
    }

    if (!last_monom) {
        return new_monom_in_end(poly_inst, degree, coeff);
    }
    monom_t* new_monom = (monom_t*)malloc(sizeof(monom_t));
    if (!new_monom) {
        return NULL;
    }

    new_monom->degree = degree;
    new_monom->coeff = coeff;
    new_monom->next = last_monom->next;
    last_monom->next = new_monom;

    if (poly_inst->tail == last_monom) {
        poly_inst->tail = new_monom;
    }
    return new_monom;
}

monom_t* find_after_which(poly_t* poly_inst, int degree) {
    monom_t* current_monom = poly_inst->head;
    if (!current_monom) {
        return NULL;
    }
    current_monom = current_monom->next;
    monom_t* prev_monom = poly_inst->head;

    while (current_monom) {
        if (current_monom->degree > degree) {
            return prev_monom;
        }
        prev_monom = current_monom;
        current_monom = current_monom->next;
    }
    return prev_monom;
}

poly_t* sort_poly(poly_t* poly_inst) {
    if (!poly_inst  !poly_inst->head) {
        return poly_inst;
    }
    monom_t* current_monom = poly_inst->head;

    poly_t* sorted_poly = initialize_poly();
    monom_t* insert_check = new_monom_in_begin(sorted_poly, current_monom->degree, current_monom->coeff);
    if (!insert_check) {
        return NULL;
    }

    current_monom = current_monom->next;
    while (current_monom) {
        if (current_monom->degree < sorted_poly->head->degree) {
            monom_t* insert_check = new_monom_in_begin(sorted_poly, current_monom->degree, current_monom->coeff);
            if (!insert_check) {
                return NULL;
            }
        }
        else if (current_monom->degree > sorted_poly->tail->degree) {
            monom_t* insert_check = new_monom_in_end(sorted_poly, current_monom->degree, current_monom->coeff);
            if (!insert_check) {
                return NULL;
            }
        }
        else {
            monom_t* prev_monom = find_after_which(sorted_poly, current_monom->degree);
            monom_t* insert_check = new_monom_after_current(sorted_poly, prev_monom, current_monom->degree, current_monom->coeff);
            if (!insert_check) {
                return NULL;
            }
        }
        current_monom = current_monom->next;
    }
    return sorted_poly;
}

char* read_poly_from_file(FILE* file) {
    char* polynomial_str = NULL;
    char symbol;
    int str_len = 0;

    while ((symbol = fgetc(file)) != EOF && symbol != '\n') {
        polynomial_str = (char*)realloc(polynomial_str, (str_len + 1) * sizeof(char));
        if (!polynomial_str) {
            return NULL;
        }
        polynomial_str[str_len] = symbol;
        str_len++;
    }

    if (str_len > 0) {
        polynomial_str = (char*)realloc(polynomial_str, (str_len + 1) * sizeof(char));
        if (!polynomial_str) {
            return NULL;
        }
        polynomial_str[str_len] = '\0';
    }
    else {
        free(polynomial_str);
        return NULL;
    }
    return polynomial_str;
}

poly_t* read_poly_from_str(char* str) {
    int deg = 0;
    int co = 0;
    int sgn = 0;
    bool has_x = false;

    if (str[0] == '\0') {
        return NULL;
    }

    poly_t* new_poly = initialize_poly();
    for (int i = 0; str[i] != '\0'; i++) {
        if (is_sign(str[i]) == 1  is_sign(str[i]) == -1) {
            if (sgn != 0) {
                if (!has_x) deg = 0;
                if (has_x && deg == 0) deg = 1;
                if (has_x && co == 0) co = 1;
                monom_t* check_insert = new_monom_in_end(new_poly, deg, sgn * co);
                if (check_insert == NULL) {
                    return NULL;
                }
            }
            deg = 0, co = 0, sgn = is_sign(str[i]), has_x = false;
        }
        else {
            if (sgn == 0) sgn = 1;
            if (str[i] == 'x') has_x = true;
            if (is_sign(str[i]) == 2 && !has_x) co = co * 10 + (int)(str[i] - '0');
            if (is_sign(str[i]) == 2 && has_x) deg = deg * 10 + (int)(str[i] - '0');
        }
    }
    if (!has_x) deg = 0;
    if (has_x && deg == 0) deg = 1;
    if (has_x && co == 0) co = 1;
    monom_t* check_insert = new_monom_in_end(new_poly, deg, sgn * co);
    if (check_insert == NULL) {
        return NULL;
    }
    return new_poly;
}
//
// Created by User on 20.11.2024.
//
