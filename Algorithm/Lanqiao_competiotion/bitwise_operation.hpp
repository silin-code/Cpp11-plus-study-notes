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

// 把一个数字翻译成"选中了哪些元素"
// mask : 那个数字（比如 5）
// n    : 一共有几个元素，编号 0 ~ n-1（比如 3）
void printSet(int mask, int n)
{
	cout << "{ ";
	for (int i = 0; i < n; i++)      // 逐位检查：第 0 位 → 第 1 位 → ... → 第 n-1 位
	{
		if (getBit(mask, i))          // getBit 返回非 0 → 那一位是 1 → 元素 i 被选中
		{
			cout << i << " ";
		}
	}
	cout << "}" << endl;
}

// mask   : 已经拿走的数。bit i 对应【数字 i】（i 从 1 到 m）
// m      : 最大的可选数字（数字范围 1..m）
// target : 目标总和
// 返回   : 当前要动手的人，有没有一个"还没拿的数"，拿走之后 sum 就 >= target
bool canWinInOneMove(int mask, int m, int target)
{
	int sum = 0;
	for (int i = 1; i <= m; i++)
	{
		if (mask & (1 << i)) sum += i;
	}
	for (int i = 1; i <= m; i++)
	{
		if (!(mask & (1 << i))&&sum+i>=target)//没被选
		{
			return true;
		}
	}
	return false;
}