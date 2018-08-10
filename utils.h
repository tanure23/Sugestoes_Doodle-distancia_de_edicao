#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int mod(int x);

int min(int a, int b, int c);

int pruning(int edit_limit, char* input, char* now);

int edit_distance(char* input, char* now);

char* write_in_str(char* dest, int distance);

void suggestions_printer(int how_many, char* recommended_name);

#endif /*UTILS_H*/