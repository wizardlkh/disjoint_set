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

// 필요한 구조체
typedef struct _point
{
	int x;   // x좌표
	int y;   // y좌표
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

// 우선순위 큐에 넣고 정렬할 데이터
struct X_NODE // X객체 2개 저장 및 두 객체의 x값 차이를 정렬기준으로
{
	X_NODE()
	{
	}

	X_NODE(X x1, X x2) :x1(x1), x2(x2), key(abs(x1.x - x2.x))
	{
	}

	X x1;
	X x2;

	int key; // X객체 2개의 x좌표 차이 (정렬기준)
};

struct X_COMPARE // 
{
	bool operator () (X_NODE& a, X_NODE& b)
	{
		return a.key > b.key;
	}
};

struct Y_NODE // Y객체 2개 저장 및 두 객체의 x값 차이를 정렬기준으로
{
	Y_NODE()
	{
	}

	Y_NODE(Y y1, Y y2) :y1(y1), y2(y2), key(abs(y1.y - y2.y))
	{
	}

	Y y1;
	Y y2;

	int key; // Y객체 2개의 x좌표 차이 (정렬기준)
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

	point = new Point[N + 1]; // point[1] ~ [N] 까지 생성
	quest = new Quest[Q]; // quest[0] ~ [Q-1] 까지 생성
	parent = new int[N]; // 노드별 연결 정보 저장 (값이 같으면 연결됨)  parent[0] ~ [N-1]

	for (int i = 1; i <= N; i++)
		cin >> point[i].x >> point[i].y;
	for (int i = 0; i < Q; i++)
		cin >> quest[i].fr >> quest[i].to >> quest[i].hp;

	// 연결정보 초기화 (모두 연결 X)
	for (int i = 0; i < N; i++)
		parent[i] = i;

	// HP 개수 파악 및 저장(같은것 제외)
	for (int i = 0; i < Q; i++)
	{
		hv.push_back(HP(quest[i].hp));
		hv[i].q_num = i;
	}

	sort(hv.begin(), hv.end());

	// X 개수 파악 및 저장(같은것 제외)
	for (int i = 0; i < N; i++)
	{
		xv.push_back(X(point[i + 1].x));
		xv[i].p_idx = i + 1;
	}

	sort(xv.begin(), xv.end());

	// Y 개수 파악 및 저장(같은것 제외)
	for (int i = 0; i < N; i++)
	{
		yv.push_back(Y(point[i + 1].y));
		yv[i].p_idx = i + 1;
	}

	sort(yv.begin(), yv.end());

	// X좌표 차이로 정렬 (X-PQ 제작)
	for (int i = 0; i < N - 1; i++)
		XData.push(X_NODE(xv[i], xv[i + 1]));

	// Y좌표 차이로 정렬 (Y-PQ 제작)
	for (int i = 0; i < N - 1; i++)
		YData.push(Y_NODE(yv[i], yv[i + 1]));

	// hp정보 바탕으로 parent[1]~[n] 정보 갱신
	for (int i = 0; i < Q; i++)
	{
		// n_hp 갱신
		n_hp = hv[i].hp;
		// q_idx 갱신
		q_idx = hv[i].q_num;

		// hp 값이 같으면 연결정보 갱신x 
		if (hv[i].hp == b_hp)
			quest[q_idx].result = findParent(parent, quest[q_idx].fr - 1, quest[q_idx].to - 1);
		else // hp 값이 증가하면 연결정보 갱신o 
		{
			// PQ를 통해 연결되야 하는 정점들 연결	
			while (XData.empty() == false && XData.top().key <= n_hp)
			{
				x_node = XData.top(); // 우선순위큐(XData)에서 X객체 2개 저장한 x_node 객체 뽑기 (x좌표 차이 적은순)

									  // X좌표 차이가 HP보다 작거나 같으면 두 정점 연결
				unionParent(parent, x_node.x1.p_idx - 1, x_node.x2.p_idx - 1);

				// 연결한 정보는 PQ에서 제거
				XData.pop();
			}

			while (YData.empty() == false && YData.top().key <= n_hp)
			{
				y_node = YData.top(); // 우선순위큐(XData)에서 Y객체 2개 저장한 y_node 객체 뽑기 (y좌표 차이 적은순)

									  // Y좌표 차이가 HP보다 작거나 같으면 두 정점 연결
				unionParent(parent, y_node.y1.p_idx - 1, y_node.y2.p_idx - 1);

				// 연결한 정보는 PQ에서 제거
				YData.pop();
			}

			quest[q_idx].result = findParent(parent, quest[q_idx].fr - 1, quest[q_idx].to - 1);

			// b_hp 갱신
			b_hp = hv[i].hp;
		}
	}

	// 문제번호 순으로 결과 출력하기
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
// 부모 노드 찾아주는 함수 
int getParent(int parent[], int x) {
	if (parent[x] == x) {
		// 최종 부모노드 
		return x;
	}
	return parent[x] = getParent(parent, parent[x]);
}

// 두 부모 노드를 합치는 함수 (두 노드를 연결하는 함수)
int unionParent(int parent[], int a, int b) {
	a = getParent(parent, a);
	b = getParent(parent, b);

	// 작은값을 부모노드로 선택 
	if (a<b) {
		parent[b] = a;
		return a;
	}
	else {
		parent[a] = b;
		return b;
	}
}

// 같은 부모를 가지는지 확인
int findParent(int parent[], int a, int b) {
	a = getParent(parent, a);
	b = getParent(parent, b);
	if (a == b) {
		return 1;
	}
	return 0;
}