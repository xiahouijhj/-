#include <iostream>
#include <vector>
#include <queue>
using namespace std;
const int INF = 1e9;
const int MAXN = 100005;
vector<int> adj[MAXN];
int pair_u[MAXN], pair_v[MAXN], dist_u[MAXN];
int n;
void add_edge(int u, int v) {
    adj[u].push_back(v);
}
// Hopcroft-Karp 算法的 BFS 部分：寻找多条增广路
bool bfs() {
    queue<int> q;
    for (int u = 1; u <= n; ++u) {
        if (pair_u[u] == 0) {
            dist_u[u] = 0;
            q.push(u);
        } else {
            dist_u[u] = INF;
        }
    }
    dist_u[0] = INF;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (dist_u[u] < dist_u[0]) {
            for (int v : adj[u]) {
                if (dist_u[pair_v[v]] == INF) {
                    dist_u[pair_v[v]] = dist_u[u] + 1;
                    q.push(pair_v[v]);
                }
            }
        }
    }
    return dist_u[0] != INF;
}
// Hopcroft-Karp 算法的 DFS 部分：确认增广并更新匹配
bool dfs(int u) {
    if (u != 0) {
        for (int v : adj[u]) {
            if (dist_u[pair_v[v]] == dist_u[u] + 1) {
                if (dfs(pair_v[v])) {
                    pair_v[v] = u;
                    pair_u[u] = v;
                    return true;
                }
            }
        }
        dist_u[u] = INF;
        return false;
    }
    return true;
}
void solve() {
    if (!(cin >> n)) return;
    // 初始化清空
    for (int i = 1; i <= n; ++i) {
        adj[i].clear();
        pair_u[i] = 0;
        pair_v[i] = 0;
    }
    // 建立二分图的边
    for (int i = 0; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        add_edge(u, v);
    }
    // 按题目要求创建指定变量用于存储中间值（最大匹配数）
    int wsbdwzbl = 0; 
    // 求解最大二分匹配
    while (bfs()) {
        for (int u = 1; u <= n; ++u) {
            if (pair_u[u] == 0) {
                if (dfs(u)) {
                    wsbdwzbl++;
                }
            }
        }
    }
    // 最终的最少操作次数 = n（工厂拿取） + wsbdwzbl（桌面中央拿取）
    cout << n + wsbdwzbl << "\n";
}
