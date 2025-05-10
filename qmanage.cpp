#include<qmanage.h>
qmanage::qmanage() {
	ifstream ifs;
	ifs.open("qstore.txt", ios::in);
	if (!ifs.is_open())//
	{//��ʧ�ܣ�˵���ı��ļ���ɾ��
		cout << "�ļ�������"<<endl;
		qarry = NULL;
		qnum = 0;
		isempty = true;
		return;
	}
	char ch='0';
	ifs>>ch;
	if (ifs.eof())//�ж�����Ƿ�Ϊ��
	{
		cout << "������Ŀ"<<endl;
		qarry = NULL;
		qnum = 0;
		isempty = true;
		return;
	}
	//�ı��ǿգ��Ͱ��ı��е����ݶ��뵽����
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
		getline(ifs, qbody);//��ʼ�����
		if (qbody.empty())//�ж϶����Ķ����Ƿ�Ϊ��
		{
			if (!getline(ifs, qbody))
				break;

		}
		getline(ifs, opt);//��ʼ����ѡ��ʹ�
		getline(ifs, ans);
		qstore* q = NULL;
		q = new qstore(qbody, opt, ans);
		this->qarry[num] = q;//�������ָ������
		num++;

	}
	this->qnum = num;//��������
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
{//������������
	if (qarry != NULL)
	{
		delete[] qarry;
		qarry = NULL;
	}
}
void qmanage:: addq()//�����Ŀ������
{
	cout << "Ҫ��Ӽ�����Ŀ�� ";
	int addnum=0;
	cin >> addnum;
	if (addnum != 0)
	{
		int newsize = addnum + qnum;//�µ���Ŀ����
		qstore** newspace = new qstore * [newsize];//�����¿ռ�
//��ԭ�пռ����Ŀ�����¿ռ�
		if (qarry != NULL)//�ж�ԭ�ռ��Ƿ�Ϊ��
		{
			for (int i = 0; i < qnum; i++)
			{
				newspace[i] = qarry[i];
			}
	    }
		for (int i = 0; i < addnum; i++)
		{
			//��Ŀ
			qstore* q = NULL;//ָ����Ŀ���ָ��
			string body, opt, ans;//��ɣ�ѡ���
			cout << "��" << i+1 << "�������ɣ�";
			if (i == 0)
			char ch = getchar();//�ѻ������Ļس��̵�
			getline(cin, body);//����cin����ո�����
				cout << "��" << i+1 << "����ı�ѡ�";
				getline(cin, opt);
				cout << "��" << i+1 << "����Ĵ𰸣�";
				getline(cin, ans);
				q = new qstore(body, opt, ans);
				newspace[qnum+i] = q;//������õ���Ŀ����ָ������
		}
		////�ͷ�ԭ�ռ䲢����Ϊ�¿ռ������Ŀ����
		delete[] qarry;
		qarry = newspace;
		qnum =newsize;
		cout << "��ӳɹ�!";
		this->saveq();//���浽�ı�
		isempty = false;
	}
	else {
		cout << "�������";
	}
}
void qmanage::saveq()//������Ŀ���ı�
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
	cout << setw(50) << "1.�����Ŀ" << endl
		<< setw(50) << "2.�������" << endl
		<< setw(50) << "3.�༭��Ŀ" << endl
		<< setw(50) << "4.������" << endl
	<< setw(52) << "5.�������˵�" << endl;
	cout << "���������ѡ��";
}

void qmanage::seeq()//�鿴�������
{
	if (isempty)
	{
		cout << "��ǰ���Ϊ��,�������Ŀ" << endl;
	}
	else {
		for (int i = 0; i < qnum; i++)
		{
			cout << "��Ŀ" << i + 1 <<":"<<endl;
			cout << qarry[i]->qbody << endl;
			cout << qarry[i]->opt << endl;
			cout << "����𰸣�" << qarry[i]->ans;
			cout << endl<<endl;
		}
	}
}
void qmanage::cleanq()
{
	ofstream clean;
	clean.open("qstore.txt",ios::trunc);
	clean.close();
	cout << "��ճɹ�" << endl;
//�������
	qarry = NULL;
	qnum = 0;
	isempty = true;
}
void::qmanage::editq() {
	system("cls");
	
	while (1)
	{
		bool error = 0;//�ж��޸��Ƿ�Ϸ���bool��
		cout << "Ҫ�༭�ĵ���Ŀ������0�����ϼ��˵����� " << endl;
		cout << "��Ŀ��ţ�";
		int qn = -1;
		cin >> qn;
		if (qn > 0 && qn <=qnum)
		{
			int choice = -1;
			string qbody, opt, ans;
			char ch;


			cout << "Ҫ�༭" << "��" << qn << "��ģ�" << endl;
			cout << "1.���" << endl << "2.��ѡ��" << endl <<
				"3.��" << endl << "���������ѡ��";
			cin >> choice;
			switch (choice)
			{
			case 1:
				cout << "�������µ����";
				ch = getchar();
				getline(cin, qbody);

				qarry[qn - 1]->qbody = qbody;
				break;

			case 2:
				cout << "�������µ�ѡ��";
				ch = getchar();
				getline(cin, opt);
				qarry[qn - 1]->opt = opt;
				break;
			case 3:
				cout << "�������µĴ�";
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
				cout << "���Ϸ�" << endl;
				continue;
			}
			cout << "�޸ĳɹ�" << endl;
			saveq();

		}
		else
		{
			if (qn == 0)
			{
				return;
			}
			cout << "�޷��༭����,��ȷ�ϸ����Ƿ����" << endl;
			system("pause");
			editq();
		}
	}
}
void qmanage::answerfunc()
{
	system("cls");
	cout << setw(50) << "����ϵͳ" << endl;
	int num = 0;
	cout << "��Ҫ�𼸵���?(����0��ʾ�����ϼ��˵�)" << endl;
	cin >> num;
	if (num == 0)
		return;
	else if(num>qnum)
	{
		cout << "�����������" << num << "��";
		system("pause");
		answerfunc();
	}
	else
	{
	string* answer = new string[num];//������¼�û��𰸵��ַ�����
	int* n = new int[num];//������¼�����Ŀ������еı��
	for (int i = 0; i < num; i++)
	{
		n[i] = randnum(i,num);//����һ��������֣����ظ�����������
	}
//��ʾ��Ŀ��ͬʱ�ռ���
		for (int i = 0; i < num; i++)
		{
			cout << i+1<<".";
			qarry[n[i]]->getq();
			cout << "�������" << i+1 << "���" << endl;
			cin >> answer[i];
		}
		system("pause");
//�Զ��о�
		for (int i = 0; i < num; i++)
		{
			if (answer[i] == qarry[n[i]]->ans)
			{
				cout << "��" << i+1 << "��" << "��ȷ"<<endl;
			}
			else
				cout << "��" << i+1 << "��" << "����"<<endl;
		}
		system("pause");
	}
}
int qmanage::randnum(int i,int num)
{//����һ�����ظ����������
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
	return a[i];//������������е�һ��
}
