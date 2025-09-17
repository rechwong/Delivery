#include "wow.h"

//--------------------------------------------------

void Initsetmeal(SetList &L)
{
InitSetList(L);
ifstream setin("taocan.txt");
	if(setin.is_open())
		cout<<"打开taocan.txt文件成功！"<<endl;
	else{
		cout<<"打开taocan.txt文件失败!"<<endl;
	}
if(setin.peek() != EOF){
int i=0;
		while(!setin.eof()){
			
			SetElem setmeal;
			setin >> setmeal.Num;
			setin >> setmeal.Name;
			setin >> setmeal.Description;
			setin >> setmeal.Price;
			setin >> setmeal.Status;
		    strcpy(L.base[i].Num,setmeal.Num);
		    strcpy(L.base[i].Name,setmeal.Name);
		    strcpy(L.base[i].Description,setmeal.Description);
		    L.base[i].Price=setmeal.Price;
		    L.base[i].Status=setmeal.Status;	    
		    i++;
		}
		L.length =i-1;
		setin.close();
		cout<<"套餐加载成功！"<<endl;
		//Traverorder(L);
	}
}

Status InitSetList(SetList &L)
{  
   L.base=new SetElem[MAXSIZE];
   if(!L.base) {cout<<"队列初始化失败";exit(OVERFLOW);}
   L.length=0;
}

void Traversetmeal(SetList &L)
{  
for( int i=0,j=L.length;i<L.length;i++) TraverList(L,i); 
}

Status TraverList(SetList &L,int n)
{   
    cout <<"| "<<L.base[n].Num<<setfill(' ')<<setw(15);
	cout <<L.base[n].Name<<setfill(' ')<<setw(30);
	cout <<L.base[n].Description<<setfill(' ')<<setw(10);
	cout <<L.base[n].Price<<setfill(' ')<<setw(15);
	if(L.base[n].Status) cout<<"可预订 |\n"; 
	else cout<<"不可预定 |\n";            
}
void Addsetmeal(SetList &L)
{   
	cout<<"请输入待添加的套餐编号:";
	cin>>L.base[L.length].Num;
	cout<<"请输入待添加的套餐名:"; 
	cin>>L.base[L.length].Name;
	cout<<"请输入待添加的描述:";
	cin>>L.base[L.length].Description; 
	cout<<"请输入待添加的价格:"; 
	cin>>L.base[L.length].Price;
	cout<<"请输入待添加的状态(可否预定1/0):"; 
    cin>>L.base[L.length].Status;//填0和1以上的数字会死循环 
    L.length++;
}
/* 
void Findsetmeal(SetList &L)   //查找套餐 
{   int flag,i,j,x;
    char s[20];
    cout<<"您要怎么查找套餐？";
    cout<<"1.编号 2.套餐名";
	cin>>flag;
	switch(flag)
	{   case 1:
	           cout<<"请输入要查找的套餐编号";
	           cin >>s;
	           for(i=0,j=L.length;i<j;i++)
	           {  if(strcmp(L.base[i].Num,s)==0) TraverList(L,i);  
	           }
	           break;
	    case 2: cout<<"请输入要查找的套餐名";
	           cin >>s;
	           for(i=0,j=L.length;i<j;i++)
	           {  if(strcmp(L.base[i].Name,s)==0) TraverList(L,i);  
	           }
	           break;
	    	default:cout<<"输入错误";
	} 
    
}
*/


void Deletesetmeal(SetList &L)
{    char s[20];
     int i,j;
     cout<<"请输入您要删除的套餐编号" ;
     cin >>s;
	 for(i=0,j=L.length;i<j;i++)
	 {  
	    if(strcmp(L.base[i].Num,s)==0) 
	    {
	      for(;i<j-1;i++)
		  {  strcpy(L.base[i].Num,L.base[i+1].Num);
		     strcpy(L.base[i].Name,L.base[i+1].Name);
			 strcpy(L.base[i].Description,L.base[i+1].Description);
			 L.base[i].Price=L.base[i+1].Price;
			 L.base[i].Status=L.base[i+1].Status;
		  }
		  L.length --; 
		  cout<<"删除完毕\n"; 
		  return ;
	    }
	 }
		 cout<<"未找到目标套餐编号";
}


