#include <limits.h>

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int N, M;
vector<vector<int>> adj;

void input() {
  cin >> N >> M;
  adj = vector<vector<int>>(N + 1, vector<int>(N + 1, INT_MAX / 2));
  int A, B;
  for (int i = 0; i < M; i++) {
    cin >> A >> B;
    adj[A][B] = 1;
    adj[B][A] = 1;
  }
}

void floyd() {
  for (int i = 1; i <= N; i++) adj[i][i] = 0;

  for (int k = 1; k <= N; k++) {
    for (int i = 1; i <= N; i++) {
      for (int j = 1; j <= N; j++) {
        adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
      }
    }
  }
}

void solution() {
  floyd();
  int kbn;
  int min_kbn = INT_MAX;
  int min_kbn_idx;
  for (int i = 1; i <= N; i++) {
    kbn = 0;
    for (int j = 1; j <= N; j++) {
      if (i == j) continue;
      kbn += adj[i][j];
    }
    if (kbn < min_kbn) {
      min_kbn = min(kbn, min_kbn);
      min_kbn_idx = i;
    }
  }
  cout << min_kbn_idx;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  input();
  solution();

  return 0;
}