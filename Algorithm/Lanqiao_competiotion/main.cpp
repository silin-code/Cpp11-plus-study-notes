#include<iostream>
#include"MyAlgorithm.hpp"
#include "bitwise_operation.hpp"
using namespace std;

int main()
{
	printBinary(-1);
	int mask = 0;
	setBit(mask, 1);  printBinary(mask, 8);   // 0000 0010
	setBit(mask, 3);  printBinary(mask, 8);   // 0000 1010
	setBit(mask, 5);  printBinary(mask, 8);   // 0010 1010
	cout << getBit(mask, 3) << endl;          // 1
	cout << getBit(mask, 2) << endl;          // 0

}