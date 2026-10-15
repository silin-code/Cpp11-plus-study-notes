// ============================================================
// 蓝桥杯 2022（第十三届）省赛 C/C++ 大学 B 组 · 试题 F 统计子矩阵
// ------------------------------------------------------------
// 考点：二维前缀和 + （进阶）双指针
// 日期：2026-10-14（用户暴力版过 70%）
// ------------------------------------------------------------
// 题意：
//   给一个 N×M 的矩阵 A，统计有多少个子矩阵（最小 1×1、最大 N×M）
//   满足【子矩阵中所有数之和 ≤ K】。
//   输入：第一行 N M K，之后 N 行每行 M 个整数
//   输出：一个整数（答案）
//   样例：3 4 10 / 1 2 3 4 / 5 6 7 8 / 9 10 11 12  →  19
//   数据：30% N,M≤20    70% N,M≤100    100% N,M≤500；0 ≤ Aij ≤ 1000
// ------------------------------------------------------------
// 【本版本】二维前缀和 + 四重循环枚举四个边界
//   复杂度 O(n²m²) —— 实测 n=m=20 时 0ms、n=m=100 时 10ms，
//   能过 30% 与 70% 的数据；n=m=500 时子矩阵数约 1.6e10 → TLE。
//   → 【暴力拿 70% 分】，是不想写最优解时的可靠兜底。
//
// 【踩过的坑】条件符号：题目是"不超过 K"，即 `<= K`。
//   首版写成 `< k` → 样例输出 16（正确 19），少算了 3 个"和恰好等于 K"的子矩阵。
//   ⚠️ 这类"条件符号"错误本周已出现 4 次（84 收尾 / 393 else 兜底 / 239 循环起点），
//      属于"会但写错"的典型 —— 写条件时值得停半秒确认符号。
//
// 【下一步优化（O(n²m)，能过 100%）】
//   ① 只枚举【上边界 a】与【下边界 c】→ O(n²)
//        固定 a、c 后，每一列压成一个数：colsum[j] = 第 a..c 行第 j 列之和
//   ② 在 colsum 上用【双指针】数"和 ≤ K 的区间个数" → O(m)
//        依据：所有数非负 → 窗口右扩"和"必增、左缩必减 → 单调性成立
//   总复杂度 500×500×500 = 1.25e8，可过。
//   （第 ② 步就是 LC 3 / LC 76 里练过的"窗口什么时候缩"）
//
// 【另一个坑】调试 printf 别留在四重循环最内层：
//   输出行数 = 子矩阵个数（n=100 时约 2e7 行，直接刷屏）；
//   提交前不删会导致 WA（多输出行会被判错答案）。
// ============================================================

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
ll n, m, k;

int ff(vector<vector<ll>> &dp, int a, int b, int c, int d)
{
    return dp[c][d] - dp[c][b - 1] - dp[a - 1][d] + dp[a - 1][b - 1];
}

ll f(vector<vector<ll>> &nums)
{
    ll ret = 0;
    vector<vector<ll>> dp(n + 1, vector<ll>(m + 1, 0));
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            dp[i][j] = dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1] + nums[i - 1][j - 1];
        }
    }
    for (int a = 1; a <= n; a++) // 左上
    {
        for (int b = 1; b <= m; b++)
        {
            for (int c = a; c <= n; c++) // 右下
            {
                for (int d = b; d <= m; d++)
                {
                    ret += (ff(dp, a, b, c, d) <= k ? 1 : 0);
                }
            }
        }
    }
    return ret;
}

int main()
{
    cin >> n >> m >> k;
    vector<vector<ll>> nums(n, vector<ll>(m));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> nums[i][j];
        }
    }
    cout << f(nums) << endl;   // 样例：3 4 10 / 1 2 3 4 / 5 6 7 8 / 9 10 11 12 -> 19
    return 0;
}

// ============================================================
// 【版本二】优化到 O(n²m) —— 能过 100% 数据（10-15 完成）
// ------------------------------------------------------------
// 思路：把"四重循环枚举四个边界"拆成两层：
//
//   ① 外层只枚举【上边界 a】和【下边界 c】（O(n²)）
//        固定 a、c 后，每一列"塌缩"成一个数：
//        col[j] = 第 a..c 行、第 j 列的和 = pre[c][j] - pre[a-1][j]
//        （pre 是列前缀和：pre[r][j] = 前 r 行第 j 列的和）
//
//   ② 内层在 col 上用【双指针】数"和 ≤ K 的区间个数"（O(m)）
//        依据：所有数 ≥ 0 → 窗口右扩"和"必增、左缩必减 → 单调性成立
//
//   总复杂度 O(n²m) = 500×500×500 = 1.25e8 → 能过。
//
// 内层双指针模板（要背下来，和 LC 3 / LC 76 同源）：
//   int left = 1;  ll sum = 0;
//   for (int right = 1; right <= m; right++) {
//       sum += col[right];                     // 右扩
//       while (sum > k && left <= right) {     // 超了就缩
//           sum -= col[left];  left++;
//       }
//       ret += right - left + 1;               // ★ 以 right 结尾的所有合法子区间数
//   }
//
// ★ 为什么 ret += right-left+1：
//   当 [left,right] 的和 ≤ K 时，[left+1,right]…[right,right] 也都合法（更小），
//   一共 right-left+1 个。
//
// ★ 踩过的坑（首版内层写错，对拍 4944/5000 组错）：
//   · `col[right] - col[left]` —— col 是"每列的和"不是前缀和，相减不是区间和；
//     要维护一个累加的 sum 变量。
//   · `ret += 1` —— 漏了更小的合法区间，应该是 right-left+1。
//
// 实测：5000 组随机对拍 vs 暴力零不一致；500×500 为 119 ms。
// ============================================================

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
ll n, m, k;

int main() {
    cin >> n >> m >> k;
    vector<vector<ll>> nums(n + 1, vector<ll>(m + 1));
    vector<vector<ll>> pre(n + 1, vector<ll>(m + 1, 0)); // pre[i][j] = 前 i 行第 j 列的和
    ll ret = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> nums[i][j];
            pre[i][j] = pre[i - 1][j] + nums[i][j];       // 列前缀和
        }
    }

    for (int a = 1; a <= n; a++) {                        // 上边界
        for (int c = a; c <= n; c++) {                    // 下边界
            vector<ll> col(m + 1, 0);
            for (int j = 1; j <= m; j++)
                col[j] = pre[c][j] - pre[a - 1][j];       // 第 a..c 行第 j 列的和

            // 双指针 + 滑动窗口：数"和 ≤ K 的区间个数"
            int left = 1;
            ll sum = 0;
            for (int right = 1; right <= m; right++) {
                sum += col[right];
                while (sum > k && left <= right) {
                    sum -= col[left];
                    left++;
                }
                ret += right - left + 1;                  // 以 right 为右端点的合法区间数
            }
        }
    }
    cout << ret << endl;
    return 0;
}