Status InitQueue(SqQueue &Q)
{  
   Q.base=new QElemType[MAXSIZE];
   if(!Q.base) {cout<<"队列初始化失败";exit(OVERFLOW);}
   Q.front=Q.rear=0;
}

void Initorder(SqQueue &Q)
{
InitQueue(Q);
ifstream orderin("dingdan.txt");
	if(orderin.is_open())
		cout<<"打开dingdan.txt文件成功！"<<endl;
	else{
		cout<<"打开dingdan.txt文件失败!"<<endl;
		return;  // 打开文件失败，直接返回
	    }	
if(orderin.is_open()&&orderin.peek() != EOF) 
  {
    int j=0;
    OrderElem Order;
		while(!orderin.eof())
		{		
			orderin >> Order.Mark;
			orderin >> Order.MealNum;
			orderin >> Order.Mark2;
			orderin >> Order.OrderName;
            orderin >> Order.Telephone;
			orderin >> Order.Address;
	//	 if(strcmp(Order.Address,"万象城")==0) strcpy(Order.Address,"万向城");//txt  LocateVex
			orderin >> Order.Date;
			orderin >> Order.OrderTime;
			orderin >> Order.Orderstatus; 
if(Order.Orderstatus)         //已派送         //判断txt文件中是否有已派送的订单，存储已派送存储文件中 
  {
   ofstream orderout("ordercnt.txt",ios::app); // 打开文本文件，并设置可追加写入(bug:没设置;
	     if(orderout.is_open())
        {
            orderout << Order.Mark<<"  ";
			orderout << Order.MealNum<<"  ";
			orderout << Order.Mark2<<"  ";
			orderout << Order.OrderName<<"  ";
            orderout << Order.Telephone<<"  ";
			orderout << Order.Address<<"  ";
			orderout << Order.Date<<"  ";
			orderout << Order.OrderTime<<"  ";
			orderout << Order.Orderstatus<<"  "<<endl;
			orderout.close();
		}   
	    else cout<<"无法打开输出文件！" << endl;	      
  }  
else      {                       //未派送 
		    strcpy(Q.base[j].Mark,Order.Mark);
		    strcpy(Q.base[j].MealNum,Order.MealNum);
		    strcpy(Q.base[j].Mark2,Order.Mark2);
		    strcpy(Q.base[j].OrderName,Order.OrderName);
		    strcpy(Q.base[j].Telephone,Order.Telephone);
		    strcpy(Q.base[j].Address,Order.Address);
		    strcpy(Q.base[j].Date,Order.Date);
		    strcpy(Q.base[j].OrderTime,Order.OrderTime);
		    Q.base[j].Orderstatus=Order.Orderstatus;
	       j++;
		  }
		 
		}
		Q.rear = j;
		orderin.close();
		
		cout<<"订单加载成功！"<<endl;
  }
}

Status EnQueue(SqQueue &Q,QElemType e)
{  
   string d1,d2,t;
   Get_OccurTime(d1,d2,t); 
   if((Q.rear+1)%MAXSIZE==Q.front) return ERROR;
       //char数组和string有区别,string!=char*，没法直接用需d1.c_str()改  
   strcpy(Q.base[Q.rear].Mark,d1.c_str());                             //无法直接 Q.base[Q.rear]=e;
   strcpy(Q.base[Q.rear].MealNum,e.MealNum);
   strcpy(Q.base[Q.rear].Mark2,e.Mark2);
   strcpy(Q.base[Q.rear].OrderName,e.OrderName);
   strcpy(Q.base[Q.rear].Telephone,e.Telephone);
   strcpy(Q.base[Q.rear].Address,e.Address);
  
   strcpy(Q.base[Q.rear].Date,d2.c_str());
   strcpy(Q.base[Q.rear].OrderTime,t.c_str());
   Q.base[Q.rear].Orderstatus=e.Orderstatus;
   Q.rear=(Q.rear+1)%MAXSIZE;
}

