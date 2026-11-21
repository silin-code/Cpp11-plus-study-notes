#include <vector>
#include <cstdio>
using namespace std;

// ============================================================
// 默写练习：不看 number_theory.hpp，把埃氏筛写出来
// ------------------------------------------------------------
// 要求：
//   - 函数名 sieve，参数 int n，返回 vector<bool>，长度 n+1
//   - 第 i 位表示 i 是不是质数
//   - 不用写任何试除（不要出现 x % d）
// 验证：编译运行，看下面两行输出是否对
//   sieve(30): 2 3 5 7 11 13 17 19 23 29
//   sieve(100) 个数: 25
// ============================================================

vector<bool> sieve(int n) {
    vector<bool> isPrime(n + 1, true);   // n+1 个格子，全部先当成质数

    isPrime[0]=isPrime[1]=false;
    for(int i=2;i*i<=n;i++)
    {
        if(isPrime[i])
        {
            for(int k=i*i;k<=n;k+=i)
            {
                isPrime[k]=false;
            }
        }
    }

    return isPrime;
}


int main() {
    setbuf(stdout, NULL);

    vector<bool> a = sieve(30);
    printf("sieve(30):  ");
    for (int i = 2; i <= 30; i++) if (a[i]) printf("%d ", i);
    printf("\n");

    vector<bool> b = sieve(100);
    int cnt = 0;
    for (int i = 2; i <= 100; i++) if (b[i]) cnt++;
    printf("sieve(100) 个数: %d\n", cnt);

    return 0;
}
