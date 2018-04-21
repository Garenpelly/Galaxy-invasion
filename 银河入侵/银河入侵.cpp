/********************************************
//Title:��������

//Team: SuperMaker

//Headman: Haijun Ma

//Team member: Hao Liu, Yan Liu, Yubing Liu, Ziheng Li 

//Time:2017/6/20
********************************************/
# include <conio.h>
# include <stdio.h> 
# include <windows.h>
# include <stdlib.h>
# include <math.h>
# include <time.h>
#include <graphics.h> 
#pragma comment(lib,"Winmm.lib") //��Ƶ����ͷ�ļ� 

bool shujv[100]; //��Ϣ���� 


clock_t d1 = clock();
clock_t d2 = clock();

bool switch_back_music=true;          //�������ֿ���
bool switch_butter_music=true;	      //Ч�����ֿ���

clock_t delay1=clock();
clock_t delay2=clock();
clock_t delay3=clock();
clock_t delay4=clock();
clock_t it_delay_1=clock();
clock_t it_delay =clock();

int count_it_plan_1=0;

int width;	                          //������
int height;                           //����߶�

IMAGE background;                     //����
IMAGE firstground;                    //����
IMAGE zuoback;
IMAGE youback;

#define left 30                       //��೤�� 
#define right 180                     //�Ҳ೤��

#define back_w width - left - right   //�������
#define back_h height * 2 	      	  //�����߶�

int back_move = 0;                    //�����ƶ��ٶ�

IMAGE it_plan1[3];                    //�з��ɻ�ͼ
IMAGE it_plan2[3];                    //�л�����ͼ

IMAGE it_zidan;                       //�л��ӵ�
IMAGE it_zidan2;                      //�л��ӵ�����

IMAGE it_boom;                        //�л���ը
IMAGE buffer(1980,1024);              //������
IMAGE win_image[2];
IMAGE lose_image[2];


IMAGE soundon[2];
IMAGE soundoff[2];

bool collision(int x1,int y1,int w1,int h1,int x2,int y2,int w2,int h2);   // ������ײ��⺯��
void speed(int x1,int y1,int x2,int y2,double &x,double &y);               //���㷽����ٶ�
void file(int a);                                                          //���ļ�
void fight_web(int);                                                       //��ʾ 
void My_plan_move();                                                       //�ҵķɻ��ƶ� 
void My_zidan_exist();                                                     //�ҵ��ӵ�����
void My_zidan_move();                                                      //�ҵ��ӵ��ƶ� 
void My_attack(struct A &a,int e);                                         //��ҹ��� 
void It_plan_exist(int);                                                   //�л����� 
void It_plan_move();                                                       //�л��ƶ� 
void It_attack(struct A a[],int e);                                        //�з����� 
void fighting(int a);                                                      //ս�� 

char renwu[30];                        //����
char renwu2[30];                       //����
int difficult=0;                       //�Ѷ�
int it_bleed_add=0;

//Ч�����ֲ���
void direct_music(int k)
{
	mciSendString("close background1",NULL,0,NULL);
	if(!switch_butter_music) 
	{
		return;
	}
	switch(k)
	{
		case 1:
			{
				mciSendString("open sound//readygo.mp3 alias background1", NULL, 0, NULL);  //׼����ʼ����ʾ�� 
				mciSendString("play background1",NULL,0,NULL);
			}break;
		case 2:
			{
				mciSendString("open sound//energyfull.mp3 alias background1", NULL, 0, NULL);  //������ʱ����ʾ�� 
				mciSendString("play background1",NULL,0,NULL);
			}break;
		case 3: 
			{
				mciSendString("open sound//flyaway.mp3 alias background1", NULL, 0, NULL);//meishayong......
				mciSendString("play background1",NULL,0,NULL);
			}break;
		case 4:
			{
				mciSendString("open sound//loading.mp3 alias background1", NULL, 0, NULL);//loading.......
				mciSendString("play background1",NULL,0,NULL);
			}break;
		
		case 5:
			{
				mciSendString("open sound//victory.mp3 alias background1", NULL, 0, NULL);//ʤ��������ʾ�� 
				mciSendString("play background1",NULL,0,NULL);
			}break;
		case 6:
			{
				mciSendString("open sound//defealt.mp3 alias background1", NULL, 0, NULL);//ʧ�ܱ�����ʾ�� 
				mciSendString("play background1",NULL,0,NULL);
			}break;
		case 7:
			{
				mciSendString("open sound//pause.mp3 alias background1", NULL, 0, NULL);//��ͣ��ʾ�� 
				mciSendString("play background1",NULL,0,NULL);
				mciSendString("close background",NULL,0,NULL);
			}break;
		
	}
}
//��������
void back_music(int k)
{

	mciSendString("close background",NULL,0,NULL);	
	if(!switch_back_music)                 //�������ֿ��� 
	{
		return;
	}
	switch(k)
	{
		case 1:
			{
				mciSendString("open sound//BGM3.mp3 alias background", NULL, 0, NULL);//������ԭʼ����ı������� 
				mciSendString("play background repeat",NULL,0,NULL);
			}break; 
		case 2:
			{
				mciSendString("open sound//BGM1.mp3 alias background", NULL, 0, NULL);//��Ϸ��ʼʱ�ı������� 
				mciSendString("play background repeat",NULL,0,NULL);
			}break; 
		case 3:
			{
				mciSendString("open sound//BGM4.mp3 alias background", NULL, 0, NULL);//��Ϸ��ʼʱ�ı������֣���2���� 
				mciSendString("play background repeat",NULL,0,NULL);
			}break;
		case 4:
			{
				mciSendString("open sound//waring0.mp3 alias background", NULL, 0, NULL);//boss�������ٵ���ʾ�� 
				mciSendString("play background",NULL,0,NULL);
			}break;
		case 5:
			{
				mciSendString("open sound//BGM7_boss2.mp3 alias background", NULL, 0, NULL);//����boss����ʾ�� 
				mciSendString("play background repeat",NULL,0,NULL);
			}break;
		case 6:
			{
				mciSendString("open sound//BGM5_boss2.mp3 alias background", NULL, 0, NULL);//����boss�ı������֣����������� 
				mciSendString("play background repeat",NULL,0,NULL);
			}break;	}
}


