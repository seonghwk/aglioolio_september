#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Edge {
  int from, to, cost;
};

bool operator<(Edge a, Edge b) { return a.cost > b.cost; }

int N;
vector<pair<int, int>> X, Y, Z;
priority_queue<Edge> edges;
vector<int> parent;

int Find(int now) {
  if (now == parent[now]) return now;
  return parent[now] = Find(parent[now]);
}

void Union(int a, int b) {
  int pa = Find(a);
  int pb = Find(b);
  parent[pb] = pa;
}

void input() {
  cin >> N;
  X.resize(N);
  Y.resize(N);
  Z.resize(N);
  parent.resize(N);
  int x, y, z;
  for (int i = 0; i < N; i++) {
    parent[i] = i;
    cin >> x >> y >> z;
    X[i] = {x, i};
    Y[i] = {y, i};
    Z[i] = {z, i};
  }
}

int kruskal() {
  int cnt = 0;
  int cost = 0;
  while (cnt != N - 1) {
    Edge now = edges.top();
    edges.pop();
    if (Find(now.from) == Find(now.to)) continue;
    Union(now.from, now.to);
    cnt++;
    cost += now.cost;
  }
  return cost;
}

void solve() {
  sort(X.begin(), X.end());
  sort(Y.begin(), Y.end());
  sort(Z.begin(), Z.end());

  for (int i = 0; i < N - 1; i++) {
    edges.push(
        {X[i].second, X[i + 1].second, abs(X[i].first - X[i + 1].first)});
    edges.push(
        {Y[i].second, Y[i + 1].second, abs(Y[i].first - Y[i + 1].first)});
    edges.push(
        {Z[i].second, Z[i + 1].second, abs(Z[i].first - Z[i + 1].first)});
  }
  cout << kruskal();
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  input();
  solve();

  return 0;
}

/*
N개의 행성
행성을 '연결'하는 터널 -> graph
3차원 좌표위의 한 점
두 행성을 연결할 때 드는 비용은 min(dx, dy, dz)
터널을 N-1개 건설, 모든 행성 연결되도록
최소 비용 구하기 -> MST
*/