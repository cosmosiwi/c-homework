#include<bits/stdc++.h>
#define rep(i, a, b) for(int i = a; i < b; i++)

using namespace std;

const int N = 1000;
int sum[N][N];
int a[N][N];

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n, L, r, t;
  cin >> n >> L >> r >> t;
  for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			cin >> a[i][j];
		}
  }
  for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			sum[i][j] = sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+a[i][j];
		}
  }
  int cnt = 0;
  for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			int x1 = max(i-r, 1), x2 = min(i+r, n);
			int y1 = max(j-r, 1), y2 = min(j+r, n);
			int num = (x2-x1+1)*(y2-y1+1);
			int res = sum[x2][y2]-sum[x1-1][y2]-sum[x2][y1-1]+sum[x1-1][y1-1];
			//cout << x1 << " " << y1 << " " << x2 << " " << y2 << " res " << res << " " << num  << " " << res/num << endl;
			if(res*1.0/num <= t)cnt++;
		}
  }
  cout << cnt << endl;
  return 0;
}
