#define DEBUG
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "function.h"

int main(int argc, char* argv[]) {
	
	printf("+------------------------+\n");
	printf("| 欢迎来到停车场管理系统 |\n");
	printf("+------------------------+\n");

	if (login() != 0) {
		printf("密码错误已至三次，请核对后重新运行。");
		return 1;
	}
	printf("登录成功，按任意键继续......\n");
	getchar();
	system("cls");
	printf("输入 \"help\" 以显示指令集\n");
	while (statues() != 1);
	return 0;
}
