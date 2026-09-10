#include<iostream>
#include"MyAlgorithm.hpp"
using namespace std;

int main()
{
	vector<int> nums = {0,1,2,3,4,5,6,7,8,9,10};
	int n = 10;
	vector<int> dif(10 + 2, 0);
	dif[0] = nums[0];
	for (int i = 1; i <= n; i++)
	{
		dif[i] = nums[i] - nums[i - 1];
	}

	cout << "输入测试组数" << endl;
	int q = 0;
	cin >> q;
	while(q--)
	{
		cout << "输入区间l和r" << endl;
		int l, r;
		cin >> l >> r;
		cout << "输入加上的值" << endl;
		int x;
		cin >> x;
		AddDiff(dif, l, r, x);

		vector<int> cur = restore(dif, n);//想看中间结果就临时还原一份
		for (int i = 1; i <= n; i++)
		{
			cout << cur[i] << " ";
		}
		cout << endl;
	}


}