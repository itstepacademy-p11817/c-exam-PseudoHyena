#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <conio.h>
#include <string.h>

#ifndef DATA_COUNT
#define DATA_COUNT 7
#endif // !DATA_COUNT

#ifndef MAX_NAME
#define MAX_NAME 21
#endif // !MAX_NAME

#ifndef MAX_NUMBER
#define MAX_NUMBER 15
#endif // !MAX_NUMBER

typedef struct {
	char first_name[MAX_NAME];
	char last_name[MAX_NAME];
	char* phone_number;
	char* work_number;
	char street[MAX_NAME];
	char house[MAX_NAME];
	char flat[MAX_NAME];
	

} person_t;

void cleanBuf();

int download_info(person_t** persons, int* persons_size);

int load_info(person_t** persons, int* persons_size);

void add_person(person_t** persons, int* persons_size, bool just_name, char* phone_number);

void display(person_t person);

void display_all(person_t** persons, int* persons_size);

int search(person_t** persons, int* persons_size, char* mode, bool get_person, person_t* target, bool get_input_number, char** number);

void edit_person(person_t *person);

void delete_person(int num, person_t** persons, int* persons_size);

void callIn(person_t** persons, int* persons_size, char* mode);

int search_neighbors(person_t** persons, int* persons_size, char* mode);