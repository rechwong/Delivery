#include"wow.h"
void Load_main_menu(){
	//�������˵�
	cout<<"|"<<setfill('-')<<setw(51)<<"|"<<endl;
	cout<<"|********* \" լ �� �� \" �� �� �� �� ϵ ͳ *********|"<<endl;
	cout<<"|"<<"+++++++++++ 1-�̼Ҷ� 2-�û��� 3-���ֶ� +++++++++++"<<"|"<<endl;
	cout<<"|"<<setfill('-')<<setw(51)<<"|"<<endl;
}
void Load_start_word_menu(){
	//���ؿ�ʼ�����˵� 
	cout<<"--------------------------"<<endl;
	cout<<"ϵͳ�ѿ���->->->->->->->->"<<endl;
	cout<<"--------------------------"<<endl;
	cout<<"��Ϣ����->->->->->->->->->"<<endl;
	cout<<"--------------------------"<<endl;
}
void Load_server_side_menu(){
	//�����̼Ҷ˶����˵� 
    cout<<"|"<<setfill('-')<<setw(39)<<" �̼Ҷ�"<<" ---------------------------------"<<"|"<<endl;
	cout<<"|+ 1-����ϵͳ 2-��ʾ���� 3-�ײ�����ά�� 4-ͳ����Ϣ 0-�����ϼ� 9-�ر�ϵͳ +|"<<endl;
	cout<<"|"<<setfill('-')<<setw(74)<<"|"<<endl;
}
void Load_client_side_menu(){
	//�����û��˶����˵� 
	cout<<"|--------------------- �û��� ---------------------|"<<endl;
	cout<<"|+ 1-���� 2-��ѯ���� 3-�����༭ 4-�������� 0-�˳� +|"<<endl;
	cout<<"|--------------------------------------------------|"<<endl;
}
void Load_Courier_side_menu(){
	//�������ֶ˶����˵�
	cout<<"|--------------- ���ֶ� ---------------|"<<endl;
	cout<<"|+ 1-��ʾδ���Ͷ��� 2-������� 0-�˳� +|"<<endl;
	cout<<"|--------------------------------------|"<<endl; 
} 
void Load_data_maintenance_menu(){
	//���ػ�������ά�������˵�
	cout<<"|------------------- �ײ�����ά�� ---------------------|"<<endl;
	cout<<"|+ 1-�鿴�ײ� 2-����ײ� 3-�޸��ײ� 4-ɾ���ײ� 0-�˳� +|"<<endl;
	cout<<"|------------------------------------------------------|"<<endl; 
}
void Load_statistics_menu(){
	//����ͳ�������˵�
	cout<<"|------ ͳ����Ϣ ------|"<<endl;
	cout<<"|+ 1-����ͳ��  0-�˳� +|"<<endl;
	cout<<"|----------------------|"<<endl; 
} 


