#define DEBUG
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "function.h"

int main(int argc, char* argv[]) {
	
	printf("+------------------------+\n");
	printf("| ��ӭ����ͣ��������ϵͳ |\n");
	printf("+------------------------+\n");

	if (login() != 0) {
		printf("��������������Σ���˶Ժ��������С�");
		return 1;
	}
	printf("��¼�ɹ��������������......\n");
	getchar();
	system("cls");
	printf("���� \"help\" ����ʾָ�\n");
	while (statues() != 1);
	return 0;
}