//͸����ͼ����(������ͼ)//����ԭͼ������ͼ
void putimage(int x,int y,IMAGE &original,IMAGE &mask)
{
	DWORD *m = GetImageBuffer(&mask);
	DWORD *o = GetImageBuffer(&original);
	
	for(int i=0;i<original.getwidth() * original.getheight();i++)
	{
		if(m[i] > 0x101010)
		{
			o[i] = 0x000000;//��ɫ
		}	
	}
	putimage(x,y,&mask,SRCAND);
	putimage(x,y,&original,SRCPAINT);
}
void putimage(int x,int y,IMAGE &original)
{
	IMAGE mask(original.getwidth(),original.getheight());
	
	DWORD *m = GetImageBuffer(&mask);
	DWORD *o = GetImageBuffer(&original);
	
	for(int i=0;i<original.getwidth() * original.getheight();i++)
	{
		if(o[i] > 0x010101 * 10 )
		{
			m[i] = 0x000000;//��ɫ
		}
		else 
		{
			m[i] = 0xffffff;//��ɫ
		}
	}
	
	putimage(x,y,&mask,SRCAND);
	putimage(x,y,&original,SRCPAINT);
}

int Start()
{
	void cleardevice();
	loadimage(NULL, "ͼƬ\\�ؿ�.jpg",800,700);
	MOUSEMSG m;

	while(true) 
	{

		m = GetMouseMsg();

		switch(m.uMsg)
		{
		case WM_LBUTTONDOWN:{
				if(m.x>=36&&m.x<=238&&m.y>=270&&m.y<=448)
				{
					return 1;
					rectangle(m.x-10, m.y-10, m.x+10, m.y+10);
				}//1
				else if(m.x>=297&&m.x<=503&&m.y>=270&&m.y<=468)
				{
					return 2;
					rectangle(m.x-10, m.y-10, m.x+10, m.y+10);
				}//2
				else if(m.x>=569&&m.x<=768&&m.y>=270&&m.y<=468)
				{
					return 3;
					rectangle(m.x-10, m.y-10, m.x+10, m.y+10);
				}//3
				break;
			}
		}
	}
}
int choose()
{
	void cleardevice();
	loadimage(NULL, "ͼƬ\\�ӵ�ѡ��.jpg",800,700);
	MOUSEMSG m;

	while(true) 
	{

		m = GetMouseMsg();

		switch(m.uMsg)
		{
		case WM_LBUTTONDOWN:{
				if(m.x>=8&&m.x<=256&&m.y>=196&&m.y<=347)
				{
					return 1;
					rectangle(m.x-10, m.y-10, m.x+10, m.y+10);
				}
				else if(m.x>=300&&m.x<=550&&m.y>=196&&m.y<=347)
				{
					return 2;
					rectangle(m.x-10, m.y-10, m.x+10, m.y+10);
				}//����
				else if(m.x>=606&&m.x<=848&&m.y>=196&&m.y<=347)
				{
					return 3;
					rectangle(m.x-10, m.y-10, m.x+10, m.y+10);
				}
				else if(m.x>=410&&m.x<=530&&m.y>=390&&m.y<=510)
				{
					rectangle(m.x-10, m.y-10, m.x+10, m.y+10);
				}
				break;
			}
		}
	}
}
int Difficult()
{
	void cleardevice();
	loadimage(NULL, "ͼƬ\\��Ϸ�Ѷ�.jpg",800,700);
	MOUSEMSG m;

	while(true) 
	{

		m = GetMouseMsg();

		switch(m.uMsg)
		{
		case WM_LBUTTONDOWN:{
				if(m.x>=356&&m.x<=442&&m.y>=183&&m.y<=283)
				{
					return 0;
					rectangle(m.x-10, m.y-10, m.x+10, m.y+10);
				}
				else if(m.x>=356&&m.x<=442&&m.y>=283&&m.y<=386)
				{
					return 1;
				}
				else if(m.x>=356&&m.x<=442&&m.y>=386&&m.y<=493)
				{	
					return 2;
				}
				else if(m.x>=356&&m.x<=442&&m.y>=493&&m.y<=597)
				{
					return 3;
				}
				break;
			}
		}
	}
}


// ������ײ��⺯��
bool collision(int x1,int y1,int w1,int h1,int x2,int y2,int w2,int h2)
{
    if((abs((x1+w1/2)-(x2+w2/2)) < (w1 + w2)/2)&&abs((y1+h1/2)-(y2+h2/2)) < (h1 + h2)/2)
    {
        return true;
    }
    else
    {
        return false;
    }
}
//�ٶȷ������
void speed(int x1,int y1,int x2,int y2,double &x,double &y)
{
	x = x1 - x2;
	y = y1 - y2;

	x = 15 *( x / sqrt(x*x + y*y));
	y = 15 *( y / sqrt(x*x + y*y));
}