void Enorder(SqQueue &Q,SetList &L,AMGraph &G)
{ int k,i,flag=0;
QElemType e; 
k=Q.rear;
cout<<"请输入新的订单的套餐编号：";
cin>>e.MealNum;

for(i=0;i<L.length;i++){
if(strcmp(e.MealNum,L.base[i].Num)==0) flag=1;}
if(!flag){cout<<"套餐编号不存在,输入失败";return;} 
 
cout<<"请输入新的订单的套餐数量:"; 
cin>>e.Mark2;

if(!isNumeric(e.Mark2)) {cout<<"数量不合法,输入失败";return;}

cout<<"请输入新的订单的订单人名:"; 
cin>>e.OrderName;
cout<<"请输入新的订单的电话:";
cin>>e.Telephone;
if(!isNumeric(e.Telephone)) {cout<<"电话字符不合法,输入失败";return;}
if(strlen(e.Telephone)!=11) {cout<<"电话字符位数不合法,输入失败";return;}
cout<<"请输入新的订单的地址："; 
cin>>e.Address;

int x=0,y=0;

for(x=1;x<=G.vexnum;x++){
if(G.vexs[x]==e.Address) y=1;}
if(!y) {cout<<"地址未找到，输入失败";return;}

e.Orderstatus=0;
EnQueue(Q,e); 
TraverQueue(Q,Q.rear-1) ;   
return ;              
}

Status QueueLength(SqQueue Q)   
{  return((Q.rear-Q.front+MAXSIZE)%MAXSIZE); }

Status LocateVex(AMGraph &G,VerTexType u)
{   int i;
    if(u=="金桥") return 3;  //txt
    if(u=="万象城") return 10; 
    for(i=1;i<=G.vexnum;i++)
    {    
	    if(G.vexs[i]==u) return i;
    }
    return -1;//找不到返回-1 
}

Status TraverQueue(SqQueue &Q,int n)
{
cout<<"| "<<Q.base[n].Mark<<setfill(' ')<<setw(7);
cout<<Q.base[n].MealNum<<setfill(' ')<<setw(6);
cout<<Q.base[n].Mark2<<setfill(' ')<<setw(10);
cout<<Q.base[n].OrderName<<setfill(' ')<<setw(15);
cout<<Q.base[n].Telephone<<setfill(' ')<<setw(13);
cout<<Q.base[n].Address<<setfill(' ')<<setw(15);
cout<<Q.base[n].Date<<setfill(' ')<<setw(12);
cout<<Q.base[n].OrderTime<<setfill(' ')<<setw(11);
if(Q.base[n].Orderstatus) cout<<"已派送"; 
else cout<<"未派送"<<" |"<<endl;
}

void Traverorder(SqQueue &Q)
{ int i,j;i=Q.rear,j=Q.front;
  for(;j<i;j++) TraverQueue(Q,j);
}

Status CreateUDN(AMGraph &G)
{//采用邻接矩阵表示法，创建无向网G
      int k; 
      int x=0;int i,j;
      G.vexnum=0,G.arcnum=0;
      ifstream vexin("已有地址.txt");
	if(vexin.is_open())
		cout<<"打开已有地址.txt文件成功!"<<endl;
	else{
		cout<<"打开已有地址.txt文件失败!"<<endl;
	}
	if(vexin.is_open()&&vexin.peek() != EOF){//10 .10.最后一行输入两遍  循环后再更新G.vexnum=x   ---p -1bug
		while(!vexin.eof()){
			vexin >> x;
			vexin >> G.vexs[x];
		}
		G.vexnum=x;	//bug解决方法 
		vexin.close();
		cout<<"地址加载成功！"<<endl;
	}
	  for(i=1;i<=x;i++)
	    for(j=1;j<=x;j++)
	       G.arcs[i][j]=MaxInt;

ifstream arcin("各地址距离表.txt");
	if(arcin.is_open())
		cout<<"地址距离表.txt文件成功!"<<endl;
	else{
		cout<<"地址距离表.txt文件失败!"<<endl;
	}
	if(arcin.is_open()&&arcin.peek() != EOF){
		while(!arcin.eof()){
string arc1,arc2;
float w;			
			arcin >> arc1>> arc2>> w;                //txt中点的错误如0·74应为0.74，会导致无法正确读取浮点数             
			i=LocateVex(G,arc1);
			//cout<<i=
			j=LocateVex(G,arc2);
            G.arcs[i][j]=w;
            G.arcs[j][i]=G.arcs[i][j];				
		}
		vexin.close();
		cout<<"地址加载成功！"<<endl;
	}
 //cout<<"地图\n";
 /* 
	  for(i=1;i<=x;i++)
	  {
	  for(j=1;j<=x;j++)
	    {
	    if(G.arcs[i][j]==32767) cout<<"0  ";
	    else cout<<G.arcs[i][j]<<"  ";
	    }
	    cout<<endl;
      }
*/ 
//	  cout<<"加载成功!\n"<<endl; 

	  return OK;
}

