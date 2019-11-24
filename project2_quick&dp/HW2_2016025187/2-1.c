//
//  2-1.c
//  HW2_2016025187
//
//  Created by 김도은 on 2019/10/17.
//  Copyright © 2019 김도은. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void insertionSort(int A[], int start, int end);
int select_pivot(int A[], int left, int right);
void quickSort(int A[], int left, int right);
void threeSort(int A[], int left, int m, int right);
int partition(int A[], int left, int right);

void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main(void) {
    
    FILE *input = fopen("input2-1.txt", "r");
    FILE *output = fopen("output2-1.txt", "w");
    
    int key, count=0;
    int array[200000];
    
    while(EOF != fscanf(input, "%d", &key)){
        array[count++] = key;
    }
    clock_t start, end;
    float delay;
    
    start = clock();
    quickSort(array, 0, count-1);
    end = clock();
    delay = (float)(end-start)/CLOCKS_PER_SEC;
    
    int i;
    for(i=0; i<count; i++){
        fprintf(output, "%d ", array[i]);
    }
    fprintf(output, "\n");
    fprintf(output, "%f s", delay);
    
    fclose(input);
    fclose(output);
    
    return 0;
}

void insertionSort(int A[], int start, int end){
    int x;
    for(x=start+1; x<end; x++){
        int val = A[x];
        int j = x-1;
        while(j>=0 && val<A[j]){
            A[j+1] = A[j];
            j--;
        }
        A[j+1] = val;
    }
}

int select_pivot(int A[], int left, int right){
    srand((unsigned)time(NULL));
//    printf("left : %d, right : %d\n", left, right);
    int random1 = rand()%(right - left + 1) + left;
    int random2 = rand()%(right - left + 1) + left;
    int random3 = rand()%(right - left + 1) + left;
//    printf("random1 : %d. random2 : %d, ramdon3 : %d\n", random1, random2, random3);
//    printf("random1 : %d. random2 : %d, ramdon3 : %d\n", A[random1], A[random2], A[random3]);

    if( (A[random1] < A[random2] && A[random2] < A[random3]) ||
       (A[random3] < A[random2] && A[random2] < A[random1]) ){
//        printf("random2\n\n");
        swap(&A[random2], &A[right]);
    }
    else if( (A[random2] < A[random1] && A[random1] < A[random3]) ||
            (A[random3] < A[random1] && A[random1] < A[random2]) ){
//        printf("random1\n\n");
        swap(&A[random1], &A[right]);
    }
    else{
//        printf("random3\n\n");
        swap(&A[random3], &A[right]);
    }
    
    return A[right];
}

void quickSort(int A[], int left, int right){
    int l = left;
    int r = right;
    
    if(l<r){
        if((r-l) <= 10){
            insertionSort(A, l, r+1);
        }
        else{
            int p = partition(A, l, r);
            if(p == -1){
                printf("input num must bigger than 3\n");
                return;
            }
            quickSort(A, l, p-1);
            quickSort(A, p+1, r);
        }
    }
}

void threeSort(int A[], int left, int m, int right){
    if(A[left]>A[m]) swap(&A[left], &A[m]);
    if(A[m]>A[right]) swap(&A[m], &A[right]);
    if(A[right]>A[m]) swap(&A[left], &A[m]);
}

int partition(int A[], int left, int right){
    int i, j, pivot;
    /*
     * m = (front + left) / 2 경우 int의 범위를 초과해버리는 경우가 있기때문에
     * 아래와 같이 mid값을 정한다
     * 여기서는 명세 조건이 "각 원소는 0 이상 1000 미만의 값을 가짐" 이기에 상관없다
     */
    int m = left + (right - left) / 2;
    
    /*
     * 3개 우선정렬
     */
    threeSort(A, left, m, right);
    
    
    /*
     * 중간값 퀵소트에서는 우선적으로 3개의 값들에 대해 정렬을 수행한다
     * 만약 정렬대상이 3개 이하라면 위의 3개의 if문을 수행하는 것만으로도 정렬이 모두 끝난다
     * 따라서 데이터의 개수가 3개 초과가 될 때만 추가적인 정렬을 수행한다
     */
    if(right - left + 1 > 3){
        pivot = select_pivot(A, left, right);
        i = left-1;
        j = right;
        
        for(;;){
            while(A[--j] > pivot);
            while(A[++i] < pivot);
            if(i<j) swap(&A[i], &A[j]);
            else{
                swap(&A[i], &A[right]);
                return i;
            }
        }
    }
    
    return -1;
}

