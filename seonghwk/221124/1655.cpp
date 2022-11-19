#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;

int N;
priority_queue<int, vector<int>, less<int>> pq_front;
priority_queue<int, vector<int>, greater<int>> pq_back;

void input() {
  cin >> N;
  int num;
  for (int i = 0; i < N; i++) {
    cin >> num;
    if (pq_front.size() > pq_back.size())
      pq_back.push(num);
    else
      pq_front.push(num);

    if (!pq_front.empty() && !pq_back.empty() &&
        (pq_front.top() > pq_back.top())) {
      int temp_front = pq_front.top();
      int temp_back = pq_back.top();
      pq_front.pop();
      pq_back.pop();
      pq_front.push(temp_back);
      pq_back.push(temp_front);
    }
    cout << pq_front.top() << "\n";
  }
}
void solution() { return; }

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  input();
  solution();
  return 0;
}

/*
지금까지 등장한 수 중 중간값
중간에 있는 두 수 중 작은 수
*/