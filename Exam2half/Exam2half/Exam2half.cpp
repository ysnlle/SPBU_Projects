#include <iostream>
#include <vector>

using namespace std;
struct Mine {
	int x, y;
};

double dist(Mine a, Mine b) {
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

struct Vertex {
	int v;
	bool up, down;

	Vertex(int ve) {
		v = ve; up = false; down = false;
	}
	Vertex(int ve, bool u, bool d) {
		v = ve; up = u; down = d;
	}
};

vector<vector<Vertex>> BuildGraph(vector<Mine> mines, double rad,int up, int down) {
	int n = mines.size();
	double diam = 2 * rad;
	vector<vector<Vertex>> graph(n);

	for (int i = 0; i < n; ++i) {
		for (int j = i+1; j < n; ++j) {
			if (dist(mines[i], mines[j]) <= diam) {
				graph[i].push_back(Vertex(j));
				graph[j].push_back(Vertex(i));
			}
		}
	}
	for (int i = 0; i < n; ++i) {
		if (abs(mines[i].y - down) <= rad) {
			graph.push_back({ i });
			graph[i].push_back(Vertex(graph.size() - 1, false, true));
		}
		if (abs(mines[i].y - up) <= rad) {
			graph.push_back({ i });
			graph[i].push_back(Vertex(graph.size() - 1, true, false));
		}

	}
	return graph;
}

class Minefield {
	friend vector<vector<int>>BuildGraph(vector<Mine>, double);
private:
	vector<Mine> mines;
	double rad;
	int up; int down;
	vector<vector<Vertex>> G;

	void DFS_h(Vertex u, vector<bool>& vis, vector<Vertex>& way, bool& triger1, bool& triger2) {
		if (u.up == true)  triger1 = true;
		if (u.down == true) triger2 = true;
		
		vis[u.v] = true;

		for (int i = 0; i < G[u.v].size(); ++i) {
			if (vis[G[u.v][i].v] == false) {
				way.push_back(G[u.v][i]);
				DFS_h(G[u.v][i], vis, way, triger1, triger2);
			}
		}
	}

public:
	Minefield(vector<Mine> m, double r, int u, int d) {
		mines = m; rad = r; up = u; down = d;
		G = BuildGraph(mines, rad, up,down);
	}

	bool DFS(Vertex u) {
		vector<Vertex> way;
		vector<bool> vis(G.size(), false);
		bool triger1 = false, triger2 = false;

		way.push_back(u);
		DFS_h(u, vis, way, triger1, triger2);

		if (triger1 && triger2) return false;
		return true;

	}

	bool CanPass() {
		for (int i = 0; i < mines.size(); ++i) {
			if (!DFS(Vertex(i))) return false;
		}
		return true;
	}
};


int main() {
	vector<Mine> mines = { {1,2},{2,2},{4,3},{5,5},{6,6},{8,2},{11,6},{13,5},{12,2} };
	double rad = 1.5;
	Minefield A(mines, rad, 0, 7);

	vector<vector<Vertex>> b = BuildGraph(mines, rad, 0, 7);
	bool a = A.CanPass();
	cout << a;

}