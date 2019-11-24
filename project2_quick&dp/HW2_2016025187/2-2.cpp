//
//  2-2.c
//  HW2_2016025187
//
//  Created by 김도은 on 2019/10/17.
//  Copyright © 2019 김도은. All rights reserved.
//

#include <iostream>
#include <limits.h>
#include <vector>
using namespace std;

void tracking(vector <vector <int> > v, int len_chunk){
    if (v[len_chunk].size() == 2){
        int first_chunk_len = v[len_chunk][0];
        int second_chunk_len = v[len_chunk][1];

        if (v[first_chunk_len].size() == 1)
            printf("%d ", first_chunk_len);
        if (v[second_chunk_len].size() == 1)
            printf("%d ", second_chunk_len);

        if (v[first_chunk_len].size() == 2)
            tracking(v, first_chunk_len);
        if (v[second_chunk_len].size() == 2)
            tracking(v, second_chunk_len);
    }
    printf("\n");
    return;
}

void cutRod(int A[], int n){
    int i, j;

    vector <vector<int> > len_list;
    len_list.resize(n+1);

    int rod[n+1];
    rod[0] = 0;
    for (i = 1; i <= n ; i++){
        rod[i] = A[i];
    }

    for(i = 1; i <= n; i++){
        int maxRod = INT_MIN;
        int first_chunk_len = 0;
        int second_chunk_len = 0;
        for (j = 0; j <= i/2; j++){
            if (maxRod < rod[j] + rod[i-j]){
                maxRod = rod[j] + rod[i-j];
                first_chunk_len = j;
                second_chunk_len = i - j;
            }
        }
        if (first_chunk_len != 0)
            len_list[i].push_back(first_chunk_len);
        if (second_chunk_len != 0)
            len_list[i].push_back(second_chunk_len);
        rod[i] = maxRod;
    }

    printf("%d\n", rod[n]);
    tracking(len_list, n);
}

int main(void) {
    FILE *input = fopen("input2-2.txt", "r");

    int i, rod;
    int array[105];

    fscanf(input, "%d", &rod);
    for(i = 1; i <= rod; i++){
        fscanf(input, "%d ", &array[i]);
    }

    cutRod(array, rod);

    fclose(input);

    return 0;
}
