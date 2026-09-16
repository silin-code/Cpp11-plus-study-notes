// ============================================================
// LeetCode 79. 单词搜索
// 考点：回溯 · 网格型（B 型 DFS：承接返回值 + 原地标记）
// 复杂度：时间 O(m·n·4^L)，空间 O(L)，L = word 长度
// 日期：2026-09-16
// ============================================================
//
// 【题意】
// 在 m×n 字符网格里找 word：相邻格子（上下左右）按顺序连成 word。
// 同一个格子不能重复使用。返回是否 存在。
//
// 【A 型还是 B 型】
//   题目问"是否存在" → B 型：bool 返回，找到一个立刻收工。
//   返回值代表："从当前格子出发，剩下的字符能不能匹配上。"
//
// 【B 型四条铁律（就是这题卡住的地方）】
//   1. 返回值必须用变量接住：bool 通 = dfs(...)。单独写 dfs(...) 等于扔掉结果。
//   2. 撤销要排在 return true 之前（本轮用先撤销再上抛）。
//   3. 兜底 return false 不能漏：所有方向都不通，说明这条路死。
//   4. 别用 bool flag 参数把结果带回去 —— 参数按值传递，改的是副本。
//      （想传回去得用 bool&，但这里根本不需要，直接接返回值就行。）
//
// 【出口写在哪】
//   匹配到 position == word.size() 才算真的成功 —— 说明
//   word 的最后一个字符已经在上一层校验过了。
//   所以进入函数时 position 已经"匹配到第几个"。注意语义定在哪一边。
//
// 【越界检查的顺序】
//   if (x>=0 && x<m && y>=0 && y<n && board[x][y]==word[position] && !visit[x][y])
//   四个边界判断必须写在 board[x][y] 之前，靠 && 短路挡住越界访问。
//
// 【为什么这题不能记忆化】
//   memo[i][j] 的答案还取决于"哪些格子已经走过"（visit 集合），
//   同一格绕一圈来和直接来，可用格子不同 → 结论不通用。
//   把 visit 进状态就是指数级 → 等于没记忆化。
//   记忆化的标准题是 LC 329（最长递增路径），状态就是 (i,j)，答案唯一。
//
// 【易错】
// 1. 递归返回值不接（把结果丢了）。
// 2. 用 bool flag 参数回传（按值传递，白写）。
// 3. 出口条件放在循环里而不是函数开头。
// 4. 起点要遍历整个网格，每个起点都要重新走一遍。
// ============================================================

class Solution {
public:
    int m, n;
    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    // 从 (i, j) 出发，board[i][j] 已经匹配 word[position-1]，继续匹配 position 起的字符
    bool dfs(vector<vector<char>>& board, vector<vector<bool>>& visit,
             int i, int j, int position, string& word) {
        if (position == (int)word.size()) return true;      // 单词匹配完，成功

        for (int a = 0; a < 4; a++) {
            int x = i + dx[a], y = j + dy[a];
            // 越界检查必须在访问 board[x][y] 之前
            if (x >= 0 && x < m && y >= 0 && y < n
                && board[x][y] == word[position] && !visit[x][y]) {

                visit[x][y] = true;                         // 做选择
                bool 通 = dfs(board, visit, x, y, position + 1, word);   // ① 接住返回值
                visit[x][y] = false;                        // ② 先撤销，恢复现场
                if (通) return true;                        // ③ 再往上抛
            }
        }
        return false;                                       // ④ 兜底
    }

    bool exist(vector<vector<char>>& board, string word) {
        if (board.empty() || word.empty()) return false;
        m = board.size();
        n = board[0].size();

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == word[0]) {
                    vector<vector<bool>> visit(m, vector<bool>(n, false));
                    visit[i][j] = true;                     // 起点占位
                    if (dfs(board, visit, i, j, 1, word)) return true;
                }
            }
        }
        return false;
    }
};
