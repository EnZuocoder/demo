#include<menu.h>
menu::menu()
{
}
void menu::showmenu() {
	system("cls");//����
	cout << setw(50) << "1.��ʼ����" << endl
		<< setw(50) << "2.�������" << endl
		<< setw(50) << "3.�˳�ϵͳ" << endl;
}
void menu::exitmenu() {

	cout << "��ӭ�´�ʹ��";
	system("pause");
	exit(0);//�˳�����

}