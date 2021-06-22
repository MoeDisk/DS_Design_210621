#include "parking.h"

int main(void){
	SeqStackCar Enter,Temp;
	LinkQueueCar Wait;
	int which;
	InitStack(&Enter);	//初始化车站
	InitStack(&Temp);	//初始化让路临时栈
	InitQueue(&Wait);	//初始化便道
	while(1){
		time_t rawtime;
		struct tm *info;
		char buffer[80];
		time( &rawtime );
		info = localtime( &rawtime );
		printf("欢迎！%s", asctime(info));
		printf("\t==========\n");
		printf("\t堆栈停车场\n");
		printf("\t==========\n\n");
		printf("\t好消息每分钟5角钱\n\n");
		printf("\t只有三位欲停从速\n\n");
		printf("\t> (1)停车\n");
		printf("\t> (2)提车\n");
		printf("\t> (3)详情\n");
		printf("\t> (4)退出\n");
		printf("\n你想干嘛：");
		while(1){
				scanf("%d",&which);
				if(which>=1 && which<=4)	break;
				else	printf("\n输入的什么玩意儿重新输：");
		}
			switch(which){
					case 1:
						arrival(&Enter,&Wait);
						system("pause");
						system("cls");
						break;
					case 2:
						leave(&Enter,&Temp,&Wait);
						system("pause");
						system("cls");
						break;
					case 3:
						list(Enter,Wait);
						leave(&Enter,&Temp,&Wait);
						system("pause");
						system("cls");
					case 4:
						MessageBox(NULL,"退了就别回来了","停车大师",MB_OK);
						exit(0);
					default:
						break;
				}
	}
}