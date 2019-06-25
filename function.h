#define DEBUG
#define totalspace			100
#define realusername		"PlanC"
#define realuserpassword	"password"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cars = 0;
int spacepointer = 0;

struct parkingspace {
	int time;
	int parkserial;
	char carserial[5];
};

struct Parkinglot {
	struct parkingspace ParkingSpace[totalspace];
} Parkinglot;

int login() {
	int i = 0;
	int retrytimes = 3;
	char inputusername[10] = {"\0"};
	char inputpassword[15] = {"\0"};

#ifdef RELEASE
	while (retrytimes--) {
		printf("请输入用户名:");
		scanf("%s", inputusername);
		if (strcmp(inputusername, realusername) != 0) {
			if (retrytimes == 3) {
				printf("三次错误，程序退出。");
				return 1;
			}
			continue;
		}
		else {
			break;
		}
	}
	
	while (retrytimes--) {
		printf("请输入密码:");
		for (i = 0; i < 8; i++) inputpassword = getch();
		inputpassword[8] = "\0";
		if (strcmp(inputpassword, realuserpassword) != 0) {
			if (retrytimes == 3) {
				printf("三次错误，程序退出");
				return 2;
			}
			continue;
		}
		else {
			break;
		}
	}
#endif
	return 0;
}

int statues() {
	char command[20] = {"\0"};
	printf("PMS >");
	scanf("%s", command);
	if (strcmp(command, "cls") == 0) {
		system("cls");
		return 4;
	}
	if (strcmp(command, "park") == 0) {
		cars++;
		spacepointer++;
		if (spacepointer != totalspace) {
			sscanf(command, "%*s%s", Parkinglot.ParkingSpace[spacepointer].carserial);
		}
		return 3;
	}
	if (strcmp(command, "help") == 0) {
		printf("\tcls  - 清理历史操作\n");
		printf("\texit - 退出此程序\n");
		printf("\thelp - 输出此列表\n");
		printf("\tjump - 将时间增加一小时\n");
		printf("\tmap  - 查看停车场状况\n");
		printf("\tpark - 新增入库车辆\n");
		return 2;
	}
	if (strcmp(command, "exit") == 0) {
		printf("程序已退出\n");
		return 1;
	}
	return 0;
}
