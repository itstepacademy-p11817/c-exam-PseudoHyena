#include "directory.h"

void cleanBuf() {
	while (getchar() != '\n');
}

int download_info(person_t** persons, int* persons_size) {
	FILE* file = NULL;
	fopen_s(&file, "database.txt", "r");

	if (file == NULL) {
		fopen_s(&file, "database.txt", "w");
		fclose(file);
		
		return 0;
	}

	char string[MAX_NAME];
	int str_count = 0;

	while (fgets(string, MAX_NAME, file) != NULL) {
		if (string[0] != '\n') {
			str_count++;
		}
	}

	fseek(file, 0, SEEK_SET);

	if (str_count % DATA_COUNT != 0) {
		fclose(file);
		return 1;
	}

	*persons_size = str_count / DATA_COUNT;
	*persons = (person_t*)(malloc((*persons_size) * sizeof(person_t)));

	person_t person;

	for (int i = 0; i < *persons_size; ++i) {
		fgets(string, MAX_NAME, file);
		string[strlen(string) - 1] = '\0';
		strcpy_s(person.first_name, MAX_NAME, string);

		fgets(string, MAX_NAME, file);
		string[strlen(string) - 1] = '\0';
		strcpy_s(person.last_name, MAX_NAME, string);

		fgets(string, MAX_NUMBER, file);
		string[strlen(string) - 1] = '\0';
		person.phone_number = (char*)(malloc(MAX_NUMBER * sizeof(char)));
		strcpy_s(person.phone_number, MAX_NUMBER, string);

		fgets(string, MAX_NUMBER, file);
		string[strlen(string) - 1] = '\0';
		person.work_number = (char*)(malloc(MAX_NUMBER * sizeof(char)));
		strcpy_s(person.work_number, MAX_NUMBER, string);

		fgets(string, MAX_NAME, file);
		string[strlen(string) - 1] = '\0';
		strcpy_s(person.street, MAX_NAME, string);

		fgets(string, MAX_NAME, file);
		string[strlen(string) - 1] = '\0';
		strcpy_s(person.house, MAX_NAME, string);

		fgets(string, MAX_NAME, file);
		if (i != *persons_size - 1) {
			string[strlen(string) - 1] = '\0';
		}
		strcpy_s(person.flat, MAX_NAME, string);

		(*persons)[i] = person;
	}

	fclose(file);
	return 0;
}

int load_info(person_t** persons, int* persons_size) {
	FILE* temp_file = NULL;
	fopen_s(&temp_file, "database.temp", "w+");

	for (int i = 0; i < *persons_size; ++i) {
		fprintf(temp_file, (*persons)[i].first_name);
		fprintf(temp_file, "\n");
		fprintf(temp_file, (*persons)[i].last_name);
		fprintf(temp_file, "\n");
		fprintf(temp_file, (*persons)[i].phone_number);
		fprintf(temp_file, "\n");
		fprintf(temp_file, (*persons)[i].work_number);
		fprintf(temp_file, "\n");
		fprintf(temp_file, (*persons)[i].street);
		fprintf(temp_file, "\n");
		fprintf(temp_file, (*persons)[i].house);
		fprintf(temp_file, "\n");
		fprintf(temp_file, (*persons)[i].flat);
		if (i != *persons_size - 1) {
			fprintf(temp_file, "\n");
		}
	}

	FILE* file = NULL;
	fopen_s(&file, "database.txt", "w");

	fseek(temp_file, 0, SEEK_SET);
	char string[MAX_NAME];

	while (fgets(string, MAX_NAME, temp_file) != NULL) {
		if (string[0] != '\n') {
			fprintf(file, string);
		}
	}

	fclose(temp_file);
	fclose(file);
}