Status DeQueue(SqQueue &Q)
{  
   if(Q.front==Q.rear) return ERROR;
   Q.front=(Q.front+1)%MAXSIZE;
}
	
Status LocateQueue(SqQueue Q,QElemType &e)
{  int i=Q.rear ,j=Q.front,flag,k=0;
     if(strcmp(e.Mark,"0")!=0) flag=1;        //判断是按哪种方式查找订单 
     if(strcmp(e.OrderName,"0")!=0) flag=2;
     if(strcmp(e.Telephone,"0")!=0) flag=3;
   switch(flag){
   case 1:  {
                     for(;j<i;j++)
                     {if(strcmp(e.Mark,Q.base[j].Mark)==0) {k=1;cout<<"已找到订单：" ;TraverQueue(Q,j);}} 
					 if(!k) cout<<"未按此编号查到订单\n"; 
			       return 0; 
			} 
                    
   case 2:  {
                     for(;j<i;j++) 
					 { if(strcmp(e.OrderName,Q.base[j].OrderName)==0){k=1;cout<<"已找到订单：" ;TraverQueue(Q,j);}}
					 if(!k) cout<<"未按此订单人姓名查到订单\n";
					return 0;
			}
                   
   case 3:  {
                     for(;j<i;j++)
                     {  if(strcmp(e.Telephone,Q.base[j].Telephone)==0){k=1;cout<<"已找到订单：" ;TraverQueue(Q,j);}}
					 if(!k) cout<<"未按此电话号码查到订单\n";
					return 0;
			} 
   default :cout<<"输入错误，请重新输入.\n"; 
    }             
}
void Findorder(SqQueue Q)
{   QElemType e;int i=0,w;char s[20], p[20]="0";
    strcpy(e.Mark,p);
	strcpy(e.OrderName,p);
	strcpy(e.Telephone,p);
    cout<<"请问您要按什么查找订单？";
    cout<<"1.编号 2.订单人姓名 3.订单电话 ";
    cin>>i;
	switch(i) 
	{  case 1:cout<<"请问需查找的订单编号是什么?";
	           cin>>s;
	           strcpy(e.Mark,s);
	            LocateQueue(Q,e);
	           
	          break;
	   case 2:cout<<"请问需查找的订单人姓名是什么?";
	           cin>>s;
	           strcpy(e.OrderName,s);
	            LocateQueue(Q,e);
	            
	          break;
	   case 3:cout<<"请问需查找的订单电话是什么?";
	           cin>>s;
	           strcpy(e.Telephone,s);
	            LocateQueue(Q,e);
	            
	          break;
	   default :cout<<"输入错误，请重新输入";
	}
}