struct play
{
	int GOOD;    //���
	int LV;      //�ȼ�
	int EX;      //���� 
	int PLAN[3]; //�ɻ��Ƿ�ӵ��

	int jilu[3];
	
	int count;
	clock_t time;

	void init()
	{
		GOOD = 0;
		LV = 1;
		EX = 0;
		PLAN[0] = PLAN[1] = PLAN[2] = 0;
	}
	void lv_up()
	{
		if(EX > LV * 100  && LV < 10)
		{
			LV++;
			EX = 0;
		}
	}
}player;

struct A       //�ƶ����� 
{
	double X,Y;
	double x,y;
	int w;
	int h;
	bool exist;
	int ATK;

	void move() //�ƶ� 
	{
		X+=x;
		Y+=y;
		ATK = 5;
		if(Y<-h || Y>height-h || X<left || X>left+width)
		{
			exist=false;
		}
	}
};

struct My_plan
{
	int x,y;               //�ɻ����� 
	int ATK;               //������
	
	double ATT;            //��������

	int Blue;              //��ħ��

	int LIFE;              //���� 
	double BLOOD;          //Ѫ�� 
	bool protect;          //����״̬
	clock_t protect_delay; //����״̬ʱ��

	int w;                 //���
	int h;                 //�߶�

	A zidan[100];          //�ӵ���
	A zidan_left[100];     //�ӵ��� 
	A zidan_right[100];    //�ӵ��� 
	A superzidan;          //�����ӵ� 
	clock_t super_delay;   //�����ӵ��ӳ�

	int count;             //�ӵ���
	bool zidans[3];

	IMAGE plan_image[5];   //�ɻ�ͼƬ
	IMAGE zidan_image;     //�ӵ�ͼƬ
	IMAGE zidan_image2;    //�ӵ�����ͼ

	IMAGE super_image;     //�����ӵ�ͼƬ
	
	int init(int lv)       //�ɻ��ȼ���ʼ�� 
	{
		Blue = 0;
		count = 0;
		superzidan.ATK = 10;
		superzidan.exist = false;
		super_delay = clock();
		w = 90;
		h = 80;
		protect = false;
		superzidan.w = 100;
		superzidan.h = height;
		LIFE = 3;

		switch(lv) //�ɻ������ֵȼ� 
		{
			case 1:
			{
				ATT = 0.8;
				ATK = 30;
				BLOOD = 10;
				zidans[0]=true;
				zidans[1]=zidans[2]=false;
			} break;
			case 2:
			{
				ATT = 0.7;
				ATK = 20;
				BLOOD = 10;
				zidans[0]=false;
				zidans[1]=zidans[2]=true;
			} break;
			case 3:
			{	
				ATT = 0.6;
				ATK = 20;
				BLOOD = 10;
				zidans[0]=true;
				zidans[1]=zidans[2]=true;
			}break;
			default : return 0; 
		}
		for(int i=0;i<100;i++)
		{
        	zidan[i].ATK = zidan_right[i].ATK = zidan_right[i].ATK = ATK;
		}
		return 1; 
	}

	void show() //��ӡ����Ļ
	{
		if(superzidan.exist) //����ż��� 
		{
			superzidan.X = x;
			superzidan.Y = y - height ;

			putimage(x-10,y-10,plan_image[2]);//��ʾ�ɻ�
			putimage(superzidan.X ,superzidan.Y,&super_image,SRCPAINT); //��ʾ�����ӵ�
		}
		else if(clock()%500>250) //�ɻ���˸ 
		{
			if(protect) putimage(x,y,&plan_image[0],SRCPAINT);
			else putimage(x,y,plan_image[0]);
		}
		else
		{
			if(protect) putimage(x,y,&plan_image[1],SRCPAINT);
			else putimage(x-5,y-5,plan_image[1]);
		}
		for(int i=0;i<100;i++) //��ʾ�ӵ�
		{
			if(zidan[i].exist)
			{
				putimage(zidan[i].X,zidan[i].Y,zidan_image,zidan_image2);
			}
			if(zidan_left[i].exist)
			{
				putimage(int(zidan_left[i].X),int(zidan_left[i].Y),zidan_image,zidan_image2);
			}
			if(zidan_right[i].exist)
			{
				putimage(zidan_right[i].X,zidan_right[i].Y,zidan_image,zidan_image2);
			}
		}
	 }
	int hurt(int hurt_lv)//������
	{	
		protect = false;
		BLOOD -= hurt_lv*ATT;
		if(BLOOD <= 0)
		{
			LIFE--;
			if(LIFE>0) BLOOD = 10;
			else BLOOD = 0;

			x = left + (back_w)/2 - 40;
			y = height - 100;
			protect_delay = clock();
			protect = true;
		}
		return 1;
	}
	void zidan_exist(int a)
	{
		 //��ͨ�ӵ�����
		zidan[count].X = x + 30;
        zidan[count].Y = y - 40;
		zidan[count].y = -15;
        zidan[count].w = zidan[count].h = 40;
		zidan[count].exist = zidans[0];
	
		zidan_left[count].X = x +15;
		zidan_left[count].Y = y - 40;
		zidan_left[count].x = 0;
		zidan_left[count].y = -15;
        zidan_left[count].exist = zidans[1];

        zidan_left[count].w = zidan_left[count].h = 40;

		zidan_right[count].X = x + 45;
        zidan_right[count].Y = y - 40;
        zidan_right[count].x = 0;
		zidan_right[count].y = -15;
        zidan_right[count].exist = zidans[2];
        
        zidan_right[count].w = zidan_right[count].h = 40;
		
		if(zidans[0] && zidans[1] && zidans[2])
		{
			zidan_right[count].x = 1;
			zidan_left[count].x = -1;
		}
		count ++;
		count = count % 100;
		
	}
	void super_exist(int a) //���ɳ����ӵ�
	{
		if(a)  //�����ӵ�
		{
			if(Blue>=100)
			{
				Blue = 0;
				superzidan.exist=true;
				
				superzidan.X = x;
				superzidan.Y = y-height ;
				
				super_delay = clock();
			}
		}
		else if(clock() - super_delay > 
			3000) 
		{
			super_delay = clock();
			superzidan.exist = false;
		}
	}
}my_plan;

