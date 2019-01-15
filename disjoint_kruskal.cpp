#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// �θ��带 ������
int getParent(int parent[], int node) {
	if (parent[node] == node) {
		return node;
	}
	return getParent(parent, parent[node]);
}

// �� ����� �θ��带 ��ħ
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

// ���� �θ��带 ������ Ȯ��
int findParent(int parent[], int x, int y) {
	x = getParent(parent, x);
	y = getParent(parent, y);
	if (x == y) {
		// ���� �θ� ���
		return 1;
	}
	else {
		// �ٸ� �θ� ���
		return 0;
	}
}

// �������� ����
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
	int n = 7; // ����� ����
	int m = 11; // ������ ����
	vector<Edge> v;
	vector<Edge>::iterator iter; // �ݺ��� ����

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

								 // �Ÿ��� ������������ ����
	sort(v.begin(), v.end());

	/*
	for(iter = v.begin(); iter != v.end() ; iter++)
		cout << (*iter).distance << '\n';
		*/

	cout << '\n';

	// �ʱ�ȭ
	int * parent = new int[n];
	for (int i = 0; i<n; i++) {
		parent[i] = i;
	}

	int sum = 0;
	for (int i = 0; i<v.size(); i++) {
		cout << v[i].distance ;
		if (!findParent(parent, v[i].node[0] - 1, v[i].node[1] - 1)) {
			cout << ' ' <<"O" << '\n' ;
			
			// ����Ŭ�� ������ �ʴ� ��� (�ٸ� �θ� ���°��)
			sum += v[i].distance;

			// ������ �ϰ� ����, ���� �θ� ���� �ǹǷ�...
			unionParent(parent, v[i].node[0] - 1, v[i].node[1] - 1);
		}// end if
		else
			cout << ' ' <<"X" << '\n';

	}// end for

	 // ��� Ȯ��
	cout << '\n'<< sum << '\n';

	return 0;
}