void Deleteorder(SqQueue &Q)              //删除订单 
{   
     char s[20];
     int i,j;
     cout<<"请输入您要删除的订单编号:" ;
     cin >>s;
	 for(i=Q.front,j=Q.rear;i!=j;i=(i+1)%MAXSIZE)
	 {  
	    if(strcmp(Q.base[i].Mark,s)==0)//判断订单编号是否相等 
	    {
	        //cout<<"i="<<i<<"j="<<j;
	        for(;(i+1)%MAXSIZE!=j;i=(i+1)%MAXSIZE)
	        {
	         strcpy(Q.base[i].Mark,Q.base[i+1].Mark);
		     strcpy(Q.base[i].MealNum,Q.base[i+1].MealNum);
		     strcpy(Q.base[i].Mark2,Q.base[i+1].Mark2);
		     strcpy(Q.base[i].OrderName,Q.base[i+1].OrderName);
		     strcpy(Q.base[i].Telephone,Q.base[i+1].Telephone);
		     strcpy(Q.base[i].Address,Q.base[i+1].Address);
		     strcpy(Q.base[i].Date,Q.base[i+1].Date);
		     strcpy(Q.base[i].OrderTime,Q.base[i+1].OrderTime);
             Q.base[i].Orderstatus=Q.base[i+1].Orderstatus;
			}
			Q.rear=(Q.rear-1+MAXSIZE)%MAXSIZE;
		  cout<<"删除完毕"; 
		  return ;
	    }	 
	 }
	 cout<<"未找到目标订单编号"; 
}
void Changesetmeal(SetList &L)            //修改套餐
{    char s[20];
     int i,j;
     cout<<"|"<<"------------------------------- 套餐列表 --------------------------------|\n";
     cout<<"| 套餐编号   "<<"套餐名称      "<<"套餐描述\t\t     "<<"套餐价格"<<"    "<<"可否预订 |\n";
	 Traversetmeal(L);
	 cout<<"|"<<setfill('-')<<setw(74)<<"|"<<endl;
     
     cout<<"请输入您要修改的套餐编号" ;
     cin >>s;
	 for(i=0,j=L.length;i<j;i++)
	 {  
	    if(strcmp(L.base[i].Num,s)==0) 
	    {
	          cout<<"请输入该套餐新编号："; 
		     cin>>L.base[i].Num;
		      cout<<"请输入该套餐新名字："; 
		     cin>>L.base[i].Name;
		      cout<<"请输入该套餐新描述："; 
			 cin>>L.base[i].Description;
			  cout<<"请输入该套餐新价格："; 
			 cin>>L.base[i].Price;
			  cout<<"请输入该套餐新状态(0/1)："; 
			 cin>>L.base[i].Status;
		  cout<<"修改完毕"; 
		 		return ;   
	    }

	 }
	 cout<<"未找到目标套餐编号\n"; 
}
void Changeorder(SqQueue &Q,SetList &L)		      //修改订单
{    char s1[20],s2[20];
   //  string s2;
     int i,j,flag,x;
     cout<<"请输入您要修改的订单编号" ;
     cin >>s1;
	 for(i=Q.front,j=Q.rear;i!=j;i=(i+1)%MAXSIZE)
	 {  
	    if(strcmp(Q.base[i].Mark,s1)==0)//判断订单编号是否相等 
	    {     
		        cout<<"|"<<"------------------------------- 套餐列表 --------------------------------|\n";
			    cout<<"| 套餐编号   "<<"套餐名称      "<<"套餐描述\t\t     "<<"套餐价格"<<"    "<<"可否预订 |\n";
				Traversetmeal(L);
				cout<<"|"<<setfill('-')<<setw(74)<<"|"<<endl;
				
				cout<<"原订单:\n"; 
				cout<<"|"<<setfill('-')<<setw(106)<<"|"<<endl;
			    cout<<"| 订单编号\t 套餐名  数量    订单人       订单电话     订单地址  \t  订单日期    订单时间   订单状态 |\n"; 
			    TraverQueue(Q,i);
		        cout<<"|"<<setfill('-')<<setw(106)<<"|"<<endl;
		        
	       cout<<"请输入该新订单要订购的套餐编号：";
		   cin>>s2;
		   for(i=0;i<L.length;i++){
           if(strcmp(s2,L.base[i].Num)==0) {
          flag=1;x=i;}}
           if(!flag){cout<<"套餐编号不存在,输入失败\n";return;}   
		    
		   strcpy(Q.base[x].MealNum,s2) ;
		    
		   cout<<"请输入该订单新套餐数量：";
		   cin>>s2;
		   if(!isNumeric(s1)) {cout<<"数量不合法,输入失败\n";return;}
		   strcpy(Q.base[x].Mark2,s2);
		   
          cout<<"修改完毕\n修改后订单:";
		  TraverQueue(Q,x);
		  return ;
		}
	 }	 
	 cout<<"未找到目标订单编号\n" ; 
}