struct it_plan    //�л��ṹ��
{
	double X,Y;   //���� 
	double x,y;   //���� 
	int w,h;      //��ȣ��߶� 
	int bleed;
	
	clock_t exist_delay;  //�ɻ�����ʱ����

	bool exist;           //�ɻ��Ƿ����
	bool boom;            
	clock_t boom_delay;   //����״̬ʱ��
		
	int count;            //�ӵ�����
	A zidan[5];           //�ӵ�1 
	A zidan2[5];          //�ӵ�2 
	clock_t delay;        //�ӵ����ɼ�ʱ�� 
	
	void init()
	{
		boom=exist=false;
		count=0;
		delay=clock()-1000;
		
		switch(difficult)
		{
			case 0: bleed= 30+it_bleed_add;exist_delay =1000;break;
			case 1: bleed = 40+it_bleed_add,exist_delay=800;break;
			case 2: bleed = 60+it_bleed_add,exist_delay=700;break;
			default: bleed = 80+it_bleed_add,exist_delay=500;break;
		}
	}

	void shoot(int a=0)   //�ӵ�����
	{
		if(a==0)	      //�����ӵ�
		{
			if(clock() - delay>1000)
			{
				delay = clock(); 
			
				zidan2[count].w = zidan[count].w = 5;		//���
				zidan2[count].h = zidan[count].h = 15;		//�߶�
				
				zidan2[count].X = zidan[count].X= X + 17;
				zidan2[count].Y = zidan[count].Y= Y + 25;


				{
					zidan2[count].exist = zidan[count].exist = true;
					
					double s = rand()%2 + 1;
					speed(my_plan.x,my_plan.y,X,Y,zidan[count].x,zidan[count].y);
					speed(my_plan.x+35,my_plan.y,X,Y,zidan2[count].x,zidan2[count].y);
					zidan2[count].x *=1.8 + s/10; 
					zidan[count].x *= 1.8 + s/10;
					zidan2[count].y *=1.8 + s/10; 
					zidan[count].y *= 1.8 + s/10;
							
					count ++ ;
					count %= 5;
				}
			}
		}
		else if(clock() - delay > 2000 && Y <= height*8/10 ) //�������һ���ӵ�������2�� 
		{
			delay = clock(); 
			
			zidan2[count].w = zidan[count].w = 5;		//���
			zidan2[count].h = zidan[count].h = 15;		//�߶�
			
			zidan2[count].X = zidan[count].X= X + 17;
			zidan2[count].Y = zidan[count].Y= Y + 25;

			if(a==1) 
			{
				zidan[count].exist = false;
				zidan2[count].exist = true;
				zidan2[count].x = 0 ;       //x�ٶ�
				zidan2[count].y = 10 ;		//y�ٶ�
			}
			else if(a==2)
			{
				zidan2[count].exist = zidan[count].exist = true;
				zidan[count].x = -1;
				zidan[count].y = 10;
				zidan2[count].x = 1;
				zidan2[count].y = 10;
			}
			count ++ ;
			count %= 5;
		}
	}
	void zidan_move() //�ӵ��ƶ� 
	{
		for(int i=0;i<5;i++)
		{
			zidan[i].move();
			zidan2[i].move();
		}
	}
	int zidan_meet(int x1,int y1,int w1,int h1) //�����ҷŷɻ�
	{
		for(int i=0;i<5;i++)
		{
			if(zidan[i].exist)
			if(collision(x1,y1,w1,h1,zidan[i].X,zidan[i].Y,zidan[i].w,zidan[i].h))
			{
				my_plan.hurt(1);
				zidan[i].exist = false;
			}
			if(zidan2[i].exist)
			if(collision(x1,y1,w1,h1,zidan2[i].X,zidan2[i].Y,zidan2[i].w,zidan2[i].h))
			{
				my_plan.hurt(1);
				zidan2[i].exist = false;
			}
		}
		return 0;
	}

	void exists(int game_width) //���ɷɻ�
	{
		X = (back_w)*(rand()%10)/10 +left;
		Y = 0;

		for(int i=0;i<5;i++)
		{
			zidan[i].exist = false;
		}
		init();
		shoot();
		exist = true;
	}
	int belong()
	{
		for(int i=0;i<5;i++)
		{
			if(zidan[i].exist || zidan2[i].exist)
			{
				return 1;
			}

		}
		return 0;
	}

	int hurt(int a)              //������
	{
		bleed -= a;
		if(bleed<=0)
		{
			exist = false;
			boom = true;          //��ǵл���������״̬
			boom_delay = clock();
		}
		return boom;
	}

	void move(int a=0)            //�ƶ�
	{
		if(a==0)                  //�л�ͣ���ƶ�
		{
			x=0;y=0;
			if(Y<100) y= 25;
			else if(Y<200) y=1;
			else y = 5;

			if(Y > 300)
			{	y=0;
				if(X>(back_w)/2)
				{x = 10;}
				else x =-10;
			}

			X+=x;
			Y+=y;
			if(X<0 || X > back_w) exist=false;
			
		}
		if(a==1)
		{
			Y+= 5;
		}
	}
}it_plan_1[51];

