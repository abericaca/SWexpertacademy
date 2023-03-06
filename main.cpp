#include <bits/stdc++.h>
#define pii pair<int, int>
#define INF 2100000000
using namespace std;

struct pan
{
	bool up, down, left, right;
};

int N;
vector<pii> core_loc;
int max_core, min_wire;

pan Freeway(int u, int board[15][15])
{
	int x = core_loc[u].first, y = core_loc[u].second;

	bool up = true, down = true, left = true, right = true;
	for (int i = 0; i < x; i++)
	{
		if (board[i][y] != 0)
		{
			up = false;
			break;
		}
	}
	for (int i = x + 1; i < N; i++)
	{
		if (board[i][y] != 0)
		{
			down = false;
			break;
		}
	}
	for (int j = 0; j < y; j++)
	{
		if (board[x][j] != 0)
		{
			left = false;
			break;
		}
	}
	for (int j = y + 1; j < N; j++)
	{
		if (board[x][j] != 0)
		{
			right = false;
			break;
		}
	}

	return {up, down, left, right};
}

void DFS(int board[15][15], int num, int core, int wire){
	if(N - num + core < max_core) return;
	if(num == core_loc.size()) {
		if (core == max_core) min_wire = min(min_wire, wire);
		else if (core > max_core) {
			max_core = core;
			min_wire = wire;

			//test
			printf("<<board>>\n");
			for(int i = 0; i<N; i++){
				for(int j =0; j < N; j++){
					cout<<board[i][j]<<' ';
				}
				cout<<'\n';
			}
		}
		return;
	}

	int x = core_loc[num].first, y = core_loc[num].second;
	pan freeway = Freeway(num, board);
	if (freeway.up) {
		for(int i = 0; i < x; i++) board[i][y] = 2;
		DFS(board, num + 1, core + 1, wire + x);
		for(int i = 0; i < x; i++) board[i][y] = 0;
	}
	if (freeway.down) {
		for(int i = x + 1; i < N; i++) board[i][y] = 2;
		DFS(board, num + 1, core + 1, wire + N - 1 - x);
		for(int i = x + 1; i < N; i++) board[i][y] = 0;
	}
	if (freeway.left) {
		for(int i = 0; i < y; i++) board[x][i] = 2;
		DFS(board, num + 1, core + 1, wire + y);
		for(int i = 0; i < y; i++) board[x][i] = 0;
	}
	if (freeway.right) {
		for(int i = y + 1; i < N; i++) board[x][i] = 2;
		DFS(board, num + 1, core + 1, wire + N - 1 - y);
		for(int i = y + 1; i < N; i++) board[x][i] = 0;
	}
	DFS(board, num + 1, core, wire);
}

int main()
{
	int T;
	cin >> T;
	for (int t = 1; t <= T; t++)
	{
		cin >> N;
		int board[15][15];
		core_loc.clear();
		max_core = 0;
		min_wire = INF;

		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				cin >> board[i][j];
				if (board[i][j] == 0)
					continue;
				if (i == 0 || i == N - 1 || j == 0 || j == N - 1)
					continue;

				core_loc.push_back({i, j});
				pan freeway = Freeway(core_loc.size() - 1, board);
				if (freeway.up == 0 && freeway.down == 0 && freeway.left == 0 && freeway.right == 0)
				{
					core_loc.pop_back();
				}
			}
		}

		DFS(board, 0, 0, 0);
		printf("#%d %d\n", t, min_wire);
	}

	return 0;
}