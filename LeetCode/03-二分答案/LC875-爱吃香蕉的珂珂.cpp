// ============================================================
// LeetCode 875. 爱吃香蕉的珂珂
// 考点：二分答案（check = 向上取整求和）
// 复杂度：时间 O(n log(max(piles)))，空间 O(1)
// 日期：2026-09-13
// ============================================================
//
// 【题意】
// piles[i] 是第 i 堆香蕉的数量，h 是限时（小时）。
// 每小时选定一个速度 k（根/小时）且固定不变，同一小时内只能吃一堆，
// 这堆吃完后剩下的时间浪费掉。求最小的 k 使总耗时 <= h。
//
// 【为什么是二分答案】
// "求最小的 k"直接求很难，但"给定 k 算要几小时"非常好算 —— 这就是 check。
// 而且 k 越大耗时越少（单调），满足单调性即可二分。
//
// 【check 要点】
// 每堆需要 ceil(piles[i] / k) 小时。
// C++ 整数除法向下取整，所以用 (a + b - 1) / b 实现向上取整。
//
// 【易错】
// 1. lo 从 1 开始（速度不能为 0，否则 check 里除零）。
// 2. check(mid) 为真时写 hi = mid，不能 return —— 可行不等于最小。
// 3. hours 用 long long：10^9 级数据累加会超 int。
// ============================================================

class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int lo = 1, hi = 0;
        for (auto e : piles) hi = max(hi, e);  // 上界：最大的一堆（再快无意义）

        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;

            // check：以 mid 的速度吃，一共需要几小时
            long long hours = 0;
            for (int e : piles) {
                hours += (e + mid - 1) / mid;  // ceil(e / mid)
            }

            if (hours <= h) hi = mid;          // 可行 → 往小逼
            else            lo = mid + 1;      // 不可行 → 往大逼
        }
        return lo;                             // lo == hi，即最小可行速度
    }
};
