//测试
//输入要求：要求表达式使用英文输入法下的加减乘除，表达式中无空格(注意结尾空格),
// 乘以负数（非首位）时要用括号把数字和符号括起来
//如：5+(-2)*9
// (2+3)*(-4/2)
//其他可用测试案例：               output:
       //3.5+(-2.1)*4/2          -0.7
       //(-5.6)/0.8-3.2*2        -13.4 
       //(2+3)*(-4/2)            -10
       //-(-(4+9)*10)            130 
//异常处理:
       //5/0  output:Error: Divide by zero!
       //6 +  9      Error: There are special characters in the expression.   
       //(8+9*7      Error: round braket isn't right!
       //.5+0.4      Error: the position of point isn't right!
       //4+5-        Error: the position of sign isn't right!
//tips:如果给出案例通不过：可能是空格原因,保证表达中无空格（特别是结尾空格）
#include<iostream>
#include<string>
using namespace std;
//采用链栈结构
struct Node
{
    double data;
    Node* next;
};
bool checkexp(string x);//表达式检查函数
bool checkbraket(string x);//专门用于检查括号是否匹配的函数代码复用
bool illegal=false;
int priority(double n);
double caculate(double a, double b,double s);
//链栈
class linkstack {
public:
    linkstack();
    ~linkstack();
    bool empty();
    double get_top();
    bool push(double x);
    double pop();
private:
    Node* top;//栈顶指针
    double count;//节点数      
};
linkstack::linkstack()
{
    count = 0;
    top = NULL;
}
bool linkstack::empty()
{
    if (count == 0)
        return true;
    else
        return false;
}
double linkstack::get_top()
{
    return top->data;
}
bool linkstack::push(double x)
{
    Node* s = new Node;
    s->data = x;
    s->next = top;
    top = s;
    count++;
    return 1;
}
double linkstack::pop()
{
    if (this->empty())
    {         
        return 0;
    }
    else
    {
        double x ;
        x = top->data;
        Node* d = top;
        top = top->next;
        count--;
        delete d;
        return x;
    }
}
linkstack::~linkstack()
{
    while (!empty()) {
        pop();
    }
}
int main()
{
    linkstack num;//数字栈
    linkstack sign;//符号栈
    cout << "请输入需要求解的表达式：" << endl;
    //表达式字符串
       string e;
       string n;//数字字符串
       bool totaln = false;
       double currents;//表示当前读到符号
       getline(cin, e);//整行将用户输入读入字符串  
       if(!checkexp(e)) 
       {
           for (int i = 0; i < e.length(); i++)
           {
               if (isdigit(e[i]))//对数字的处理使用到了isdigit判断是否是数值
               {   //识别连续的数字字符包括小数点
                   while (isdigit(e[i]) || e[i] == '.')
                       n += e[i++];
  //5.61+2
                       i--;
                       num.push(stod(n));
                       n.clear();
               }
               else {//这里表示对符号的处理情况：
                   if (sign.empty())//符号栈为空直接压入栈
                      sign.push(e[i]);
                   else if (e[i] == '(')//左括号直接压入
                   {
                       sign.push(e[i]);
                   }
                   else if (e[i] == ')')//遇到右括号持续弹栈进行运算直到遇到左括号
                   {
                       while (sign.get_top() != '(')
                       {
                               num.push(caculate(num.pop(), num.pop(), sign.pop()));
                       }
                       sign.pop();//运算完毕弹出栈中的左括号
                   }
                   else//其他运算符的情况 
                   {
                       //用栈模拟计算
                       //对减号还是负号的特殊处理,非明显减号就压零因为因为一个数的相反数等于零减这个数
                       if (e[i] == '-'&&(i==0||!isdigit(e[i+1])||!isdigit(e[i-1])))
                           num.push(0);
                       currents = (double)e[i];
                       {
                           while (!sign.empty() && (priority(currents) < priority(sign.get_top())
                               || priority(currents) == priority(sign.get_top())))
                           {
                               if (sign.empty())
                                   break;
                               //计算
                               num.push(caculate(num.pop(), num.pop(), sign.pop()));
                           }
                           sign.push(currents);
                       }
                   }
               }
           }
           //扫尾：弹出符号栈的剩余符号
           while (!sign.empty())
           {
               num.push(caculate(num.pop(), num.pop(), sign.pop()));
           }
           cout << "结果是：" << num.get_top() << endl;
       }
}
//优先级判定函数：
int priority(double n)
{
    int ret;
    int x = (int)n;
    switch (x)
    {
    case '+':ret = 1; break;
    case '-':
            ret = 1;
        break;
    case '*':ret = 2; break;
    case '/':ret = 2; break;
    case '(':ret = 0; break;//由于只对栈中的左括号进行判定，将其优先级设为零
    default:  ret = 0; break;
    }
    return ret;
}
//计算函数：
double caculate(double a,double b,double s)//函数传参是从右往左的，栈顶元素是减数传给b,
{
    int x =(int) s;
    double ret = -0.00001;
    switch (x)
    {
    case '+':ret = a + b; break;
    case '-':
        ret = a - b;
        break;
    case '*':ret = a * b; break;
    case '/':
        if (b == 0)
        {
            illegal = true;
            cout << "Error: Divide by zero!" << endl;
            exit(1);
        }
        ret = a/b ;//先弹出来的是除数 
        break;
    default: cout << "Error: error form!";  break;
    }
    return ret;
}
bool checkexp(string x)
{  
    bool illegal=false;
    for (int i = 0; i < x.length(); i++)
    {
        //对表达式进行检查，不符合规范的表达式直接输出错误信息

        //1.检查表达式中是否有特殊字符
        if (x[i] != '+' && x[i] != '-' && x[i] != '*' && x[i] != '/'
            && x[i] != '(' && x[i] != ')'
            && !isdigit(x[i]) && x[i] != '.')//好丑陋的代码
        {
            illegal = true;
            cout << "Error: There are special characters in the expression.";
            break;
        }
        //2.检查表达式中运算符中是否非法连续以及是否在表达式的首尾
        if (x[i] == '+' || x[i] == '-' || x[i] == '*' || x[i] == '/')
        {
            if ((i == 0&&x[i]!='-') || i == x.length() - 1)
            {
                illegal = true;
                cout << "Error: the position of sign isn't right!";
                break;
            }
            if (!isdigit(x[i + 1]) && x[i + 1] != '(')
            {
                illegal = true;
                cout << "Error: Constant signs in expression!";
                break;
            }
        }
        //3.检查表达式中小数点的位置是否合法,点不能出现在头尾，并且点的两边必须有数字
        if (x[i] == '.')
        {
            if (i == 0 || i == x.length() - 1 || !isdigit(x[i - 1]) || !isdigit(x[i + 1]))
            {
                cout << "Error: the position of point isn't right!";
                illegal = true;
                break;
            }
        }
    }
    if(illegal==false)//前面检查都不违法的情况下才会进行括号检查
    illegal = checkbraket(x);
    return illegal;
}
bool checkbraket(string x)
{
    linkstack p;
    for (int i = 0; i < x.length(); i++)
    {
        if (x[i] == '(')
            p.push(x[i]);
        else if (x[i] == ')')
        {
            if (p.empty() || p.get_top() != '(')
            {
                cout << "Error: round braket isn't right!";
                return true;
            }
            p.pop();
        }
    }
    if (!p.empty())
        cout << "Error: round braket isn't right!";
    return !p.empty();
}
//运算符号对应的阿斯克码：
//+  -  *  /  (  )
//43 45 42 47 40 41
