#ifndef _wow_h_
#define _wow_h_

#include<time.h>
#include <cstdio>
#include<vector>
#include <algorithm> 
#include<cctype>
#include<iomanip>//setw( n ) �����Ϊn���ַ�  //setiosflags(ios::left) �����
     /*��setfill(char c) �÷� : ������Ԥ����������Ѵ���û����Ŀ�ȴ�С���������õ��ַ�c���
������ cout<<setfill(��@��)<<setw(5)<<255<<endl;
���������:
����@@255*/

#include<fstream>   //�ļ���ȡͷ�ļ� 
#include<stdio.h>
#include<string>//str.substr(0, 4)
#include<string.h>
#include<malloc.h>  //new
#include<iostream>
#include<sstream>
using namespace std;
#define OK 1
#define ERROR 0

//--------ͼ-------------
#define MaxInt 32767 
#define MAXSIZE 20       
#define OVERFLOW -1     
#define MVNum 20        //������� 


typedef int Status; 
typedef string VerTexType;//������� 
typedef float ArcType;    //������



//------------�ײͽṹ�����ͳ�ʼ��-----------------------------------
typedef struct SetElem{
	char Num[20];
	char Name[20];
	char Description[100];
	int  Price;
	bool Status;
}SetElem;

typedef struct {
    SetElem * base;
    int length;
}SetList;
//------------------------------------------
//------------�����ṹ�����ͳ�ʼ��------------------------------------ 
typedef struct OrderElem{
	char Mark[20];
	char MealNum[20];
	char Mark2[20];
	char OrderName[20];
	char Telephone[20];
	char Address[200];
	char Date[100];
	char OrderTime[100];
	bool Orderstatus;//δ����0��������1 
}OrderElem;
typedef OrderElem QElemType;

typedef struct{
	OrderElem * base;
	int front;
	int rear;
}SqQueue;

//-------------ͼ���ڽӾ���洢��ʾ-------------
typedef struct
	{
  VerTexType vexs[MVNum];
  ArcType arcs[MVNum][MVNum];
  int vexnum,arcnum;
}AMGraph;    
void ShortestPath_Dijkstra(AMGraph G, int v, ArcType dist[], int path[]);

//-------------------��������------------
Status InitSetList(SetList &L);   //��ʼ���ײͽṹ��ռ䣬�Ἧ���ڳ�ʼ���ײ���ʹ�� 
void Initsetmeal(SetList &L);     //��ʼ���ײ����ݣ����ļ��ж�ȡ�����ײ���Ϣ 
Status TraverList(SetList &L,int n);//����ײͶ����е�һ���ײͽṹ����Ϣ,�����ã������߳�����
void Traversetmeal(SetList &L);   //��������ײͣ���������ײ���Ϣ 
void Addsetmeal(SetList &L);      //����ײ� 
void Findsetmeal(SetList &L);     //�����ײ� 
void Changesetmeal(SetList &L);   //�޸��ײ� 
void Deletesetmeal(SetList &L);   //ɾ���ײ� 

Status InitQueue(SqQueue &Q);     //��ʼ�������ṹ����пռ䣬�Ἧ���ڳ�ʼ��������ʹ�� 
void Initorder(SqQueue &Q);       //��ʼ���������ݣ����ļ��ж�ȡ���ж�����Ϣ 
Status TraverQueue(SqQueue &Q,int n); //������������е�һ�������ṹ����Ϣ,�����ã������߳�����
void Traverorder(SqQueue &Q);     //�������������������ж�����Ϣ 
Status EnQueue(SqQueue &Q,QElemType e); //���ṹ����Ϣ����������������пռ��У������ã������߳����� 
void Enorder(SqQueue &Q,SetList &L,AMGraph &G);         //����һ������ 
Status QueueLength(SqQueue Q);    //�������г��ȣ���Ч�������� 
void Deleteorder(SqQueue &Q);              //ɾ������
void Changeorder(SqQueue &Q,SetList &L);		      //�޸Ķ���   
Status LocateQueue(SqQueue Q,QElemType &e);//������Ϣ���Ҷ�����������Findorder�� 
void Findorder(SqQueue Q);        //���Ҷ�����������ҵ���Ϣ����������� 
void Out_order(SqQueue &Q);       //���Ͷ��������¶�����Ϣ���������Ͷ��������ڴ��� 


Status CreateUDN(AMGraph &G);     //�����ڽӾ����ʾ��������������G
Status LocateVex(AMGraph &G,VerTexType u);//�ڽӾ������������㶨λ���������ض���λ��(�����������к�)

void printShortestPath(AMGraph G, vector<int> shortestPath);
void ShortestPath_Dijkstra(AMGraph G, int v, ArcType dist[], int path[]);//��ȡ����㵽�յ�����·����
vector<int> getShortestPath(AMGraph G, VerTexType startVex, VerTexType endVex);//ʹ��Dijkstra�㷨�������㵽����������·����
double calculateTime(AMGraph G, vector<int> shortestPath);
 
//----------------------------------------
void Get_OccurTime(string &date1,string &date2,string &time1);//��ȡ��ǰʱ�䣬��ȡ���ں�ʱ�� 
void Application();
void Load_main_menu();//һ���˵� 
void Load_start_word_menu();//���ؿ���ϵͳ����(����) 
void Load_server_side_menu();//�����̼Ҷ˶����˵�
void Load_client_side_menu();//�����û��˶����˵�
void Load_Courier_side_menu();//�������ֶ˶����˵�
void Load_data_maintenance_menu();//���ػ�������ά�������˵�
void Load_statistics_menu();//����ͳ�������˵�

void offwork(SetList &L);

void statistics(SetList &L,SqQueue &Q);
int isNumeric(const char* str);
#endif
