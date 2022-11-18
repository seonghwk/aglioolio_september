#include <limits.h>

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int N, M;
vector<vector<int>> adj;

void input() {
  cin >> N >> M;
  adj = vector<vector<int>>(N + 1, vector<int>(N + 1));
  int a, b;
  for (int i = 0; i < M; i++) {
    cin >> a >> b;
    adj[a][b] = 1;
  }
}

void floyd() {
  for (int i = 1; i <= N; i++) adj[i][i] = 1;
  for (int k = 1; k <= N; k++) {
    for (int i = 1; i <= N; i++) {
      for (int j = 1; j <= N; j++) {
        adj[i][j] = adj[i][j] || (adj[i][k] && adj[k][j]);
      }
    }
  }
}

void solution() {
  floyd();
  int ret = 0;
  int cnt;
  for (int i = 1; i <= N; i++) {
    cnt = 0;
    for (int j = 1; j <= N; j++) {
      cnt += adj[i][j] || adj[j][i];
    }
    if (cnt == N) ret++;
  }
  cout << ret;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  input();
  solution();
  return 0;
}