void add_person(person_t** persons, int* persons_size, bool just_name, char* phone_number) {
	person_t person;

	char fullname[MAX_NAME * 2];
	char fullname2[MAX_NAME * 2];

	bool break_flag = true;

	while (true) {
		break_flag = true;

		printf("Введите имя: ");
		gets_s(person.first_name, MAX_NAME);

		printf("Введите фамилию: ");
		gets_s(person.last_name, MAX_NAME);
		
		strcpy_s(fullname, MAX_NAME * 2, person.first_name);
		strcat_s(fullname, MAX_NAME * 2, " ");
		strcat_s(fullname, MAX_NAME * 2, person.last_name);

		for (int i = 0; i < *persons_size; ++i) {
			strcpy_s(fullname2, MAX_NAME * 2, (*persons)[i].first_name);
			strcat_s(fullname2, MAX_NAME * 2, " ");
			strcat_s(fullname2, MAX_NAME * 2, (*persons)[i].last_name);

			if (strcmp(fullname, fullname2) == 0) {
				printf("В базе уже есть этот контакт!\n");
				break_flag = false;
				break;
			}
		}

		if (break_flag == true) {
			break;
		}
	}
	
	if (just_name == false) {
		char self_number[MAX_NUMBER];
		char work_number[MAX_NUMBER];

		while (true) {
			break_flag = true;

			printf("Введите личный номер: ");
			gets_s(self_number, MAX_NUMBER);

			for (int i = 0; i < *persons_size; ++i) {
				if (strcmp(self_number, (*persons)[i].phone_number) == 0) {
					printf("В базе уже есть такой номер!\n");
					break_flag = false;
					break;
				}
			}

			if (break_flag == true) {
				break;
			}
		}

		char input = 0;
		while (true) {
			printf("Добавить рабочий телефон? (y/n): ");
			scanf_s("%c", &input);
			cleanBuf();

			if (input == 'n') {
				person.work_number = "none";
				break;
			}
			else if (input == 'y') {
				while (true) {
					break_flag = true;

					printf("Введите рабочий номер: ");
					gets_s(work_number, MAX_NUMBER);

					for (int i = 0; i < *persons_size; ++i) {
						if (strcmp(work_number, (*persons)[i].work_number) == 0) {
							printf("В базе уже есть такой номер!\n");
							break_flag = false;
							break;
						}
					}

					if (break_flag == true) {
						break;
					}
				}

				person.work_number = (char*)(malloc(MAX_NUMBER * sizeof(char)));
				strcpy_s(person.work_number, MAX_NUMBER, work_number);

				break;
			}
		}

		person.phone_number = (char*)(malloc(MAX_NUMBER * sizeof(char)));
		strcpy_s(person.phone_number, MAX_NUMBER, self_number);
	}
	else {
		person.phone_number = phone_number;
		person.work_number = "none";
	}
	
	char input = 0;
	while (true) {
		printf("Жилая площадь в наличии? (y/n): ");
		scanf_s("%c", &input);
		cleanBuf();

		if (input == 'n') {
			strcpy_s(person.street, MAX_NAME, "none");
			strcpy_s(person.house, MAX_NAME, "none");
			strcpy_s(person.flat, MAX_NAME, "none");
			break;
		}
		else if (input == 'y') {
			printf("Введите название улицы: ");
			gets_s(person.street, MAX_NAME);

			printf("Введите номер дома: ");
			gets_s(person.house, MAX_NAME);

			printf("Введите номер квартиры: ");
			gets_s(person.flat, MAX_NAME);

			break;
		}
	}

	(*persons_size) += 1;
	*persons = (person_t*)(realloc(*persons, (*persons_size) * sizeof(person_t)));
	(*persons)[(*persons_size) - 1] = person;
}