void Get_OccurTime(string &date1, string &date2,string &time1){//变量名不可使用time 
	time_t nowtime;
	struct tm* p;
	time(&nowtime);//C 库函数 time_t time(time_t *seconds) 返回自纪元 Epoch（1970-01-01 00:00:00 UTC）起经过的时间，以秒为单位。如果 seconds 不为空，则返回值也存储在变量 seconds 中。
	int y, m, d, h, mi, sec;
	p = localtime(&nowtime);
	y = p->tm_year + 1900;
	m = p->tm_mon + 1;
	d = p->tm_mday;
	h = p->tm_hour;
	mi = p->tm_min;
	sec = p->tm_sec;
	
	std::ostringstream ss;
    ss << y;      
//	cout<<ss;           
	date1 = date2 =ss.str();//<sstream>               <iostring> std::to_string(y);C++11
	date2 +="-";
	if(m<10) date1+="0";date2+="0";
	ss.str(""); // 重置 ss 的内容为空字符串
	ss << m;
	date1 += ss.str();//<iostring>  <=C++11
	date2 += ss.str() ;
	date2 +="-";
	char buffer[256];
	if(d<10) date1+="0";date2+="0";
    sprintf(buffer , "%d", d);
	date1 += buffer;
	date2 += buffer;
	
	if(h<10) date1+="0";time1+="0";
     snprintf(buffer, sizeof(buffer), "%d", h);//#<cstdio>
	date1 += buffer;    
	time1 = buffer;
	time1 +=":";
	if(mi<10) date1+="0";time1+="0";
	ss.str(""); // 重置 ss 的内容为空字符串
	ss << mi;
	date1 += ss.str();
	time1 += ss.str();
	time1 +=":";
	if(sec<10) date1+="0";time1+="0";
	ss.str(""); // 重置 ss 的内容为空字符串
	ss << sec;
	date1 += ss.str();
	time1 += ss.str();
}





void offwork(SetList &L)
{    
  int i;
	ofstream setout("taocan.txt");
	if(!setout.is_open()){
		cout<<"打开taocan文件失败!"<<endl;
	}
	if(setout.is_open()){
		for(i = 0; i < L.length ; i++){
			setout << L.base[i].Num<<" ";
			setout << L.base[i].Name<<" ";
			setout << L.base[i].Description<<" ";
			setout << L.base[i].Price<<" ";	
			setout << L.base[i].Status<<" "<<endl;
			if( i != L.length )
				setout<<endl;
		}
		setout.close();
	} 
}



void Out_order(SqQueue &Q)
{   
    Q.base[Q.rear-1].Orderstatus=1;
	Q.rear=(Q.rear-1+MAXSIZE)%MAXSIZE;
	//cout<<"Q.rear="<<Q.rear;
    ofstream orderout("ordercnt.txt",ios::app); // 打开文本文件，并设置可追加写入);
	     if(orderout.is_open())
        {
            orderout << Q.base[Q.rear].Mark<<"  ";
			orderout << Q.base[Q.rear].MealNum<<"  ";
			orderout << Q.base[Q.rear].Mark2<<"  ";
			orderout << Q.base[Q.rear].OrderName<<"  ";
            orderout << Q.base[Q.rear].Telephone<<"  ";
			orderout << Q.base[Q.rear].Address<<"  ";
			orderout << Q.base[Q.rear].Date<<"  ";
			orderout << Q.base[Q.rear].OrderTime<<"  ";
			orderout << Q.base[Q.rear].Orderstatus<<"  \n";
			orderout.close();
		}
		else cout<<"打开ordercnt.txt失败"; 
		cout<<"派送成功";
}

void Renewsetmeal(SetList &L)    //更新套餐信息，存储 
{   
    
}


// Dijkstra算法
void ShortestPath_Dijkstra(AMGraph G, int v, ArcType dist[], int path[]) {
    bool S[MVNum]; // S集合记录已确定好最短路径的顶点
    for (int i = 1; i <= G.vexnum; i++) {
        dist[i] = G.arcs[v][i];
        S[i] = false;  // 初始时S集合为空
        if (dist[i] < MaxInt)
            path[i] = v;
        else
            path[i] = 0; // 初始化为0
    }
    dist[v] = 0;
    S[v] = true;
    // 对初始化后的dist数组执行n-1次循环，每次将一个顶点纳入到S中
    for (int i = 1; i <= G.vexnum; i++) {
        // 查找当前未确定好最短路径的v到各顶点中距离最短的顶点min
        int min = MaxInt;
        int u = v;
        for (int j = 1; j <= G.vexnum; j++) {
            if (!S[j] && dist[j] < min) {
                u = j;
                min = dist[j];
            }
        }

        S[u] = true;
        // 更新dist数组和path数组
        for (int k = 1; k <= G.vexnum; k++) {
            if (!S[k] && G.arcs[u][k] < MaxInt && dist[u] + G.arcs[u][k] < dist[k]) {
                dist[k] = dist[u] + G.arcs[u][k];
                path[k] = u;
            }
        }
    }
}

