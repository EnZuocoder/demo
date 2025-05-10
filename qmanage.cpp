#include<qmanage.h>
qmanage::qmanage() {
	ifstream ifs;
	ifs.open("qstore.txt", ios::in);
	if (!ifs.is_open())//
	{//打开失败，说明文本文件被删除
		cout << "文件不存在"<<endl;
		qarry = NULL;
		qnum = 0;
		isempty = true;
		return;
	}
	char ch='0';
	ifs>>ch;
	if (ifs.eof())//判断题库是否为空
	{
		cout << "暂无题目"<<endl;
		qarry = NULL;
		qnum = 0;
		isempty = true;
		return;
	}
	//文本非空，就把文本中的数据读入到堆区
	qnum = this->getqnum();
	qarry = new qstore * [this->qnum];
	this->initq();

}
void qmanage::initq()
{
	ifstream ifs;
	ifs.open("qstore.txt", ios::in);
	int num = 0;
	string qbody, opt, ans;
	while (1)
	{
		getline(ifs, qbody);//初始化题干
		if (qbody.empty())//判断读到的东西是否为空
		{
			if (!getline(ifs, qbody))
				break;

		}
		getline(ifs, opt);//初始化备选项和答案
		getline(ifs, ans);
		qstore* q = NULL;
		q = new qstore(qbody, opt, ans);
		this->qarry[num] = q;//读入二级指针数组
		num++;

	}
	this->qnum = num;//更新数量
	ifs.close();
}
int qmanage::getqnum()
{
	ifstream ifs;
	ifs.open("qstore.txt", ios::in);
	string a, b, c;
	int num = 0;
	while (ifs >> a, ifs >> b, ifs >> c)
	{
		num++;
	}
	return num;

}
qmanage::~qmanage()
{//析构堆区数据
	if (qarry != NULL)
	{
		delete[] qarry;
		qarry = NULL;
	}
}
void qmanage:: addq()//添加题目到堆区
{
	cout << "要添加几个题目？ ";
	int addnum=0;
	cin >> addnum;
	if (addnum != 0)
	{
		int newsize = addnum + qnum;//新的题目数量
		qstore** newspace = new qstore * [newsize];//开辟新空间
//将原有空间的题目放入新空间
		if (qarry != NULL)//判断原空间是否为空
		{
			for (int i = 0; i < qnum; i++)
			{
				newspace[i] = qarry[i];
			}
	    }
		for (int i = 0; i < addnum; i++)
		{
			//题目
			qstore* q = NULL;//指向题目类的指针
			string body, opt, ans;//题干，选项，答案
			cout << "第" << i+1 << "道题的题干：";
			if (i == 0)
			char ch = getchar();//把缓冲区的回车吞掉
			getline(cin, body);//不用cin避免空格问题
				cout << "第" << i+1 << "道题的备选项：";
				getline(cin, opt);
				cout << "第" << i+1 << "道题的答案：";
				getline(cin, ans);
				q = new qstore(body, opt, ans);
				newspace[qnum+i] = q;//将输入好的题目放入指针数组
		}
		////释放原空间并更新为新空间更新题目数量
		delete[] qarry;
		qarry = newspace;
		qnum =newsize;
		cout << "添加成功!";
		this->saveq();//保存到文本
		isempty = false;
	}
	else {
		cout << "输入错误";
	}
}
void qmanage::saveq()//保存题目到文本
{
	fstream fst;
	fst.open("qstore.txt", ios::out);
	for (int i = 0; i < qnum; i++)
	{
		fst << qarry[i]->qbody << endl
			<< qarry[i]->opt << endl
			<< qarry[i]->ans << endl << endl;
	}
	fst.close();

}
void qmanage::showqmenu() 
{
	system("cls");
	cout << setw(50) << "1.添加题目" << endl
		<< setw(50) << "2.速览题库" << endl
		<< setw(50) << "3.编辑题目" << endl
		<< setw(50) << "4.清空题库" << endl
	<< setw(52) << "5.返回主菜单" << endl;
	cout << "请输入你的选择：";
}

