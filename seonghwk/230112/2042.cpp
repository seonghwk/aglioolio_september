#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

// N : 수의 개수
// M : 변경 횟수
// K : 구간 합 구하는 횟수
int N, M, K;
vector<ll> arr;
vector<ll> segtree;
vector<pair<ll, pair<ll, ll>>> query;

void input() {
  cin >> N >> M >> K;
  arr.resize(N);
  segtree.resize(4 * N);
  query.resize(M + K);
  for (int i = 0; i < N; i++) {
    cin >> arr[i];
  }
  ll a, b, c;
  for (int i = 0; i < M + K; i++) {
    cin >> a >> b >> c;
    query[i] = {a, {b, c}};
  }
}

ll init(int node, int left, int right) {
  if (left == right) return segtree[node] = arr[left];

  int mid = (left + right) / 2;
  ll leftResult = init(node * 2, left, mid);
  ll rightResult = init(node * 2 + 1, mid + 1, right);
  return segtree[node] = leftResult + rightResult;
}

ll update(int node, int nodeLeft, int nodeRight, ll index, ll value) {
  if (index < nodeLeft || nodeRight < index) return segtree[node];
  if (nodeLeft == nodeRight) return segtree[node] = value;

  int mid = (nodeLeft + nodeRight) / 2;
  ll leftResult = update(node * 2, nodeLeft, mid, index, value);
  ll rightResult = update(node * 2 + 1, mid + 1, nodeRight, index, value);
  return segtree[node] = leftResult + rightResult;
}

ll sumQuery(int node, int nodeLeft, int nodeRight, ll left, ll right) {
  if (right < nodeLeft || nodeRight < left) return 0;
  if (left <= nodeLeft && nodeRight <= right) return segtree[node];

  int mid = (nodeLeft + nodeRight) / 2;
  ll leftResult = sumQuery(node * 2, nodeLeft, mid, left, right);
  ll rightResult = sumQuery(node * 2 + 1, mid + 1, nodeRight, left, right);
  return leftResult + rightResult;
}

void printTree() {
  for (int i = 1; i < 4 * N; i++) {
    cout << segtree[i] << " ";
  }
  cout << "\n";
}

void solve() {
  init(1, 0, N - 1);
  for (int i = 0; i < M + K; i++) {
    ll mode = query[i].first;
    if (mode == 1) {
      // update
      ll index = query[i].second.first - 1;
      ll value = query[i].second.second;
      update(1, 0, N - 1, index, value);
    } else {
      // sum query
      ll left = query[i].second.first - 1;
      ll right = query[i].second.second - 1;
      cout << sumQuery(1, 0, N - 1, left, right) << "\n";
    }
  }
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

          15
     10       5
  3    7     5   0
1  2  3  4
*/