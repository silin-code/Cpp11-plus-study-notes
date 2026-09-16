// ============================================================
// LeetCode 51. N 皇后
// 考点：回溯 · 棋盘型（按行递归 + 三个约束数组）
// 复杂度：时间 O(n!)，空间 O(n)
// 日期：2026-09-16
// ============================================================
//
// 【题意】
// 在 n×n 棋盘放 n 个皇后，任意两个不能同行、同列、同斜线，
// 返回所有摆法（用 'Q' / '.' 的字符串数组表示）。
//
// 【形态定型】
//   每层的"选择" = 这一行的皇后放在哪一列
//   递归维度     = 行 r（棋盘型按"行"递归，一行一行往下放）
//   循环         = 列 c 从 0 到 n-1
//   约束         = col[c] / diag1[r-c+n] / diag2[r+c] 三个 bool 数组
//
// 【三个约束数组的下标公式】
//   col[c]          —— 同一列
//   diag1[r - c + n]—— 主对角 ↘（r-c 为常数，可能为负，+n 抬到非负）
//   diag2[r + c]    —— 副对角 ↙（r+c 为常数）
//
// 【数组最大下标必须先算出来】
//   r, c ∈ [0, n-1]
//   r - c + n ∈ [0, 2n-2+n]  ← 实际范围 [1, 2n-1]，开 2n+1 足够
//   r + c     ∈ [0, 2n-2]    ← 最大是 2n-2
//
//   本行代码原来的错：diag2 开了 10。n ≥ 6 时 2n-2 ≥ 10 → 越界。
//   纪律：开数组前先把最大下标算出来写下来。
//
// 【另一个初始化坑】
//   board.resize(n, "") 之后 board[i].resize(n) 填的是 '\0'，不是 '.'。
//   实测 n=4 会输出 '\x00Q\x00\x00'。
//   正确写法：board.resize(n, string(n, '.'))
//
// 【易错】
// 1. 三个约束数组都要"做选择时置 true，撤销时置 false"，漏一个就出错。
// 2. 出口 r == n 时才收集，收集完直接 return，不要再往下递归。
// 3. 行列填的字符别记混：放皇后填 'Q'，撤销填回 '.'。
// ============================================================

class Solution {
public:
    vector<vector<string>> ret;
    int N;
    vector<bool> col, diag1, diag2;

    void dfs(vector<string>& board, int r) {
        if (r == N) {                           // 出口：n 行都放好了
            ret.push_back(board);
            return;
        }
        for (int c = 0; c < N; c++) {
            if (col[c] || diag1[r - c + N] || diag2[r + c]) continue;

            board[r][c] = 'Q';                  // 做选择：三个标记一起置位
            col[c] = true;
            diag1[r - c + N] = true;
            diag2[r + c] = true;

            dfs(board, r + 1);                  // 下一行

            board[r][c] = '.';                  // 撤销选择：三个标记一起还原
            col[c] = false;
            diag1[r - c + N] = false;
            diag2[r + c] = false;
        }
    }

    vector<vector<string>> solveNQueens(int n) {
        N = n;
        col.assign(n, false);
        diag1.assign(2 * n + 1, false);         // r-c+n 最大到 2n-1
        diag2.assign(2 * n + 1, false);         // r+c   最大到 2n-2
        vector<string> board(n, string(n, '.'));    // 关键：全都填 '.'
        dfs(board, 0);
        return ret;
    }
};
