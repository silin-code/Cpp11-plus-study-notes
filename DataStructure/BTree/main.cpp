#include<iostream>
#include<windows.h>
using namespace std;
#include"BTree.hpp"


void Test()
{
	int a[] = { 53, 139, 75, 49, 145, 36, 101 };
	BTree<int, 3> t;
	for (auto e : a)
	{
		t.Insert(e);
	}
	cout << "插入后中序遍历: ";
	t.InOrder();
	cout << endl;

	cout << "删除 53 后: ";
	t.Remove(53);
	t.InOrder();
	cout << endl;

	cout << "删除 75 后: ";
	t.Remove(75);
	t.InOrder();
	cout << endl;

	cout << "删除 36 后: ";
	t.Remove(36);
	t.InOrder();
	cout << endl;

	cout << "删除 49 后: ";
	t.Remove(49);
	t.InOrder();
	cout << endl;

	cout << "删除 101 后: ";
	t.Remove(101);
	t.InOrder();
	cout << endl;

	cout << "删除 139 后: ";
	t.Remove(139);
	t.InOrder();
	cout << endl;

	cout << "删除 145 后: ";
	t.Remove(145);
	t.InOrder();
	cout << endl;

	cout << "删除 999(不存在): ";
	cout << (t.Remove(999) ? "成功" : "失败") << endl;
}

int main()
{
	//SetConsoleOutputCP(CP_UTF8);
	Test();
} 