void save()
{
	FILE *p;
	p = fopen("����\\player.txt","w");
	fprintf(p,"%d ",player.GOOD);
	fprintf(p,"%d ",player.LV);
	fprintf(p,"%d ",player.EX);
	fprintf(p,"%d ",player.PLAN[0]);
	fprintf(p,"%d ",player.PLAN[1]);
	fprintf(p,"%d\n",player.PLAN[2]);
	fclose(p); 
} 

void file(int a) //���ļ�
{
	switch(a)
	{
		case 0:
			{
				player.init();
				FILE *p;
				p = fopen("����\\player.txt","r");
				fscanf(p,"%d",&player.GOOD);
				fscanf(p,"%d",&player.LV);
				fscanf(p,"%d",&player.EX);
				fscanf(p,"%d",&player.PLAN[0]);
				fscanf(p,"%d",&player.PLAN[1]);
				fscanf(p,"%d",&player.PLAN[2]);
				fclose(p);
				
				loadimage(&firstground,_T("ͼƬ\\main.jpg"),width,height,true); 
				loadimage(&zuoback,_T("ͼƬ\\��߽�3.jpg"),left,height,true); 
				loadimage(&youback,_T("ͼƬ\\�ұ߿�2.jpg"),right,height,true);
				loadimage(&it_boom,_T("ͼƬ\\��ը.jpg"),60,60,true);
				
				loadimage(&win_image[0],_T("ͼƬ\\win.jpg"),400,300,true);
				loadimage(&win_image[1],_T("ͼƬ\\win����.jpg"),400,300,true);
				loadimage(&lose_image[0],_T("ͼƬ\\lose.jpg"),400,300,true);
				loadimage(&lose_image[1],_T("ͼƬ\\lose����.jpg"),400,300,true);
				
				loadimage(&my_plan.plan_image[0],_T("ͼƬ\\�ɻ�1.1.jpg"),120,80,true);
				loadimage(&my_plan.plan_image[1],_T("ͼƬ\\�ɻ�1.2.jpg"),130,85,true);
				loadimage(&my_plan.plan_image[2],_T("ͼƬ\\�ɻ�1.3.jpg"),140,80,true);
				
				loadimage(&it_zidan,_T("ͼƬ\\�л��ӵ�.jpg"),15,15,true);
			}break;
		case 1:
			{
				loadimage(&my_plan.zidan_image,_T("ͼƬ\\�ӵ�.jpg"),20,40,true);
				loadimage(&my_plan.zidan_image2,_T("ͼƬ\\�ӵ�1����.jpg"),20,40,true);
				loadimage(&my_plan.super_image,_T("ͼƬ\\�����ӵ� (2).jpg"),100,height,true);

				loadimage(&it_plan1[0],_T("�л�\\�л�1.jpg"),60,60,true);
				loadimage(&it_plan1[1],_T("�л�\\����ͼ\\�л�1.jpg"),60,60,true);
			}break;
		case 2:
			{
				loadimage(&my_plan.zidan_image,_T("ͼƬ\\�ӵ�2.jpg"),20,40,true);
				loadimage(&my_plan.zidan_image2,_T("ͼƬ\\�ӵ�2����.jpg"),20,40,true);
				loadimage(&my_plan.super_image,_T("ͼƬ\\�����ӵ� (2).jpg"),100,height,true);

				loadimage(&it_plan1[0],_T("�л�\\�л�1.jpg"),60,60,true);
				loadimage(&it_plan1[1],_T("�л�\\����ͼ\\�л�1.jpg"),60,60,true);
			}break;
		case 3:
			{
				loadimage(&my_plan.zidan_image,_T("ͼƬ\\�ӵ�3.jpg"),20,40,true);
				loadimage(&my_plan.zidan_image2,_T("ͼƬ\\�ӵ�2����.jpg"),20,40,true);
				loadimage(&my_plan.super_image,_T("ͼƬ\\�����ӵ� (2).jpg"),100,height,true);


				loadimage(&it_plan1[0],_T("�л�\\�л�1.jpg"),60,60,true);
				loadimage(&it_plan1[1],_T("�л�\\����ͼ\\�л�1.jpg"),60,60,true);
			}break;
		default :break;
	}
}

void first_web(int a,int b)
{
	SetWorkingImage(&buffer);                           // ���ڻ�������ͼ
	putimage(0,0,&firstground);

	for(int i=1;i<=a;i++)
	{
		putimage(100,100*i,&it_boom);
	}
	for(i=1;i<=b;i++)
	{
		putimage(700,100*i,&it_boom);
	}
	SetWorkingImage();
	putimage(0,0,&buffer);
}

