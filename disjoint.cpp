#include <stdio.h>

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

int main(void) {
	int parent[11];
	for (int i = 1; i <= 10; i++) {
		parent[i] = i;
		printf("node : %d / parent : %d\n", i, parent[i]); // 연결 전 출력
	}
	printf("\n");

	// 연결 -> 핵심
	unionParent(parent, 1, 2);
	unionParent(parent, 2, 3);
	unionParent(parent, 3, 4);
	unionParent(parent, 5, 6);
	unionParent(parent, 6, 7);
	unionParent(parent, 7, 8);
	unionParent(parent, 9, 10);

	// 결과 확인 
	for (int i = 1; i <= 10; i++) {
		printf("node : %d / parent : %d\n", i, parent[i]); // 연결 후 출력
	}
	printf("\n");

	printf("1과 5는 연결이 되어있나? : %d\n", findParent(parent, 1, 5));
	printf("1과 3은  연결이 되어있나? : %d\n", findParent(parent, 1, 3));
	printf("5과 10은 연결이 되어있나? : %d\n", findParent(parent, 5, 10));

	return 0;
}