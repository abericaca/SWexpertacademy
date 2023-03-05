#include <bits/stdc++.h>
#define changed 1
#define pii pair<int, int>
#define INF 2100000000
using namespace std;

struct pan{
	bool up, down, left, right;
};
int N;
vector<pii> core;

pan Freeway(int u, int board[15][15]) {
	int x = core[u].first, y = core[u].second;

	bool up = true, down = true, left = true, right = true;
	for (int i = 0; i < x; i++) {
		if (board[i][y] != 0) {
			up = false;
			break;
		}
	}
	for (int i = x + 1; i < N; i++) {
		if (board[i][y] != 0) {
			down = false;
			break;
		}
	}
	for (int j = 0; j < y; j++) {
		if (board[x][j] != 0) {
			left = false;
			break;
		}
	}
	for (int j = y + 1; j < N; j++) {
		if (board[x][j] != 0) {
			right = false;
			break;
		}
	}

	return { up, down, left, right };
}

pii DFS(const int& u, int board[15][15]) {	//return max_core, min_wire
	if (u == N) return { 0, 0 };

	pan freeway = Freeway(u, board);
	if (freeway.up == 0 && freeway.down == 0 && freeway.left == 0 && freeway.right == 0) {
		return DFS(u + 1, board);
	}

	//up, down, left, right made 
	pii up, down, left, right;
	if (freeway.up) {
		for (int x = core[u].first, y = core[u].second; x >= 0; x--) {
			board[x][y] = 1;
		}
		up = DFS(u + 1, board);
		for (int x = core[u].first, y = core[u].second; x >= 0; x--) {
			board[x][y] = 0;
		}
	}
	if (freeway.down) {
		for (int x = core[u].first, y = core[u].second; x < N; x++) {
			board[x][y] = 1;
		}
		down = DFS(u + 1, board);
		for (int x = core[u].first, y = core[u].second; x < N; x++) {
			board[x][y] = 0;
		}
	}
	if (freeway.left) {
		for (int x = core[u].first, y = core[u].second; y >= 0; y--) {
			board[x][y] = 1;
		}
		left = DFS(u + 1, board);
		for (int x = core[u].first, y = core[u].second; y >= 0; y--) {
			board[x][y] = 0;
		}
	}
	if (freeway.right) {
		for (int x = core[u].first, y = core[u].second; y < N; y++) {
			board[x][y] = 1;
		}
		right = DFS(u + 1, board);
		for (int x = core[u].first, y = core[u].second; y < N; y++) {
			board[x][y] = 0;
		}
	}

	//all blocked _ do nothing
	// if (allblocked) {
	// 	rt = min(rt, DFS(u + 1, board));
	// }
	
	// return rt;
}


int main() {
	int T; cin >> T;
	for (int t = 1; t <= T; t++) {
		cin >> N;
		int board[15][15];
		core.clear();

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> board[i][j];
				if (board[i][j] == 0) continue;
				if (i == 0 || i == N - 1 || j == 0 || j == N - 1) continue;

				core.push_back({ i, j });
				pan freeway = Freeway(core.size() - 1, board);
				if (freeway.up == 0 && freeway.down == 0 && freeway.left == 0 && freeway.right == 0) {
					core.pop_back();
				}
			}
		}
		printf("#%d %d\n", t, DFS(0, board));
	}

	return 0;
}