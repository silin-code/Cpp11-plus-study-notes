#pragma once
#include<vector>
using namespace std;

class UF{
private:
    vector<int> p;
public:
    UF(int n)
    {
        p.resize(n,-1);
    }
    int find(int x)
    {
        if(p[x]<0) return x;
        return p[x]=find(p[x]);
    }
    void unite(int x, int y)
    {
        int f1=find(x);
        int f2=find(y);

        // 负数约定必须加这一句：两端已同组时若继续执行，
        // p[f1] += p[f2] 会让大小翻倍，p[f2] = f1 会把根的负数写成【正数】（自我指向）
        // -> find 无限递归 -> 栈溢出 0xC00000FD
        if (f1 == f2) return;

        if(p[f1]>p[f2])
        {
            swap(f1,f2);
        }
        p[f1]+=p[f2];
        p[f2]=f1;
    }

    bool issame(int x, int y)
    {
        return find(x)==find(y);
    }

    int countSet()
    {
        int ret=0;
        for(auto e:p)
        {
            if(e<0) ret++;
        }
        return ret;
    }
};