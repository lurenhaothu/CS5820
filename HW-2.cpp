#include <stdio.h>
#include <vector>

using namespace std;

int main(){
    int n, m;
    scanf("%d%d", &n, &m);
    vector<vector<int>> edges;
    int head, tail;
    for(int i = 0; i < m; i++){
        scanf("%d%d", &head, &tail);
        edges.push_back({head - 1, tail - 1});
    }

    vector<vector<int>> Adj(n, vector<int> {});

    for(int i = 0; i < m; i++){
        //printf("%d %d\n", edges[i][0], edges[i][1]);
        Adj[edges[i][0]].push_back(edges[i][1]);
        Adj[edges[i][1]].push_back(edges[i][0]);
    }

    //printf("checkpoint 1");

    vector<int> Machine(n, -1), Discovered(n, 0);
    int DisNum = 0, CurMachine = 0, ListNum = 0;
    vector<vector<vector<int>>> PairList;

    while(DisNum != n){
        int s = 0;
        while(Discovered[s] != 0) s++;
        Machine[s] = CurMachine;
        Discovered[s] = 1;
        ListNum ++;
        DisNum++;
        CurMachine = !CurMachine;
        PairList.push_back(vector<vector<int>>(1, vector<int>(1, s)));
        int i = 0;
        
        //printf("checkpoint 2");

        while(PairList[ListNum - 1][i].size() != 0){
            PairList[ListNum - 1].push_back(vector<int>{});
            int layerSize = PairList[ListNum - 1][i].size();
            for(int j = 0; j < layerSize; j++){
                int node = PairList[ListNum - 1][i][j];
                int AdjSize = Adj[node].size();
                for(int k = 0; k < AdjSize; k++){
                    int pair = Adj[node][k];
                    if(Discovered[pair] == 0){
                        Discovered[pair] = 1;
                        Machine[pair] = CurMachine;
                        DisNum++;
                        PairList[ListNum - 1][i+1].push_back(pair);

                        //printf("checkpoint 3");
                    }
                }
            }
            i++;
            CurMachine = !CurMachine;
        }
    }

    int result = 1;

    //printf("checkpoint 4");

    for(int i = 0; i < m; i++){
        if(Machine[edges[i][0]] == Machine[edges[i][1]]) result = 0;
    }

    printf("%d\n", result);
    if(result){
        for(int i = 0; i < n; i++){
            printf("%d\n", Machine[i] + 1);
        }
    }

    return 0;
}
