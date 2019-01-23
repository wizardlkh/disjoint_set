#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// Disjoint sets
int getParent(int parent[], int x);
int unionParent(int parent[], int a, int b);
int findParent(int parent[], int a, int b);

// �ʿ��� ����ü
typedef struct _point
{
	int x;   // x��ǥ
	int y;   // y��ǥ
} Point;

typedef struct _from_to_hp
{
	int fr;
	int to;
	int hp;

	int result;
} Quest;

class HP
{
public:
	int hp;
	int q_num;

	HP(int hp) {
		this->hp = hp;
	}
	bool operator <(HP &ohp) {
		return this->hp < ohp.hp;
	}
};

class X
{
public:
	int x;
	int p_idx;

	X()
	{
	}

	X(int x) {
		this->x = x;
	}
	bool operator <(X &ox) {
		return this->x < ox.x;
	}
};

class Y
{
public:
	int y;
	int p_idx;

	Y()
	{
	}

	Y(int y) {
		this->y = y;
	}
	bool operator <(Y &oy) {
		return this->y < oy.y;
	}
};

// �켱���� ť�� �ְ� ������ ������
struct X_NODE // X��ü 2�� ���� �� �� ��ü�� x�� ���̸� ���ı�������
{
	X_NODE()
	{
	}

	X_NODE(X x1, X x2) :x1(x1), x2(x2), key(abs(x1.x - x2.x))
	{
	}

	X x1;
	X x2;

	int key; // X��ü 2���� x��ǥ ���� (���ı���)
};

struct X_COMPARE // 
{
	bool operator () (X_NODE& a, X_NODE& b)
	{
		return a.key > b.key;
	}
};

struct Y_NODE // Y��ü 2�� ���� �� �� ��ü�� x�� ���̸� ���ı�������
{
	Y_NODE()
	{
	}

	Y_NODE(Y y1, Y y2) :y1(y1), y2(y2), key(abs(y1.y - y2.y))
	{
	}

	Y y1;
	Y y2;

	int key; // Y��ü 2���� x��ǥ ���� (���ı���)
};

struct Y_COMPARE
{
	bool operator () (Y_NODE& a, Y_NODE& b)
	{
		return a.key > b.key;
	}
};


int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	priority_queue< X_NODE, vector< X_NODE >, X_COMPARE > XData;
	priority_queue< Y_NODE, vector< Y_NODE >, Y_COMPARE > YData;

	X_NODE x_node;
	Y_NODE y_node;

	int * parent;

	int N, Q, nextV, idx, q_idx, q;
	Point * point;
	Quest * quest;
	cin >> N >> Q;
	int HP_num = 0, bf = -1, *R_HP, b_hp = -1, n_hp = -1;
	vector<HP> hv;
	vector<X> xv;
	vector<Y> yv;

	point = new Point[N + 1]; // point[1] ~ [N] ���� ����
	quest = new Quest[Q]; // quest[0] ~ [Q-1] ���� ����
	parent = new int[N]; // ��庰 ���� ���� ���� (���� ������ �����)  parent[0] ~ [N-1]

	for (int i = 1; i <= N; i++)
		cin >> point[i].x >> point[i].y;
	for (int i = 0; i < Q; i++)
		cin >> quest[i].fr >> quest[i].to >> quest[i].hp;

	// �������� �ʱ�ȭ (��� ���� X)
	for (int i = 0; i < N; i++)
		parent[i] = i;

	// HP ���� �ľ� �� ����(������ ����)
	for (int i = 0; i < Q; i++)
	{
		hv.push_back(HP(quest[i].hp));
		hv[i].q_num = i;
	}

	sort(hv.begin(), hv.end());

	// X ���� �ľ� �� ����(������ ����)
	for (int i = 0; i < N; i++)
	{
		xv.push_back(X(point[i + 1].x));
		xv[i].p_idx = i + 1;
	}

	sort(xv.begin(), xv.end());

	// Y ���� �ľ� �� ����(������ ����)
	for (int i = 0; i < N; i++)
	{
		yv.push_back(Y(point[i + 1].y));
		yv[i].p_idx = i + 1;
	}

	sort(yv.begin(), yv.end());

	// X��ǥ ���̷� ���� (X-PQ ����)
	for (int i = 0; i < N - 1; i++)
		XData.push(X_NODE(xv[i], xv[i + 1]));

	// Y��ǥ ���̷� ���� (Y-PQ ����)
	for (int i = 0; i < N - 1; i++)
		YData.push(Y_NODE(yv[i], yv[i + 1]));

	// hp���� �������� parent[1]~[n] ���� ����
	for (int i = 0; i < Q; i++)
	{
		// n_hp ����
		n_hp = hv[i].hp;
		// q_idx ����
		q_idx = hv[i].q_num;

		// hp ���� ������ �������� ����x 
		if (hv[i].hp == b_hp)
			quest[q_idx].result = findParent(parent, quest[q_idx].fr - 1, quest[q_idx].to - 1);
		else // hp ���� �����ϸ� �������� ����o 
		{
			// PQ�� ���� ����Ǿ� �ϴ� ������ ����	
			while (XData.empty() == false && XData.top().key <= n_hp)
			{
				x_node = XData.top(); // �켱����ť(XData)���� X��ü 2�� ������ x_node ��ü �̱� (x��ǥ ���� ������)

									  // X��ǥ ���̰� HP���� �۰ų� ������ �� ���� ����
				unionParent(parent, x_node.x1.p_idx - 1, x_node.x2.p_idx - 1);

				// ������ ������ PQ���� ����
				XData.pop();
			}

			while (YData.empty() == false && YData.top().key <= n_hp)
			{
				y_node = YData.top(); // �켱����ť(XData)���� Y��ü 2�� ������ y_node ��ü �̱� (y��ǥ ���� ������)

									  // Y��ǥ ���̰� HP���� �۰ų� ������ �� ���� ����
				unionParent(parent, y_node.y1.p_idx - 1, y_node.y2.p_idx - 1);

				// ������ ������ PQ���� ����
				YData.pop();
			}

			quest[q_idx].result = findParent(parent, quest[q_idx].fr - 1, quest[q_idx].to - 1);

			// b_hp ����
			b_hp = hv[i].hp;
		}
	}

	// ������ȣ ������ ��� ����ϱ�
	for (int i = 0; i < Q; i++)
	{
		if (quest[i].result == 1)
			cout << "YES" << '\n';
		else if (quest[i].result == 0)
			cout << "NO" << '\n';
	}

	return 0;
}

// Disjoint sets
// �θ� ��� ã���ִ� �Լ� 
int getParent(int parent[], int x) {
	if (parent[x] == x) {
		// ���� �θ��� 
		return x;
	}
	return parent[x] = getParent(parent, parent[x]);
}

// �� �θ� ��带 ��ġ�� �Լ� (�� ��带 �����ϴ� �Լ�)
int unionParent(int parent[], int a, int b) {
	a = getParent(parent, a);
	b = getParent(parent, b);

	// �������� �θ���� ���� 
	if (a<b) {
		parent[b] = a;
		return a;
	}
	else {
		parent[a] = b;
		return b;
	}
}

// ���� �θ� �������� Ȯ��
int findParent(int parent[], int a, int b) {
	a = getParent(parent, a);
	b = getParent(parent, b);
	if (a == b) {
		return 1;
	}
	return 0;
}