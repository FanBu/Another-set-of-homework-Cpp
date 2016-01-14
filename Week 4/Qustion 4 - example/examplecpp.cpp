/*
question:       A:大整数的加减乘除;
总时间限制: 1000ms 内存限制: 65536kB;
描述;
给出两个正整数以及四则运算操作符（+ - * /），求运算结果;

输入;
第一行：正整数a，长度不超过100;
第二行：四则运算符o，o是“+”，“-”，“*”，“/”中的某一个;
第三行：正整数b，长度不超过100;

保证输入不含多余的空格或其它字符;
输出;
一行：表达式“a o b”的值。;

补充说明：;
1. 减法结果有可能为负数;
2. 除法结果向下取整;
3. 输出符合日常书写习惯，不能有多余的0、空格或其它字符;6
样例输入;
9876543210
+
9876543210
样例输出;
19753086420
description：    不对除数为0的情况进行判断，不对所给两个数是否为负数进行判断;
author:         No.20;
time:           2014年3月24日17:33:18;
**/

#include <iostream>     
#include <fstream>  
#include <string>  
#include <cstring>  
using namespace std;

const static int MAXSIZE = 202;

class BigInteger
{
public:
	// 构造函数;  
	BigInteger(const char* str);

public:
	// 运算符重载;  
	BigInteger operator+ (const BigInteger& bi);
	BigInteger operator- (const BigInteger& bi);
	BigInteger operator* (const BigInteger& bi);
	BigInteger operator/ (const BigInteger& bi);
	BigInteger& operator= (const BigInteger& bi);
	bool operator< (const BigInteger& bi);
	bool operator> (const BigInteger& bi);
	bool operator== (const BigInteger& bi);
	bool operator!= (const BigInteger& bi);
	friend ostream& operator<< (ostream& o, const BigInteger& bi);
	friend istream& operator>> (istream& i, BigInteger& bi);

private:
	// 成员变量;  
	char str[MAXSIZE];              // 字符型数据;  
	int iVal[MAXSIZE];              // 整型数据;  
	bool bNeg;                      // 标记负数;  
	int size;                       // 标记位数;  

private:
	// 辅助函数;  
	void intToCahr(BigInteger* bi); // 将整型数值转换为字符串;  
};

BigInteger::BigInteger(const char* str = "")
{
	// 初始化成员变量;  
	memset(this->str, 0, MAXSIZE*sizeof(char));
	memset(this->iVal, 0, MAXSIZE*sizeof(int));
	bNeg = false;
	this->size = strlen(str);
	if (str != "")   // str如果是空的就不用赋值了;  
	{
		// 存储字符数组;  
		memcpy(this->str, str, this->size);
		// 逆转字符数组，存储到整型数组中;  
		for (int i = 0; i<size; i++)
		{
			this->iVal[i] = static_cast<int>(this->str[size - i - 1] - '0');
		}
	}

}

BigInteger BigInteger::operator+ (const BigInteger &bi)
{
	BigInteger biTemp;
	// 如果两个数都为0则直接返回0;  
	if (!strcmp(this->str, "0") && !strcmp(bi.str, "0"))
	{
		return "0";
	}

	// 正整数的和为正数,默认;  
	// 取出两个数的最大长度,可能出现进位，所以取最大值加1;  
	biTemp.size = (this->size > bi.size ? this->size : bi.size) + 1;

	// 执行相加操作;  
	for (int i = 0; i<biTemp.size; i++)
	{
		biTemp.iVal[i] += iVal[i] + bi.iVal[i];
		// 对进位进行操作;  
		if (i + 1 != MAXSIZE)
		{
			// 保证进位不越界;  
			biTemp.iVal[i + 1] += biTemp.iVal[i] / 10;
		}
		// 保留小于10的部分;  
		biTemp.iVal[i] = biTemp.iVal[i] % 10;
	}
	// 转换;  
	intToCahr(&biTemp);

	return biTemp;
}

