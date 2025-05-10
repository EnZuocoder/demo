
#include<menu.h>
#include<qmanage.h>
int main()
{
	menu m;//主菜单类对象
	qmanage q;//题库管理类对象
	int choice = 0;//记录用户选择
	while (1)
	{
		m.showmenu();
		cout << "请输入你的选择：";
		cin >> choice;
		switch (choice)
		{case 1:
			q.answerfunc();//答题功能模块
			
			break;
		 case 2:
			 q.showqmenu(); //题库管理菜单
			
			 while (1)
			 {
				 cin >> choice;
				 switch (choice)
				 {
				 case 1:
					 q.addq();
					 cout << endl << "请输入你的选择：";
					 break;
				 case 2:
					 system("cls");
					 q.seeq();
					 while (1)
					 {
						 cout << "按4返回:";
						 cin >> choice;
						 if (choice == 4)
						 {
							 choice = 0;
							 system("cls");
							 break;
						 }
							 
					 }
					 q.showqmenu();
					 break;
				 case 3:
					 q.editq();
					 q.showqmenu();
					 break;
				 case 4:
					 q.cleanq();
					 cout << "请输入你的选择：";
					 break;
					 
				 case 5:
					 system("cls");
					 break;
				 default:
					 system("cls");
					 q.showqmenu();
					 break;
				 }
				 if (choice == 5)
					 break;
			 }
			 break;
		 case 3:
			 m.exitmenu();//退出菜单
			 break;

		default:
			system("cls");//如果输入并非1,2,3清屏，让用户重新输入
			break;
		}
	}
		return 0;
}
