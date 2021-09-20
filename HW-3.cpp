#include<stdio.h>
#include<algorithm>
#include<vector>

using namespace std;

bool comp(vector<int> a, vector<int> b){
    return (a[2] < b[2]);
}

int main(){
    int n, m;
    int v1, v2, e;
    vector<vector<int>> edge;
    scanf("%d%d", &n, &m);
    for(int i = 0; i < m; i++){ 
        scanf("%d%d%d", &v1, &v2, &e);
        edge.push_back(vector<int>{v1, v2, e});
    }
    sort(edge.begin(), edge.end(), comp);

    vector<int> CompName(n, -1), CompSize(n, 1);
    int CompNum = n;

    for(int i = 0; i < m; i++){
        int name1 = edge[i][0], name2 = edge[i][1];
        if(CompName[name1] != -1){
            while(CompName[name1] != -1) name1 = CompName[name1];
            CompName[edge[i][0]] = name1;
        }
        if(CompName[name2] != -1){
            while(CompName[name2] != -1) name2 = CompName[name2];
            CompName[edge[i][1]] = name2;
        }
        if(name1 == name2){
            continue;
        }else{
            if(CompSize[name1] >= CompSize[name2]){
                CompName[name2] = name1;
                CompSize[name1] += CompSize[name2];
                CompSize[name2] = 0;
                CompNum--;
            }else{
                CompName[name1] = name2;
                CompSize[name2] += CompSize[name1];
                CompSize[name1] = 0;
                CompNum--;
            }
        }
        if(CompNum == 3) break;
    }
    sort(CompSize.begin(), CompSize.end());
    printf("%d\n%d\n%d\n", CompSize[n - 3], CompSize[n - 2], CompSize[n - 1]);

    return 0;
}