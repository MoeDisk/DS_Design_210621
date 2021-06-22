#include "parking.h"

//初始化车场 
void InitStack(SeqStackCar *s){
	int i;
	s->top=0;
	for(i=0;i<=3;i++)	s->stack[s->top+i]=NULL;
}

//初始化便道
int InitQueue(LinkQueueCar *Q){
	Q->head=(QueueNode *)malloc(sizeof(QueueNode));
	if(Q->head!=NULL){
		Q->head->next=NULL;
		Q->rear=Q->head;
		return 1;
	}else return -1;
}

//出栈信息打印
void print(CarNode *p,int room){
    time_t u;
	struct tm *o;	//停车时间
	struct tm *l;	//驶离时间
	time (&u);
	o=localtime(&u);
	l=localtime(&u);
    p->leave.hour=l->tm_hour;
    p->leave.min=l->tm_min;
	int A1,A2,B1,B2;
	printf("\n你的车牌号:");
	puts(p->num);
	printf("\n你停车的时间: %d:%d",p->reach.hour,p->reach.min);
	printf("你走的时间: %d:%d",p->leave.hour,p->leave.min);
	A1=p->reach.hour;
	A2=p->reach.min;
	B1=p->leave.hour;
	B2=p->leave.min;
	printf("\n交停车费: %2.1f元",((B1-A1)*60+(B2-A2))*0.5);
	free(p);
}

//车辆进场
int arrival(SeqStackCar *Enter,LinkQueueCar *W){
    time_t u;
	struct tm *o;
	time (&u);
	o=localtime(&u);
	CarNode *p;
	QueueNode *t;
	p=(CarNode *)malloc(sizeof(CarNode));
	system("cls");
	printf("\n\t输入车牌号:\t");
	scanf("%s",p->num);
	//车场未满，车进车场，反之进便道
	if(Enter->top<3){
		Enter->top++;  //栈顶指针加1
		p->reach.hour=o->tm_hour;
		p->reach.min=o->tm_min;
		MessageBox(NULL,"停车成功","停车大师",MB_OK);
		printf("\n\t你的车停在：%d 号位置\n",Enter->top);
		printf("\n\t你停车的时间为：%d点%d分\n",o->tm_hour,o->tm_min);
		printf("\n");
		Enter->stack[Enter->top]=p;
		return 1;
	}else{
		system("cls");
		MessageBox(NULL,"车位抢没了请排队","停车大师",MB_OK);
		t=(QueueNode *)malloc(sizeof(QueueNode));
		t->data=p;
		t->next=NULL;
		W->rear->next=t;
		W->rear=t;
		return 1;
	}
}

//车辆离开
void leave(SeqStackCar *Enter,SeqStackCar *Temp,LinkQueueCar *W){
	int i, room;
    time_t u; //time_t是time.h定义的结构体
	struct tm *o; //停车时间
	time (&u);
	o=localtime(&u);
	CarNode *p,*t;
	QueueNode *q;
	//判断车场内是否有车
	if(Enter->top>0){
		//输入离开车辆的信息
		while(1){
		system("cls");
		printf("\n输入要出来的车在车场的位置(共%d个)：\n",Enter->top);
		scanf("%d",&room);
		if(room>=1&&room<=Enter->top)	break;
	}
    while(Enter->top>room){
      Temp->top++;
      Temp->stack[Temp->top]=Enter->stack[Enter->top];
      Enter->stack[Enter->top]=NULL;
      Enter->top--;
    }
    p=Enter->stack[Enter->top];
    Enter->stack[Enter->top]=NULL;
    Enter->top--;
    while(Temp->top>=1){
      Enter->top++;
      Enter->stack[Enter->top]=Temp->stack[Temp->top];
      Temp->stack[Temp->top]=NULL;
      Temp->top--;
    }
    print(p,room);
    //判断通道上是否有车及车站是否已满
	//便道的车辆进入车场
    if((W->head!=W->rear)&&Enter->top<3){
      q=W->head->next;
      t=q->data;
      Enter->top++;
      printf("\n便道的%s号车进入车场第%d位置.",t->num,Enter->top);
      printf("\n此车进入的时间为%d:%d",o->tm_hour,o->tm_min);
      t->reach.hour=o->tm_hour;
      t->reach.min=o->tm_min;
      W->head->next=q->next;
      if(q==W->rear)
		W->rear=W->head;
		Enter->stack[Enter->top]=t;
		free(q);
    }
  }
  else
    MessageBox(NULL,"车场里没有车","停车大师",MB_OK);
}
//列表显示车场信息
void list1(SeqStackCar *S){
  int i;
  //判断车站内是否有车
  if(S->top>0){
	system("cls");
	printf("\n车场:\n");
	printf("\n 位置 进场时间 车牌号\n\n");
    for(i=1;i<=S->top;i++){
      printf("  %d ",i);
      printf("    %d:%d ",S->stack[i]->reach.hour,S->stack[i]->reach.min);
      printf(" %s\n",S->stack[i]->num);
    }
  }else{
	    system("cls");
		MessageBox(NULL,"车场里没有车","停车大师",MB_OK);
  }
}

void list2(LinkQueueCar *W){
	QueueNode *p;
	p=W->head->next;
	//判断通道上是否有车
	if(W->head!=W->rear){
      system("cls");
    printf("\n等待车辆的车牌号为:\n\n");
    while(p!=NULL){
      puts(p->data->num);
      p=p->next;
    }
  }else{ 
    system("cls");
    MessageBox(NULL,"便道里没有车","停车大师",MB_OK);
	}
} 

void list(SeqStackCar S,LinkQueueCar W){
	int flag=1;
	int g;
	while(flag){
    	system("cls");
    	printf("\n\t详情：\n");
    	printf("\n\t>1.号位置车场\n\n\t>2.号位置便道\n\n\t>3.退出\n\n");
    while(1){
      	scanf("%d",&g);
      	if(g>=1 || g<=3)	break;
	    else	printf("\n请选择 1|2|3:");
    }
    switch(g){
    	case 1:
      		list1(&S);
      		system("pause");
      		system("cls");
      		break;  //列表显示车场信息
    	case 2:
      		list2(&W);
      		system("pause");
      		system("cls");
      		break;  //列表显示便道信息
    	case 3:
		    exit(0);
		default: break;
    }
  }
}
