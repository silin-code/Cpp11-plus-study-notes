// ============================================================
// LeetCode 1011. 在 D 天内送达包裹的能力
// 考点：二分答案（check = 贪心分段）
// 复杂度：时间 O(n log(sum(weights)))，空间 O(1)
// 日期：2026-09-13
// ============================================================
//
// 【题意】
// weights[i] 是第 i 个包裹的重量，days 是天数限制。
// 船每天只能装一次，按顺序装货、不能拆分包裹。求最小的载重 capacity。
//
// 【和 LC 875 的区别】
// 香蕉可以"一堆吃几小时"（可拆），但包裹必须整件装船（不可拆），
// 所以 check 不能用向上取整，要改成"贪心装货"。
//
// 【check 思路】
// 尽量往当天塞，装不下就开新的一天。
//   装不下 → cnt++，当天载重清零
//   无论如何都把当前元素累加进去
//
// 【上下界】
//   lo = max(weights)：容量小于最大包裹时，那个包裹永远装不上
//   hi = sum(weights)：一天全部运完
//
// 【易错】
// 1. cnt 从 1 开始（数组非空，至少一天）。
// 2. `sum = 0` 之后再无条件 `sum += e`；写成 if...else 时不要两处都加 e。
// 3. 千万不要用 std::reduce（C++17），蓝桥杯 Dev-C++ 只支持 C++11；
//    求和用 accumulate(v.begin(), v.end(), 0LL)。
// ============================================================

class Solution {
public:
    int shipWithinDays(vector<int>& weights, int days) {
        int lo = 0, hi = 0;
        for (int w : weights) {
            lo = max(lo, w);                   // 下界：至少要能装下最大的包裹
            hi += w;                           // 上界：一天全部运完
        }

        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;

            // check：以 mid 为容量，需要几天
            int cnt = 1;                       // 至少一天
            long long load = 0;                // 当天已装重量
            for (int w : weights) {
                if (load + w > mid) {          // 装不下 → 开新的一天
                    cnt++;
                    load = 0;
                }
                load += w;                     // 无论是否换天，当前包裹都要装上
            }

            if (cnt <= days) hi = mid;         // 可行 → 往小逼
            else             lo = mid + 1;     // 不可行 → 往大逼
        }
        return lo;
    }
};
