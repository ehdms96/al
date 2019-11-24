#include <iostream>
#include <tuple>
#include <vector>
#define inf -1
using namespace std;

typedef tuple<int, int, int> Tuple; //value, k번째 배열, t번째 원소

//typedef struct HeapStruct PriorityQueue;
typedef struct HeapStruct{
    int Capacity;
    int Size;
    vector<Tuple> Elements;
} PriorityQueue;

int IsFull(PriorityQueue *H) {
    if(H->Size == (H->Capacity))
        return 1;
    else return 0;
}
void Swap(Tuple *a, Tuple *b){
    Tuple tmp = *a;
    *a = *b;
    *b = tmp;
}

void Init(PriorityQueue *H, int capacity);
void Insert(PriorityQueue *H, Tuple X);
void HeapSort(vector<Tuple> A, int N);
void PercDown(vector<Tuple> A, int left, int right); //A[left]~A[right]를 min힙으로 만듦
Tuple DelTop(PriorityQueue *H);
void Print(PriorityQueue *H);

int main(void) {
    
    FILE *input = fopen("input1-2.txt", "r"); //실행파일과 같은 경로상에 있는 input파일
    
    int inputArr[99][99];
    int i,j;
    char c;
    Tuple top;
    
    for(i=0; i<99; i++){
        for(j=0; j<99; j++){
            inputArr[i][j] = inf; //초기화
        }
    }
    
    int k;
    fscanf(input, "%d", &k);
    for(i=0; i<k; i++){
        for(j=0; j<99; j++){
            if(EOF!=fscanf(input, "%d%c", &inputArr[i][j], &c)){
                if(c == ' '){
                    continue;
                }
                else if(c == '\n'){
                    break;
                }
            }
        }
    }
    
    PriorityQueue Q;
    Init(&Q, k);
    
    //각 정렬된 배열에서의 가장 작은 값을 뽑아 k개수를 갖는 최소힙을 만든다
    //시간복잡도 : O(k)
    for(int i=0; i<k; i++){
        Insert(&Q, make_tuple(inputArr[i][0], i, 0)); //value, k번째 배열, t번째 원소
    }
    for(;;){
        if(k==0) //k개의 배열의 모든 원소에 대해 insert가 끝남
            break;
        
        //만들어진 힙에서 최소원소를 뽑아내고 힙의 구조를 복원한다
        //시간복잡도 : O(log(k))
        top = DelTop(&Q);
        printf("%d ", get<0>(top));
        
        //해당 원소가 속해 있던 원래의 정렬된 배열에서 다음 값을 힙에 추가하고 힙을 다시 정렬
        //시간 복잡도 : O(log(k))
        if(inputArr[get<1>(top)][get<2>(top)+1] != inf){ //inf(-1)값이 들어오면 Insert를 skip
            Insert(&Q, make_tuple(inputArr[get<1>(top)][get<2>(top)+1],
                                    get<1>(top), //해당원소가 속해있던 원래의 정렬된 배열
                                    get<2>(top)+1)); //에서 그 다음값을 의미함
            //HeapSort(Q.Elements, k); <-insert함수에서 이미 Heap을 다시 정렬했음
        }
        else{
            k--; //정렬된 배열의 모든 원소를 Heap에 insert완료함
            continue;
        }
    }
    printf("\n");
    
    fclose(input);
    return 0;
}

void Init(PriorityQueue *H, int capacity){
    H->Capacity = capacity;
    H->Size = 0;
    H->Elements.push_back(make_tuple(-9999, -1, -1));
}

void Insert(PriorityQueue *H, Tuple X){
    int i;
    if(IsFull(H)==1){
        printf("Priority Queue is Full\n");
        return;
    }
    
    //트리를 거슬러 올라가면서 부모노드와 비교
    //i가 루트노드가 아니면서 삽입할 X값이 i의 부모노드보다 크면
    for(i=++H->Size; get<0>(H->Elements[i/2]) > get<0>(X); i/=2)
        //i번째 노드와 부모 노드를 교환한다
        H->Elements[i] = H->Elements[i/2];
    //새로운 노드를 삽입한다
    H->Elements[i] = X;
}

void HeapSort(vector<Tuple> A, int N){
    int i;
    for(i = N/2; i>0; i--)
        PercDown(A, i, N);
    for(i = N; i>0; i--){
        Swap(&A[1], &A[i]);
        PercDown(A, 1, i-1);
    }
}
//A[left] ~ A[right]를 min힙으로 만드는 함수
void PercDown(vector<Tuple> A, int left, int right){
    Tuple temp = A[left]; //루트 노드
    int Parent, Child;
    
    for(Parent = left; Parent*2 <= right; Parent = Child){
        int cl = Parent*2; //왼쪽 자식
        int cr = cl+1; //오른쪽 자식
        Child = (cr <= right && A[cr] > A[cl]) ? cr : cl; //큰값을 선택
        if(temp > A[Child])
            break; //A[Parent] = A[Child];
        else
            A[Parent] = A[Child]; //break;
    }
    A[Parent] = temp;
}

Tuple DelTop(PriorityQueue *H){
    int i, Child;
    Tuple MinElement, LastElement;

    MinElement = H->Elements[1];
    LastElement = H->Elements[H->Size--];

    //PercDown
    for(i=1; i*2<=H->Size; i=Child){
        Child = i*2;
        if(Child != H->Size && H->Elements[Child + 1] < H->Elements[Child])
            Child++;
        if(LastElement > H->Elements[Child])
            H->Elements[i] = H->Elements[Child];
        else
            break;
    }
    H->Elements[i] = LastElement;
    return MinElement;
}

//test
void Print(PriorityQueue *H){
    int i;
    for(i=1; i<=H->Size; i++){
        printf("%2d ", get<0>(H->Elements[i]));
    }
    //printf("\n");
}
