#include "wow.h"

//--------------------------------------------------

void Initsetmeal(SetList &L)
{
InitSetList(L);
ifstream setin("taocan.txt");
	if(setin.is_open())
		cout<<"��taocan.txt�ļ��ɹ���"<<endl;
	else{
		cout<<"��taocan.txt�ļ�ʧ��!"<<endl;
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
		cout<<"�ײͼ��سɹ���"<<endl;
		//Traverorder(L);
	}
}

Status InitSetList(SetList &L)
{  
   L.base=new SetElem[MAXSIZE];
   if(!L.base) {cout<<"���г�ʼ��ʧ��";exit(OVERFLOW);}
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
	if(L.base[n].Status) cout<<"��Ԥ�� |\n"; 
	else cout<<"����Ԥ�� |\n";            
}
void Addsetmeal(SetList &L)
{   
	cout<<"���������ӵ��ײͱ��:";
	cin>>L.base[L.length].Num;
	cout<<"���������ӵ��ײ���:"; 
	cin>>L.base[L.length].Name;
	cout<<"���������ӵ�����:";
	cin>>L.base[L.length].Description; 
	cout<<"���������ӵļ۸�:"; 
	cin>>L.base[L.length].Price;
	cout<<"���������ӵ�״̬(�ɷ�Ԥ��1/0):"; 
    cin>>L.base[L.length].Status;//��0��1���ϵ����ֻ���ѭ�� 
    L.length++;
}
/* 
void Findsetmeal(SetList &L)   //�����ײ� 
{   int flag,i,j,x;
    char s[20];
    cout<<"��Ҫ��ô�����ײͣ�";
    cout<<"1.��� 2.�ײ���";
	cin>>flag;
	switch(flag)
	{   case 1:
	           cout<<"������Ҫ���ҵ��ײͱ��";
	           cin >>s;
	           for(i=0,j=L.length;i<j;i++)
	           {  if(strcmp(L.base[i].Num,s)==0) TraverList(L,i);  
	           }
	           break;
	    case 2: cout<<"������Ҫ���ҵ��ײ���";
	           cin >>s;
	           for(i=0,j=L.length;i<j;i++)
	           {  if(strcmp(L.base[i].Name,s)==0) TraverList(L,i);  
	           }
	           break;
	    	default:cout<<"�������";
	} 
    
}
*/


void Deletesetmeal(SetList &L)
{    char s[20];
     int i,j;
     cout<<"��������Ҫɾ�����ײͱ��" ;
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
		  cout<<"ɾ�����\n"; 
		  return ;
	    }
	 }
		 cout<<"δ�ҵ�Ŀ���ײͱ��";
}


Status InitQueue(SqQueue &Q)
{  
   Q.base=new QElemType[MAXSIZE];
   if(!Q.base) {cout<<"���г�ʼ��ʧ��";exit(OVERFLOW);}
   Q.front=Q.rear=0;
}