// 获取从当前位置到目标位置的最短路径
vector<int> getShortestPath(AMGraph G, VerTexType startVex, VerTexType endVex) {
    // 查找起点和终点在顶点数组中的位置
    int startIndex = LocateVex(G, startVex);
    int endIndex = LocateVex(G, endVex);
 
    if (startIndex == -1 || endIndex == -1) {
        cout << "起点或终点不存在！" << endl;
        return vector<int>(); // 返回空vector
    }

    ArcType dist[MVNum]; // 存储起点到各顶点的最短距离
    int path[MVNum];     // 存储最短路径
    ShortestPath_Dijkstra(G, startIndex, dist, path);

    // 构造最短路径
    vector<int> shortestPath;
    shortestPath.push_back(startIndex);
    
    int p = path[endIndex];
    while (p != startIndex) {
     
		shortestPath.push_back(p);
        p = path[p];     
    }  
    shortestPath.push_back(endIndex);

    printShortestPath(G,shortestPath);
    return shortestPath;//怕报错，return一下 
}

void printShortestPath(AMGraph G, vector<int> shortestPath) {
    cout<<"最短路径为:"; 
	for (int i = 0; i < shortestPath.size(); i++) {
        int index = shortestPath[i];
        cout << G.vexs[index] << " ";
    }
    cout << endl;
    
    cout <<"大概需要"<<60*calculateTime(G,shortestPath)+10<<"分钟"<<"才能送达\n";
	 
}

double calculateTime(AMGraph G, vector<int> shortestPath) {
	
	double averageSpeed =30.0;
    double totalTime = 0.0;
    for (int i = 1; i < shortestPath.size(); i++) {
        int start = shortestPath[i - 1];
        int end = shortestPath[i];
        double distance = G.arcs[start][end];
        double time = distance / averageSpeed;
        totalTime += time;
    }
    return totalTime;
}

