#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 부모노드를 가져옴
int getParent(int parent[], int node) {
	if (parent[node] == node) {
		return node;
	}
	return getParent(parent, parent[node]);
}

// 두 노드의 부모노드를 합침
int unionParent(int parent[], int x, int y) {
	x = getParent(parent, x);
	y = getParent(parent, y);
	if (x < y) {
		parent[y] = x;
		return x;
	}
	else {
		parent[x] = y;
		return y;
	}
}

// 같은 부모노드를 갖는지 확인
int findParent(int parent[], int x, int y) {
	x = getParent(parent, x);
	y = getParent(parent, y);
	if (x == y) {
		// 같은 부모 노드
		return 1;
	}
	else {
		// 다른 부모 노드
		return 0;
	}
}

// 간선들의 정보
class Edge {
public:
	int node[2];
	int distance;
	Edge(int x, int y, int distance) {
		this->node[0] = x;
		this->node[1] = y;
		this->distance = distance;
	}
	bool operator <(Edge &edge) {
		return this->distance < edge.distance;
	}
};

int main(int argc, char* argv[]) {
	int n = 7; // 노드의 개수
	int m = 11; // 간선의 개수
	vector<Edge> v;
	vector<Edge>::iterator iter; // 반복자 정의

	v.push_back(Edge(1, 7, 12)); // 1
	v.push_back(Edge(4, 7, 13)); // 2
	v.push_back(Edge(1, 4, 18)); // 3
	v.push_back(Edge(1, 2, 67)); // 4
	v.push_back(Edge(1, 5, 17)); // 5
	v.push_back(Edge(2, 4, 24)); // 6
	v.push_back(Edge(2, 5, 62)); // 7
	v.push_back(Edge(3, 5, 20)); // 8
	v.push_back(Edge(3, 6, 37)); // 9
	v.push_back(Edge(5, 6, 45)); // 10
	v.push_back(Edge(5, 7, 73)); // 11

								 // 거리를 오름차순으로 정렬
	sort(v.begin(), v.end());

	/*
	for(iter = v.begin(); iter != v.end() ; iter++)
		cout << (*iter).distance << '\n';
		*/

	cout << '\n';

	// 초기화
	int * parent = new int[n];
	for (int i = 0; i<n; i++) {
		parent[i] = i;
	}

	int sum = 0;
	for (int i = 0; i<v.size(); i++) {
		cout << v[i].distance ;
		if (!findParent(parent, v[i].node[0] - 1, v[i].node[1] - 1)) {
			cout << ' ' <<"O" << '\n' ;
			
			// 사이클이 생기지 않는 경우 (다른 부모를 갖는경우)
			sum += v[i].distance;

			// 연결을 하고 나면, 같은 부모를 갖게 되므로...
			unionParent(parent, v[i].node[0] - 1, v[i].node[1] - 1);
		}// end if
		else
			cout << ' ' <<"X" << '\n';

	}// end for

	 // 결과 확인
	cout << '\n'<< sum << '\n';

	return 0;
}