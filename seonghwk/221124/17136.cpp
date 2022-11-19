#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Node {
  int y, x;
};

vector<vector<int>> board(10, vector<int>(10));
vector<int> paper(6, 5);
int min_cnt;

void input() {
  min_cnt = 26;
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      cin >> board[i][j];
    }
  }
}

int getMaxSize(const Node& now) {
  for (int size = 0; size < 5; size++) {
    for (int i = 0; i <= size; i++) {
      if (now.x + size >= 10 || now.y + i >= 10) return size;
      if (board[now.y + i][now.x + size] == 0) return size;
    }
    for (int j = 0; j <= size; j++) {
      if (now.y + size >= 10 || now.x + j >= 10) return size;
      if (board[now.y + size][now.x + j] == 0) return size;
    }
  }
  return 5;
}

void fillBoard(const Node& now, const int& size, const int& mode) {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      board[now.y + i][now.x + j] = mode;
    }
  }
}

Node getNextNode(Node now) {
  while (true) {
    if (now.x == 10) {
      now.y++;
      now.x = 0;
    }
    if (now.y == 10) break;
    if (board[now.y][now.x] == 1) break;
    now.x++;
  }
  return now;
}

void dfs(Node now, int cnt) {
  // base case
  if (now.y == 10) {
    min_cnt = min(cnt, min_cnt);
    return;
  }

  // recursive case
  if (board[now.y][now.x] == 1) {
    int size = getMaxSize(now);
    for (int i = size; i > 0; i--) {
      if (paper[i] == 0) continue;
      fillBoard(now, i, 0);
      paper[i]--;
      dfs(getNextNode(now), cnt + 1);
      fillBoard(now, i, 1);
      paper[i]++;
    }
  } else {
    dfs(getNextNode(now), cnt);
  }
}

void solution() {
  dfs({0, 0}, 0);
  if (min_cnt == 26) min_cnt = -1;
  cout << min_cnt;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  input();
  solution();

  return 0;
}

/*
크기가 1, 2, 3, 4, 5인 색종이 각각 5개씩
10*10 종이에서 1이 적힌 칸 채우기
모든 칸 붙이는데 필요한 색종이의 최소 개수
불가능하면 -1

불가능한 경우가 있을까? -> 1짜리로 덮으면 되지 않나? -> 1을 다 써버렸으면
불가능한경우 생긴다.

getMaxSize에서 잘못 구현했다.

*/