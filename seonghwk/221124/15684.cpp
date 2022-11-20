#include <limits.h>

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Node {
  int y, x;
};

int N, M, H;
vector<vector<int>> board;
int min_cnt;

void input() {
  min_cnt = 4;
  cin >> N >> M >> H;
  board = vector<vector<int>>(H + 1, vector<int>(N + 1));
  int a, b;
  for (int i = 0; i < M; i++) {
    cin >> a >> b;
    board[a][b] = 1;
  }
}

int goDown(int now) {
  for (int i = 1; i <= H; i++) {
    if (board[i][now] == 1)
      now++;
    else if (now > 1 && board[i][now - 1] == 1)
      now--;
  }
  return now;
}

Node getNextNode(Node now) {
  while (true) {
    if (now.x >= N) {
      now.x = 1;
      now.y++;
    }
    if (now.y == H + 1) break;

    if (board[now.y][now.x] == 1)
      now.x += 2;
    else if (now.x > 1 && board[now.y][now.x - 1] == 1)
      now.x += 1;
    else
      break;
  }
  return now;
}

void dfs(Node now, int cnt) {
  // base case
  if (now.y == H + 1) {
    for (int i = 1; i <= N; i++) {
      if (goDown(i) != i) return;
    }
    min_cnt = min(cnt, min_cnt);
    return;
  }

  // recursive case
  if (board[now.y][now.x] == 1) {
    dfs(getNextNode(now), cnt);
  } else if (now.x > 1 && board[now.y][now.x - 1] == 1) {
    // 다음칸으로 이동
    dfs(getNextNode(now), cnt);
  } else {
    dfs(getNextNode({now.y, now.x + 1}), cnt);
    if (cnt < 3) {
      board[now.y][now.x] = 1;
      dfs(getNextNode(now), cnt + 1);
      board[now.y][now.x] = 0;
    }
  }
}

void solution() {
  dfs({1, 1}, 0);
  if (min_cnt == 4) min_cnt = -1;
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
교점을 grid의 한 칸으로 간주
위에서 아래로 내려가면서 진행 중, 두 방향 확인하기
해당 칸에 가로선이 있으면 -> 오른쪽으로 이동
해당 칸 왼쪽에 가로선이 있으면 -> 왼쪽으로 이동
i번 출발, i번 도착할 수 있도록 조작하기위해
추가해야 하는 가로선 개수의 최솟값

우선 최대한 안두는 쪽으로 해결할 수 있는지 확인
가장 깊은 곳에서부터 하나씩 추가해보다가 3 넘어가면 가지치기로 탈출
*/