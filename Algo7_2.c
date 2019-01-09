#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
//#define _CRT_SECURE_NO_WARNINGS
void BFS(int start);

int v; //vertex의 수
int **map, *visit, *queue; //인접 행렬과 방문 여부를 나타내는 행렬, 큐
int rear= 0, front=0; //전단과 후단

int main(void) {
	int *arr; // 파일의 데이터를 저장할 포인터 변수 선언.
	int size = 1;
	FILE* f; // 파일
	int startTime = 0, endTime = 0;
	float gap;
	int start; //시작 정점

	f = fopen("graph.txt", "r"); //파일 열기

	if (f == NULL) {
		printf("파일이 열리지 않습니다.");
		exit(1);
	}

	arr = (int *)malloc(sizeof(int));

	while (feof(f) == 0) {
		arr = (int *)realloc(arr, (size) * sizeof(int));
		fscanf(f, "%d", &arr[size - 1]);
		size++;
	}

	v = arr[0]; //배열의 첫 번째 값이 vertex의 수 

	//visit,queue 1차원 배열 생성
	visit = (int *)malloc(sizeof(int)*v);
	queue = (int *)malloc(sizeof(int)*v);

	//visit,queue 배열 초기화
	for (int i = 0; i < v;i++) {
		visit[i] = 0;
		queue[i] = 0;
	}

	//가로,세로 v만큼의 크기를 가진 2차원 배열 생성
	map = (int**)malloc(sizeof(int*)*v);
	for (int i = 0; i < v; i++) {
		map[i] = (int*)malloc(sizeof(int) * v);
	}

	//생성한 2차원 배열에 값을 넣어준다.
	for (int i = 0; i < v; i++) {
		for (int j = 0; j < v; j++) {
			map[i][j] = arr[i*v + j + 1];
		}
	}

	printf("시작 정점을 입력해주세요 : ");
	scanf("%d", &start); //시작 정점값 입력받음

	startTime = clock();

	BFS(start); //DFS호출

	endTime = clock();
	gap = (float)(endTime - startTime) / (CLOCKS_PER_SEC);

	printf("측정 시간 : %f\n", gap);

	/*메모리 free*/
	free(arr);
	for (int i = 0; i < v; i++) {
		free(map[i]);
	}
	free(map);
	free(visit);
	free(queue);

	fclose(f); //파일 닫기

	system("pause"); // 테스트 보기 위해.
}

void BFS(int start) {
	visit[start] = 1; //정점 start를 방문했다고 표시

	queue[rear++] = start; //큐에 start삽입하고, rear 1증가
	while (front < rear) { //rear이 front보다 클 경우에만.
		start = queue[front++]; //큐의 첫번째 데이터를 제외하고 제외된 값 가지고 옴. front 1증가
		for (int i = 0; i < v; i++) {
			//정점 start와 i가 만나고, 정점 i를 방문하지 않은 경우
			if (map[start][i] == 1 && !visit[i]) {
				visit[i] = 1; //정점 i방문했다고 표시
				printf("%d에서 %d로 이동\n", start, i);
				queue[rear++] = i; //큐에 i를 삽입하고 rear 1증가
			}
		}
	}
}
