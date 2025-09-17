#ifndef _wow_h_
#define _wow_h_

#include<time.h>
#include <cstdio>
#include<vector>
#include <algorithm> 
#include<cctype>
#include<iomanip>//setw( n ) 设域宽为n个字符  //setiosflags(ios::left) 左对齐
     /*▲setfill(char c) 用法 : 就是在预设宽度中如果已存在没用完的宽度大小，则用设置的字符c填充
　　如 cout<<setfill(‘@‘)<<setw(5)<<255<<endl;
　　结果是:
　　@@255*/

#include<fstream>   //文件读取头文件 
#include<stdio.h>
#include<string>//str.substr(0, 4)
#include<string.h>
#include<malloc.h>  //new
#include<iostream>
#include<sstream>
using namespace std;
#define OK 1
#define ERROR 0

//--------图-------------
#define MaxInt 32767 
#define MAXSIZE 20       
#define OVERFLOW -1     
#define MVNum 20        //最大结点数 


typedef int Status; 
typedef string VerTexType;//结点类型 
typedef float ArcType;    //边类型



//------------套餐结构体类型初始化-----------------------------------
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
//------------订单结构体类型初始化------------------------------------ 
typedef struct OrderElem{
	char Mark[20];
	char MealNum[20];
	char Mark2[20];
	char OrderName[20];
	char Telephone[20];
	char Address[200];
	char Date[100];
	char OrderTime[100];
	bool Orderstatus;//未派送0，已派送1 
}OrderElem;
typedef OrderElem QElemType;

typedef struct{
	OrderElem * base;
	int front;
	int rear;
}SqQueue;

//-------------图的邻接矩阵存储表示-------------
typedef struct
	{
  VerTexType vexs[MVNum];
  ArcType arcs[MVNum][MVNum];
  int vexnum,arcnum;
}AMGraph;    
void ShortestPath_Dijkstra(AMGraph G, int v, ArcType dist[], int path[]);

//-------------------函数声明------------
Status InitSetList(SetList &L);   //初始化套餐结构体空间，会集合在初始化套餐中使用 
void Initsetmeal(SetList &L);     //初始化套餐数据，从文件中读取已有套餐信息 
Status TraverList(SetList &L,int n);//输出套餐队列中的一个套餐结构体信息,被调用，避免冗长代码
void Traversetmeal(SetList &L);   //遍历输出套餐，输出所有套餐信息 
void Addsetmeal(SetList &L);      //添加套餐 
void Findsetmeal(SetList &L);     //查找套餐 
void Changesetmeal(SetList &L);   //修改套餐 
void Deletesetmeal(SetList &L);   //删除套餐 

Status InitQueue(SqQueue &Q);     //初始化订单结构体队列空间，会集合在初始化订单中使用 
void Initorder(SqQueue &Q);       //初始化订单数据，从文件中读取已有订单信息 
Status TraverQueue(SqQueue &Q,int n); //输出订单队列中的一个订单结构体信息,被调用，避免冗长代码
void Traverorder(SqQueue &Q);     //遍历输出订单，输出所有订单信息 
Status EnQueue(SqQueue &Q,QElemType e); //将结构体信息复制输入进订单队列空间中，被调用，避免冗长代码 
void Enorder(SqQueue &Q,SetList &L,AMGraph &G);         //增加一个订单 
Status QueueLength(SqQueue Q);    //订单队列长度，有效内容数量 
void Deleteorder(SqQueue &Q);              //删除订单
void Changeorder(SqQueue &Q,SetList &L);		      //修改订单   
Status LocateQueue(SqQueue Q,QElemType &e);//根据信息查找订单，内置在Findorder中 
void Findorder(SqQueue Q);        //查找订单，输入查找的信息，根据其查找 
void Out_order(SqQueue &Q);       //派送订单，更新订单信息，将已派送订单存入内存中 


Status CreateUDN(AMGraph &G);     //采用邻接矩阵表示法，创建无向网G
Status LocateVex(AMGraph &G,VerTexType u);//邻接矩阵无向网顶点定位函数，返回顶点位置(顶点数组序列号)

void printShortestPath(AMGraph G, vector<int> shortestPath);
void ShortestPath_Dijkstra(AMGraph G, int v, ArcType dist[], int path[]);//获取从起点到终点的最短路径。
vector<int> getShortestPath(AMGraph G, VerTexType startVex, VerTexType endVex);//使用Dijkstra算法计算从起点到各顶点的最短路径。
double calculateTime(AMGraph G, vector<int> shortestPath);
 
//----------------------------------------
void Get_OccurTime(string &date1,string &date2,string &time1);//获取当前时间，获取日期和时间 
void Application();
void Load_main_menu();//一级菜单 
void Load_start_word_menu();//加载开启系统界面(美观) 
void Load_server_side_menu();//加载商家端二级菜单
void Load_client_side_menu();//加载用户端二级菜单
void Load_Courier_side_menu();//加载骑手端二级菜单
void Load_data_maintenance_menu();//加载基础数据维护三级菜单
void Load_statistics_menu();//加载统计三级菜单

void offwork(SetList &L);

void statistics(SetList &L,SqQueue &Q);
int isNumeric(const char* str);
#endif
