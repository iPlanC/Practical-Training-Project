#define DEBUG
#define totalspace			100
#define realusername		"PlanC"
#define realuserpassword	"password"
#include "included.h"

int cars = 0;
int costperhour = 2;
int spacepointer = 0;

struct parkingspace {
	int time;
	int parkserial;
	char carserial[5];
};

struct Parkinglot {
	struct parkingspace ParkingSpace[totalspace];
} Parkinglot;

int Login() {
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

void Park() {
	printf("car serial:");
	scanf("%s", Parkinglot.ParkingSpace[spacepointer].carserial);
	cars++;
	spacepointer++;
}

void Show_map() {
	int i = 0;
	printf("共有 %d 辆汽车\n", spacepointer);
	printf("车 牌\t时 间\t缴 费\n");
	for (i = 0; i < spacepointer; i++) printf("%s\t%d\t%d\n", Parkinglot.ParkingSpace[i].carserial, Parkinglot.ParkingSpace[i].time, Parkinglot.ParkingSpace[i].time * costperhour);
}

void Time_Jump() {
	int i = 0;
	int hour = 0;
	printf("请输入要跳过的时长");
	scanf("%d", &hour);
	for (i = 0; i < spacepointer; i++) Parkinglot.ParkingSpace[i].time += hour;
}

int Statues() {
	char command[20] = {"\0"};
	printf("PMS >");
	scanf("%s", command);
	if (strcmp(command, "cls") == 0) {
		system("cls");
		return 1;
	}

	if (strcmp(command, "help") == 0) {
		printf("\tcls  - 清理历史操作\n");
		printf("\tearn - 显示历史收入(TODO)\n");
		printf("\texit - 退出此程序\n");
		printf("\thelp - 输出此列表\n");
		printf("\tjump - 将时间增加 n 小时\n");
		printf("\tleft - 登记指定车牌号的车离库(TODO)\n");
		printf("\tmap  - 查看停车场状况\n");
		printf("\tpark - 新增入库车辆\n");
		printf("\tPMS  - 显示自述文字(TODO)\n");
		return 2;
	}

	if (strcmp(command, "jump") == 0) {
		Time_Jump();
		return 3;
	}

	if (strcmp(command, "map") == 0) {
		Show_map();
		return 4;
	}

	if (strcmp(command, "park") == 0) {
		Park();
		return 5;
	}

	if (strcmp(command, "exit") == 0) {
		printf("程序已退出\n");
		return 0;
	}
	return 0;
}
