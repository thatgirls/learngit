```c++
class bignum
{
private:

	vector<int> value;    //可以控制大数的位数 
	int len;       //大数长度    
public:
	int flag;    //判断正负,1为正，0为负数
	bignum()
	{
		len = 1;
		memset(&value, 0, sizeof(value));
	}   //构造函数
	~bignum();				//AC解构函数；
	bignum(const int);       //AC将一个int类型的变量转化为大数
	bignum(const char);      //AC将char型转为大数;
	bignum(const string);   //AC将一个string类型的变量转化为大数
	bignum(const short);    //AC将一个short型的变量转为大数
	bignum(const long long);//AC将一个longlong型的变量转为大数
	bignum &operator =(const bignum &);  //AC重载赋值运算符，大数之间进行赋值运算
	friend istream& operator>>(istream&, bignum&);   //AC重载输入运算符
	friend ostream& operator<<(ostream&, bignum&);   //AC重载输出运算符
	bignum operator +(const bignum &) const;   //AC重载加法运算符，两个大数之间的相加运算
	bignum operator -(const bignum &) const;   //AC重载减法运算符，两个大数之间的相减运算
	bignum operator *(const bignum &) const;   //AC重载乘法运算符，两个大数之间的相乘运算 
	bignum operator /(const long long    &) const;  //AC重载除法运算符，大数对一个整数进行相除运算 大数太难了。。要能除尽啊！！！
	bignum operator / (const bignum &) const;  //AC挑战大数除法
	bool   operator >(const bignum & T)const;   //AC大数和另一个大数的大小比较
	bool   operator <(const bignum & T)const;      //AC大数和另一个大数的大小比较
	bool   operator ==(const bignum & T)const;      //AC大数和另一个大数的大小比较
	void   print();       //AC输出大数
};
```

该大数类的基本框架如上代码所示，按要求实现了大数的加减乘除，并谢了大数除以整数，建立了char,int,string,char*,short,long long 型的构造函数，析构函数，重载了+-*/四个符号，同时重载>>,<<,>,<,==,=；利用了stl库的vector作为数据的基本结构（那个万恶的越界啊。。。。为了节省空间没有初始分配足够大的空间），采用cmake编译（比起make是真的好用）vector向量的越界问题通过vector的resize函数在需要的时候分配了足够的空间（开始以为vector是动态数组，在前几天的编程时候并没有注意，但是在最后测试的时候，，，，呵呵，600行代码debug...不分源的后果。。。）在选用resize之前使用了reserve，发现reserve函数并不会实际的给vector创建空间，这是这次比较重要的收获，在主函数的编写，先对基本的构造进行了测试：

```c++
int main()
{
	bignum a, b, d, e, f, y, n, m;
	int x, t1, t2;
	long long t3, t4;
	short t5, t6;
	char t7, t8;
	char t9[20], t10[20];
	string t11, t12;
	cout << "下面是构造函数功能演示" << endl;
	cout << "将int利用构造函数转为大数,请输入两个int型数据" << endl;
	cin >> t1 >> t2;
	bignum b1(t1), b2(t2);
	cout << b1 << " " << b2 << endl;
	cout << "将longlong利用构造函数转为大数,请输入两个longlong型数据" << endl;
	cin >> t3 >> t4;
	bignum b3(t3), b4(t4);
	cout << b3 << " " << b4 << endl;
	cout << "将short转为大数,请输入两个short型数据" << endl;
	cin >> t5 >> t6;
	bignum b5(t5), b6(t6);
	cout << b5 << " " << b6 << endl;
	cout << "将char转为大数,请输入两个char型数据" << endl;
	cin >> t7 >> t8;
	bignum b7(t7), b8(t8);
	cout << b7 << " " << b8 << endl;
	cout << "将string转为大数,请输入两个string型数组数据" << endl;
	cin >> t11 >> t12;
	bignum b11(t11), b12(t12);
	cout << b11 << " " << b12 << endl;
	cout << "下面测试大数加减乘除" << endl;
	cout << "实现了大数加减乘除，并实现了大数除int型" << endl;
	cout << "请输入两个大数(把大的数放在前面)" << endl;
	cin >> a >> b;
	cout << "A+B的值为：";
	d = a + b;
	cout << d << endl;
	cout << "A-B的值为：";
	e = a - b;
	cout << e << endl;
	cout << "A*B的值为：";
	f = a * b;
	cout << f << endl;
	cout << "A/B的值为：";
	n = a / b;
	cout << n << endl;
	cout << "emmmm请输入一个大数，再输入一个整数（int）的" << endl;
	cin >> y >> x;
	m = y / x;
	cout << "商的值为：";
	cout << m << endl;
	system("pause");
}
```

过引导，让用户随便输入（按要求啊），再立刻输出构造好的大数类，检测<<和对应构造函数，之后随便输两个大数，会在屏幕上输出大数加减乘除的结果，最后是一个小彩蛋，顺便写了大数除以int型的函数emmmm能不能算是一个小小的加分项（手动滑稽）本次作业，让我第一次独立编写这么大一个类，也是第一次重载运算符（以前用的函数）加深了对c++类应用的理解，更加加深了对该死的向量的理解（那个该死的越界啊，debug 3天都在处理越界）至于内存方面，调用的向量，内存应该占得不多，这是向量自身的好处，算法复杂度（正常的大数运算，没啥新创造，除法是真的难写，，，）

在程序关键的地方加了应有的注释，缩进是按照VS2017的感觉走的（习惯了整齐）代码量693行（除法长啊）在被越界逼的差点砸电脑的时候看到修好了bug真的感动哭了aaaaaa