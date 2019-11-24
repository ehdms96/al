//
//  3-3.cpp
//  HW#3
//
//  Created by 김도은 on 2019/11/21.
//  Copyright © 2019 김도은. All rights reserved.
//

/*
 인접행렬이 주어진 그래프가 DAG(Directed Acyclic Graph)인지 판별하고,
 DAG 라면 DFS 를 이용한 topological sort 를 수행하여 결과를 출력하라.
 (hint1: DAG 의 판별은 DFS 의 back edge 를 활용할 수 있다.)
 (hint2: DFS 의 과정에서 BLACK 이 된 node 의 역순이 topological sort 의 결과이다.)
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

FILE *input;
int graph[101][101];
int visit[101];
int node;
int node_tmp;
int topSort[101];
int DAG;
int check[101];

void dfs(int x){
    check[x]++;
    
    //종료되는 시점에서 해당 정점과 연결된 정점들에 대해 모든 depth를 보았을 때 종료
    //(간선이 없거나 이미 방문한 경우)
    if (visit[x]){
        return;
    }
    else{
        visit[x] = 1;
        for (int i=1; i<=node; i++){
            if (graph[x][i]){
                dfs(i);
            }
        }
        //dfs종료 시점에서 출력한 역순은 topSort의 결과가 된다
        topSort[node_tmp--] = x;
        return;
    }
}

void topological_sort(void){

    //초기 : 선행 정점을 가지지 않는 정점에 대해
    for (int i=1; i<=node && DAG; i++){
        if (!visit[i]){
            for (int j=1; j<=node; j++){
                check[j] = 0;
            }
            
            dfs(i);
            
            //u, v간의 dependency가 v->u라고 가정하자
            //dfs(v)에서 v와 연결된 간선들의 집합 E(v)에 대해
            //dfs(u)가 먼저 종료되어야 한다
            //그렇지 않다면 주어진 그래프가 DAG가 아닌 cycle이 존재한다
            if (check[i] > 1){
                DAG = 0;
            }
        }
    }
}

int main(void){
    input = fopen("input3-3.txt", "r");
    
    DAG = 1;

    fscanf(input, "%d", &node);
    node_tmp = node;

    for(int i=1; i<=node; i++){
        for(int j=1; j<=node; j++){
            fscanf(input, "%d", &graph[i][j]);
        }
    }

    topological_sort();

    printf("%d\n", DAG);
    if (DAG){
        for (int i=1; i<=node; i++){
            printf("%d ", topSort[i]);
        }
    }
    printf("\n");

    return 0;
}
