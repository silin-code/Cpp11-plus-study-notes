// ============================================================
// LeetCode 1482. 制作 m 束花所需的最少天数
// 考点：二分答案（check = 连续段计数）+ 离散化二分
// 复杂度：时间 O(n log n)，空间 O(n)
// 日期：2026-09-13
// ============================================================
//
// 【题意】
// bloomDay[i] 是第 i 朵花开放的日子。要摘 m 束花，每束需要 k 朵
// **连续相邻**的花。求最少要等到第几天；花不够则返回 -1。
//
// 【check 的核心：数连续段】
// 扫描一遍，维护「当前连续开了几朵」keepnum：
//   花开了 → keepnum++，凑够 k 就 flowersnum++ 并清零
//   没开   → keepnum = 0（连续性断了，前面的作废）
//
// 不要用双重循环枚举起点：会越界（起点靠后时 i+k 超出 n），
// 而且连续 k 朵时会重复计数。单层扫描每朵花只被看一次。
//
// 【无解判断】
// 需要 m * k 朵花，不是 m 朵：
//   if ((long long)m * k > n) return -1;
// m 最大 10^6、k 最大 10^5，乘积 10^11 会超 int，必须强转 long long。
//
// 【离散化二分（可选优化）】
// 候选答案就是"某些花开放的日子"，去重排序后在下标上二分，
// 轮数从 log(10^9) ≈ 30 降到 log(10^5) ≈ 17。
// 用这种写法时注意：lo/hi 是**下标**，arr[mid] 才是**天数**，两者不能混
// （写成 lo = mid 这种把值当下标赋回去，会死循环）。
// ============================================================

class Solution {
public:
    int minDays(vector<int>& bloomDay, int m, int k) {
        int n = bloomDay.size();
        if ((long long)m * k > n) return -1;   // 花的总数不够，无解

        set<int> s(bloomDay.begin(), bloomDay.end());   // 去重
        vector<int> arr(s.begin(), s.end());            // 有序的唯一天数
        int lo = 0, hi = arr.size() - 1;                // 在下标上二分

        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            int num = arr[mid];                         // 实际候选天数

            // check：第 num 天能摘几束
            int flowersnum = 0;                         // 已经能摘的束数
            int keepnum = 0;                            // 当前连续开了几朵
            for (int i = 0; i < n; i++) {
                if (bloomDay[i] <= num) {
                    keepnum++;
                    if (keepnum == k) {                 // 连续凑够 k 朵
                        flowersnum++;
                        keepnum = 0;                    // 用掉了，重新数
                    }
                } else {
                    keepnum = 0;                        // 断了，前面的作废
                }
            }

            if (flowersnum < m) lo = mid + 1;           // 凑不够 → 往大逼
            else                hi = mid;               // 够了   → 往小逼
        }
        return arr[lo];                                 // 下标换回天数
    }
};
