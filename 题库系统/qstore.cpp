#include<qstore.h>
//构造函数
qstore::qstore(string qb,string op,string aw)
{
	qbody = qb;
	opt = op;
	ans= aw;
}
//打印题干和备选项
void qstore::getq() {

	cout << qbody << endl;
	cout << opt << endl;
}
