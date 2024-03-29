#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

/* 함수 정의*/
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* 재귀 함수 */
int quickSort(int *a, int n);

int hashCode(int key);
int hashing(int *a, int **ht);
int search(int *ht, int key);


int main()
{
	char command;
	int *array = NULL;
	int *hashtable = NULL;
	int key = -1;
	int index = -1;

	srand(time(NULL)); //랜덤 함수

	do{
    printf("[----- [박성준] [2021040026] -----]\n");
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

    //스위치 문으로 답변 받아오기
		switch(command) { 
		case 'z': case 'Z':
			initialize(&array);
			break;
		case 'q': case 'Q':
			freeArray(array);
			break;
		case 's': case 'S':
			selectionSort(array);
			break;
		case 'i': case 'I':
			insertionSort(array);
			break;
		case 'b': case 'B':
			bubbleSort(array);
			break;
		case 'l': case 'L':
			shellSort(array);
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array);

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);
			printArray(hashtable);
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable);
			index = search(hashtable, key);
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P':
			printArray(array);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}
//초기 설정
int initialize(int** a)
{
	int *temp = NULL;

	// array가 NULL, 메모리 할당
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  
	} else
		temp = *a;

	// 랜덤값 -> 배열의 값 
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0;
}

//배열 free
int freeArray(int *a)
{
	if(a != NULL)
		free(a);
	return 0;
}

//배열 출력 
void printArray(int *a)
{
  //비어있을경우
	if (a == NULL) {
    //아무것도없음
		printf("nothing to print.\n");
		return;
	}
  //끝까지 돌면서 인덱스와 값 둘 다 프린트
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i);
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]);
	printf("\n");
}

//선택정렬
int selectionSort(int *a)
{
	int min;
	int minindex;
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");
  //배열 출력
	printArray(a);
  
	for (i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		minindex = i;
		min = a[i];
    
    //반복문 통해 최소 값 찾고, 갱신하는 선택정렬 진행
		for(j = i+1; j < MAX_ARRAY_SIZE; j++)
		{
			if (min > a[j])
			{
				min = a[j];
				minindex = j;
			}
		}
		a[minindex] = a[i];
		a[i] = min;
	}

	printf("----------------------------------------------------------------\n");
  //정렬배열 출력
	printArray(a);
	return 0;
}

//삽입정렬
int insertionSort(int *a)
{
	int i, j, t;
  
	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");
  //배열출력
	printArray(a);
  //삽입정렬 진행
	for(i = 1; i < MAX_ARRAY_SIZE; i++)
	{
		t = a[i];
		j = i;
		while (a[j-1] > t && j > 0)
		{
			a[j] = a[j-1];
			j--;
		}
		a[j] = t;
	}

	printf("----------------------------------------------------------------\n");
  //정렬된 배열 출력
	printArray(a);

	return 0;
}
//버블정렬
int bubbleSort(int *a)
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

  //반복문 두개를 이용해서 버블정렬 진행
	for(i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		for (j = 0; j < MAX_ARRAY_SIZE; j++)
		{
			if (a[j-1] > a[j])
			{
				t = a[j-1];
				a[j-1] = a[j];
				a[j] = t;
			}
		}
	}

	printf("----------------------------------------------------------------\n");
  //정렬된 배열 출력
	printArray(a);

	return 0;
}

//셸정렬
int shellSort(int *a)
{
	int i, j, k, h, v;
  
	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");
  //배열출력
	printArray(a);

  //반복문 4개를 이용하여 셸정렬 진행 
	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2)
	{
		for (i = 0; i < h; i++)
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h)
			{
				v = a[j];
				k = j;
				while (k > h-1 && a[k-h] > v)
				{
					a[k] = a[k-h];
					k -= h;
				}
				a[k] = v;
			}
		}
	}
	printf("----------------------------------------------------------------\n");
  //정렬된 배열 출력
	printArray(a);

	return 0;
}

//퀵정렬
int quickSort(int *a, int n)
{
	int v, t;
	int i, j;
  
  //재귀함수를 이용하여 퀵 정렬 진행
	if (n > 1)
	{
		v = a[n-1];
		i = -1;
		j = n - 1;
    
		while(1)
		{
			while(a[++i] < v);
			while(a[--j] > v);

			if (i >= j) break;
			t = a[i];
			a[i] = a[j];
			a[j] = t;
		}
		t = a[i];
		a[i] = a[n-1];
		a[n-1] = t;
    
		quickSort(a, i);
		quickSort(a+i+1, n-i-1);
	}


	return 0;
}
//해쉬코드 생성
int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE;
}
//
int hashing(int *a, int **ht)
{
	int *hashtable = NULL;

	/* hash table == NULL, 메모리 할당 */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  // 메모리주소 복사
	} else {
		hashtable = *ht;	// hash table != NULLreset, to -1
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		hashtable[i] = -1;

	int key = -1;
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		key = a[i];
		hashcode = hashCode(key);
		if (hashtable[hashcode] == -1)
		{
			hashtable[hashcode] = key;
		} else 	{

			index = hashcode;

			while(hashtable[index] != -1)
			{
				index = (++index) % MAX_HASH_TABLE_SIZE;
				
			}
			hashtable[index] = key;
		}
	}

	return 0;
}

int search(int *ht, int key)
{
	int index = hashCode(key);
  //ht[index] 와 key 동일, 그때 index값
	if(ht[index] == key)
		return index;
  //ht[index] 와 key 다를 때는,범위안에 있을 수 있도록 하고, 리턴
	while(ht[++index] != key)
	{
		index = index % MAX_HASH_TABLE_SIZE;
	}
	return index;
}


