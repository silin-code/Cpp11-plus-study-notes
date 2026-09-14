// ============================================================
// LeetCode 1283. 使结果不超过阈值的最小除数
// 考点：二分答案（check 回到向上取整）
// 复杂度：时间 O(n log(max(nums)))，空间 O(1)
// 日期：2026-09-13（一次通过）
// ============================================================
//
// 【题意】
// 选一个正整数 d 作为除数，把每个 nums[i] 除以 d 后**向上取整**再求和，
// 要求总和 <= threshold。求最小的 d。
//
// 【结构】
// 与 LC 875 完全同构：二分对象是「除数」，check 是「向上取整求和」。
//
// 【上下界】
//   lo = 1：除数必须是正整数
//   hi = max(nums)：d >= max(nums) 时每个 ceil(nums[i]/d) 都是 1，
//                   总和 = n；再往上加 d 结果不会变小，没有意义
//
// 【易错】
// 判定可写成「不可行在前」：
//   if (sum > threshold) lo = mid + 1;   // 不满足 → 往大逼
//   else                 hi = mid;       // 满足   → 往小逼
// 与「可行在前」等价，按自己习惯写即可，但方向不能反。
// ============================================================

class Solution {
public:
    int smallestDivisor(vector<int>& nums, int threshold) {
        int lo = 1, hi = 0;
        for (auto e : nums) hi = max(hi, e);

        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;

            // check：以 mid 为除数，向上取整求和
            long long sum = 0;
            for (auto e : nums) sum += (e + mid - 1) / mid;

            if (sum > threshold) lo = mid + 1;   // 和太大 → 除数要更大
            else                 hi = mid;       // 达标   → 试试更小的除数
        }
        return lo;
    }
};