void display(person_t person) {
	printf("##########################################\n");
	printf("#Name: %s ", person.first_name);
	printf("%s:", person.last_name);
	for (int i = strlen(person.first_name) + strlen(person.last_name); i < 32; ++i) {
		printf(" ");
	}
	printf("#\n");
	printf("#Phone: %s", person.phone_number);
	for (int i = strlen(person.phone_number); i < 33; ++i) {
		printf(" ");
	}
	printf("#\n");
	printf("#Work phone: %s", person.work_number);
	for (int i = strlen(person.work_number); i < 28; ++i) {
		printf(" ");
	}
	printf("#\n");
	printf("#Street: %s", person.street);
	for (int i = strlen(person.street); i < 32; ++i) {
		printf(" ");
	}
	printf("#\n");
	printf("#House: %s", person.house);
	for (int i = strlen(person.house); i < 33; ++i) {
		printf(" ");
	}
	printf("#\n");
	printf("#Flat: %s", person.flat);
	for (int i = strlen(person.flat); i < 34; ++i) {
		printf(" ");
	}
	printf("#\n");
	printf("##########################################\n");
}

void display_all(person_t** persons, int* persons_size) {
	for (int i = 0; i < *persons_size; ++i) {
		for (int j = 0; j < *persons_size; ++j) {
			if (strcmp((*persons)[i].first_name, (*persons)[j].first_name) < 0) {
				person_t temp;
				temp = (*persons)[i];
				(*persons)[i] = (*persons)[j];
				(*persons)[j] = temp;
			}
			else if (strcmp((*persons)[i].first_name, (*persons)[j].first_name) == 0) {
				if (strcmp((*persons)[i].last_name, (*persons)[j].last_name) < 0) {
					person_t temp;
					temp = (*persons)[i];
					(*persons)[i] = (*persons)[j];
					(*persons)[j] = temp;
				}
			}
		}
	}

	for (int i = 0; i < *persons_size; ++i) {
		display((*persons)[i]);
	}
}

int search(person_t** persons, int* persons_size, char* mode, bool get_person , person_t* target, bool get_input_number, char** number) {
	int first_in = -1;

	if (strcmp(mode, "fullname") == 0) {
		char input[MAX_NAME * 2];
		
		printf("Введите полное имя: ");
		gets_s(input, MAX_NAME * 2);

		for (int i = 0; i < *persons_size; ++i) {
			char fullname[MAX_NAME * 2] = "";
			strcat_s(fullname, MAX_NAME * 2, (*persons)[i].first_name);
			strcat_s(fullname, MAX_NAME * 2, " ");
			strcat_s(fullname, MAX_NAME * 2, (*persons)[i].last_name);

			if (strcmp(fullname, input) == 0) {
				first_in = i;
				
				if (get_person == true) {
					*target = (*persons)[i];
					return first_in;
				}
				else {
					display((*persons)[i]);
					return first_in;
				}
			}
		}

		return first_in;
	}
	else if (strcmp(mode, "firstname") == 0) {
		char input[MAX_NAME];

		printf("Введите имя: ");
		gets_s(input, MAX_NAME);

		int count_finded = 0;

		for (int i = 0; i < *persons_size; ++i) {
			if (strcmp((*persons)[i].first_name, input) == 0) {
				if (count_finded == 0) {
					first_in = i;
				}

				count_finded++;

				display((*persons)[i]);
			}
		}

		printf("Total: %d\n\n", count_finded);

		return first_in;
	}
	else if (strcmp(mode, "lastname") == 0) {
		char input[MAX_NAME];

		printf("Введите фамилию: ");
		gets_s(input, MAX_NAME);

		int count_finded = 0;

		for (int i = 0; i < *persons_size; ++i) {
			if (strcmp((*persons)[i].last_name, input) == 0) {
				if (count_finded == 0) {
					first_in = i;
				}

				count_finded++;

				display((*persons)[i]);
			}
		}

		printf("Total: %d\n\n", count_finded);

		return first_in;
	}
	else if (strcmp(mode, "number") == 0){
		char input[MAX_NUMBER];

		printf("Введите номер: ");
		gets_s(input, MAX_NUMBER);

		if (get_input_number == true) {
			strcpy_s((*number), MAX_NUMBER, input);
		}

		for (int i = 0; i < *persons_size; ++i) {
			if (strcmp((*persons)[i].phone_number, input) == 0 ||
				strcmp((*persons)[i].work_number, input) == 0) {
				
				first_in = i;

				if (get_person == true) {
					*target = (*persons)[i];
					return first_in;
				}
				else {
					display((*persons)[i]);
					return first_in;
				}
			}
		}

		return first_in;
	}

}

