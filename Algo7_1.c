#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
//#define _CRT_SECURE_NO_WARNINGS
void DFS(int start);

int v; //vertex의 수
int **map, *visit; //인접 행렬과 방문 여부를 나타내는 행렬

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

	//arr배열 동적 할당
	arr = (int *)malloc(sizeof(int));

	//파일 크기만큼 realloc
	while (feof(f) == 0) {
		arr = (int *)realloc(arr, (size) * sizeof(int));
		fscanf(f, "%d", &arr[size - 1]);
		size++;
	}

	v = arr[0]; //배열의 첫 번째 값이 vertex의 수 
	
	//visit 1차원 배열 생성
	visit = (int *)malloc(sizeof(int)*v);

	//visit배열 초기화
	for (int i = 0; i < v;i++) {
		visit[i] = 0;
	}

	//가로,세로 v만큼의 크기를 가진 2차원 배열 생성
	map = (int**)malloc(sizeof(int*)*v);
	for (int i = 0; i < v; i++) {
		map[i] = (int*)malloc(sizeof(int) * v);
	}

	//생성한 2차원 배열에 값을 넣어준다.
	for (int i = 0; i < v; i++) {
		for (int j = 0; j < v; j++) {
			map[i][j] = arr[i*v + j+1];
		}
	}


	printf("시작 정점을 입력해주세요 : ");
	scanf("%d", &start); //시작 정점값 입력받음
	
	startTime = clock();
	
	DFS(start); //DFS호출

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

	fclose(f); //파일 닫기

	system("pause"); // 테스트 보기 위해.
}

void DFS(int start) {
	visit[start] = 1; //정점 start를 방문했다고 표시
	
	for (int i = 0; i < v; i++) {
		/*정점 start와 정점 i가 연결되어있고, 정점 i를 방문하지 않았을 때*/
		if (map[start][i] == 1 && !visit[i]) {
			printf("%d에서 %d로 이동\n", start, i); //start에서 i로 이동
			DFS(i); //정점 i에서 다시 DFS를 시작한다.
		}
	}
}