void fight_web(int x=0) //��ʾ 
{
	if(clock() - delay1 > 50)
	{
		delay1 = clock();
		SetWorkingImage(&buffer);                           // ���ڻ�������ͼ
		

		//�����ƶ�
		/*{
			back_move += 5;
			back_move %= back_h;
			putimage(left,back_move - back_h,&background);  
			putimage(left,back_move ,&background);//��ӡ����
		}*/
		
		//����
		putimage(left,0,&background);


		//��ӡ�л��͵л��ӵ�
		for(int i=0;i<50;i++)
		{	
			if(it_plan_1[i].exist) //��ʾ�л�
			{
				putimage(it_plan_1[i].X,it_plan_1[i].Y,it_plan1[0]);
			}
			else if(it_plan_1[i].boom) 
			{
				putimage(it_plan_1[i].X,it_plan_1[i].Y,&it_boom,SRCPAINT);
				if(clock() - it_plan_1[i].boom_delay > 500) 
				{
					it_plan_1[i].boom = false;
				}
			}
			if(it_plan_1[i].belong())
			{
				for(int j=0;j<5;j++) //��ʾ�л��ӵ�
				{
					if(it_plan_1[i].zidan[j].exist)
					putimage(it_plan_1[i].zidan[j].X,it_plan_1[i].zidan[j].Y,it_zidan);
					if(it_plan_1[i].zidan2[j].exist)
					putimage(it_plan_1[i].zidan2[j].X,it_plan_1[i].zidan2[j].Y,it_zidan);
				}
			}
		}
		//��ӡս��
		my_plan.show();
		//��ʾ�߿�
		putimage(0,0,&zuoback);
		putimage(left+back_w,0,&youback);
		
		setlinecolor(0x2A2AA5);
		line(left+back_w+10,100,left+back_w+175,100);  //��
		line(left+back_w+10,100,left+back_w+10,410);   //��
		line(left+back_w+175,100,left+back_w+175,410); //��
		line(left+back_w+10,410,left+back_w+200,410);  //��
		line(left+back_w+10,300,left+back_w+200,300);  //��
		line(left+back_w+10,200,left+back_w+200,200);  //��
		
		setbkmode(TRANSPARENT);
		setcolor(0xB9DAFF);
		char ch[10]="";
		outtextxy(left+back_w+50,110,"ʱ��");
		
		outtextxy(left+back_w+50,210,"�÷�:");
		
		outtextxy(left+back_w+50,310,"����");
		
		sprintf(ch, "%ds",player.time);
		outtextxy(left+back_w+110,150,ch);
		
		sprintf(ch, "%d",player.count);
		outtextxy(left+back_w+110,250,ch);
		
		outtextxy(left+back_w+50,355,renwu);
		outtextxy(left+back_w+50,375,renwu2);
		
		//��ʾ��
		setfillcolor(0x999999);
		
		fillroundrect(left,height-25,left+150,height-40,10,10);
		setfillcolor(BLUE);
		
		if(my_plan.Blue < 2);
		else if(my_plan.Blue < 100)
		{	
			fillroundrect(left,height-25,left+150*my_plan.Blue/100,height-40,10,10);
		}
		else //�߲ʹ���˸
		{
			if(clock()%500>400)			{setfillcolor(0x0000FF);}
			else if(clock()%500>300)	{setfillcolor(0x00A5FF);}
			else if(clock()%500>200)	{setfillcolor(0x00D7FF);}
			else if(clock()%500>100)	{setfillcolor(0x008000);}
			else						{setfillcolor(0x800000);}
			
			fillroundrect(left,height-25,left+150*my_plan.Blue/100,height-40,10,10);
		}
		//��ʾ��
		if(my_plan.LIFE == 0)
		{
			setfillcolor(0x999999);
			fillroundrect(left,height-10,left+200,height-24,10,10);
		}
		else if(my_plan.LIFE == 1)
		{
			setfillcolor(0x999999);
			fillroundrect(left,height-10,left+200,height-24,10,10);
			
			setfillcolor(0x0000ff);
			fillroundrect(left,height-10,left+200*my_plan.BLOOD/10,height-24,10,10);
		}
		else if(my_plan.LIFE == 2)
		{
			setfillcolor(0x5555ff);
			fillroundrect(left,height-10,left+200,height-24,10,10);
			setfillcolor(0x0000ff);
		
			fillroundrect(left,height-10,left+200*my_plan.BLOOD/10,height-24,10,10);
		}
		else if(my_plan.LIFE == 3)
		{
			setfillcolor(0xAAAAff);
			fillroundrect(left,height-5,left+200,height-21,10,10);

			setfillcolor(0x5555ff);
		
			fillroundrect(left,height-5,left+200*my_plan.BLOOD/10,height-21,10,10);
		}
		//ʤ��
		if(x==1)
		{
			putimage(150,200,win_image[0],win_image[1]);
		}
		//ʧ��
		else if(x==-1)
		{
			putimage(150,200,lose_image[0],lose_image[1]);
		}
		SetWorkingImage();
		putimage(0,0,&buffer);
	}
}

void My_plan_move() //ս���ƶ� 
{
	if(clock() - delay2 > 20)
	{
		delay2 = clock();
		if (GetAsyncKeyState('a') & 0x8000 ||GetAsyncKeyState('A') & 0x8000)  
		{  
			if (my_plan.x>= left - 30)
			{  
				my_plan.x= my_plan.x- 10*2;
			}  
		}  
		if (GetAsyncKeyState('w') & 0x8000 ||GetAsyncKeyState('W') & 0x8000)  
		{  
			if (my_plan.y>= 15 )  
			{  
				my_plan.y= my_plan.y- 10;
			}  
		}  
		if (GetAsyncKeyState('d') & 0x8000 ||GetAsyncKeyState('D') & 0x8000)  
		{  
			if (my_plan.x<= back_w + left - 50)  
			{  
				my_plan.x= my_plan.x+ 10*2;  
			}  
		}  
		if (GetAsyncKeyState('s') & 0x8000 ||GetAsyncKeyState('S') & 0x8000)  
		{  
			if (my_plan.y<= height - 100)  
			{
				my_plan.y= my_plan.y+ 10;
			} 
		}
	}
}

