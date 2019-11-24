//
//  3-1.cpp
//  HW#3
//
//  Created by 김도은 on 2019/11/20.
//  Copyright © 2019 김도은. All rights reserved.
//

/*
 directed graph 에 대한 인접 행렬이 주어졌을 때,
 DFS 방식으로 탐색할 때의 모든 edge 의 종류를 출력하고,
 마지막으로 DFS 의 결과를 출력하는 코드를 작성하라.
 (hint: DFS-visit 함수 내에서 발견하는 인접 node 의 종류(색깔)에 따라 출력)
 */

#include<iostream>
#include<vector>
using namespace std;

FILE *input;

vector<vector<int> > adj;
vector<int> discovered, finished;
vector<int> order;

int node;
int cnt;

void dfs(int now) {
    order.push_back(now+1);
    discovered[now] = cnt++;
    
    for (int i = 0; i < adj[now].size(); i++){
        int next = adj[now][i];
        printf("(%d, %d) ", now+1, next+1);

        if (discovered[next] == -1) {
            printf("tree edge\n");
            dfs(next);
        }
        else if (discovered[now] < discovered[next]){
            printf("forward edge\n");
        }
        else if (finished[next] == 0){
            printf("back edge\n");
        }
        else{
            printf("cross edge\n");
        }
    }
    
    finished[now] = 1;
}

int main(){
    int num;
    input = fopen("input3-1.txt", "r");
    fscanf(input, "%d", &node);
    
    adj = vector<vector<int> >(node);
    discovered = vector<int>(node, -1);
    finished = vector<int>(node, 0);
    
    //간선 추가
    for(int i=0; i<node; i++){
        for(int j=0; j<node; j++){
            fscanf(input, "%d", &num);
            if(num == 1){
                adj[i].push_back(j);
            }
        }
    }
    
    //0에서 시작.
    int start = 0;
    while(start < node){
        
        if(finished[start] == 1){
            start++;
            continue;
        }
        
        dfs(start);
        
        start++;
    }
    
    for(int i=0; i<order.size(); i++){
        printf("%d ", order[i]);
    }
    printf("\n");

    return 0;
}
