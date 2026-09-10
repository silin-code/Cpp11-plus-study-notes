#pragma once
#include<vector>
#include<string>
#include<map>
#include<queue>
#include<unordered_map>
#include<stack>
#include<list>
using namespace std;
//一维差分
//给[l,r]区间内的每个数加上x
void AddDiff(vector<int>& diff,int l, int r, int x)
{
	diff[l] += x;
	diff[r+1] -= x;
}

//需要看结果时调用，不破坏d
vector<int> restore(const vector<int>& d, int n)
{
	vector<int> a(n + 1);
	int  cur = 0;
	for (int i = 1; i <= n; i++)
	{
		cur += d[i];
		a[i] += cur;
	}
	return a;
}