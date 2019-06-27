#define DEBUG
#define Defaultspace		1
#define realusername		"PlanC"
#define realuserpassword	"password"
#include "included.h"

int cars = 0;
int totalspace = 1;
float VIPdiscount = 0.0;
int VIPcounter = 0;
int runninghour = 0;
int runningdays = 0;
float totalearn = 0.0;
int costperhour = 1;
int spacepointer = 0;
int sidewaypointer = 0;

struct vip {
	char carserial[5];
};

struct viplist {
	struct vip VIP[100];
} VIPlist;

struct parkingspace {
	int time;
	int isVIP;
	int parkserial;
	char carserial[5];
};

struct Parkinglot {
	struct parkingspace ParkingSpace[Defaultspace];
} Parkinglot;

struct sideway {
	struct parkingspace ParkingSpace[1000000];
} Sideway;

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
			if (retrytimes == 0) {
				printf("三次错误，程序退出。\n");
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
		for (i = 0; i < 8; i++) inputpassword[i] = getch();
		inputpassword[8] = '\0';
		if (strcmp(inputpassword, realuserpassword) != 0) {
			if (retrytimes == 0) {
				printf("三次错误，程序退出。\n");
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

void Config() {
	int i = 0;
	int select = 0;
	char serial[5] = {'\0'};
	printf("1.更改每小时停车费(现为 \"%d\" )\n", costperhour);
	printf("2.更改VIP客户列表(现有 \"%d\" 位)\n", VIPcounter);
	printf("3.更改VIP折扣(现为 \"%.0f\" 折)\n", VIPdiscount * 10);
	printf("4.更改停车场车位数(现为 \"%d\" )\n", totalspace);
	printf("请输入选项以更改相应内容\n");
	scanf("%d", &select);
	switch (select) {
	case 1:
		printf("请输入更改后的停车费 >");
		scanf("%d", &costperhour);
		break;
	case 2:
		printf("请输入新的VIP客户 >");
		scanf("%s", serial);
		strcpy(VIPlist.VIP[VIPcounter].carserial, serial);
		VIPcounter++;
		break;
	case 3:
		printf("请输入新的VIP折扣 >");
		scanf("%f", &VIPdiscount);
		break;
	case 4:
		printf("请输入新的车位数 >");
		scanf("%d", &totalspace);
		break;
	}
}

void Count_earn() {
	printf("共计在 \"%d\" 天 \"%d\" 小时，收入 \"%.2f\" rmb。\n", runninghour / 24, runninghour % 24, totalearn);
}

void Help() {
	printf("\tcfg  - 更改相关参数\n");
	printf("\tcls  - 清理历史操作\n");
	printf("\tearn - 显示历史收入\n");
	printf("\texit - 退出此程序\n");
	printf("\thelp - 输出此列表\n");
	printf("\tjump - 将时间增加 n 小时\n");
	printf("\tleft - 登记指定车牌号的车离库\n");
	printf("\tmap  - 查看停车场状况\n");
	printf("\tpark - 新增入库车辆\n");
	printf("\tPMS  - 显示自述文字\n");
	printf("  请注意，运行任何带有 \"TODO\" 标签的命令都会导致提示命令错误\n\n");
}

void Time_jump() {
	int i = 0;
	int hour = 0;
	printf("请输入要跳过的时长");
	scanf("%d", &hour);
	for (i = 0; i < spacepointer; i++) {
		Parkinglot.ParkingSpace[i].time += hour;
	}
	runninghour += hour;
}

void Leave() {
	int i = 0;
	int flag = 0;
	float cost = 0.0;
	char serial[5] = {'\0'};
	printf("请输入出库车牌号：");
	scanf("%s", serial);
	for (i = 0; i < spacepointer; i++) {
		if (strcmp(Parkinglot.ParkingSpace[i].carserial, serial) == 0) {
			flag = 1;
			cost = (float)(Parkinglot.ParkingSpace[i].time * costperhour);
			if (Parkinglot.ParkingSpace[i].isVIP == 1) cost = cost * VIPdiscount;
			totalearn = totalearn + cost;
			printf("车牌号 \"%s\" 请求离库，需挪动 \"%d\" 辆车，车库剩余 \"%d\" 辆车，收取停车费 \"%.2f\" 元，今日总收入 \"%.2f\" 元。\n", serial, spacepointer - i - 1, spacepointer - 1, cost, totalearn);
			for (; i < spacepointer; i++) {
				strcpy(Parkinglot.ParkingSpace[i - 1].carserial, Parkinglot.ParkingSpace[i].carserial);
				Parkinglot.ParkingSpace[i - 1].parkserial = Parkinglot.ParkingSpace[i].parkserial;
				Parkinglot.ParkingSpace[i - 1].time = Parkinglot.ParkingSpace[i].time;
			}
			if (sidewaypointer != 0) {
				strcpy(Parkinglot.ParkingSpace[totalspace - 1].carserial, Sideway.ParkingSpace[0].carserial);
				Parkinglot.ParkingSpace[totalspace - 1].parkserial = totalspace;
				Parkinglot.ParkingSpace[totalspace - 1].time = 0;
				sidewaypointer--;
			}
			else {
				spacepointer--;
			}
			break;
		}
	}
	if (flag != 1) {
		printf("未找到车牌号，请核对后重试。\n");
		return;
	}
}

void Show_map() {
	int i = 0;
	printf("共有 %d 辆汽车\n", spacepointer);
	printf("车 位\t车 牌\t时 间\t缴 费\n");
	for (i = 0; i < spacepointer; i++) {
		printf("%3d\t%s\t%d h\t%d rmb\n", Parkinglot.ParkingSpace[i].parkserial + 1, Parkinglot.ParkingSpace[i].carserial, Parkinglot.ParkingSpace[i].time, Parkinglot.ParkingSpace[i].time * costperhour);
	}
	printf("共有 \"%d\" 辆车在便道等待。\n", sidewaypointer);
}

void Park() {
	int i = 0;
	char serial[5] = {'\0'};
	printf("请输入入库车牌号：");
	scanf("%s", serial);
	if (spacepointer < totalspace) {
		strcpy(Parkinglot.ParkingSpace[spacepointer].carserial, serial);
		Parkinglot.ParkingSpace[spacepointer].time = 0;
		for (i = 0; i < VIPcounter; i++) {
			if (strcmp(Parkinglot.ParkingSpace[spacepointer].carserial, VIPlist.VIP[i].carserial) == 0) {
				Parkinglot.ParkingSpace[spacepointer].isVIP = 1;
			}
			else {
				Parkinglot.ParkingSpace[spacepointer].isVIP = 0;
			}
		}
		printf("车牌号 \"%s\" 已停放\n", Parkinglot.ParkingSpace[spacepointer].carserial);
		spacepointer++;
	}
	else {
		strcpy(Sideway.ParkingSpace[sidewaypointer].carserial, serial);
		printf("车库已满，车牌号 \"%s\" 已停放至便道。\n", Sideway.ParkingSpace[sidewaypointer].carserial);
		sidewaypointer++;
	}
	cars++;
}

int Statues() {
	int i = 0;
	char command[20] = {"\0"};
	for (i = 0; i < totalspace; i++) Parkinglot.ParkingSpace[i].parkserial = i;
	printf("PMS >");
	scanf("%s", command);
	if (strcmp(command, "cfg") == 0) {
		Config();
		return 9;
	}
	if (strcmp(command, "cls") == 0) {
		system("cls");
		return 1;
	}

	if (strcmp(command, "earn") == 0) {
		Count_earn();
		return 2;
	}
	if (strcmp(command, "help") == 0) {
		Help();
		return 3;
	}

	if (strcmp(command, "jump") == 0) {
		Time_jump();
		return 4;
	}

	if (strcmp(command, "left") == 0) {
		Leave();
		return 5;
	}

	if (strcmp(command, "map") == 0) {
		Show_map();
		return 6;
	}

	if (strcmp(command, "park") == 0) {
		Park();
		return 7;
	}

	if (strcmp(command, "PMS") == 0) {
		system("notepad .\\LICENSE");
		return 8;
	}

	if (strcmp(command, "exit") == 0) {
		printf("程序已退出\n");
		return 0;
	}
	printf("未找到命令 \"%s\" ，请核对后重试。\n", command);
	return -1;
}
