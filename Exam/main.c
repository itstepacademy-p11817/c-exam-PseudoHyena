////////////////////////////////////////////
//          ��������������� ������        //
//              ������� ������            //
////////////////////////////////////////////
//               ����������               //
//1) �������������� � �������� ��������   //
//   ������ �� ������� ���������, ��� ��� //
//   ��� ���������. (����� � �������      //
//   ������������ ������� �����, �� ����- //
//   �������� ��� ��� �� �����))          //
//2) �� ���� ���� �������, ��� ������ ��� //
//   ��� �� ���������: ��������� "�����   //
//   ������" ���� �� �����.               //
//3) �������������� ������� ��� ��        //
//   ���������, �� ����� ��������� �������//
//   ���� �� �� �������, ������ �� �������//
//   �� 4, ������� 4 ����� ���������, ��� //
//   2, 3, 5, 6, ��� � 3, 5, 2, 6. �����, //
//   ��� �� ����� ��������))              //
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
		printf("������ �������� �����!\n");
		system("pause");
		return 1;
	}

	printf("1) ������� add, ����� �������� ����� �������\n");
	printf("2) ������� edit, ����� ������������� �������\n");
	printf("3) ������� del, ����� ������� ������� �������\n");
	printf("4) ������� call, ����� ���������\n");
	printf("5) ������� display, ����� ������� ���� ������\n");
	printf("6) ������� search, ����� ����� �������(�)\n");
	printf("7) ������� save ��� ��������������� ����������\n");
	printf("8) ������� exit, ����� ������� ����������\n\n");


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
				printf("������ �������� ���!\n");
			}
		}
		else if (strcmp(input, "del") == 0) {
			int num = search(&persons, &persons_size, "number", false, NULL, false, NULL);

			if (num != -1) {
				delete_person(num, &persons, &persons_size);
			}
			else {
				printf("������ �������� ���!\n");
			}
		}
		else if (strcmp(input, "call") == 0) {
			printf("1) ������� �������\n");
			printf("2) ������� �����\n");

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
			printf("1) ������ ������� �� ������� �����\n");
			printf("2) ������ �������� �� �����\n");
			printf("3) ������ �������� �� �������\n");
			printf("4) ������ ������� �� ������\n");
			printf("5) ������ ��� �������� ����\n");
			printf("6) ������ ��������� �������\n");

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
			printf("����� ������� ���, ��� ��� ������� �������!\n");
		}
	}

	load_info(&persons, &persons_size);

	return 0;
}