void Initorder(SqQueue &Q)
{
InitQueue(Q);
ifstream orderin("dingdan.txt");
	if(orderin.is_open())
		cout<<"��dingdan.txt�ļ��ɹ���"<<endl;
	else{
		cout<<"��dingdan.txt�ļ�ʧ��!"<<endl;
		return;  // ���ļ�ʧ�ܣ�ֱ�ӷ���
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
	//	 if(strcmp(Order.Address,"�����")==0) strcpy(Order.Address,"�����");//txt  LocateVex
			orderin >> Order.Date;
			orderin >> Order.OrderTime;
			orderin >> Order.Orderstatus; 
if(Order.Orderstatus)         //������         //�ж�txt�ļ����Ƿ��������͵Ķ������洢�����ʹ洢�ļ��� 
  {
   ofstream orderout("ordercnt.txt",ios::app); // ���ı��ļ��������ÿ�׷��д��(bug:û����;
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
	    else cout<<"�޷�������ļ���" << endl;	      
  }  
else      {                       //δ���� 
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
		
		cout<<"�������سɹ���"<<endl;
  }
}

Status EnQueue(SqQueue &Q,QElemType e)
{  
   string d1,d2,t;
   Get_OccurTime(d1,d2,t); 
   if((Q.rear+1)%MAXSIZE==Q.front) return ERROR;
       //char�����string������,string!=char*��û��ֱ������d1.c_str()��  
   strcpy(Q.base[Q.rear].Mark,d1.c_str());                             //�޷�ֱ�� Q.base[Q.rear]=e;
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
cout<<"�������µĶ������ײͱ�ţ�";
cin>>e.MealNum;

for(i=0;i<L.length;i++){
if(strcmp(e.MealNum,L.base[i].Num)==0) flag=1;}
if(!flag){cout<<"�ײͱ�Ų�����,����ʧ��";return;} 
 
cout<<"�������µĶ������ײ�����:"; 
cin>>e.Mark2;

if(!isNumeric(e.Mark2)) {cout<<"�������Ϸ�,����ʧ��";return;}

cout<<"�������µĶ����Ķ�������:"; 
cin>>e.OrderName;
cout<<"�������µĶ����ĵ绰:";
cin>>e.Telephone;
if(!isNumeric(e.Telephone)) {cout<<"�绰�ַ����Ϸ�,����ʧ��";return;}
if(strlen(e.Telephone)!=11) {cout<<"�绰�ַ�λ�����Ϸ�,����ʧ��";return;}
cout<<"�������µĶ����ĵ�ַ��"; 
cin>>e.Address;

int x=0,y=0;

for(x=1;x<=G.vexnum;x++){
if(G.vexs[x]==e.Address) y=1;}
if(!y) {cout<<"��ַδ�ҵ�������ʧ��";return;}

e.Orderstatus=0;
EnQueue(Q,e); 
TraverQueue(Q,Q.rear-1) ;   
return ;              
}

Status QueueLength(SqQueue Q)   
{  return((Q.rear-Q.front+MAXSIZE)%MAXSIZE); }

Status LocateVex(AMGraph &G,VerTexType u)
{   int i;
    if(u=="����") return 3;  //txt
    if(u=="�����") return 10; 
    for(i=1;i<=G.vexnum;i++)
    {    
	    if(G.vexs[i]==u) return i;
    }
    return -1;//�Ҳ�������-1 
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
if(Q.base[n].Orderstatus) cout<<"������"; 
else cout<<"δ����"<<" |"<<endl;
}

void Traverorder(SqQueue &Q)
{ int i,j;i=Q.rear,j=Q.front;
  for(;j<i;j++) TraverQueue(Q,j);
}

Status CreateUDN(AMGraph &G)
{//�����ڽӾ����ʾ��������������G
      int k; 
      int x=0;int i,j;
      G.vexnum=0,G.arcnum=0;
      ifstream vexin("���е�ַ.txt");
	if(vexin.is_open())
		cout<<"�����е�ַ.txt�ļ��ɹ�!"<<endl;
	else{
		cout<<"�����е�ַ.txt�ļ�ʧ��!"<<endl;
	}
	if(vexin.is_open()&&vexin.peek() != EOF){//10 .10.���һ����������  ѭ�����ٸ���G.vexnum=x   ---p -1bug
		while(!vexin.eof()){
			vexin >> x;
			vexin >> G.vexs[x];
		}
		G.vexnum=x;	//bug������� 
		vexin.close();
		cout<<"��ַ���سɹ���"<<endl;
	}
	  for(i=1;i<=x;i++)
	    for(j=1;j<=x;j++)
	       G.arcs[i][j]=MaxInt;

ifstream arcin("����ַ�����.txt");
	if(arcin.is_open())
		cout<<"��ַ�����.txt�ļ��ɹ�!"<<endl;
	else{
		cout<<"��ַ�����.txt�ļ�ʧ��!"<<endl;
	}
	if(arcin.is_open()&&arcin.peek() != EOF){
		while(!arcin.eof()){
string arc1,arc2;
float w;			
			arcin >> arc1>> arc2>> w;                //txt�е�Ĵ�����0��74ӦΪ0.74���ᵼ���޷���ȷ��ȡ������             
			i=LocateVex(G,arc1);
			//cout<<i=
			j=LocateVex(G,arc2);
            G.arcs[i][j]=w;
            G.arcs[j][i]=G.arcs[i][j];				
		}
		vexin.close();
		cout<<"��ַ���سɹ���"<<endl;
	}
 //cout<<"��ͼ\n";
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
//	  cout<<"���سɹ�!\n"<<endl; 

	  return OK;
}

Status DeQueue(SqQueue &Q)
{  
   if(Q.front==Q.rear) return ERROR;
   Q.front=(Q.front+1)%MAXSIZE;
}
	
Status LocateQueue(SqQueue Q,QElemType &e)
{  int i=Q.rear ,j=Q.front,flag,k=0;
     if(strcmp(e.Mark,"0")!=0) flag=1;        //�ж��ǰ����ַ�ʽ���Ҷ��� 
     if(strcmp(e.OrderName,"0")!=0) flag=2;
     if(strcmp(e.Telephone,"0")!=0) flag=3;
   switch(flag){
   case 1:  {
                     for(;j<i;j++)
                     {if(strcmp(e.Mark,Q.base[j].Mark)==0) {k=1;cout<<"���ҵ�������" ;TraverQueue(Q,j);}} 
					 if(!k) cout<<"δ���˱�Ų鵽����\n"; 
			       return 0; 
			} 
                    
   case 2:  {
                     for(;j<i;j++) 
					 { if(strcmp(e.OrderName,Q.base[j].OrderName)==0){k=1;cout<<"���ҵ�������" ;TraverQueue(Q,j);}}
					 if(!k) cout<<"δ���˶����������鵽����\n";
					return 0;
			}
                   
   case 3:  {
                     for(;j<i;j++)
                     {  if(strcmp(e.Telephone,Q.base[j].Telephone)==0){k=1;cout<<"���ҵ�������" ;TraverQueue(Q,j);}}
					 if(!k) cout<<"δ���˵绰����鵽����\n";
					return 0;
			} 
   default :cout<<"�����������������.\n"; 
    }             
}
void Findorder(SqQueue Q)
{   QElemType e;int i=0,w;char s[20], p[20]="0";
    strcpy(e.Mark,p);
	strcpy(e.OrderName,p);
	strcpy(e.Telephone,p);
    cout<<"������Ҫ��ʲô���Ҷ�����";
    cout<<"1.��� 2.���������� 3.�����绰 ";
    cin>>i;
	switch(i) 
	{  case 1:cout<<"��������ҵĶ��������ʲô?";
	           cin>>s;
	           strcpy(e.Mark,s);
	            LocateQueue(Q,e);
	           
	          break;
	   case 2:cout<<"��������ҵĶ�����������ʲô?";
	           cin>>s;
	           strcpy(e.OrderName,s);
	            LocateQueue(Q,e);
	            
	          break;
	   case 3:cout<<"��������ҵĶ����绰��ʲô?";
	           cin>>s;
	           strcpy(e.Telephone,s);
	            LocateQueue(Q,e);
	            
	          break;
	   default :cout<<"�����������������";
	}
}

void Deleteorder(SqQueue &Q)              //ɾ������ 
{   
     char s[20];
     int i,j;
     cout<<"��������Ҫɾ���Ķ������:" ;
     cin >>s;
	 for(i=Q.front,j=Q.rear;i!=j;i=(i+1)%MAXSIZE)
	 {  
	    if(strcmp(Q.base[i].Mark,s)==0)//�ж϶�������Ƿ���� 
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
		  cout<<"ɾ�����"; 
		  return ;
	    }	 
	 }
	 cout<<"δ�ҵ�Ŀ�궩�����"; 
}
void Changesetmeal(SetList &L)            //�޸��ײ�
{    char s[20];
     int i,j;
     cout<<"|"<<"------------------------------- �ײ��б� --------------------------------|\n";
     cout<<"| �ײͱ��   "<<"�ײ�����      "<<"�ײ�����\t\t     "<<"�ײͼ۸�"<<"    "<<"�ɷ�Ԥ�� |\n";
	 Traversetmeal(L);
	 cout<<"|"<<setfill('-')<<setw(74)<<"|"<<endl;
     
     cout<<"��������Ҫ�޸ĵ��ײͱ��" ;
     cin >>s;
	 for(i=0,j=L.length;i<j;i++)
	 {  
	    if(strcmp(L.base[i].Num,s)==0) 
	    {
	          cout<<"��������ײ��±�ţ�"; 
		     cin>>L.base[i].Num;
		      cout<<"��������ײ������֣�"; 
		     cin>>L.base[i].Name;
		      cout<<"��������ײ���������"; 
			 cin>>L.base[i].Description;
			  cout<<"��������ײ��¼۸�"; 
			 cin>>L.base[i].Price;
			  cout<<"��������ײ���״̬(0/1)��"; 
			 cin>>L.base[i].Status;
		  cout<<"�޸����"; 
		 		return ;   
	    }

	 }
	 cout<<"δ�ҵ�Ŀ���ײͱ��\n"; 
}
void Changeorder(SqQueue &Q,SetList &L)		      //�޸Ķ���
{    char s1[20],s2[20];
   //  string s2;
     int i,j,flag,x;
     cout<<"��������Ҫ�޸ĵĶ������" ;
     cin >>s1;
	 for(i=Q.front,j=Q.rear;i!=j;i=(i+1)%MAXSIZE)
	 {  
	    if(strcmp(Q.base[i].Mark,s1)==0)//�ж϶�������Ƿ���� 
	    {     
		        cout<<"|"<<"------------------------------- �ײ��б� --------------------------------|\n";
			    cout<<"| �ײͱ��   "<<"�ײ�����      "<<"�ײ�����\t\t     "<<"�ײͼ۸�"<<"    "<<"�ɷ�Ԥ�� |\n";
				Traversetmeal(L);
				cout<<"|"<<setfill('-')<<setw(74)<<"|"<<endl;
				
				cout<<"ԭ����:\n"; 
				cout<<"|"<<setfill('-')<<setw(106)<<"|"<<endl;
			    cout<<"| �������\t �ײ���  ����    ������       �����绰     ������ַ  \t  ��������    ����ʱ��   ����״̬ |\n"; 
			    TraverQueue(Q,i);
		        cout<<"|"<<setfill('-')<<setw(106)<<"|"<<endl;
		        
	       cout<<"��������¶���Ҫ�������ײͱ�ţ�";
		   cin>>s2;
		   for(i=0;i<L.length;i++){
           if(strcmp(s2,L.base[i].Num)==0) {
          flag=1;x=i;}}
           if(!flag){cout<<"�ײͱ�Ų�����,����ʧ��\n";return;}   
		    
		   strcpy(Q.base[x].MealNum,s2) ;
		    
		   cout<<"������ö������ײ�������";
		   cin>>s2;
		   if(!isNumeric(s1)) {cout<<"�������Ϸ�,����ʧ��\n";return;}
		   strcpy(Q.base[x].Mark2,s2);
		   
          cout<<"�޸����\n�޸ĺ󶩵�:";
		  TraverQueue(Q,x);
		  return ;
		}
	 }	 
	 cout<<"δ�ҵ�Ŀ�궩�����\n" ; 
}