BigInteger BigInteger::operator- (const BigInteger& bi)
{
	BigInteger biTemp;
	// 设置标志位，对两个数的大小进行判断;  
	int flag = 0;
	// 通过长度判断;  
	if (this->size > bi.size)
	{
		flag = 1;
	}
	else if (this->size < bi.size)
	{
		flag = -1;
	}
	else
	{
		// 通过大小判断;  
		flag = strcmp(this->str, bi.str);
	}

	// 值相等时直接返回0;  
	if (0 == flag)
	{
		return "0";
	}
	// 被减数比减数大;  
	else if (flag > 0)
	{
		// 差的长度至少和被减数相同;  
		biTemp.size = this->size;
		// 相减;  
		for (int i = 0; i<biTemp.size; i++)
		{
			biTemp.iVal[i] += this->iVal[i] - bi.iVal[i];
			// 如果结果小于0，即转为正数,并向后一位借一;  
			if (biTemp.iVal[i] < 0)
			{
				if (i + 1 != MAXSIZE)
				{
					biTemp.iVal[i + 1] -= 1;
				}

				biTemp.iVal[i] += 10;
			}
		}
	}
	// 被减数小于减数;  
	else
	{
		// 取负号;  
		biTemp.bNeg = true;
		biTemp.size = bi.size;
		// 相减;  
		for (int i = 0; i<bi.size; i++)
		{
			biTemp.iVal[i] += bi.iVal[i] - this->iVal[i];
			// 如果结果小于0，即转为正数,并向后一位借一;  
			if (biTemp.iVal[i] < 0)
			{
				biTemp.iVal[i + 1] -= 1;
				biTemp.iVal[i] += 10;
			}
		}
	}
	// 如果差为0，则直接返回;  
	// 因为biTemp还未确认长度，所以使用strcmp进行比较  
	if (!strcmp(biTemp.str, "0"))
	{
		return "0";
	}
	// 转换;  
	intToCahr(&biTemp);

	return biTemp;
}

BigInteger BigInteger::operator* (const BigInteger& bi)
{
	BigInteger biTemp;
	// 如果其中一个数为0，直接返回0值;  
	if (!strcmp(this->str, "0") || !strcmp(bi.str, "0"))
	{
		return "0";
	}
	// 积的长度可能为两个因数的长度加1;  
	biTemp.size = this->size + bi.size + 1;
	// 用第一个数的每一位去乘上第二个数的每一位;  
	for (int i = 0; i<this->size; i++)
	{
		for (int j = 0; j<bi.size; j++)
		{
			biTemp.iVal[i + j] += this->iVal[i] * bi.iVal[j];
			if (i + j + 1 != MAXSIZE)
			{
				biTemp.iVal[i + j + 1] += biTemp.iVal[i + j] / 10;
			}
			biTemp.iVal[i + j] = biTemp.iVal[i + j] % 10;
		}
	}
	intToCahr(&biTemp);

	return biTemp;
}

BigInteger BigInteger::operator/ (const BigInteger& bi)
{
	BigInteger biTemp;
	// 如果被除数为0，直接返回;  
	if (!strcmp(this->str, "0"))
	{
		return "0";
	}
	// 如果除数为1，返回被除数  
	if (!strcmp(bi.str, "1"))
	{
		return *this;
	}

	// 取得商的长度;  
	biTemp.size = this->size;

	// 判断被除数和除数的大小;  
	int flag = 0;
	if (this->size > bi.size)
	{
		flag = 1;
	}
	else if (this->size < bi.size)
	{
		flag = -1;
	}
	else
	{
		flag = strcmp(this->str, bi.str);
	}

	// 如果被除数小于除数，结果为0;  
	if (flag < 0)
	{
		return "0";
	}
	// 被除数等于除数;  
	else if (flag == 0)
	{
		return "1";
	}
	// 被除数大于除数,用被除数减去除数;  
	else
	{
		BigInteger shang;
		BigInteger div = *this;
		BigInteger dr = bi;
		BigInteger tmp;
		while (div.size >= dr.size)
		{
			tmp = "1";
			if (div.str[0] >= dr.str[0] && strcmp(div.str, dr.str) > 0)
			{
				int k = div.size - dr.size;
				for (int i = 0; i<k; i++)
				{
					tmp = tmp * "10";
				}
				div = div - dr*tmp;
				shang = shang + tmp;
			}
			else if (div.str[0] >= dr.str[0] && div.size - dr.size >= 1)
			{
				int k = div.size - dr.size - 1;
				for (int i = 0; i<k; i++)
				{
					tmp = tmp * "10";
				}
				div = div - dr*tmp;
				shang = shang + tmp;
			}
			else if ((div.str[0] < dr.str[0] && div.size == dr.size) || (div.size == dr.size && strcmp(div.str, dr.str) < 0))
			{
				return shang;
			}
			else if (div.str[0] < dr.str[0] && div.size - dr.size >= 1)
			{
				int k = div.size - dr.size - 1;
				for (int i = 0; i<k; i++)
				{
					tmp = tmp * "10";
				}
				div = div - dr*tmp;
				shang = shang + tmp;
			}
			else
			{
				/*div = div - dr;
				shang = shang + "1";*/
			}
		}
		return shang;
	}

	// 商为0时直接返回  
	if (!strcmp(biTemp.str, "0"))
	{
		return "0";
	}
	// 转换;  
	intToCahr(&biTemp);

	return biTemp;
}

