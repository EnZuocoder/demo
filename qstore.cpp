#include<qstore.h>
//���캯��
qstore::qstore(string qb,string op,string aw)
{
	qbody = qb;
	opt = op;
	ans= aw;
}
//��ӡ��ɺͱ�ѡ��
void qstore::getq() {

	cout << qbody << endl;
	cout << opt << endl;
}
