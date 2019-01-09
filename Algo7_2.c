#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
//#define _CRT_SECURE_NO_WARNINGS
void BFS(int start);

int v; //vertex�� ��
int **map, *visit, *queue; //���� ��İ� �湮 ���θ� ��Ÿ���� ���, ť
int rear= 0, front=0; //���ܰ� �Ĵ�

int main(void) {
	int *arr; // ������ �����͸� ������ ������ ���� ����.
	int size = 1;
	FILE* f; // ����
	int startTime = 0, endTime = 0;
	float gap;
	int start; //���� ����

	f = fopen("graph.txt", "r"); //���� ����

	if (f == NULL) {
		printf("������ ������ �ʽ��ϴ�.");
		exit(1);
	}

	arr = (int *)malloc(sizeof(int));

	while (feof(f) == 0) {
		arr = (int *)realloc(arr, (size) * sizeof(int));
		fscanf(f, "%d", &arr[size - 1]);
		size++;
	}

	v = arr[0]; //�迭�� ù ��° ���� vertex�� �� 

	//visit,queue 1���� �迭 ����
	visit = (int *)malloc(sizeof(int)*v);
	queue = (int *)malloc(sizeof(int)*v);

	//visit,queue �迭 �ʱ�ȭ
	for (int i = 0; i < v;i++) {
		visit[i] = 0;
		queue[i] = 0;
	}

	//����,���� v��ŭ�� ũ�⸦ ���� 2���� �迭 ����
	map = (int**)malloc(sizeof(int*)*v);
	for (int i = 0; i < v; i++) {
		map[i] = (int*)malloc(sizeof(int) * v);
	}

	//������ 2���� �迭�� ���� �־��ش�.
	for (int i = 0; i < v; i++) {
		for (int j = 0; j < v; j++) {
			map[i][j] = arr[i*v + j + 1];
		}
	}

	printf("���� ������ �Է����ּ��� : ");
	scanf("%d", &start); //���� ������ �Է¹���

	startTime = clock();

	BFS(start); //DFSȣ��

	endTime = clock();
	gap = (float)(endTime - startTime) / (CLOCKS_PER_SEC);

	printf("���� �ð� : %f\n", gap);

	/*�޸� free*/
	free(arr);
	for (int i = 0; i < v; i++) {
		free(map[i]);
	}
	free(map);
	free(visit);
	free(queue);

	fclose(f); //���� �ݱ�

	system("pause"); // �׽�Ʈ ���� ����.
}

void BFS(int start) {
	visit[start] = 1; //���� start�� �湮�ߴٰ� ǥ��

	queue[rear++] = start; //ť�� start�����ϰ�, rear 1����
	while (front < rear) { //rear�� front���� Ŭ ��쿡��.
		start = queue[front++]; //ť�� ù��° �����͸� �����ϰ� ���ܵ� �� ������ ��. front 1����
		for (int i = 0; i < v; i++) {
			//���� start�� i�� ������, ���� i�� �湮���� ���� ���
			if (map[start][i] == 1 && !visit[i]) {
				visit[i] = 1; //���� i�湮�ߴٰ� ǥ��
				printf("%d���� %d�� �̵�\n", start, i);
				queue[rear++] = i; //ť�� i�� �����ϰ� rear 1����
			}
		}
	}
}
