#include<iostream>
#include<vector>
#include<sstream>
#include<unordered_map>
#include<unordered_set>
#include<queue>
#include<algorithm>
#include <climits>


using namespace std;

int main(){
    ios::sync_with_stdio(false);

    int n, k;
    cin>>n>>k;
    vector<unordered_map<int, vector<int>>> edges(n + k + 2, unordered_map<int, vector<int>>{});
    vector<vector<unordered_set<int>>> residual(n + k + 2, vector<unordered_set<int>>(2, unordered_set<int>{}));//[0] forward, [1] backward
    //edge[n + k] : t, edge[n + k + 1] : s
    string edgeIn;
    int num;
    for(int i = 0; i < n; i++){
        edges[n + k + 1][i] = {1, 0};
        residual[n + k + 1][0].insert(i);
        residual[i][1].insert(n + k + 1);
    }
    for(int i = -1; i < n; i++){
        getline(cin, edgeIn);
        istringstream iss(edgeIn);
        while(iss >> num){
            //cout<<num;
            edges[i][num] = {1, 0};
            residual[i][0].insert(num);
            residual[num][1].insert(i); 
        }
    }
    for(int i = n; i < n + k; i++){
        cin>>num;
        if(num > 0){
            edges[i][n + k] = {num, 0};
            residual[i][0].insert(n + k);
            residual[n + k][1].insert(i);
        }
    }
    for(int i = 0; i < n - 1; i++){
        cin>>num;
        edges[n + k + 1][i][1] = 1;
        residual[n + k + 1][0].erase(i);
        residual[i][1].erase(n + k + 1);
        residual[i][0].insert(n + k + 1);
        residual[n + k + 1][1].insert(i);
        edges[i][num][1] = 1;
        residual[i][0].erase(num);
        residual[num][1].erase(i);
        residual[num][0].insert(i);
        residual[i][1].insert(num);
        edges[num][n + k][1]++;
        if(residual[n + k][0].find(num) == residual[n + k][0].end()){
            residual[n + k][0].insert(num);
            residual[num][1].insert(n + k);
        }
        if(edges[num][n + k][1] == edges[num][n + k][0]){
            residual[num][0].erase(n + k);
            residual[n + k][1].erase(num);
        }
    }

    queue<vector<int>> qF, qB;
    vector<int> pathF, pathB;
    vector<bool> searchedF, searchedB;
    do{
        if(pathF.size() != 0){
            for(int i = 1; i < pathF.size() - 1; i++){
                if(edges[pathF[i]].find(pathF[i + 1]) == edges[pathF[i]].end()){
                    edges[pathF[i + 1]][pathF[i]][1] -= pathF[0];
                    if(residual[pathF[i + 1]][0].find(pathF[i]) == residual[pathF[i + 1]][0].end()){
                        residual[pathF[i + 1]][0].insert(pathF[i]);
                        residual[pathF[i]][1].insert(pathF[i + 1]);
                    }
                    if(edges[pathF[i + 1]][pathF[i]][1] == 0){
                        residual[pathF[i]][0].erase(pathF[i + 1]);
                        residual[pathF[i + 1]][1].erase(pathF[i]);
                    }
                }else{
                    edges[pathF[i]][pathF[i + 1]][1] += pathF[0];
                    if(residual[pathF[i + 1]][0].find(pathF[i]) == residual[pathF[i + 1]][0].end()){
                        residual[pathF[i + 1]][0].insert(pathF[i]);
                        residual[pathF[i]][1].insert(pathF[i + 1]);
                    }
                    if(edges[pathF[i]][pathF[i + 1]][1] == edges[pathF[i]][pathF[i + 1]][0]){
                        residual[pathF[i]][0].erase(pathF[i + 1]);
                        residual[pathF[i + 1]][1].erase(pathF[i]);
                    }
                }
            }

        }

        qF = queue<vector<int>>();
        qB = queue<vector<int>>();
        pathF = vector<int>();
        pathB = vector<int>();
        qF.push(vector<int>{INT_MAX, n + k + 1});
        qB.push(vector<int>{INT_MAX, n + k});
        searchedF = vector<bool>(n + k + 2, false);
        searchedB = vector<bool>(n + k + 2, false);
        searchedF[n + k + 1] = true;
        searchedB[n + k] = true;
        while(!qB.empty() && !qF.empty()){
            if(qF.size() <= qB.size()){
                int n = qF.size();
                for(int i = 0; i < n; i++){
                    for(auto& pr : residual[qF.front().back()][0]){
                        if(searchedF[pr]) continue;
                        qF.push(qF.front());
                        qF.back().push_back(pr);
                        if(edges[qF.front().back()].find(pr) == edges[qF.front().back()].end()){//reverse edge
                            qF.back().front() = min(qF.back().front(), edges[pr][qF.front().back()][1]);
                        }else{
                            qF.back().front() = min(qF.back().front(), edges[qF.front().back()][pr][0] - edges[qF.front().back()][pr][1]);
                        }
                        if(searchedB[pr]){
                            pathF = qF.back();
                            while(qB.front().back() != pr) qB.pop();
                            pathB = qB.front();
                            reverse(pathB.begin(), pathB.end());
                            pathF.insert(pathF.end(), pathB.begin() + 1, pathB.end() - 1);
                            pathF[0] = min(pathF[0], pathB.back());
                            qF = queue<vector<int>>();
                            break;
                        }
                        searchedF[pr] = true;
                    }
                    if(!qF.empty())qF.pop();
                    else break;
                }
            }else{
                int n = qB.size();
                for(int i = 0; i < n; i++){
                    for(auto& pr : residual[qB.front().back()][1]){
                        if(searchedB[pr]) continue;
                        qB.push(qB.front());
                        qB.back().push_back(pr);
                        if(edges[pr].find(qB.front().back()) == edges[pr].end()){//reverse edge
                            qB.back().front() = min(qB.back().front(), edges[qB.front().back()][pr][1]);
                        }else{
                            qB.back().front() = min(qB.back().front(), edges[pr][qB.front().back()][0] - edges[pr][qB.front().back()][1]);
                        }
                        if(searchedF[pr]){
                            pathB = qB.back();
                            while(qF.front().back() != pr) qF.pop();
                            pathF = qF.front();
                            reverse(pathB.begin(), pathB.end());
                            pathF.insert(pathF.end(), pathB.begin() + 1, pathB.end() - 1);
                            pathF[0] = min(pathF[0], pathB.back());
                            qB = queue<vector<int>>();
                            break;
                        }
                        searchedB[pr] = true;
                    }
                    if(!qB.empty())qB.pop();
                    else break;
                }
            }
            
        }
    }while(pathF.size() != 0);

    vector<int> res(n, -1);
    int rNum = 0;
    for(int i = n; i < n + k; i++){
        for(auto p : residual[i][0]){
            if(p != n + k){
                res[p] = i;
                rNum++;
            }
        }
    }
    if(rNum == n){
        cout<<"Yes\n";
        for(int i = 0; i < n - 1; i++) cout<<res[i]<<' ';
        cout<<res[n - 1]<<"\n";
    }else{
        vector<int> inc(k, 0);
        if(rNum == n - 1){
            for(int CapInc = n; CapInc < n + k; CapInc++){
                if(residual[CapInc][0].find(n + k) != residual[CapInc][0].end()) continue;
                residual[CapInc][0].insert(n + k);
                residual[n + k][1].insert(CapInc);

                qF = queue<vector<int>>();
                qB = queue<vector<int>>();
                pathF = vector<int>();
                pathB = vector<int>();
                qF.push(vector<int>{n + k + 1});
                qB.push(vector<int>{CapInc});
                searchedF = vector<bool>(n + k + 2, false);
                searchedB = vector<bool>(n + k + 2, false);
                searchedF[n + k + 1] = true;
                searchedB[n + k] = true;
                searchedB[CapInc] = true;
                while(!qB.empty() && !qF.empty()){
                    if(qF.size() <= qB.size()){
                        int n1 = qF.size();
                        for(int i = 0; i < n1; i++){
                            for(auto& pr : residual[qF.front().back()][0]){
                                if(searchedF[pr]) continue;
                                qF.push(qF.front());
                                qF.back().push_back(pr);
                                if(searchedB[pr]){
                                    inc[CapInc - n] = 1;
                                    qF = queue<vector<int>>();
                                    break;
                                }
                                searchedF[pr] = true;
                            }
                            if(!qF.empty())qF.pop();
                            else break;
                        }
                    }else{
                        int n1 = qB.size();
                        for(int i = 0; i < n1; i++){
                            for(auto& pr : residual[qB.front().back()][1]){
                                if(searchedB[pr]) continue;
                                qB.push(qB.front());
                                qB.back().push_back(pr);
                                if(searchedF[pr]){
                                    inc[CapInc - n] = 1;
                                    qB = queue<vector<int>>();
                                    break;
                                }
                                searchedB[pr] = true;
                            }
                            if(!qB.empty())qB.pop();
                            else break;
                        }
                    }
                    
                }
                residual[CapInc][0].erase(n + k);
                residual[n + k][1].erase(CapInc);
            }
        }
        cout<<"No\n";
        for(int i = 0; i < k - 1; i++) cout<<inc[i]<<' ';
        cout<<inc[k - 1]<<"\n";
    }
    return 0;
}