// ============================================================
// LeetCode 39. 组合总和
// 考点：回溯 · 组合型（start 参数，元素可重复使用）
// 复杂度：时间 O(n^(target/min)) 量级，空间 O(target/min)
// 日期：2026-09-16
// ============================================================
//
// 【题意】
// 给定无重复元素的正整数数组 candidates 和目标 target，
// 每个数字可以 无限次 使用，找出所有和为 target 的组合。
//
// 【形态定型】
//   每层的"选择" = 挑一个下标 >= start 的数
//   循环起点     = start（组合里下标只增不减，天然不重复）
//   约束         = 不需要 visit（"选过谁"由 start 保证）
//
// 【start 怎么传：i 还是 i + 1？】
//   可重复使用  → 传 i      （下一个位置还能再选自己）
//   不可重复用  → 传 i + 1  （下一个位置只能往后选）
//   这一题是"无限次使用" → 传 i。
//
// 【剪枝的严格前提】
//   if (sum + candidates[i] > target) break;
//   这里的 break 依赖"数组升序"：一旦当前数超标，后面的更大，全都不用试了。
//   → 所以 必须先 sort，否则 break 就是错的剪枝（会漏解）。
//
// 【易错】
// 1. 漏 sort 直接导致 break 剪枝失效，答案偏少。
//    实测 candidates=[8,7,4,3], target=11：漏 sort 版本输出 0 个，正确是 3 个。
// 2. path 收集 / 撤销要和递归成对。
// 3. 出口在"进入函数后判断剩余值"，也可以放在循环内判断，
//    但两者选一个，不要重复收集。
// ============================================================

class Solution {
public:
    vector<vector<int>> ret;
    vector<int> path;

    void dfs(vector<int>& candidates, int start, int remain) {
        if (remain == 0) {                      // 出口：刚好凑够
            ret.push_back(path);
            return;
        }
        for (int i = start; i < (int)candidates.size(); i++) {
            if (candidates[i] > remain) break;  // 依赖升序的剪枝

            path.push_back(candidates[i]);      // 做选择
            dfs(candidates, i, remain - candidates[i]);   // 传 i：本数还能再用
            path.pop_back();                    // 撤销选择
        }
    }

    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());       // break 剪枝的前提
        dfs(candidates, 0, target);
        return ret;
    }
};