void edit_person(person_t *person) {
	char input = 0;

	while (true) {
		printf("Изменить имя?(y/n): ");
		scanf_s("%c", &input);
		cleanBuf();

		if (input == 'n') {
			break;
		}
		else if (input == 'y') {
			printf("Введите имя: ");
			gets_s((*person).first_name, MAX_NAME);
			break;
		}
	}

	while (true) {
		printf("Изменить фамилию?(y/n): ");
		scanf_s("%c", &input);
		cleanBuf();

		if (input == 'n') {
			break;
		}
		else if (input == 'y') {
			printf("Введите фамилию: ");
			gets_s((*person).last_name, MAX_NAME);
			break;
		}
	}

	while (true) {
		printf("Изменить личный номер?(y/n): ");
		scanf_s("%c", &input);
		cleanBuf();

		if (input == 'n') {
			break;
		}
		else if (input == 'y') {
			printf("Введите личный номер: ");
			gets_s((*person).phone_number, MAX_NUMBER);
			break;
		}
	}

	while (true) {
		printf("Изменить рабочий номер?(y/n): ");
		scanf_s("%c", &input);
		cleanBuf();

		if (input == 'n') {
			break;
		}
		else if (input == 'y') {
			printf("Введите номер: ");
			gets_s((*person).work_number, MAX_NUMBER);
			break;
		}
	}

	while (true) {
		printf("Изменить улицу?(y/n): ");
		scanf_s("%c", &input);
		cleanBuf();

		if (input == 'n') {
			break;
		}
		else if (input == 'y') {
			printf("Введите название улицы: ");
			gets_s((*person).street, MAX_NAME);
			break;
		}
	}

	while (true) {
		printf("Изменить номер дома?(y/n): ");
		scanf_s("%c", &input);
		cleanBuf();

		if (input == 'n') {
			break;
		}
		else if (input == 'y') {
			printf("Введите номер: ");
			gets_s((*person).house, MAX_NAME);
			break;
		}
	}

	while (true) {
		printf("Изменить номер квартиры?(y/n): ");
		scanf_s("%c", &input);
		cleanBuf();

		if (input == 'n') {
			break;
		}
		else if (input == 'y') {
			printf("Введите номер: ");
			gets_s((*person).flat, MAX_NAME);
			break;
		}
	}
}

void delete_person(int num, person_t** persons, int* persons_size) {
	for (int i = num; i < *persons_size - 1; ++i) {
		(*persons)[i] = (*persons)[i + 1];
	}

	(*persons_size) -= 1;
	*persons = (person_t*)(realloc(*persons, (*persons_size) * sizeof(person_t)));
}

