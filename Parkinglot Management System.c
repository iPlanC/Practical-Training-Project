#define DEBUG
#include "function.h"
#include "included.h"

int main(int argc, char* argv[]) {
	
	printf("+------------------------+\n");
	printf("| 欢迎来到停车场管理系统 |\n");
	printf("+------------------------+\n");

	if (Login() != 0) {
		printf("错误已至三次，请核对后重新运行。\n");
		return 1;
	}
	printf("登录成功，按任意键继续......\n");
	getchar();
	system("cls");
	printf("输入 \"help\" 以显示指令集\n");
	while (Statues() != 0);
	return 0;
}
