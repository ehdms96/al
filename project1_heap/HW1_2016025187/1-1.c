#include <stdio.h>
#include <stdlib.h>

//typedef struct HeapStruct PriorityQueue;
typedef struct HeapStruct{
    int Capacity;
    int Size;
    int *Elements;
} PriorityQueue;

void Init(PriorityQueue *H, int capacity);

int IsFull(PriorityQueue *H) {
    if(H->Size == (H->Capacity-1))
        return 1;
    else return 0;
}
void Swap(int *a, int *b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void Insert(PriorityQueue *H, int X);
int DeleteMin(PriorityQueue *H);
void HeapSort(int A[], int N);
void PercDown(int A[], int left, int right); //A[left]~A[right]를 max힙으로 만듦
void Print(PriorityQueue *H);

int main(void) {
    PriorityQueue Q;
    Init(&Q, 99);
    
    int num;
    int i;
    for(i=1; i<100; i++){
        scanf("%d", &num);
        if(num == -1)
            break;
        //정렬할 값을 순서 상관없이 입력받는대로 배열을 사용하여 완전 이진 트리에 배치한다
        Q.Elements[i] = num;
    }
    
    Q.Size = i-1; //사이즈를 설정해준다
    HeapSort(Q.Elements, Q.Size); //마지막노드부터 이진 힙의 규칙에 맞도록 재배치한다
    
    int j;
    for(j=0; j<i-1; j++){
        //마지막노드와 자리를 바꿔 print를 한뒤
        //사이즈를 줄이고 다시 재배치를 하며 끝까지 반복한다
        printf("%d ", DeleteMin(&Q));
    }
    printf("\n");
    
    return 0;
}

void Init(PriorityQueue *H, int capacity){
    H->Capacity = capacity;
    H->Size = 0;
    H->Elements = malloc(sizeof(int)*H->Capacity);
    H->Elements[0] = 9999;
}

//위 코드에서는 Insert함수를 이용하여 재배치를 하며 insert하지 않고, 정렬되지않은 채로 한번에 받음
void Insert(PriorityQueue *H, int X){
    int i;
    if(IsFull(H)==1){
        printf("Priority Queue is Full\n");
        return;
    }
    
    //트리를 거슬러 올라가면서 부모노드와 비교
    //i가 루트노드가 아니면서 삽입할 X값이 i의 부모노드보다 작으면
    for(i=++H->Size; H->Elements[i/2] < X; i/=2)
        //i번째 노드와 부모 노드를 교환한다
        H->Elements[i] = H->Elements[i/2];
    //새로운 노드를 삽입한다
    H->Elements[i] = X;
}

int DeleteMin(PriorityQueue *H){
    int i, Child;
    int MinElement, LastElement;

    MinElement = H->Elements[1];
    LastElement = H->Elements[H->Size--];

    //PercDown
    for(i=1; i*2<=H->Size; i=Child){
        Child = i*2;
        if(Child != H->Size && H->Elements[Child + 1] > H->Elements[Child])
            Child++;
        if(LastElement < H->Elements[Child])
            H->Elements[i] = H->Elements[Child];
        else
            break;
    }
    H->Elements[i] = LastElement;
    return MinElement;
}

void HeapSort(int A[], int N){
    int i;
    for(i = N/2; i>0; i--)
        PercDown(A, i, N);
    for(i = N; i>0; i--){
        Swap(&A[1], &A[i]);
        PercDown(A, 1, i-1);
    }
}
//A[left] ~ A[right]를 max힙으로 만드는 함수
void PercDown(int A[], int left, int right){
    int temp = A[left]; //루트 노드
    int Parent, Child;
    
    for(Parent = left; Parent*2 <= right; Parent = Child){
        int cl = Parent*2; //왼쪽 자식
        int cr = cl+1; //오른쪽 자식
        Child = (cr <= right && A[cr] < A[cl]) ? cr : cl; //작은값을 선택
        if(temp < A[Child])
            break; //A[Parent] = A[Child];
        else
            A[Parent] = A[Child]; //break;
    }
    A[Parent] = temp;
}

//test용
void Print(PriorityQueue *H){
    int i;
    for(i=1; i<=H->Size; i++){
        printf("%d ", H->Elements[i]);
    }
    printf("\n");
}
