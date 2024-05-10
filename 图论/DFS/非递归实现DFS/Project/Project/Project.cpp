#include<iostream>
#include<stack>
#include<vector>
using namespace std;

// 移动方向
int moves[4][2] = { {1,0},{-1,0},{0,1},{0,-1} };
// 判断这个点是否可走
bool isOK(int x, int y, vector<vector<bool>> visited) {
	return x >= 0 && x < 3 && y >= 0 && y < 3 && !visited[x][y];
}
vector<vector<bool>> visited(3, vector<bool>(3, false));

struct State {
	int x, y;
	vector<pair<int, int>> path;
	bool isBack;
};
int main() {
	stack<State> st;
	State state;
	state.x = state.y = 0;
	state.isBack = false;
	st.push(state);
	while (!st.empty()) {
		State state = st.top();
		st.pop();
		int x = state.x;
		int y = state.y;
		if (state.isBack) {
			visited[x][y] = false;
			continue;
		}

		state.path.push_back({ x,y });
		state.isBack = true;
		visited[x][y] = true;
		st.push(state);
		if (x == 2 && y == 2) {
			for (auto& it : state.path) {
				cout << "( " << it.first << "," << it.second << " )";
			}
			cout << endl;
			continue;
		}
		state.isBack = false;
		for (int i = 0; i < 4; i++) {
			int nx = x + moves[i][0];
			int ny = y + moves[i][1];
			if (isOK(nx, ny, visited)) {
				state.x = nx;
				state.y = ny;
				st.push(state);
			}
		}
	}

}


// 递归方式
void dfs(int x, int y, vector<pair<int, int>>& path) {
	if (x == 2 && y == 2) {
		for (int i = 0; i < path.size(); i++) {
			cout << "( " << path[i].first << "," << path[i].second << " )";
		}
		cout << endl;
		return;
	}
	visited[x][y] = true;
	for (int i = 0; i < 4; i++) {
		int nx = x + moves[i][0];
		int ny = y + moves[i][1];
		if (isOK(nx, ny, visited)) {
			path.push_back({ nx,ny });
			dfs(nx, ny, path);
			path.pop_back();
		}
	}
	visited[x][y] = false;
}