#include"wow.h"
void Load_main_menu(){
	//加载主菜单
	cout<<"|"<<setfill('-')<<setw(51)<<"|"<<endl;
	cout<<"|********* \" 宅 急 送 \" 订 餐 管 理 系 统 *********|"<<endl;
	cout<<"|"<<"+++++++++++ 1-商家端 2-用户端 3-骑手端 +++++++++++"<<"|"<<endl;
	cout<<"|"<<setfill('-')<<setw(51)<<"|"<<endl;
}
void Load_start_word_menu(){
	//加载开始工作菜单 
	cout<<"--------------------------"<<endl;
	cout<<"系统已开启->->->->->->->->"<<endl;
	cout<<"--------------------------"<<endl;
	cout<<"信息加载->->->->->->->->->"<<endl;
	cout<<"--------------------------"<<endl;
}
void Load_server_side_menu(){
	//加载商家端二级菜单 
    cout<<"|"<<setfill('-')<<setw(39)<<" 商家端"<<" ---------------------------------"<<"|"<<endl;
	cout<<"|+ 1-开启系统 2-显示订单 3-套餐数据维护 4-统计信息 0-返回上级 9-关闭系统 +|"<<endl;
	cout<<"|"<<setfill('-')<<setw(74)<<"|"<<endl;
}
void Load_client_side_menu(){
	//加载用户端二级菜单 
	cout<<"|--------------------- 用户端 ---------------------|"<<endl;
	cout<<"|+ 1-订单 2-查询订单 3-订单编辑 4-订单撤销 0-退出 +|"<<endl;
	cout<<"|--------------------------------------------------|"<<endl;
}
void Load_Courier_side_menu(){
	//加载骑手端二级菜单
	cout<<"|--------------- 骑手端 ---------------|"<<endl;
	cout<<"|+ 1-显示未派送订单 2-逐个派送 0-退出 +|"<<endl;
	cout<<"|--------------------------------------|"<<endl; 
} 
void Load_data_maintenance_menu(){
	//加载基础数据维护三级菜单
	cout<<"|------------------- 套餐数据维护 ---------------------|"<<endl;
	cout<<"|+ 1-查看套餐 2-添加套餐 3-修改套餐 4-删除套餐 0-退出 +|"<<endl;
	cout<<"|------------------------------------------------------|"<<endl; 
}
void Load_statistics_menu(){
	//加载统计三级菜单
	cout<<"|------ 统计信息 ------|"<<endl;
	cout<<"|+ 1-汇总统计  0-退出 +|"<<endl;
	cout<<"|----------------------|"<<endl; 
} 


