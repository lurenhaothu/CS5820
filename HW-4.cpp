#include<stdio.h>
#include<vector>

using namespace std;

int main(){
    int n, c1, c2, c3;
    vector<vector<int>> cost;
    scanf("%d", &n);
    if(n == 1){
        int co1;
        scanf("%d", &co1);
        printf("%d\n%d\n", co1, 1);
        return 0;
    }else if(n == 2){
        int co1, co2, co3;
        scanf("%d%d%d", &co1, &co2, &co3);
        if(co1 + co3 > co2){
            printf("%d\n%d\n", co2, 2);
        }else{
            printf("%d\n%d%d\n", co1 + co3, 1, 1);
        }
        return 0;
    }

    for(int i = 0; i < n - 2; i++){
        scanf("%d%d%d", &c1, &c2, &c3);
        cost.push_back(vector<int>{c1, c2, c3});
    }
    scanf("%d%d%d", &c1, &c2, &c3);
    cost.push_back(vector<int>{c1, c2});
    cost.push_back(vector<int>{c3});

    vector<int> OPT(n + 1, 0);
    OPT[0] = 0;
    OPT[1] = cost[0][0];
    OPT[2] = cost[0][1] > (cost[0][0] + cost[1][1]) ? (cost[0][0] + cost[1][1]) : cost[0][1];
    for(int i = 3; i <= n; i++){
        int r1 = OPT[i - 1] + cost[i - 1][0];
        int r2 = OPT[i - 2] + cost[i - 2][1];
        int r3 = OPT[i - 3] + cost[i - 3][2];
        r1 = r1 < r2 ? r1 : r2;
        r1 = r1 < r3 ? r1 : r3;
        OPT[i] = r1;
    }

    vector<int> result;
    int ptr = n;
    while(ptr != 0){
        if(OPT[ptr] == OPT[ptr - 1] + cost[ptr - 1][0]){
            result.push_back(1);
            ptr = ptr - 1;
        }else if(OPT[ptr] == OPT[ptr - 2] + cost[ptr - 2][1]){
            result.push_back(2);
            ptr = ptr - 2;
        }else if(OPT[ptr] == OPT[ptr - 3] + cost[ptr - 3][2]){
            result.push_back(3);
            ptr = ptr - 3;
        }
    }
     printf("%d\n", OPT[n]);
     for(int i = result.size() - 1; i >=0; i--){
         printf("%d ", result[i]);
     }
     printf("\n");

    return 0;
}
