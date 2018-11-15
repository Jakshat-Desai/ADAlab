#include <bits/stdc++.h>
using namespace std;

class node {
 public:
  int id, st, bt;
  node() {}
  node(int i, int a, int b) {
    id = i;
    st = a;
    bt = b;
  }
};

bool compare(node a, node b) {
  if (a.st != b.st) return a.st < b.st;
  return a.id < b.id;
}

class comp {
 public:
  bool operator()(node a, node b) {
    if (a.bt != b.bt) {
      return a.bt > b.bt;
    }
    return a.id > b.id;
  }
};

int main() {
  int n, a, b;
  cin >> n;
  node p[n];
  int ct[n];
  int tat[n];
  int wt[n];
  for (int i = 0; i < n; i++) {
    cin >> a >> b;
    p[i] = node(i, a, b);
  }
  sort(p, p + n, compare);
  int cur = 0;
  int i = 0;
  priority_queue<node, vector<node>, comp> pq;
  while (i < n) {
    if (!pq.empty()) {
      node temp = pq.top();
      pq.pop();
      cur = max(cur + temp.bt, temp.st + temp.bt);
      ct[temp.id] = cur;
    }
    int j = i;
    while (j < n && p[j].st <= cur) j++;
    for (int k = i; k < j; k++) pq.push(p[k]);

    if (i == j && pq.empty()) {
      pq.push(p[i]);
      i++;
    } else
      i = j;
  }
  while (!pq.empty()) {
    node temp = pq.top();
    pq.pop();
    cur = max(cur + temp.bt, temp.st + temp.bt);
    ct[temp.id] = cur;
  }
  for (int i = 0; i < n; i++) {
    tat[i] = ct[i] - p[i].st;
    wt[i] = tat[i] - p[i].bt;
  }
  int sum = 0, tt = 0;
  for (int i = 0; i < n; i++) {
    sum += wt[i];
    tt += tat[i];
  }
  cout << "Average waiting time : ";
  cout << (sum / double(n)) << endl;
  cout << "Average turn around time : ";
  cout << (tt / double(n)) << endl;
  return 0;
}