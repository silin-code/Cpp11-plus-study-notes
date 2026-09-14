// ============================================================
// LeetCode 303. 区域和检索 - 数组不可变
// 考点：一维前缀和（构造一次，查询 O(1)）
// 复杂度：构造 O(n)，查询 O(1)，空间 O(n)
// 日期：2026-09-11
// ============================================================
//
// 【题意】
// 给定数组 nums，多次查询 sumRange(left, right) = nums[left..right] 之和。
//
// 【核心】
// pre[i] 定义为前 i 个元素之和（nums[0..i-1]），所以 pre[0] = 0 是哨兵。
// 查询 [left, right] 时下标要 +1：
//     pre[right + 1] - pre[left]
//
// 用 pre[0] = 0 当哨兵的好处：left == 0 时自然退化成 pre[right+1]，
// 不需要写任何边界判断。
//
// 【易错】
// pre[i] 的含义一定要盯死（是"前 i 个"还是"含第 i 个"），
// 下标偏移全靠它。这里是「前 i 个」，所以查询用 right + 1。
// ============================================================

class NumArray {
public:
    NumArray(vector<int>& nums) {
        int n = nums.size();
        num.resize(n + 1, 0);
        num[0] = 0;                            // 哨兵：空前缀和为 0
        for (int i = 1; i <= n; i++) {
            num[i] = nums[i - 1] + num[i - 1];  // num[i] = nums[0..i-1] 之和
        }
    }

    int sumRange(int left, int right) {
        return num[right + 1] - num[left];
    }

    vector<int> num;
};
