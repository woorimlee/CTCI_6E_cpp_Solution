#include <iostream>
#include <queue>
#include <tuple>

using namespace std;

int M, N, H;
//[i][0] == z, [i][1] == y, [i][2] == x
//위 아래 왼쪽 오른쪽 앞 뒤
int dir[6][3] = { {0, -1, 0}, {0, 1, 0}, {0, 0, -1}, {0, 0, 1}, {1, 0, 0}, {-1, 0, 0} };
int tomato[101][101][101];
queue< tuple <int, int, int> > q;

void printTomato() {
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < M; k++) {
				cout << tomato[i][j][k] << " ";
			}
			cout << "\n";
		}
	}
	cout << "\n";
	return;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int q_size = 0;
	int day = 0;
	//토마토가 안 익는 경우가 없다면,
	//익은 갯수 + 빈 공간 == M * N * H 
	//total에 저장해뒀다가 -1을 출력하는 경우에 쓸거임
	int total = 0;
	cin >> M >> N >> H;
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < M; k++) {
				cin >> tomato[i][j][k];
				if (tomato[i][j][k] == 1) {
					q.push({ i, j, k });
					total++;
				}
				else if (tomato[i][j][k] == -1) {
					total++;
				}
			}
		}
	}

	int nx, ny, nz;
	q_size = q.size();
	while (q_size--) {
		auto [z, y, x] = q.front();
		q.pop();
		//상 하 좌 우 앞 뒤 방향에 덜 익은 토마토가 있으면
		//익게 만들고 queue에 넣어놔서 다음 타임에 또 익은 상태를 확장시킴
		for (int j = 0; j < 6; j++) {
			nz = z + dir[j][0];
			ny = y + dir[j][1];
			nx = x + dir[j][2];
			if (0 <= nx && nx < M && 0 <= ny && ny < N && 0 <= nz && nz < H) {
				if (tomato[nz][ny][nx] == 0) {
					tomato[nz][ny][nx] = 1;
					q.push({ nz, ny, nx });
					total++;
				}
			}
		}
		if (!q_size) {
			if (q_size = q.size())
				day++;
		}
	}
	//안 익은 갯수가 하나라도 있다면 while문 빠져나와서 -1 출력하고 프로그램 종료.
	if (total != N * M * H) {
		cout << -1;
	}
	else
		cout << day;
	return 0;
}