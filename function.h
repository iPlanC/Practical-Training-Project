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
		printf("�������û���:");
		scanf("%s", inputusername);
		if (strcmp(inputusername, realusername) != 0) {
			if (retrytimes == 3) {
				printf("���δ��󣬳����˳���");
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
		for (i = 0; i < 8; i++) inputpassword = getch();
		inputpassword[8] = "\0";
		if (strcmp(inputpassword, realuserpassword) != 0) {
			if (retrytimes == 3) {
				printf("���δ��󣬳����˳�");
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
	printf("���� %d ������\n", spacepointer);
	printf("�� ��\tʱ ��\t�� ��\n");
	for (i = 0; i < spacepointer; i++) printf("%s\t%d\t%d\n", Parkinglot.ParkingSpace[i].carserial, Parkinglot.ParkingSpace[i].time, Parkinglot.ParkingSpace[i].time * costperhour);
}

void Time_Jump() {
	int i = 0;
	int hour = 0;
	printf("������Ҫ������ʱ��");
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
		printf("\tcls  - ������ʷ����\n");
		printf("\tearn - ��ʾ��ʷ����(TODO)\n");
		printf("\texit - �˳��˳���\n");
		printf("\thelp - ������б�\n");
		printf("\tjump - ��ʱ������ n Сʱ\n");
		printf("\tleft - �Ǽ�ָ�����ƺŵĳ����(TODO)\n");
		printf("\tmap  - �鿴ͣ����״��\n");
		printf("\tpark - ������⳵��\n");
		printf("\tPMS  - ��ʾ��������(TODO)\n");
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
		printf("�������˳�\n");
		return 0;
	}
	return 0;
}