void My_zidan_exist() //ս���ӵ����� 
{
	if(clock() - delay3 > 60)
	{
		delay3 = clock();
		
		if(GetAsyncKeyState('j') & 0x8000 || GetAsyncKeyState('J') & 0x8000) //��ͨ�ӵ�����
		{
			my_plan.zidan_exist(1);
		}
		if(my_plan.superzidan.exist)
		{
			my_plan.super_exist(0);
		}
		else if(GetAsyncKeyState('k') & 0x8000 || GetAsyncKeyState('K') & 0x8000)
		{my_plan.super_exist(1);}
		
	}
}

void My_attack(struct A &a,int e)
{
	for(int j=0;j<50;j++) //�����з��ɻ�
	{
		if(it_plan_1[j].exist)
		{
			if(collision(a.X,a.Y,a.w,a.h, it_plan_1[j].X+30, it_plan_1[j].Y,20,80) )
			{
				if(it_plan_1[j].hurt(my_plan.ATK))
				{
					player.count++;
					for(int i=0;i<50;i++)
					{
							if(it_plan_1[i].exist) break;
					}
					if(i==50) It_plan_exist(100);
					
					if(my_plan.Blue<100)
					{
						my_plan.Blue+=4;	
					}
				}
				if(e)
				a.exist = false; //�ӵ���ʧ 
			}
		}
	}
}

void My_zidan_move() //��ͨ�ӵ��ƶ�
{
	if(clock()-delay4>10)
	{
		delay4 = clock();
		if(my_plan.superzidan.exist) //�����ӵ�����
		{
			My_attack(my_plan.superzidan,0);
		}
		for(int i=0;i<100;i++) //��ͨ�ӵ��ƶ�
		{	
			if(my_plan.zidan[i].exist) 
			{
				my_plan.zidan[i].move();
				My_attack(my_plan.zidan[i],1);
			}
			if(my_plan.zidan_left[i].exist) 
			{
				my_plan.zidan_left[i].move();
				My_attack(my_plan.zidan_left[i],1);
			}
			if(my_plan.zidan_right[i].exist) 
			{
				my_plan.zidan_right[i].move();	
				My_attack(my_plan.zidan_right[i],1);
			}
		}	
	}
}

void It_plan_exist(int a=1) //�л����� 
{
	
	if(clock() - it_delay_1 > it_plan_1[0].exist_delay / a) //�л�����
	{
		it_delay_1 = clock();
		
		it_plan_1[count_it_plan_1].exists(width);
		count_it_plan_1 ++;
		count_it_plan_1 %= 50;
	}
} 
void It_plan_move(int a=0) //�л��ƶ� 
{
	if(clock() - it_delay > 50)//�л��ӳ�
	{
		it_delay = clock();
		for(int i=0;i<50;i++)
		{
			if(it_plan_1[i].exist)
			{			
				it_plan_1[i].shoot(a); //�����ӵ�
				it_plan_1[i].move(); //�л��ƶ� 
			}
			if(it_plan_1[i].belong())
			{
				it_plan_1[i].zidan_move(); //�ӵ��ƶ�
				
				if(!my_plan.protect || clock() - my_plan.protect_delay> 3000)
				it_plan_1[i].zidan_meet(my_plan.x,my_plan.y,my_plan.w,my_plan.h);//�����ҷ��ɻ� 
			}
		}
	}
}

void del_it()
{
	for(int i=0;i<50;i++)
	{
		it_plan_1[i].exist = false;
		for(int j=0;j<5;j++)
		{
			it_plan_1[i].zidan[j].exist = false;
			it_plan_1[i].zidan2[j].exist = false;
		}
	}
	for(i=0;i<100;i++)
	{
		my_plan.zidan[i].exist = false;
		my_plan.zidan_left[i].exist = false;
		my_plan.zidan_right[i].exist = false;
	}
	my_plan.superzidan.exist = false;
}
void win()
{
	direct_music(5);
	del_it();
	clock_t delay = clock();
	while(1)
	{
		if(clock() - delay > 3000) break;
		fight_web(1);
	}
	direct_music(3);
	while(1)
	{
		if(my_plan.y < -100) break;
		my_plan.y -= 8;
		fight_web();
		Sleep(10);
	}
}
void lose()
{
	del_it();	
	clock_t delay = clock();
	while(1)
	{
		if(clock() - delay > 2000) break;
		fight_web(-1);
	}	
	while(1)
	{
		if(clock() - delay > 2000) break;
		fight_web();
	}

}
void fight_init(int a)
{
	my_plan.init(a);              //��ʼ���ɻ��ȼ�
	my_plan.x = left+width/2-20;  //���ڵ�ͼ��ȵ��м� 
	my_plan.y = height - 100;     //���ڵ�ͼ�±�
	
	it_bleed_add=0;

	player.count = 0;
	player.time = 0;
	for(int i=0;i<50;i++)         //�л���ʼ��
	{
		it_plan_1[i].init();
		for(int j=0;j<5;j++)
		{
			it_plan_1[i].zidan[j].exist = false;
			it_plan_1[i].zidan2[j].exist = false;
		}
	}
}