void qmanage::seeq()//查看整个题库
{
	if (isempty)
	{
		cout << "当前题库为空,请添加题目" << endl;
	}
	else {
		for (int i = 0; i < qnum; i++)
		{
			cout << "题目" << i + 1 <<":"<<endl;
			cout << qarry[i]->qbody << endl;
			cout << qarry[i]->opt << endl;
			cout << "本题答案：" << qarry[i]->ans;
			cout << endl<<endl;
		}
	}
}
void qmanage::cleanq()
{
	ofstream clean;
	clean.open("qstore.txt",ios::trunc);
	clean.close();
	cout << "清空成功" << endl;
//堆区清空
	qarry = NULL;
	qnum = 0;
	isempty = true;
}
void::qmanage::editq() {
	system("cls");
	
	while (1)
	{
		bool error = 0;//判断修改是否合法的bool量
		cout << "要编辑哪道题目（输入0返回上级菜单）？ " << endl;
		cout << "题目序号：";
		int qn = -1;
		cin >> qn;
		if (qn > 0 && qn <=qnum)
		{
			int choice = -1;
			string qbody, opt, ans;
			char ch;


			cout << "要编辑" << "第" << qn << "题的：" << endl;
			cout << "1.题干" << endl << "2.备选项" << endl <<
				"3.答案" << endl << "请输入你的选择";
			cin >> choice;
			switch (choice)
			{
			case 1:
				cout << "请输入新的题干";
				ch = getchar();
				getline(cin, qbody);

				qarry[qn - 1]->qbody = qbody;
				break;

			case 2:
				cout << "请输入新的选项";
				ch = getchar();
				getline(cin, opt);
				qarry[qn - 1]->opt = opt;
				break;
			case 3:
				cout << "请输入新的答案";
				ch = getchar();
				getline(cin, ans);
				qarry[qn - 1]->ans = ans;
				break;
			default:
				error = 1;
				break;
			}
			if (error)
			{
				cout << "不合法" << endl;
				continue;
			}
			cout << "修改成功" << endl;
			saveq();

		}
		else
		{
			if (qn == 0)
			{
				return;
			}
			cout << "无法编辑该题,请确认该题是否存在" << endl;
			system("pause");
			editq();
		}
	}
}
void qmanage::answerfunc()
{
	system("cls");
	cout << setw(50) << "答题系统" << endl;
	int num = 0;
	cout << "你要答几道题?(输入0表示返回上级菜单)" << endl;
	cin >> num;
	if (num == 0)
		return;
	else if(num>qnum)
	{
		cout << "题库数量不足" << num << "题";
		system("pause");
		answerfunc();
	}
	else
	{
	string* answer = new string[num];//用来记录用户答案的字符数组
	int* n = new int[num];//用来记录随机题目在题库中的编号
	for (int i = 0; i < num; i++)
	{
		n[i] = randnum(i,num);//生成一串随机数字（不重复）放入数组
	}
//显示题目，同时收集答案
		for (int i = 0; i < num; i++)
		{
			cout << i+1<<".";
			qarry[n[i]]->getq();
			cout << "请输入第" << i+1 << "题答案" << endl;
			cin >> answer[i];
		}
		system("pause");
//自动判卷：
		for (int i = 0; i < num; i++)
		{
			if (answer[i] == qarry[n[i]]->ans)
			{
				cout << "第" << i+1 << "题" << "正确"<<endl;
			}
			else
				cout << "第" << i+1 << "题" << "错误"<<endl;
		}
		system("pause");
	}
}
int qmanage::randnum(int i,int num)
{//生成一串不重复的随机数组
	srand((unsigned)time(NULL));
	int* a = new int[num];
	for (int i=0;i<num;i++)
	{
		a[i] = rand() % num;
		for (int j = 0; j < i; j++)
		{
			if (a[i] == a[j])
			{
				i--;
					break;
			}
		}
	}
	return a[i];//返回随机数组中的一个
}
