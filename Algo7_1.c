#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
//#define _CRT_SECURE_NO_WARNINGS
void DFS(int start);

int v; //vertex�� ��
int **map, *visit; //���� ��İ� �湮 ���θ� ��Ÿ���� ���

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

	//arr�迭 ���� �Ҵ�
	arr = (int *)malloc(sizeof(int));

	//���� ũ�⸸ŭ realloc
	while (feof(f) == 0) {
		arr = (int *)realloc(arr, (size) * sizeof(int));
		fscanf(f, "%d", &arr[size - 1]);
		size++;
	}

	v = arr[0]; //�迭�� ù ��° ���� vertex�� �� 
	
	//visit 1���� �迭 ����
	visit = (int *)malloc(sizeof(int)*v);

	//visit�迭 �ʱ�ȭ
	for (int i = 0; i < v;i++) {
		visit[i] = 0;
	}

	//����,���� v��ŭ�� ũ�⸦ ���� 2���� �迭 ����
	map = (int**)malloc(sizeof(int*)*v);
	for (int i = 0; i < v; i++) {
		map[i] = (int*)malloc(sizeof(int) * v);
	}

	//������ 2���� �迭�� ���� �־��ش�.
	for (int i = 0; i < v; i++) {
		for (int j = 0; j < v; j++) {
			map[i][j] = arr[i*v + j+1];
		}
	}


	printf("���� ������ �Է����ּ��� : ");
	scanf("%d", &start); //���� ������ �Է¹���
	
	startTime = clock();
	
	DFS(start); //DFSȣ��

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

	fclose(f); //���� �ݱ�

	system("pause"); // �׽�Ʈ ���� ����.
}

void DFS(int start) {
	visit[start] = 1; //���� start�� �湮�ߴٰ� ǥ��
	
	for (int i = 0; i < v; i++) {
		/*���� start�� ���� i�� ����Ǿ��ְ�, ���� i�� �湮���� �ʾ��� ��*/
		if (map[start][i] == 1 && !visit[i]) {
			printf("%d���� %d�� �̵�\n", start, i); //start���� i�� �̵�
			DFS(i); //���� i���� �ٽ� DFS�� �����Ѵ�.
		}
	}
}