void Application()
{
	//启动程序
AMGraph G;
SqQueue Q;   //不能在初始化时直接定义 
SetList L;
bool isworking = 0;
   int flag=0;  //first lever menu
   int i=0,j=0,k=0;//second lever menu
   int l=0,m=0,n=0;//third lever menu
   int u=0,v=0,x=0,y=0,o,p;//fourth lever menu
  while(true)
	 {Load_main_menu();//加载主菜单 
	  if(flag==0&&j==0&&k==0){cout<<"请输入您的选项：";cin>>flag;}//(if)mei guan {}jianzhuang 
	
		switch(flag)
		{   case 1:i=1;break;
		    case 2:j=1;break;
		    case 3:k=1;break;
		    //case 0://break;
		    default:cout<<"输入错误，请重新输入\n";
		            flag=0,i=0;j=0,k=0;
		}
	    if(i==1) { 
		        Load_server_side_menu();
		        cout<<"请输入您的选项：";
		        cin>>l;
		        switch(l)
		        {  case 1: if(isworking) {cout<<"系统已经初始化了\n";break;}
				           Initsetmeal(L);
						   Initorder(Q);
						   CreateUDN(G);
						   Load_start_word_menu(); 
						   isworking = 1;
						   break;//start work;
		           case 2:
				        if(!isworking) {cout<<"系统暂未初始化";break;}
				        cout<<"|"<<setfill('-')<<setw(106)<<" 订单列表 -----------------------------------------------|"<<endl;
				        cout<<"| 订单编号\t 套餐名  数量    订单人       订单电话     订单地址  \t  订单日期    订单时间   订单状态 |\n";
				        Traverorder(Q);//traver order
				        cout<<"|"<<setfill('-')<<setw(106)<<"|"<<endl;
						   break;
		           case 3:u=1;
		                if(!isworking) {cout<<"系统暂未初始化";break;}
		                
				          while(u)
				          {
				           Load_data_maintenance_menu();//mantain information
		                   cout<<"请输入您的选项：";cin>>v; 
		                  switch (v)
		                   { case 1:cout<<"|"<<"------------------------------- 套餐列表 --------------------------------|\n";
			                        cout<<"| 套餐编号   "<<"套餐名称      "<<"套餐描述\t\t     "<<"套餐价格"<<"    "<<"可否预订 |\n";
						            Traversetmeal(L);
						            cout<<"|"<<setfill('-')<<setw(74)<<"|"<<endl;
						            
						            break;
		                  	 case 2:Addsetmeal(L);break;
		                  	 case 3:Changesetmeal(L);break;
		                  	 case 4:Deletesetmeal(L);break; 
		                  	 case 0:u=0;break;
		                  	 default:cout<<"输入错误，请重新输入\n";
		                   }
						  }
		                  break;
		           case 4:x=1;
		                if(!isworking) {cout<<"系统暂未初始化";break;}
		                 
				          while(x)
				          {
				           Load_statistics_menu();//mantain information
		                   cout<<"请输入您的选项：";cin>>y; 
		                  switch (y)
		                   { case 1:statistics(L,Q);break;
		                  	 
		                  	 case 0:x=0;break;
		                  	 deault:cout<<"输入错误，请重新输入\n";
		                   }
						  }
		                  break;
		               
		           case 9: if(!isworking) {cout<<"系统退出成功，感谢您的使用!";return;}
				           offwork(L);
			
				           cout<<"系统退出成功，感谢您的使用!\n";return ; 
				   case 0: flag=0;i=0;break;//back  
		           default:cout<<"输入错误，请重新输入\n";
		        }	          
		      } 
		      
if((isworking&&j==1)||(isworking&&k==1)){//
	    if(j) {
	    	Load_client_side_menu();
	    	cout<<"请输入您的选项：";
	    	cin>>m;
	    	switch(m)
	    	{  case 1:cout<<"|"<<"------------------------------- 套餐列表 --------------------------------|\n";
			          cout<<"| 套餐编号   "<<"套餐名称      "<<"套餐描述\t\t     "<<"套餐价格"<<"    "<<"可否预订 |\n";
					  Traversetmeal(L);
					  cout<<"|"<<setfill('-')<<setw(74)<<"|"<<endl;
			
			          Enorder(Q,L,G);break;   //book order
	    	   case 2:Findorder(Q);break;              //check order
	    	   case 3:Changeorder(Q,L);break;
	    	   case 4:Deleteorder(Q);break;
	    	   case 0:cout<<"back\n";flag=0,j=0;break;//back   
	    	   default:cout<<"输入错误，请重新输入\n";
	    	}
	          }
	          
	    if(k) {
	    	Load_Courier_side_menu();
	    	cout<<"请输入您的选项：";
			cin>>o; 
			int starpos,endpos;                  
	    	string Temporary,start_Vex,end_Vex;  //不能在switch(k)内初始化 [Error] crosses initialization of 'std::string end_Vex' 
	    	 
	    	switch(o) 
	    	{  case 1:  cout<<"|"<<setfill('-')<<setw(106)<<" 订单列表 -----------------------------------------------|"<<endl;
				        cout<<"| 订单编号\t 套餐名  数量    订单人       订单电话     订单地址  \t  订单日期    订单时间   订单状态 |\n";
				        Traverorder(Q);//traver order
				        cout<<"|"<<setfill('-')<<setw(106)<<"|"<<endl;
						   break;
	    	   case 2:
	    	   	
	    	   	
	    	   	      
	    	   	      start_Vex="  ",end_Vex="  ";
	    	   	      cout<<"请输入骑手您的位置：";
					  cin >>Temporary;
					  
					  starpos=LocateVex(G,Temporary);
			
					  if(starpos!=-1) start_Vex=G.vexs[starpos];
					  else {cout<<"输入地点不存在，请重新输入";break;}
					   
			          endpos=LocateVex(G,Q.base[Q.rear-1].Address);//-1 txt问题：1.ANSI 2.空格 3.名字 
			          
			          end_Vex=G.vexs[endpos];//bug -1.txt问题 
					  getShortestPath(G,start_Vex,end_Vex);
					  
					  
			          Out_order(Q);break;           //send order
	    	   case 0:cout<<"back\n";flag=0,k=0;break;//back
	    	   default:cout<<"输入错误，请重新输入\n";
		    }              
	          }	                      
}
else if((!isworking&&j!=0)||(!isworking&&k!=0)){cout<<"系统暂未开启\n";flag=0,i=0;j=0,k=0;}

	        system("pause");
	        system("cls");
	}	
}
