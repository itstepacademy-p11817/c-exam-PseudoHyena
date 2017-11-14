////////////////////////////////////////////
//          Экзаминационная работа        //
//              Багнюка Артема            //
////////////////////////////////////////////
//               Примечания               //
//1) Редактирование и удаление доступно   //
//   только по номерам телефонов, так как //
//   они уникальны. (Потом я добавил      //
//   уникальность полного имени, но пере- //
//   писывать код уже не хотел))          //
//2) Из слов выше следует, что полное имя //
//   так же уникально: несколько "Артем   //
//   Багнюк" быть не может.               //
//3) Дополнительное задание так же        //
//   выполнено, но вывод ближайших соседей//
//   идет не по порядку, пример из задания//
//   кв 4, соседей 4 может выглядеть, как //
//   2, 3, 5, 6, так и 3, 5, 2, 6. Думаю, //
//   это не имеет значения))              //
////////////////////////////////////////////


#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <locale.h>
#include "directory.h"

int main() {
	setlocale(LC_ALL, "russian");

	person_t* persons = NULL;
	int persons_size = 0;

	if (download_info(&persons, &persons_size) == 1) {
		printf("Ошибка открытия файла!\n");
		system("pause");
		return 1;
	}

	printf("1) Введите add, чтобы добавить новый контакт\n");
	printf("2) Введите edit, чтобы редактировать контакт\n");
	printf("3) Введите del, чтобы удалить контакт контакт\n");
	printf("4) Введите call, чтобы позвонить\n");
	printf("5) Введите display, чтобы вывести весь список\n");
	printf("6) Введите search, чтобы найти контакт(ы)\n");
	printf("7) Введите save для принудительного сохранения\n");
	printf("8) Введите exit, чтобы закрыть приложение\n\n");


	char input[10];
	while (true) {
		printf("command: ");
		gets_s(input, 10);

		if (strcmp(input, "add") == 0) {
			add_person(&persons, &persons_size, false, NULL);
		}
		else if (strcmp(input, "edit") == 0) {
			int num = search(&persons, &persons_size, "number", false, NULL, false, NULL);
			if (num != -1) {
				edit_person(&persons[num]);
			}
			else {
				printf("Такого контакта нет!\n");
			}
		}
		else if (strcmp(input, "del") == 0) {
			int num = search(&persons, &persons_size, "number", false, NULL, false, NULL);

			if (num != -1) {
				delete_person(num, &persons, &persons_size);
			}
			else {
				printf("Такого контакта нет!\n");
			}
		}
		else if (strcmp(input, "call") == 0) {
			printf("1) Выбрать контакт\n");
			printf("2) Набрать номер\n");

			char ans = 0;
			while (true) {
				printf("ans: ");
				scanf_s("%c", &ans);
				cleanBuf();

				if (ans == '1') {
					callIn(&persons, &persons_size, "contact");
					break;
				}
				else if (ans == '2') {
					callIn(&persons, &persons_size, "number");
					break;
				}
			}
		}
		else if (strcmp(input, "display") == 0) {
			display_all(&persons, &persons_size);
			printf("\n");
		}
		else if (strcmp(input, "search") == 0) {
			printf("1) Искать контакт по полному имени\n");
			printf("2) Искать контакты по имени\n");
			printf("3) Искать контакты по фамилии\n");
			printf("4) Искать контакт по номеру\n");
			printf("5) Искать все контакты дома\n");
			printf("6) Искать ближайших соседей\n");

			char ans = 0;
			while (true) {
				printf("ans: ");
				scanf_s("%c", &ans);
				cleanBuf();

				if (ans == '1') {
					search(&persons, &persons_size, "fullname", false, NULL, false, NULL);
					printf("\n");
					break;
				}
				else if (ans == '2') {
					search(&persons, &persons_size, "firstname", false, NULL, false, NULL);
					break;
				}
				else if (ans == '3') {
					search(&persons, &persons_size, "lastname", false, NULL, false, NULL);
					break;
				}
				else if (ans == '4') {
					search(&persons, &persons_size, "number", false, NULL, false, NULL);
					printf("\n");
					break;
				}
				else if (ans == '5') {
					search_neighbors(&persons, &persons_size, "all");
					break;
				}
				else if (ans == '6') {
					search_neighbors(&persons, &persons_size, "nearby");
					break;
				}
			}
		}
		else if (strcmp(input, "save") == 0) {
			load_info(&persons, &persons_size);
		}
		else if (strcmp(input, "exit") == 0) {
			break;
		}
		else {
			printf("Такой команды нет, или она введена неверно!\n");
		}
	}

	load_info(&persons, &persons_size);

	return 0;
}