BigInteger& BigInteger::operator= (const BigInteger& bi)
{
	// 判断是否是本身;  
	if (this == &bi)
	{
		return *this;
	}
	// 赋值;  
	memset(this->str, 0, MAXSIZE*sizeof(char));
	memset(this->iVal, 0, MAXSIZE*sizeof(int));
	this->size = bi.size;
	this->bNeg = bi.bNeg;
	memcpy(this->str, bi.str, bi.size);
	for (int i = 0; i<this->size; i++)
	{
		this->iVal[i] = bi.iVal[i];
	}

	return *this;
}

bool BigInteger::operator== (const BigInteger& bi)
{
	// 判断对比的是否是对象本身;  
	if (this == &bi)
	{
		return true;
	}
	// 判断字符串是否相等;  
	if (this->size < bi.size || this->size > bi.size)
	{
		return false;
	}
	else
	{
		// 长度一样时，字符串大的值大;  
		return strcmp(this->str, bi.str) == 0;
	}
}

bool BigInteger::operator!= (const BigInteger& bi)
{
	// == 的否定;  
	return !(*this == bi);
}

ostream& operator<< (ostream& o, const BigInteger& bi)
{
	// 如果是负数就输出负号;  
	if (bi.bNeg)
	{
		o << "-";
	}
	// 输出字符串值;  
	for (int i = 0; i<bi.size; i++)
	{
		// 因为数组用0初始化，所以不能单纯使用bi.str进行输出;  
		o << bi.str[i];
	}


	return o;
}

istream& operator>> (istream& i, BigInteger& bi)
{
	// 通过输入的字符串，赋值bi;  
	string str;
	i >> str;
	bi = str.c_str();

	return i;
}

void BigInteger::intToCahr(BigInteger* biTemp)
{
	// 如果整型数组的最高位不是0，则得到真正的整数长度;  
	while (biTemp->size > 0 && biTemp->iVal[biTemp->size - 1] == 0)
	{
		biTemp->size -= 1;
	}

	// 将整型数据存储为字符型;  
	for (int i = 0; i<biTemp->size; i++)
	{
		biTemp->str[i] = static_cast<char>(biTemp->iVal[biTemp->size - 1 - i] + '0');
	}
}

bool BigInteger::operator< (const BigInteger& bi)
{
	if (this->size > bi.size)
	{
		return false;
	}
	else if (this->size < bi.size)
	{
		return true;
	}
	else
	{
		return strcmp(this->str, bi.str) < 0;
	}
}

bool BigInteger::operator> (const BigInteger& bi)
{
	if (this->size < bi.size)
	{
		return false;
	}
	else if (this->size > bi.size)
	{
		return true;
	}
	else
	{
		return strcmp(this->str, bi.str) > 0;
	}
}

int main(int argc, char* argv[])
{
	BigInteger b1, b2;
	string str;
	cin >> b1 >> str >> b2;

	if (str == "+")
	{
		cout << b1 + b2 << endl;
	}
	else if (str == "-")
	{
		cout << b1 - b2 << endl;
	}
	else if (str == "*")
	{
		cout << b1*b2 << endl;
	}
	else
	{
		cout << b1 / b2 << endl;
	}

	return 0;
}