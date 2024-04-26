/*
	1.Паросочетание (англ. matсhing) M в двудольном графе — произвольное множество рёбер двудольного графа такое, что никакие два ребра не имеют общей вершины.

	2.Чередующаяся цепь (англ. alternating path) — путь в двудольном графе, для любых двух соседних рёбер которого верно, что одно из них принадлежит паросочетанию M,а другое нет.

	3.Вершины двудольного графа, инцидентные рёбрам паросочетания M,называются покрытыми (англ. matched), а неинцидентные — свободными (англ. unmatched)

	4.Дополняющая цепь (или увеличивающая цепь) (англ. augmenting path) — чередующаяся цепь, у которой оба конца свободны.

	Теор(Бержа): Паросочетание максимально, ТиТТК не существует дополнителняющих путей

*/

#include <iostream>
#include <vector>
using namespace std;


class Graph { //класс граф
private:
	vector<vector<int>> G;

	bool DFS(int start, vector<int>& matching, vector<int>& used) { //алгоритм поиска в глубину, возвращает тру, если удалось найти дополняющую цепь и фалс - в противном случае.
		if (used[start]) return false;

		used[start] = true;
		for (int to: G[start]) {
			if (matching[to] == -1 || DFS(matching[to], matching, used)) {
				matching[to] = start;
				return true;
			}
		}
		return false;

	}
	

public:
	Graph(vector<vector<int>> g) {
		G = g;
	}



	void MaxMatching() { //алгоритм Куна
		vector<int> matching(G.size(), -1);//массив паросочетаний, индекс - вершина паросочетания, значение - максимальное паросочетание
		for (int i = 0; i < G.size(); ++i) {
			vector<int> used(G.size(), false);
			DFS(i, matching, used); // запускаем DFS предварительно "обнуляя" вектор used
		}

		for (int i = 0; i < G.size(); ++i) {
			if (matching[i] != -1) cout << i << " " << matching[i] << endl;;
		}
		cout << endl;
	}

};

int main() {
	vector<vector<int>> g = {
		{5},//0
		{5,6},//1
		{7,8},//2
		{6},//3
		{5,8},//4
		{0,1,4},//5
		{1,3},//6
		{2},//7
		{2,4}//8
	};
	Graph G(g);
	G.MaxMatching();

}
/*
H/W: 0.send results by gift
	 1. Finish Matching
	 2. Определение двудольности
	 3. (2) +(1)
	 4. Ans: which part should work faster?ЫЫ
*/