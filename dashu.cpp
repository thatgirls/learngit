#include<iostream>
#include<vector>
#include<algorithm>
#include<cctype>
#include<string>
#include<string.h>
using namespace std;
int digit;
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
bool bignum::operator ==(const bignum & b)const
{
	int i;
	if (len != b.len) return false;
	else
	{
		for (int i = 0; i < b.len; i++)
		{
			if (value[i] != b.value[i]) return false;
		}
		return true;
	}
}
bignum::~bignum()
{
	value.resize(0);
}
bignum::bignum(const string b)
{
	string c = b;
	if (c[0] == '-')
	{
		int x = (c[1] - '0')*(-1);
		value.push_back(x);
		for (int i = c.size() - 1; i > 1; i--)
		{
			int t = c[i] - '0';
			value.push_back(t);
		}
		int w = (-1)*(c[1] - '0');
		value.push_back(w);
		len = value.size();
		flag = 0;
	}
	else
	{
		for (int i = c.size() - 1; i >= 0; i--)
		{
			int t = c[i] - '0';
			value.push_back(t);
		}
		len = value.size();
		flag = 1;
	}
}
bignum::bignum(const int b)
{
	int c;
	int t;
	if (b >= 0) c = b;
	else c = -b;
	while (c != 0)
	{
		t = c % 10;
		c = c / 10;
		value.push_back(t);
	}
	len = value.size();
	if (b >= 0) {
		flag = 1;
		value.push_back(c);
	}
	else
	{
		flag = 0;
		c = c * (-1);
		value.push_back(c);
	}
	len = value.size();
}
bignum::bignum(const char b)
{
	int x = b - '0';
	value.push_back(x);
	len = value.size();
}
bignum::bignum(const short b)
{
	short c;
	if (b >= 0) c = b;
	else c = -b;
	while (c != 0)
	{
		int t = c % 10;
		c = c / 10;
		value.push_back(t);
	}
	len = value.size();
	if (b >= 0) {
		flag = 1;
		value.push_back(c);
	}
	else
	{
		flag = 0;
		c = c * (-1);
		value.push_back(c);
	}
	len = value.size();
}
bignum::bignum(const long long b)
{
	long long  c;
	if (b >= 0) c = b;
	else c = -b;
	while (c != 0)
	{
		int t = c % 10;
		c = c / 10;
		value.push_back(t);
	}
	len = value.size();
	if (b >= 0) {
		flag = 1;
		value.push_back(c);
	}
	else
	{
		flag = 0;
		c = c * (-1);
		value.push_back(c);
	}
	len = value.size();
}
bignum & bignum::operator=(const bignum & b)
{
	value.resize(0);
	int newlen = b.len;
	for (int i = 0; i < newlen; i++)
	{
		value.push_back(b.value[i]);
	}
	len = newlen;
	flag = b.flag;
	return *this;
}
void bignum::print()
{
	int n = len;
	for (int i = n; i > -1; i--)
	{
		cout << value[i];
	}
}
bignum bignum::operator +(const bignum &b) const
{
	bignum t(*this);
	bignum c = b;
	int m;
	int minlen = t.len >= c.len ? c.len : t.len;
	int maxlen = t.len >= c.len ? t.len : c.len;
	t.value.resize(t.value.size() + 3);
	if (c.flag == t.flag) //同号
	{

		for (int i = 0; i < minlen; i++)
		{
			t.value[i] += c.value[i];
			m = t.value[i] / 10;
			int k = 1;
			while (m != 0)
			{
				t.value[i + k] = t.value[i + k] + m;
				m = t.value[i + k] / 10;
				t.value[i + k] %= 10;
				k++;
			}
		}
		if (t.value[c.len - 1] >= 10)
		{
			t.value[c.len] += value[c.len - 1] / 10;
			t.value[c.len - 1] -= 10;
		}
		if (t.value[value.size() - 1] != 0) t.len = t.value.size();
		else t.len = t.value.size() - 1;
	}
	else if (t.flag == 1 && c.flag == 0)
	{
		c.flag = 1;
		c.value[value.size() - 1] *= -1;
		bignum x;
		x = t - c;
		x.len = x.value.size();
		return x;
	}
	else
	{
		bignum y;
		y = c + t;
		y.len = y.value.size();
		return y;
	}
	return t;
}
bignum bignum::operator -(const bignum &b) const
{
	int i, j, big, min;
	int flag;
	bignum t(*this);
	bignum t1, t2;
	if (b.flag == 0)
	{
		bignum c = b;
		c.flag = 1;
		c.value[value.size() - 1] *= -1;
		bignum x;
		x = t + c;/*zhe
		for (int i = x.value.size(); i >= 0 ; i--)
		{
			if (x.value[i])
			{
				x.len = i + 1;
			}
		}*/
		//x.len = x.value.size();
		return x;
	}
	if (t > b)
	{
		t1 = t;
		t2 = b;
		flag = 1;
	}
	else
	{
		t1 = b;
		t2 = t;
		flag = 0;
	}
	big = t1.len;
	min = t2.len;
	t1.value.push_back(0);
	t2.value.push_back(0);
	for (i = 0; i < min; i++)
	{
		if (t1.value[i] < t2.value[i])
		{
			j = i + 1;
			while (t1.value[j] == 0)
				j++;
			t1.value[j--]--;
			while (j > i)
				t1.value[j--] += 9;
			t1.value[i] += 10;
			t1.value[i] -= t2.value[i];
		}
		else
			t1.value[i] -= t2.value[i];
	}
	t1.len = big;
	while (t1.value[t1.len - 1] == 0 && t1.len > 1)
	{
		t1.len--;
		big--;
	}
	if (!flag)
	{
		t1.value[big - 1] = 0 - t1.value[big - 1];
	}
	return t1;
}
bignum bignum::operator *(const bignum &b) const
{
	bignum ret;
	bignum a(*this);
	bignum c = b;
	ret.value.resize(100000);
	int i, j, k;
	int t, t1;
	for (i = 0; i < len; i++)
	{
		k = 0;
		for (j = 0; j < b.len; j++)
		{
			t = value[i] * b.value[j] + ret.value[i + j] + k;
			if (t > 9)
			{
				t1 = t - t / 10 * 10;
				k = t / 10;
				ret.value[i + j] = t1;
			}
			else
			{
				k = 0;
				ret.value[i + j] = t;
			}
		}
		if (k != 0)
			ret.value[i + j] = k;
	}
	ret.len = i + j;
	while (ret.value[ret.len - 1] == 0 && ret.len > 1)
		ret.len--;
	return ret;
}
bignum bignum::operator / (const long long  &b) const
{
	bignum ret;
	ret.value.resize(value.size() + 100000);
	int i, down = 0;
	for (i = len - 1; i >= 0; i--)
	{
		ret.value[i] = (value[i] + down * 10) / b;
		down = value[i] + down * 10 - ret.value[i] * b;
	}
	ret.len = len;
	while (ret.value[ret.len - 1] == 0 && ret.len > 1)
		ret.len--;
	return ret;
}
void sub(int x[], int y[], int len1, int len2)//大数减法
{
	int i;
	for (i = 0; i < len1; i++)
	{
		if (x[i] < y[i])
		{
			x[i] = x[i] + 10 - y[i];
			x[i + 1]--;
		}
		else
			x[i] = x[i] - y[i];
	}
	for (i = len1 - 1; i >= 0; i--)//判断减法结束之后，被除数的位数
	{
		if (x[i])
		{
			digit = i + 1;
			break;
		}
	}
}
int judge(int x[], int y[], int len1, int len2)
{
	int i;
	if (len1 < len2)
		return -1;
	if (len1 == len2)//若两个数位数相等
	{
		for (i = len1 - 1; i >= 0; i--)
		{
			if (x[i] == y[i])//对应位的数相等
				continue;
			if (x[i] > y[i])//被除数 大于 除数，返回值为1
				return 1;
			if (x[i] < y[i])//被除数 小于 除数，返回值为-1
				return -1;
		}
		return 0;//被除数 等于 除数，返回值为0
	}
}
bignum bignum::operator / (const bignum &b) const
{
	bignum t(*this);
	bignum c;
	int x[100], y[100],z[100] , len, len1 = t.len, len2 = b.len;
	int i , j = 0, k = 0, temp;
	for (i = 0; i < t.len; i++)
	{
		x[i] = t.value[i];
	}
	for (i = 0; i < b.len; i++)
	{
		y[i] = b.value[i];
	}
	len = len1 - len2;//两个大数位数的差值  
	for (i = len1 - 1; i >= 0; i--)//将除数后补零，使得两个大数位数相同。被除数：4541543329 除数：98745,加零后:9874500000   
	{
		if (i >= len)
			y[i] = y[i - len];
		else
			y[i] = 0;
	}
	len2 = len1;//将两个大数数位相同         
	digit = len1; //将原被除数位数赋值给digit   
	for (j = 0; j <= len; j++)
	{
		z[len - j] = 0;
		while (((temp = judge(x, y, len1, len2)) >= 0) && digit >= k)//判断两个数之间的关系以及位数与除数原位数的关系   
		{
			sub(x, y, len1, len2); //大数减法函数                  
			z[len - j]++;//储存商的每一位  
			len1 = digit;//重新修改被除数的长度  
			if (len1 < len2&&y[len2 - 1] == 0)
				len2 = len1;//将len1长度赋给len2;                        
		}
		if (temp < 0)//若被除数 小于 除数，除数减小一位。
		{
			for (i = 1; i < len2; i++)
				y[i - 1] = y[i];
			y[i - 1] = 0;
			if (len1 < len2)
				len2--;
		}
	}
	for (i = len; i > 0; i--)//去掉前缀0   
	{
		if (z[i])
			break;
	}
	for (; i >= 0; i--)
	{
		c.value.push_back(z[i]);
	}
	c.len = c.value.size();
	return c;
}
ostream& operator<<(ostream& out, bignum& b)
{
	int n = b.len;
	int i;
	for (i = n - 1; i >= 0; i--)
	{
		if (b.value[i] != 0)break;
	}
	for (; i >= 0; i--)
	{
		cout << b.value[i];
	}
	return out;
}
istream& operator>>(istream&in, bignum&b)
{
	string c;
	cin >> c;
	if (c[0] == '-')
	{
		for (int i = c.size() - 1; i > 0; i--)
		{
			int t = c[i] - '0';
			b.value.push_back(t);
		}
		b.value[b.value.size() - 1] *= -1;
		b.len = b.value.size();
		/*int x = (c[1] - '0')*(-1);
		b.value.push_back(x);
		for (int i = c.size() - 1; i > 1; i--)
		{
			int t = c[i] - '0';
			b.value.push_back(t);
		}
		int w = (-1)*(c[1] - '0');
		b.value.push_back(w);
		b.len = b.value.size();
		b.flag = 0;*/
	}
	else
	{
		for (int i = c.size() - 1; i >= 0; i--)
		{
			int t = c[i] - '0';
			b.value.push_back(t);
		}
		b.len = b.value.size();
		b.flag = 1;
	}
	return in;
}
bool bignum::operator >(const bignum & b)const
{
	if (flag == b.flag)
	{
		if (flag == 1)//都是正数
		{
			if (len > b.len) return true;
			else if (len < b.len) return false;
			else
			{
				int n = b.len;
				for (int i = n - 1; i >= 0; i--)
				{
					if (value[i] > b.value[i])
					{
						return true;
					}
					else if (value[i] == b.value[i])
					{
						continue;
					}
					else
					{
						return false;
					}
				}
				return false;
			}
		}
		else //负数
		{
			if (len > b.len) return false;
			else if (len < b.len) return true;
			else
			{
				int n = b.value.size();
				if (value[n - 1] > value[n - 1])
				{
					return true;
				}
				else if (value[n - 1] == value[n - 1])
				{
					for (int i = n - 2; i >= 0; i--)
					{
						if (value[i] > b.value[i])
						{
							return false;
						}
						else if (value[i] == b.value[i])
						{
							continue;
						}
						else
						{
							return true;
						}
					}
					return false;
				}
				else return false;
			}
		}
	}
	else
	{
		if (flag == 1 && b.flag == 0)
			return true;
		else
			return false;
	}
}
bool bignum::operator < (const bignum & b)const
{
	if (flag == b.flag)
	{
		if (flag == 1)//都是正数
		{
			if (len > b.len) return false;
			else if (len < b.len) return true;
			else
			{
				int n = b.value.size();
				for (int i = n - 1; i >= 0; i--)
				{
					if (value[i] > b.value[i])
					{
						return false;
					}
					else if (value[i] == b.value[i])
					{
						continue;
					}
					else
					{
						return true;
					}
				}
				return false;
			}
		}
		else //负数
		{
			if (len > b.len) return true;
			else if (len < b.len) return false;
			else
			{
				int n = b.value.size();
				if (value[n - 1] > value[n - 1])
				{
					return false;
				}
				else if (value[n - 1] == value[n - 1])
				{
					for (int i = n - 2; i >= 0; i--)
					{
						if (value[i] > b.value[i])
						{
							return true;
						}
						else if (value[i] == b.value[i])
						{
							continue;
						}
						else
						{
							return false;
						}
					}
					return false;
				}
				else return true;
			}
		}
	}
	else
	{
		if (flag == 1 && b.flag == 0)
			return false;
		else
			return true;
	}
}
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