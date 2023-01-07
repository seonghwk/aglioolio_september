#include <iostream>
#include <queue>
#include <vector>

using namespace std;

const int dy[] = {-1, 1, 0, 0};
const int dx[] = {0, 0, -1, 1};

struct Node {
  int y, x;
};

int h, w;
vector<vector<char>> board;
vector<vector<int>> visited;
string keys;
vector<Node> v_start;
int cnt;

void input() {
  board.clear();
  visited.clear();
  v_start.clear();
  keys = "";
  cnt = 0;

  cin >> h >> w;
  board.resize(h, vector<char>(w));
  visited.resize(h, vector<int>(w));
  string row;
  for (int i = 0; i < h; i++) {
    cin >> row;
    for (int j = 0; j < w; j++) {
      board[i][j] = row[j];
    }
  }
  cin >> keys;
  if (keys == "0") keys = "";
}

void pick_start() {
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      if (!(i == 0 || i == h - 1 || j == 0 || j == w - 1)) continue;
      if (board[i][j] != '*') v_start.push_back({i, j});
    }
  }
}

void bfs(queue<Node> q, string prev_key) {
  string now_key = prev_key;
  queue<Node> next_q;

  while (!q.empty()) {
    Node now = q.front();
    q.pop();

    char &type = board[now.y][now.x];

    // 2. 방문한 적 있으면 continue
    if (visited[now.y][now.x] != 0) continue;

    // 3. 벽이면 continue
    if (type == '*') continue;

    // 4. 문서를 찾으면 문서 개수 증가
    if (type == '$') cnt++;

    // 5. 키를 찾으면 키에 등록
    if ('a' <= type && type <= 'z') now_key += type;

    if ('A' <= type && type <= 'Z') {
      if (now_key.find(type + 'a' - 'A') == string::npos) {
        next_q.push(now);
        continue;
      }
    }
    visited[now.y][now.x] = 1;
    // now는 방문할 수 있는 상태
    for (int dir = 0; dir < 4; dir++) {
      int ny = now.y + dy[dir];
      int nx = now.x + dx[dir];

      // 1. 범위 밖이면 continue
      if (!(0 <= ny && ny < h) || !(0 <= nx && nx < w)) continue;

      // 방문 할 수 있는 곳이다, 방문처리 후 다음 방문 큐에 등록
      q.push({ny, nx});
    }
  }
  if (prev_key != now_key) bfs(next_q, now_key);
}

void solve() {
  pick_start();
  queue<Node> q;
  for (int i = 0; i < v_start.size(); i++) {
    Node start = v_start[i];
    q.push(start);
  }
  bfs(q, keys);
  cout << cnt << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int T;
  cin >> T;
  for (int tc = 1; tc <= T; tc++) {
    input();
    solve();
  }

  return 0;
}

/*
문서 훔치기
문을 열기 위해 열쇠 필요
일부 열쇠는 이미 갖고 있다
. : 빈공간
* : 벽
$ : 문서
대문자 : 문
소문자 : 키

빌딩 가장자리의 벽이 아닌 곳을 통해 드나든다

훔칠 수 있는 문서의 최대 개수


1. 시작점은 빌딩 가장자리 벽이 아닌 곳 -> 여러 곳일 수 있다.
2. 하나의 시작점 선택해서 Floodfill
3. Floodfill을 하며 내가 구할 수 있는 키를 등록하고, 구할 수 있는 키를 반환
4. 반복적으로 Floodfill을 돌리면서 누적된 키를 이용해서 Floodfill 진행


가장자리가 문으로 시작하는 경우를 고려해야한다.
*/