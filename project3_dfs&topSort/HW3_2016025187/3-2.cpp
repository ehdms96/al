//
//  3-2.cpp
//  HW#3
//
//  Created by 김도은 on 2019/11/20.
//  Copyright © 2019 김도은. All rights reserved.
//

/*
 undirected graph 에 대한 인접 행렬이 주어졌을 때, DFS 의 결과를 출력하고,
 각 node 의 component 번호를 출력하는 코드를 작성하라.
 (hint: DFS-visit 함수 내에서 발견하는 인접 node 는 직전 node 와 같은 component 번호를 가진다.)
 */

#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;

FILE *input;

vector<int> graph[205];
int arr[105][105];
int check[205];
int component = 1;
int node;

void dfs(int now) {
    if (check[now] != 0){
        return;
    }
    check[now] = component;
    printf("%d ", now);
    for (int i = 0; i < graph[now].size(); i++) {
        if (check[graph[now][i]] == 0){
            dfs(graph[now][i]);
        }
    }
    return;
}

int main() {
    
    input = fopen("input3-2.txt", "r");
    
    fscanf(input, "%d", &node);
    for(int i=1; i<=node; i++){
        for(int j=1; j<=node; j++){
            fscanf(input, "%d", &arr[i][j]);
            if(arr[i][j] == 1){
                graph[i].push_back(j);
            }
        }
    }
    
    for (int i=1; i<=node; i++) {
        if (check[i] != 0){
            continue;
        }
        dfs(i);
        component++;
    }
    
    printf("\n");
    for (int i=1; i<=node; i++) {
        printf("%d: %d\n", i, check[i]);
    }
    return 0;
}