void Application()
{
	//��������
AMGraph G;
SqQueue Q;   //�����ڳ�ʼ��ʱֱ�Ӷ��� 
SetList L;
bool isworking = 0;
   int flag=0;  //first lever menu
   int i=0,j=0,k=0;//second lever menu
   int l=0,m=0,n=0;//third lever menu
   int u=0,v=0,x=0,y=0,o,p;//fourth lever menu
  while(true)
	 {Load_main_menu();//�������˵� 
	  if(flag==0&&j==0&&k==0){cout<<"����������ѡ�";cin>>flag;}//(if)mei guan {}jianzhuang 
	
		switch(flag)
		{   case 1:i=1;break;
		    case 2:j=1;break;
		    case 3:k=1;break;
		    //case 0://break;
		    default:cout<<"�����������������\n";
		            flag=0,i=0;j=0,k=0;
		}
	    if(i==1) { 
		        Load_server_side_menu();
		        cout<<"����������ѡ�";
		        cin>>l;
		        switch(l)
		        {  case 1: if(isworking) {cout<<"ϵͳ�Ѿ���ʼ����\n";break;}
				           Initsetmeal(L);
						   Initorder(Q);
						   CreateUDN(G);
						   Load_start_word_menu(); 
						   isworking = 1;
						   break;//start work;
		           case 2:
				        if(!isworking) {cout<<"ϵͳ��δ��ʼ��";break;}
				        cout<<"|"<<setfill('-')<<setw(106)<<" �����б� -----------------------------------------------|"<<endl;
				        cout<<"| �������\t �ײ���  ����    ������       �����绰     ������ַ  \t  ��������    ����ʱ��   ����״̬ |\n";
				        Traverorder(Q);//traver order
				        cout<<"|"<<setfill('-')<<setw(106)<<"|"<<endl;
						   break;
		           case 3:u=1;
		                if(!isworking) {cout<<"ϵͳ��δ��ʼ��";break;}
		                
				          while(u)
				          {
				           Load_data_maintenance_menu();//mantain information
		                   cout<<"����������ѡ�";cin>>v; 
		                  switch (v)
		                   { case 1:cout<<"|"<<"------------------------------- �ײ��б� --------------------------------|\n";
			                        cout<<"| �ײͱ��   "<<"�ײ�����      "<<"�ײ�����\t\t     "<<"�ײͼ۸�"<<"    "<<"�ɷ�Ԥ�� |\n";
						            Traversetmeal(L);
						            cout<<"|"<<setfill('-')<<setw(74)<<"|"<<endl;
						            
						            break;
		                  	 case 2:Addsetmeal(L);break;
		                  	 case 3:Changesetmeal(L);break;
		                  	 case 4:Deletesetmeal(L);break; 
		                  	 case 0:u=0;break;
		                  	 default:cout<<"�����������������\n";
		                   }
						  }
		                  break;
		           case 4:x=1;
		                if(!isworking) {cout<<"ϵͳ��δ��ʼ��";break;}
		                 
				          while(x)
				          {
				           Load_statistics_menu();//mantain information
		                   cout<<"����������ѡ�";cin>>y; 
		                  switch (y)
		                   { case 1:statistics(L,Q);break;
		                  	 
		                  	 case 0:x=0;break;
		                  	 deault:cout<<"�����������������\n";
		                   }
						  }
		                  break;
		               
		           case 9: if(!isworking) {cout<<"ϵͳ�˳��ɹ�����л����ʹ��!";return;}
				           offwork(L);
			
				           cout<<"ϵͳ�˳��ɹ�����л����ʹ��!\n";return ; 
				   case 0: flag=0;i=0;break;//back  
		           default:cout<<"�����������������\n";
		        }	          
		      } 
		      
if((isworking&&j==1)||(isworking&&k==1)){//
	    if(j) {
	    	Load_client_side_menu();
	    	cout<<"����������ѡ�";
	    	cin>>m;
	    	switch(m)
	    	{  case 1:cout<<"|"<<"------------------------------- �ײ��б� --------------------------------|\n";
			          cout<<"| �ײͱ��   "<<"�ײ�����      "<<"�ײ�����\t\t     "<<"�ײͼ۸�"<<"    "<<"�ɷ�Ԥ�� |\n";
					  Traversetmeal(L);
					  cout<<"|"<<setfill('-')<<setw(74)<<"|"<<endl;
			
			          Enorder(Q,L,G);break;   //book order
	    	   case 2:Findorder(Q);break;              //check order
	    	   case 3:Changeorder(Q,L);break;
	    	   case 4:Deleteorder(Q);break;
	    	   case 0:cout<<"back\n";flag=0,j=0;break;//back   
	    	   default:cout<<"�����������������\n";
	    	}
	          }
	          
	    if(k) {
	    	Load_Courier_side_menu();
	    	cout<<"����������ѡ�";
			cin>>o; 
			int starpos,endpos;                  
	    	string Temporary,start_Vex,end_Vex;  //������switch(k)�ڳ�ʼ�� [Error] crosses initialization of 'std::string end_Vex' 
	    	 
	    	switch(o) 
	    	{  case 1:  cout<<"|"<<setfill('-')<<setw(106)<<" �����б� -----------------------------------------------|"<<endl;
				        cout<<"| �������\t �ײ���  ����    ������       �����绰     ������ַ  \t  ��������    ����ʱ��   ����״̬ |\n";
				        Traverorder(Q);//traver order
				        cout<<"|"<<setfill('-')<<setw(106)<<"|"<<endl;
						   break;
	    	   case 2:
	    	   	
	    	   	
	    	   	      
	    	   	      start_Vex="  ",end_Vex="  ";
	    	   	      cout<<"��������������λ�ã�";
					  cin >>Temporary;
					  
					  starpos=LocateVex(G,Temporary);
			
					  if(starpos!=-1) start_Vex=G.vexs[starpos];
					  else {cout<<"����ص㲻���ڣ�����������";break;}
					   
			          endpos=LocateVex(G,Q.base[Q.rear-1].Address);//-1 txt���⣺1.ANSI 2.�ո� 3.���� 
			          
			          end_Vex=G.vexs[endpos];//bug -1.txt���� 
					  getShortestPath(G,start_Vex,end_Vex);
					  
					  
			          Out_order(Q);break;           //send order
	    	   case 0:cout<<"back\n";flag=0,k=0;break;//back
	    	   default:cout<<"�����������������\n";
		    }              
	          }	                      
}
else if((!isworking&&j!=0)||(!isworking&&k!=0)){cout<<"ϵͳ��δ����\n";flag=0,i=0;j=0,k=0;}

	        system("pause");
	        system("cls");
	}	
}