void fighting(int a,int b) //ս�� 
{
	fight_init(b);
	
	clock_t delay = clock();
	switch(a)
	{
		case 1:
			{
				loadimage(&background,_T("ͼƬ\\�ؿ�1.jpg"),700,700,true);
				loadimage(&it_plan1[0],_T("�л�\\�л�1.jpg"),60,60,true);
				loadimage(&it_plan1[1],_T("�л�\\����ͼ\\�л�1.jpg"),60,60,true);
				
				sprintf(renwu, "%s","1���ӻ�ɱ");
				sprintf(renwu2, "%s","100���л�");
		
				while(my_plan.LIFE > 0)
				{
					//ʱ��
					player.time = (clock() - delay)/1000;
					My_zidan_exist();
					My_plan_move();
					My_zidan_move();

					It_plan_exist();
					It_plan_move(2);
					 
					fight_web();
					
					//ʧ��
					if(player.time>60||my_plan.LIFE <= 0)
					{
						fight_web();
						lose();
						break;
					}	
					//ʤ��
					else if(player.count>=100)
					{
						fight_web();
						win();
						break;
					}
				}
			}break;
		case 2:
			{
				
				loadimage(&background,_T("ͼƬ\\�ؿ�2.jpg"),back_w,back_h,true);
				loadimage(&it_plan1[0],_T("ͼƬ\\�л�A.jpg"),60,60,true);
				loadimage(&it_plan1[1],_T("ͼƬ\\�л�A����.jpg"),60,60,true);
		
				sprintf(renwu, "%s","100������");
				sprintf(renwu2, "");
				while(my_plan.LIFE > 0)
				{  
					
					//ʱ��
					player.time = (clock() - delay)/1000;
					it_bleed_add = 200;
					My_zidan_exist();
					My_plan_move();
					My_zidan_move();

					It_plan_exist();
					It_plan_move(0);
					
					fight_web();
					//ʧ��
					if(my_plan.LIFE <= 0)
					{
						fight_web();
						lose(); break;
					}	
					//ʤ��
					else if(player.time > 100)
					{
						fight_web();
						win();
						break;
					}
				}
			}break;
		case 3:
			{	
				
				loadimage(&background,_T("ͼƬ\\�ؿ�3.jpg"),back_w,height,true); 
				loadimage(&it_plan1[0],_T("ͼƬ\\�л�B.jpg"),60,60,true);
				loadimage(&it_plan1[1],_T("ͼƬ\\�л�B����.jpg"),60,60,true);

				sprintf(renwu, "%s","��������");

				while(1)
				{  
					//ʱ��
					player.time = (clock() - delay)/1000;
					
					//�Ѷ�����
					it_bleed_add = 5*player.time/20;

					My_zidan_exist();
					My_plan_move();
					My_zidan_move();
					
					It_plan_exist(4);
					It_plan_move(0);
					
					fight_web();

					//ʧ��
					if(my_plan.LIFE <= 0)
					{
						fight_web();
						lose(); break;
					}
				}
			}break;
		default :break;
	}
	Sleep(1000);
}

int main()
{ 
	MOUSEMSG m;
	int chose[2]={1,1};

	srand((unsigned)time(0));

	width = 800;
	height = 700;
  	initgraph(width ,height);

	HWND window = GetHWnd();  //�򿪳��򲢷ŵ����Ͻ�
	SetWindowPos(window,HWND_TOP,width*2/10,height/20,0,0,SWP_NOSIZE);
	
	file(0);//��ȡ�����ļ�

	
	//������Ϸ
	direct_music(4);
	loadimage(NULL, "ͼƬ\\����1.jpg",800,700);
	loadimage(&soundon[0],"ͼƬ\\������.jpg",100,100);
	loadimage(&soundon[1],"ͼƬ\\����������.jpg",100,100);
	loadimage(&soundoff[0],"ͼƬ\\������.jpg",100,100);
	loadimage(&soundoff[1],"ͼƬ\\����������.jpg",100,100);

	Sleep(3000);
	
	back_music(1);
	loadimage(NULL, "ͼƬ\\����.jpg",800,700);
	
	if(switch_back_music)
	{	putimage(700,600,soundon[0],soundon[1]);}
	else
	{	putimage(700,600,soundoff[0],soundoff[1]);}

	while(true) 
	{	
		m = GetMouseMsg();
		
		if(m.uMsg == WM_LBUTTONDOWN )
		{
			if(m.x>=277&&m.x<=397&&m.y>=260&&m.y<=380)
			{
				chose[0] = Start();
				
				back_music(2);
				
				file(chose[1]);
				fighting(chose[0],chose[1]);
				
				loadimage(NULL, "ͼƬ\\����.jpg",800,700);
				if(switch_back_music)
				{	putimage(700,600,soundon[0],soundon[1]);}
				else
				{	putimage(700,600,soundoff[0],soundoff[1]);}
				back_music(1);

			}//��ʼ
			else if(m.x>=410&&m.x<=530&&m.y>=260&&m.y<=380)
			{
				chose[1] = choose();
				file(chose[1]);
				loadimage(NULL, "ͼƬ\\����.jpg",800,700);
				if(switch_back_music)
				{	putimage(700,600,soundon[0],soundon[1]);}
				else
				{	putimage(700,600,soundoff[0],soundoff[1]);}

			}//����
			else if(m.x>=277&&m.x<=397&&m.y>=390&&m.y<=510)
			{
				closegraph();
				return 0;
			}
			else if(m.x>=410&&m.x<=530&&m.y>=390&&m.y<=510)
			{
				difficult = Difficult();
				loadimage(NULL, "ͼƬ\\����.jpg",800,700);
				if(switch_back_music)
				{	putimage(700,600,soundon[0],soundon[1]);}
				else
				{	putimage(700,600,soundoff[0],soundoff[1]);}
			}
			else if(m.x>=700&&m.x<=800&&m.y>=600&&m.y<=700)
			{
				switch_back_music = !switch_back_music;
				switch_butter_music = switch_back_music;

				back_music(1);
			
				loadimage(NULL, "ͼƬ\\����.jpg",800,700);

				if(switch_back_music)
				{	putimage(700,600,soundon[0],soundon[1]);}
				else
				{	putimage(700,600,soundoff[0],soundoff[1]);}
	
			}

		}
	}
	save();
	  
}