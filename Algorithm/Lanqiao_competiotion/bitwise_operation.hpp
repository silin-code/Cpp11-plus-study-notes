#pragma once
#include <iostream>
using namespace std;

//打印2进制
void printBinary(int x, int bitsize = 32)
{
	for (int i = bitsize-1; i >= 0; i--) {
		cout << ((x >> i) & 1);
		if (i % 4 == 0 && i > 0) cout << ' ';
	}
	cout << endl;
}


//判断mask的第i位是不是1
//从低位到高位
bool getBit(int mask, int i)
{
	return mask & (1 << i);
}

//把mask的第i位设成1
void setBit(int& mask, int i)
{
	mask = mask | (1 << i);
}

void cleanBit(int& mask, int i)
{
	mask = mask & ~(1 << i);
}

// 把 mask 的第 i 位翻转（0→1，1→0）
void flipBit(int& mask, int i)
{
	mask = mask^(1 << i);
}
// 数一数 mask 里有几个 1
int countOnes(unsigned int mask)
{
	int count = 0;
	while (mask)
	{
		if ((1 & mask ) == 1)
		{
			count++;
		}
		mask >>= 1;
	}
	return count;
}
