#include<iostream>
#include<vector>
#include<sstream>
#include<unordered_map>
#include<queue>


using namespace std;

int main(){
    ios::sync_with_stdio(false);

    int n, k;
    cin>>n>>k;
    vector<unordered_map<int, vector<int>>> edges(n + k + 2, unordered_map<int, vector<int>>{});
    //edge[n + k] : t, edge[n + k + 1] : s
    string edgeIn;
    int num;
    for(int i = 0; i < n; i++){
        edges[n + k + 1][i] = {1, 0};
    }
    for(int i = -1; i < n; i++){
        getline(cin, edgeIn);
        istringstream iss(edgeIn);
        while(iss >> num){
            //cout<<num;
            edges[i][num] = {1, 0};
        }
    }
    for(int i = n; i < n + k; i++){
        cin>>num;
        edges[i][n + k] = {num, 0};
    }
    for(int i = 0; i < n - 1; i++){
        cin>>num;
        edges[n + k + 1][i][1] = 1;
        edges[i][num][1] = 1;
        edges[num][n + k][1]++;
    }

    queue<int> q;
    q.push(n + k + 1);
    while(!q.empty()){
        for(auto& pr : edges[q.front()]){
            if(pr.second[0] > pr.second[1]){
                q.push(pr.first);
            }
        }
        q.pop();
    }



    cout<<"find!";
    return 0;
}