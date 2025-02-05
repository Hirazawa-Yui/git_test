#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <tuple>
#include <unordered_map>
#include <algorithm>

using namespace std;

const int rows = 8;
const int cols = 8;

// 迷宫地图
int maze[rows][cols] = {
    {0, 0, 0, 1, 1, 1, 1, 1},
    {1, 1, 0, 0, 0, 2, 0, 1},
    {1, 0, 0, 1, 1, 1, 0, 1},
    {1, 1, 0, 1, 5, 0, 0, 1},
    {3, 0, 0, 1, 1, 0, 1, 1},
    {1, 1, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 4, 1, 1, 0, 0},
    {1, 1, 1, 1, 1, 1, 1, 0}};

// 目标点顺序
vector<pair<int, int>> targets = {{4, 0}, {3, 4}, {6, 3}, {1, 5}, {7, 7}};

// 自定义哈希函数，用于unordered_map存储pair<int, int>
struct pair_hash
{
    template <typename T1, typename T2>
    std::size_t operator()(const std::pair<T1, T2> &p) const
    {
        auto h1 = std::hash<T1>{}(p.first);  // 对第一个元素计算哈希值
        auto h2 = std::hash<T2>{}(p.second); // 对第二个元素计算哈希值
        return h1 ^ (h2 << 1);               // 合并两个哈希值
    }
};

// 移动方向及编码：右(0), 左(1), 下(2), 上(3)
int dr[4] = {0, 0, 1, -1};
int dc[4] = {1, -1, 0, 0};

// BFS 搜索路径
string bfs(pair<int, int> start, pair<int, int> target)
{
    queue<pair<int, int>> q;
    unordered_map<pair<int, int>, pair<int, int>, pair_hash> prev;
    unordered_map<pair<int, int>, int, pair_hash> move_dir;

    q.push(start);
    prev[start] = {-1, -1};

    while (!q.empty())
    {
        auto [r, c] = q.front();
        q.pop();

        if (make_pair(r, c) == target)
            break; // 到达目标点

        for (int i = 0; i < 4; ++i)
        {
            int nr = r + dr[i], nc = c + dc[i];
            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && maze[nr][nc] != 1)
            {
                pair<int, int> next = {nr, nc};
                if (prev.find(next) == prev.end())
                {
                    prev[next] = {r, c};
                    move_dir[next] = i;
                    q.push(next);
                }
            }
        }
    }

    // 回溯路径
    string path;
    pair<int, int> curr = target;
    while (curr != start)
    {
        int dir = move_dir[curr];
        path += to_string(dir);
        curr = prev[curr];
    }
    reverse(path.begin(), path.end());
    return path;
}

int main()
{
    pair<int, int> current = {0, 0};
    string result_path;

    for (auto target : targets) {
        // 访问目标并寻找路径
        string path_to_target = bfs(current, target);
        result_path += path_to_target;
        current = target;

        // 移动到新的位置
        int new_row = (8 * current.first + current.second) / 8;
        int new_col = (8 * current.first + current.second) % 8;
        current = {new_row, new_col};
    }

    // 最后到达终点
    string path_to_end = bfs(current, {7, 7});
    result_path += path_to_end;

    cout << result_path << endl;
    return 0;
}
