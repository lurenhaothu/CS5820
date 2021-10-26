#include<iostream>
#include<vector>
#include<sstream>
#include<unordered_map>
#include<unordered_set>
#include<queue>
#include<algorithm>
#include<climits>


using namespace std;

int main(){
    ios::sync_with_stdio(false);

    int n, k;
    cin>>n>>k;
    vector<unordered_map<int, vector<int>>> edges(n + k + 2, unordered_map<int, vector<int>>{});
    vector<unordered_set<int>> residual(n + k + 2, unordered_set<int>{});//[0] forward, [1] backward
    //edge[n + k] : t, edge[n + k + 1] : s
    string edgeIn;
    int num;
    for(int i = 0; i < n; i++){
        edges[n + k + 1][i] = {1, 0};
        residual[n + k + 1].insert(i);
    }
    for(int i = -1; i < n; i++){
        getline(cin, edgeIn);
        istringstream iss(edgeIn);
        while(iss >> num){
            //cout<<num;
            edges[i][num] = {1, 0};
            residual[i].insert(num);
        }
    }
    for(int i = n; i < n + k; i++){
        cin>>num;
        if(num > 0){
            edges[i][n + k] = {num, 0};
            residual[i].insert(n + k);
        }
    }
    for(int i = 0; i < n - 1; i++){
        cin>>num;
        edges[n + k + 1][i][1] = 1;
        residual[n + k + 1].erase(i);
        residual[i].insert(n + k + 1);
        edges[i][num][1] = 1;
        residual[i].erase(num);
        residual[num].insert(i);
        edges[num][n + k][1]++;
        if(residual[n + k].find(num) == residual[n + k].end()){
            residual[n + k].insert(num);
        }
        if(edges[num][n + k][1] == edges[num][n + k][0]){
            residual[num].erase(n + k);
        }
    }

    queue<vector<int>> q;
    vector<int> path;
    vector<bool> searched(n + k + 2, false);
    bool matched = false;
    vector<int> inc(k, 0);

    q.push(vector<int>{INT_MAX, n + k + 1});
    searched[n + k + 1] = true;
    while(!q.empty()){
        int p = q.front().back();
        for(auto& pr : residual[p]){
            if(searched[pr]) continue;
            q.push(q.front());
            q.back().push_back(pr);
            if(edges[p].find(pr) == edges[p].end()){//reverse edge
                q.back().front() = min(q.back().front(), edges[pr][p][1]);
            }else{
                q.back().front() = min(q.back().front(), edges[p][pr][0] - edges[p][pr][1]);
            }
            if(pr == n + k){
                path = q.back();
                matched = true; 
            }else if(pr >= n && pr < n + k) inc[pr - n] = 1;
            searched[pr] = true;
        }
        q.pop();
    }

    
    if(matched){
        for(int i = 1; i < path.size() - 1; i++){
            if(edges[path[i]].find(path[i + 1]) == edges[path[i]].end()){
                edges[path[i + 1]][path[i]][1] -= path[0];
                if(residual[path[i + 1]].find(path[i]) == residual[path[i + 1]].end()){
                    residual[path[i + 1]].insert(path[i]);
                }
                if(edges[path[i + 1]][path[i]][1] == 0){
                    residual[path[i]].erase(path[i + 1]);
                }
            }else{
                edges[path[i]][path[i + 1]][1] += path[0];
                if(residual[path[i + 1]].find(path[i]) == residual[path[i + 1]].end()){
                    residual[path[i + 1]].insert(path[i]);
                }
                if(edges[path[i]][path[i + 1]][1] == edges[path[i]][path[i + 1]][0]){
                    residual[path[i]].erase(path[i + 1]);
                }
            }
        }
        vector<int> res(n, -1);
        for(int i = n; i < n + k; i++){
            for(auto p : residual[i]){
                if(p != n + k){
                    res[p] = i;
                }
            }
        }
        cout<<"Yes\n";
        for(int i = 0; i < n - 1; i++) cout<<res[i]<<' ';
        cout<<res[n - 1]<<"\n";
    }else{
        cout<<"No\n";
        for(int i = 0; i < k - 1; i++) cout<<inc[i]<<' ';
        cout<<inc[k - 1]<<"\n";
    }
    return 0;
}