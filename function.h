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
		printf("�������û���:");
		scanf("%s", inputusername);
		if (strcmp(inputusername, realusername) != 0) {
			if (retrytimes == 0) {
				printf("���δ��󣬳����˳���\n");
				return 1;
			}
			continue;
		}
		else {
			break;
		}
	}
	
	while (retrytimes--) {
		printf("����������:");
		for (i = 0; i < 8; i++) inputpassword[i] = getch();
		inputpassword[8] = '\0';
		if (strcmp(inputpassword, realuserpassword) != 0) {
			if (retrytimes == 0) {
				printf("���δ��󣬳����˳���\n");
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
	printf("1.����ÿСʱͣ����(��Ϊ \"%d\" )\n", costperhour);
	printf("2.����VIP�ͻ��б�(���� \"%d\" λ)\n", VIPcounter);
	printf("3.����VIP�ۿ�(��Ϊ \"%.0f\" ��)\n", VIPdiscount * 10);
	printf("4.����ͣ������λ��(��Ϊ \"%d\" )\n", totalspace);
	printf("������ѡ���Ը�����Ӧ����\n");
	scanf("%d", &select);
	switch (select) {
	case 1:
		printf("��������ĺ��ͣ���� >");
		scanf("%d", &costperhour);
		break;
	case 2:
		printf("�������µ�VIP�ͻ� >");
		scanf("%s", serial);
		strcpy(VIPlist.VIP[VIPcounter].carserial, serial);
		VIPcounter++;
		break;
	case 3:
		printf("�������µ�VIP�ۿ� >");
		scanf("%f", &VIPdiscount);
		break;
	case 4:
		printf("�������µĳ�λ�� >");
		scanf("%d", &totalspace);
		break;
	}
}

void Count_earn() {
	printf("������ \"%d\" �� \"%d\" Сʱ������ \"%.2f\" rmb��\n", runninghour / 24, runninghour % 24, totalearn);
}

void Help() {
	printf("\tcfg  - ������ز���\n");
	printf("\tcls  - ������ʷ����\n");
	printf("\tearn - ��ʾ��ʷ����\n");
	printf("\texit - �˳��˳���\n");
	printf("\thelp - ������б�\n");
	printf("\tjump - ��ʱ������ n Сʱ\n");
	printf("\tleft - �Ǽ�ָ�����ƺŵĳ����\n");
	printf("\tmap  - �鿴ͣ����״��\n");
	printf("\tpark - ������⳵��\n");
	printf("\tPMS  - ��ʾ��������\n");
	printf("  ��ע�⣬�����κδ��� \"TODO\" ��ǩ������ᵼ����ʾ�������\n\n");
}

void Time_jump() {
	int i = 0;
	int hour = 0;
	printf("������Ҫ������ʱ��");
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
	printf("��������⳵�ƺţ�");
	scanf("%s", serial);
	for (i = 0; i < spacepointer; i++) {
		if (strcmp(Parkinglot.ParkingSpace[i].carserial, serial) == 0) {
			flag = 1;
			cost = (float)(Parkinglot.ParkingSpace[i].time * costperhour);
			if (Parkinglot.ParkingSpace[i].isVIP == 1) cost = cost * VIPdiscount;
			totalearn = totalearn + cost;
			printf("���ƺ� \"%s\" ������⣬��Ų�� \"%d\" ����������ʣ�� \"%d\" ��������ȡͣ���� \"%.2f\" Ԫ������������ \"%.2f\" Ԫ��\n", serial, spacepointer - i - 1, spacepointer - 1, cost, totalearn);
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
		printf("δ�ҵ����ƺţ���˶Ժ����ԡ�\n");
		return;
	}
}

void Show_map() {
	int i = 0;
	printf("���� %d ������\n", spacepointer);
	printf("�� λ\t�� ��\tʱ ��\t�� ��\n");
	for (i = 0; i < spacepointer; i++) {
		printf("%3d\t%s\t%d h\t%d rmb\n", Parkinglot.ParkingSpace[i].parkserial + 1, Parkinglot.ParkingSpace[i].carserial, Parkinglot.ParkingSpace[i].time, Parkinglot.ParkingSpace[i].time * costperhour);
	}
	printf("���� \"%d\" �����ڱ���ȴ���\n", sidewaypointer);
}

void Park() {
	int i = 0;
	char serial[5] = {'\0'};
	printf("��������⳵�ƺţ�");
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
		printf("���ƺ� \"%s\" ��ͣ��\n", Parkinglot.ParkingSpace[spacepointer].carserial);
		spacepointer++;
	}
	else {
		strcpy(Sideway.ParkingSpace[sidewaypointer].carserial, serial);
		printf("�������������ƺ� \"%s\" ��ͣ���������\n", Sideway.ParkingSpace[sidewaypointer].carserial);
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
		printf("�������˳�\n");
		return 0;
	}
	printf("δ�ҵ����� \"%s\" ����˶Ժ����ԡ�\n", command);
	return -1;
}