void callIn(person_t** persons, int* persons_size, char* mode) {
	person_t person;
	
	if (mode == "contact") {
		if (search(persons, persons_size, "fullname", true, &person, false, NULL) != -1) {
			if (strcmp(person.work_number, "none") == 0) {
				printf("Colling %s %s\nnumber: %s\n", person.first_name, person.last_name, person.phone_number);
				system("pause");
				return;
			}
			else {
				printf("1) Звонить на личный номер\n");
				printf("2) Звонить на рабочий номер\n");

				char input = 0;
				while (true) {
					printf("Ответ: ");
					scanf_s("%c", &input);
					cleanBuf();

					if (input == '1') {
						printf("Colling %s %s\nnumber: %s\n", person.first_name, person.last_name, person.phone_number);
						system("pause");
						return;
					}
					else if (input == '2') {
						printf("Colling %s %s\nnumber: %s\n", person.first_name, person.last_name, person.work_number);
						system("pause");
						return;
					}
				}
			}
		}
		else {
			printf("Такого контакта нет!\n");
			return;
		}
	}
	else if (mode == "number") {
		char* input_number = (char*)(malloc(MAX_NUMBER * sizeof(char)));

		if (search(persons, persons_size, "number", true, &person, true, &input_number) != -1) {
			printf("Colling %s %s\nnumber: %s\n", person.first_name, person.last_name, input_number);
			system("pause");
			return;
		}
		else {
			printf("Colling %s\n", input_number);
			system("pause");

			char input = 0;
			while (true) {
				printf("\nХотите добавить номер в контакты?(y/n): ");
				scanf_s("%c", &input);
				cleanBuf();

				if (input == 'n') {
					return;
				}
				else if (input == 'y') {
					add_person(persons, persons_size, true, input_number);
					return;
				}
			}
		}
	}
}

int search_neighbors(person_t** persons, int* persons_size, char* mode) {
	int find_count = -1;
	
	if (strcmp(mode, "nearby") == 0) {
		char street[MAX_NAME];
		char house[MAX_NAME];
		
		int flat_num = 0;
		int nearby_count = 0;

		printf("Введите название улицы: ");
		gets_s(street, MAX_NAME);

		printf("Введите номер дома: ");
		gets_s(house, MAX_NAME);

		printf("Введите номер квартиры: ");
		scanf_s("%d", &flat_num);
		cleanBuf();

		printf("Введите количество ближайших соседей: ");
		scanf_s("%d", &nearby_count);
		cleanBuf();

		bool isError = true;

		for (int i = 0; i < *persons_size; ++i) {
			if (strcmp((*persons)[i].street, street) == 0) {
				isError = false;
				break;
			}
		}

		if (isError == false) {
			isError = true;

			int l = (flat_num - nearby_count / 2 < 0) ? 1 : flat_num - nearby_count / 2;
			int r = (flat_num - nearby_count / 2 < 0) ? nearby_count + 1 : flat_num + nearby_count - nearby_count / 2;

			for (int i = 0; i < *persons_size; ++i) {
				if (strcmp((*persons)[i].house, house) == 0) {
					isError = false;
					
					for (int j = l; j <= r; ++j) {

						if (j == flat_num) {
							continue;
						}

						char num[MAX_NAME];
						sprintf_s(num, MAX_NAME, "%d", j);

						if (strcmp((*persons)[i].flat, num) == 0) {
							find_count++;
							display((*persons)[i]);
						}
					}
				}
			}

			if (isError == true) {
				printf("Проживающих в этотм доме нет!\n");
			}
			else {
				printf("Total: %d\n\n", find_count + 1);
			}

			return find_count;
		}

		printf("Проживающих по этой улице нет!\n");
		return find_count;
	}
	else if (strcmp(mode, "all") == 0) {
		char street[MAX_NAME];
		char house[MAX_NAME];

		printf("Введите название улицы: ");
		gets_s(street, MAX_NAME);

		printf("Введите номер дома: ");
		gets_s(house, MAX_NAME);

		bool isError = true;

		for (int i = 0; i < *persons_size; ++i) {
			if (strcmp((*persons)[i].street, street) == 0) {
				isError = false;
				break;
			}
		}

		if (isError == false) {
			isError = true;

			for (int i = 0; i < *persons_size; ++i) {
				if (strcmp((*persons)[i].house, house) == 0) {
					isError = false;
					find_count++;
					display((*persons)[i]);
				}
			}

			if (isError == true) {
				printf("Проживающих в этотм доме нет!\n");
			}
			else {
				printf("Total: %d\n\n", find_count + 1);
			}
			
			return find_count;
		}

		printf("Проживающих по этой улице нет!\n");
		return find_count;
	}
}