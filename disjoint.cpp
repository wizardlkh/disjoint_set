#include <stdio.h>

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

int main(void) {
	int parent[11];
	for (int i = 1; i <= 10; i++) {
		parent[i] = i;
		printf("node : %d / parent : %d\n", i, parent[i]); // ���� �� ���
	}
	printf("\n");

	// ���� -> �ٽ�
	unionParent(parent, 1, 2);
	unionParent(parent, 2, 3);
	unionParent(parent, 3, 4);
	unionParent(parent, 5, 6);
	unionParent(parent, 6, 7);
	unionParent(parent, 7, 8);
	unionParent(parent, 9, 10);

	// ��� Ȯ�� 
	for (int i = 1; i <= 10; i++) {
		printf("node : %d / parent : %d\n", i, parent[i]); // ���� �� ���
	}
	printf("\n");

	printf("1�� 5�� ������ �Ǿ��ֳ�? : %d\n", findParent(parent, 1, 5));
	printf("1�� 3��  ������ �Ǿ��ֳ�? : %d\n", findParent(parent, 1, 3));
	printf("5�� 10�� ������ �Ǿ��ֳ�? : %d\n", findParent(parent, 5, 10));

	return 0;
}