void statistics(SetList &L,SqQueue &Q)   //一天的所有订单，所有订单的套餐数，每个套餐各有多少,赚取的所有金额 
{  int i,j,k,o;                          //套餐结构体中有价格，可以按数量算金额
   string date1,date2,time3;             //一天所有订单，订单的数量另外计算，在算日期的判断中添加 
  typedef struct count_type{             //年，月，日中的套餐数，可以所有相加得到，金额数量和单价相乘得到 
   int daynum;                           //所有的一切数据在打开ordercnt.txt读取，一次全部读取，读取过程中计算存储 
   int monthnum;
   int yearnum;            }count_type;
   count_type count[L.length];             //记录所有套餐的各个时间数量的结构体 
   for(i=0;i<L.length;i++) 
   {  count[i].daynum=0;
      count[i].monthnum=0;
      count[i].yearnum=0;
   //   cout<<"count["<<i<<"].daynum="<<count[i].daynum;
   // cout<<"count["<<i<<"].monthnum="<<count[i].monthnum;
   // cout<<"count["<<i<<"].yearnum="<<count[i].yearnum;
   }
    
   //cout<<"L.length="<<L.length<<endl;
   
Get_OccurTime(date1,date2,time3);
   ifstream ordercntin("ordercnt.txt");
	if(ordercntin.is_open());
	//	cout<<"打开ordercnt.txt文件成功！"<<endl;
	else{
		cout<<"打开ordercnt.txt文件失败!"<<endl;
		return;  // 打开文件失败，直接返回
	    }	
if(ordercntin.peek() != EOF)   
  {
    i=0,j=0,k=0,o=0;
	int count_time=0;
    OrderElem ordercnt;
		while(!ordercntin.eof())
		{
		    count_time++;
		  //  cout<<"循环到"<< count_time<<"次\n";
		    
			ordercntin >> ordercnt.Mark;
		//	cout<<"现在是编号为"<<ordercnt.Mark<<"的订单进入循环\n"; 
			
			ordercntin >> ordercnt.MealNum;
		//	cout<<ordercnt.MealNum ;
			for(i=0,j=L.length;i<j;i++)
	           {  if(strcmp(L.base[i].Num,ordercnt.MealNum)==0)  
			                     {	
		//	      cout<<"找到了套餐名为"<<ordercnt.MealNum<<"的订单"; 
			      k=i;
		//	      cout<<"k="<<k; 
		                         }
	           }
			
			ordercntin >> ordercnt.Mark2;
			ordercntin >> ordercnt.OrderName;
            ordercntin >> ordercnt.Telephone;
			ordercntin >> ordercnt.Address;
			ordercntin >> ordercnt.Date; 
			         
		  o = atoi(ordercnt.Mark2);			 
		//	cout<<"o="<<o<<endl;
					                             
			if(strncmp(ordercnt.Date,date2.c_str(),4)==0)  
			{
		//	cout<<"找到了一个当年的订单";   
			count[k].yearnum=count[k].yearnum+o;//cout<< "count[k="<<k<<"].yearnum="<<count[k].yearnum;
			                                                }          
			if(strncmp(ordercnt.Date,date2.c_str(),7)==0) {
			//cout<<"找到了一个当月的订单";  
		
		  
			 count[k].monthnum=count[k].monthnum+o;//count[i].monthnum++不可用 
	    //          cout<<"count[k].monthnum="<<count[k].monthnum; 
			                                       }
			if(strcmp(ordercnt.Date,date2.c_str())==0) {
		//	cout<<"找到了一个当日的订单";            //
			count[k].daynum=count[k].daynum+o;
	    //    cout<<"count[k].daynum="<<count[k].daynum;
	           }
											                             	                            
			ordercntin >> ordercnt.OrderTime;
			ordercntin >> ordercnt.Orderstatus; 
		}	
		
			if(strncmp(ordercnt.Date,date2.c_str(),4)==0){count[k].yearnum=count[k].yearnum-o;} 
		    if(strncmp(ordercnt.Date,date2.c_str(),7)==0) {count[k].monthnum=count[k].monthnum-o;}
		    if(strcmp(ordercnt.Date,date2.c_str())==0) {count[k].daynum=count[k].daynum-o;}
		    count_time--;
		    
		    int years=0,months=0,days=0,years_price=0,months_price=0,days_price=0; 
		    for(i=0;i<L.length;i++)
		    { years=years+count[i].yearnum;
		    years_price=years_price+count[i].yearnum*L.base[i].Price;
			  months=months+count[i].monthnum;
			months_price=months_price+count[i].monthnum*L.base[i].Price;
			  days=days+count[i].daynum;
			days_price=days_price+count[i].daynum*L.base[i].Price;  
		    }
		    
		    
		    cout<<"|"<<setfill('-')<<setw(49)<<"|"<<endl;
		    cout<<"| 系统一共记录了 "<<count_time<<"   个订单                    |\n" ;
		    cout<<"| 今天一共送出了 "<<days<<"     个套餐"<<"总共的金额为 "<<days_price<<"      |"<<endl; 
		    cout<<"| 本月一共送出了 "<<months<<"     个套餐"<<"总共的金额为 "<<months_price<<"      |"<<endl;
		    cout<<"| 今年一共送出了 "<<years<<"  个套餐"<<"总共的金额为 "<<years_price<<"  |"<<endl;;
		    cout<<"|"<<setfill('-')<<setw(49)<<"|"<<endl; 
		    
		    
		    cout<<"| 套餐名"<<"    "<<"当天送餐数"<<"   "<<"本月送餐数"<<"   "<<"今年送餐数"<<" |\n";
		    for(i=0;i<L.length;i++)
		    {    
		    	cout<<"| "<<L.base[i].Name<<": "<<count[i].daynum<<"            "<<count[i].monthnum<<"            "<<setw(11)<<setfill(' ') <<setiosflags(ios::left)<<count[i].yearnum<<"|"<<endl; 	
		    }
		    
		    cout<<"|"<<setfill('-')<<setw(49)<<setiosflags(ios::right)<<"|"<<endl;
		    
		
  } 
}

int isNumeric(const char* str) {
    size_t length = strlen(str);
    for (size_t i = 0; i < length; ++i) {
        if (!isdigit(str[i])) {
            return 0;
        }
    }
    return 1;
}

