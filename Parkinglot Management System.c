#define DEBUG
#include "function.h"
#include "included.h"

int main(int argc, char* argv[]) {
	
	printf("+------------------------+\n");
	printf("| ��ӭ����ͣ��������ϵͳ |\n");
	printf("+------------------------+\n");

	if (Login() != 0) {
		printf("��������������Σ���˶Ժ��������С�");
		return 1;
	}
	printf("��¼�ɹ��������������......\n");
	getchar();
	system("cls");
	printf("���� \"help\" ����ʾָ�\n");
	while (Statues() != 0);
	return 0;
}