void Get_OccurTime(string &date1, string &date2,string &time1){//����������ʹ��time 
	time_t nowtime;
	struct tm* p;
	time(&nowtime);//C �⺯�� time_t time(time_t *seconds) �����Լ�Ԫ Epoch��1970-01-01 00:00:00 UTC���𾭹���ʱ�䣬����Ϊ��λ����� seconds ��Ϊ�գ��򷵻�ֵҲ�洢�ڱ��� seconds �С�
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
	ss.str(""); // ���� ss ������Ϊ���ַ���
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
	ss.str(""); // ���� ss ������Ϊ���ַ���
	ss << mi;
	date1 += ss.str();
	time1 += ss.str();
	time1 +=":";
	if(sec<10) date1+="0";time1+="0";
	ss.str(""); // ���� ss ������Ϊ���ַ���
	ss << sec;
	date1 += ss.str();
	time1 += ss.str();
}





void offwork(SetList &L)
{    
  int i;
	ofstream setout("taocan.txt");
	if(!setout.is_open()){
		cout<<"��taocan�ļ�ʧ��!"<<endl;
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
    ofstream orderout("ordercnt.txt",ios::app); // ���ı��ļ��������ÿ�׷��д��);
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
		else cout<<"��ordercnt.txtʧ��"; 
		cout<<"���ͳɹ�";
}

void Renewsetmeal(SetList &L)    //�����ײ���Ϣ���洢 
{   
    
}


// Dijkstra�㷨
void ShortestPath_Dijkstra(AMGraph G, int v, ArcType dist[], int path[]) {
    bool S[MVNum]; // S���ϼ�¼��ȷ�������·���Ķ���
    for (int i = 1; i <= G.vexnum; i++) {
        dist[i] = G.arcs[v][i];
        S[i] = false;  // ��ʼʱS����Ϊ��
        if (dist[i] < MaxInt)
            path[i] = v;
        else
            path[i] = 0; // ��ʼ��Ϊ0
    }
    dist[v] = 0;
    S[v] = true;
    // �Գ�ʼ�����dist����ִ��n-1��ѭ����ÿ�ν�һ���������뵽S��
    for (int i = 1; i <= G.vexnum; i++) {
        // ���ҵ�ǰδȷ�������·����v���������о�����̵Ķ���min
        int min = MaxInt;
        int u = v;
        for (int j = 1; j <= G.vexnum; j++) {
            if (!S[j] && dist[j] < min) {
                u = j;
                min = dist[j];
            }
        }

        S[u] = true;
        // ����dist�����path����
        for (int k = 1; k <= G.vexnum; k++) {
            if (!S[k] && G.arcs[u][k] < MaxInt && dist[u] + G.arcs[u][k] < dist[k]) {
                dist[k] = dist[u] + G.arcs[u][k];
                path[k] = u;
            }
        }
    }
}

// ��ȡ�ӵ�ǰλ�õ�Ŀ��λ�õ����·��
vector<int> getShortestPath(AMGraph G, VerTexType startVex, VerTexType endVex) {
    // ���������յ��ڶ��������е�λ��
    int startIndex = LocateVex(G, startVex);
    int endIndex = LocateVex(G, endVex);
 
    if (startIndex == -1 || endIndex == -1) {
        cout << "�����յ㲻���ڣ�" << endl;
        return vector<int>(); // ���ؿ�vector
    }

    ArcType dist[MVNum]; // �洢��㵽���������̾���
    int path[MVNum];     // �洢���·��
    ShortestPath_Dijkstra(G, startIndex, dist, path);

    // �������·��
    vector<int> shortestPath;
    shortestPath.push_back(startIndex);
    
    int p = path[endIndex];
    while (p != startIndex) {
     
		shortestPath.push_back(p);
        p = path[p];     
    }  
    shortestPath.push_back(endIndex);

    printShortestPath(G,shortestPath);
    return shortestPath;//�±���returnһ�� 
}

void printShortestPath(AMGraph G, vector<int> shortestPath) {
    cout<<"���·��Ϊ:"; 
	for (int i = 0; i < shortestPath.size(); i++) {
        int index = shortestPath[i];
        cout << G.vexs[index] << " ";
    }
    cout << endl;
    
    cout <<"�����Ҫ"<<60*calculateTime(G,shortestPath)+10<<"����"<<"�����ʹ�\n";
	 
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

void statistics(SetList &L,SqQueue &Q)   //һ������ж��������ж������ײ�����ÿ���ײ͸��ж���,׬ȡ�����н�� 
{  int i,j,k,o;                          //�ײͽṹ�����м۸񣬿��԰���������
   string date1,date2,time3;             //һ�����ж���������������������㣬�������ڵ��ж������ 
  typedef struct count_type{             //�꣬�£����е��ײ���������������ӵõ�����������͵�����˵õ� 
   int daynum;                           //���е�һ�������ڴ�ordercnt.txt��ȡ��һ��ȫ����ȡ����ȡ�����м���洢 
   int monthnum;
   int yearnum;            }count_type;
   count_type count[L.length];             //��¼�����ײ͵ĸ���ʱ�������Ľṹ�� 
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
	//	cout<<"��ordercnt.txt�ļ��ɹ���"<<endl;
	else{
		cout<<"��ordercnt.txt�ļ�ʧ��!"<<endl;
		return;  // ���ļ�ʧ�ܣ�ֱ�ӷ���
	    }	
if(ordercntin.peek() != EOF)   
  {
    i=0,j=0,k=0,o=0;
	int count_time=0;
    OrderElem ordercnt;
		while(!ordercntin.eof())
		{
		    count_time++;
		  //  cout<<"ѭ����"<< count_time<<"��\n";
		    
			ordercntin >> ordercnt.Mark;
		//	cout<<"�����Ǳ��Ϊ"<<ordercnt.Mark<<"�Ķ�������ѭ��\n"; 
			
			ordercntin >> ordercnt.MealNum;
		//	cout<<ordercnt.MealNum ;
			for(i=0,j=L.length;i<j;i++)
	           {  if(strcmp(L.base[i].Num,ordercnt.MealNum)==0)  
			                     {	
		//	      cout<<"�ҵ����ײ���Ϊ"<<ordercnt.MealNum<<"�Ķ���"; 
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
		//	cout<<"�ҵ���һ������Ķ���";   
			count[k].yearnum=count[k].yearnum+o;//cout<< "count[k="<<k<<"].yearnum="<<count[k].yearnum;
			                                                }          
			if(strncmp(ordercnt.Date,date2.c_str(),7)==0) {
			//cout<<"�ҵ���һ�����µĶ���";  
		
		  
			 count[k].monthnum=count[k].monthnum+o;//count[i].monthnum++������ 
	    //          cout<<"count[k].monthnum="<<count[k].monthnum; 
			                                       }
			if(strcmp(ordercnt.Date,date2.c_str())==0) {
		//	cout<<"�ҵ���һ�����յĶ���";            //
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
		    cout<<"| ϵͳһ����¼�� "<<count_time<<"   ������                    |\n" ;
		    cout<<"| ����һ���ͳ��� "<<days<<"     ���ײ�"<<"�ܹ��Ľ��Ϊ "<<days_price<<"      |"<<endl; 
		    cout<<"| ����һ���ͳ��� "<<months<<"     ���ײ�"<<"�ܹ��Ľ��Ϊ "<<months_price<<"      |"<<endl;
		    cout<<"| ����һ���ͳ��� "<<years<<"  ���ײ�"<<"�ܹ��Ľ��Ϊ "<<years_price<<"  |"<<endl;;
		    cout<<"|"<<setfill('-')<<setw(49)<<"|"<<endl; 
		    
		    
		    cout<<"| �ײ���"<<"    "<<"�����Ͳ���"<<"   "<<"�����Ͳ���"<<"   "<<"�����Ͳ���"<<" |\n";
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

