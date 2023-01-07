#include <limits.h>

#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

int N, M;
vector<int> arr;
vector<int> tree[2];
int tree_size;
vector<pair<int, int>> query;

void input() {
  cin >> N >> M;
  arr.resize(N);
  int h = (int)ceil(log2(N));
  tree_size = 1 << (h + 1);
  tree[0].resize(tree_size);
  tree[1].resize(tree_size);
  query.resize(M);
  for (int i = 0; i < N; i++) {
    cin >> arr[i];
  }
  for (int i = 0; i < M; i++) {
    cin >> query[i].first >> query[i].second;
  }
}

int init(int mode, int node, int start, int end) {
  // node : node number in segment tree
  // start, end : range of original array

  if (start == end) return tree[mode][node] = arr[start];

  int mid = start + (end - start) / 2;
  int left_result = init(mode, node * 2, start, mid);
  int right_result = init(mode, node * 2 + 1, mid + 1, end);

  if (mode == 0) return tree[mode][node] = min(left_result, right_result);
  if (mode == 1) return tree[mode][node] = max(left_result, right_result);
}

int search(int mode, int node, int start, int end, int left, int right) {
  // node :
  // start, end : segment tree의 해당 node가 담당하는 범위
  // left, right : query의 범위
  if (left > end || right < start) {
    if (mode == 0) return INT_MAX;
    if (mode == 1) return INT_MIN;
  }
  if (left <= start && end <= right) return tree[mode][node];

  int mid = start + (end - start) / 2;
  int left_result = search(mode, node * 2, start, mid, left, right);
  int right_result = search(mode, node * 2 + 1, mid + 1, end, left, right);

  if (mode == 0) return min(left_result, right_result);
  if (mode == 1) return max(left_result, right_result);
}

void solve() {
  init(0, 1, 0, arr.size() - 1);
  init(1, 1, 0, arr.size() - 1);
  for (int i = 0; i < query.size(); i++) {
    for (int mode = 0; mode < 2; mode++) {
      cout << search(mode, 1, 0, arr.size() - 1, query[i].first - 1,
                     query[i].second - 1)
           << " ";
    }
    cout << "\n";
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
N개의 정수,
[a번째, b번째]에서 제일 작은 정수, 제일 큰 정수 찾기
Segment Tree
*/