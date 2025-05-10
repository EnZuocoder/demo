#include<menu.h>
menu::menu()
{
}
void menu::showmenu() {
	system("cls");//清屏
	cout << setw(50) << "1.开始答题" << endl
		<< setw(50) << "2.管理题库" << endl
		<< setw(50) << "3.退出系统" << endl;
}
void menu::exitmenu() {

	cout << "欢迎下次使用";
	system("pause");
	exit(0);//退出程序

}