#include <stdio.h>
#include <vector>

using namespace std;

int main(int argc, char *argv[]){
    //Read data from file to MPref, WPref, size
    int size, number;
    vector<vector<int>> MPref, WPref;

    scanf("%d", &size);

    for(int i = 0; i < size; i++){
        vector<int> numbers;
        for(int j = 0; j < size; j++){
            scanf("%d", &number);
            numbers.push_back(number);
        }
        MPref.push_back(numbers);
    }

    for(int i = 0; i < size; i++){
        vector<int> numbers;
        for(int j = 0; j < size; j++){
            scanf("%d", &number);
            numbers.push_back(number);
        }
        WPref.push_back(numbers);
    }

    //necesary containers
    vector<int> FreeMan, FreeMan_Q2; //list of Free men
    for(int i = size - 1; i >= 0; i--) {
        FreeMan.push_back(i);
        FreeMan_Q2.push_back(i);
    }

    vector<int> Next(size, 0), Next_Q2(size, 0); //list of next woman on the list
    Next_Q2[0] = 1;

    vector<int> WCurrent(size, -1), WCurrent_Q2(size, -1), MCurrent_Q2(size, -1);; //list of paired man for woman, -1 for single

    vector<vector<int>> WRanking(size, vector<int> (size, 0)), MRanking(size, vector<int> (size, 0));
    for(int i = 0; i < size; i++){  //rankings of each man for each woman's preference list
        for(int j = 0; j < size; j++){
            if(WPref[i][j] < size) WRanking[i][WPref[i][j]] = j;
        }
    }
    for(int i = 0; i < size; i++){  //rankings of each man for each woman's preference list
        for(int j = 0; j < size; j++){
            MRanking[i][MPref[i][j]] = j;
        }
    }

    //Gale-Shapley
    while(FreeMan.size() > 0){
        int Man = FreeMan[FreeMan.size() - 1];
        int Woman = MPref[Man][Next[Man]];
        if(WCurrent[Woman] == -1){
            WCurrent[Woman] = Man;
            Next[Man]++;
            FreeMan.pop_back();
        }else{
            if(WRanking[Woman][Man] < WRanking[Woman][WCurrent[Woman]]){
                FreeMan.pop_back();
                FreeMan.push_back(WCurrent[Woman]);
                WCurrent[Woman] = Man;
                Next[Man]++;
            }else{
                Next[Man]++;
            }
        }
    }

    //Gale-Shapley question 2
    while(FreeMan_Q2.size() > 0){
        int Man = FreeMan_Q2[FreeMan_Q2.size() - 1];
        if(Next_Q2[Man] >= size){
            FreeMan_Q2.pop_back();
            continue;
        }
        int Woman = MPref[Man][Next_Q2[Man]];
        if(WCurrent_Q2[Woman] == -1){
            WCurrent_Q2[Woman] = Man;
            Next_Q2[Man]++;
            FreeMan_Q2.pop_back();
            MCurrent_Q2[Man] = Woman;
        }else{
            if(WRanking[Woman][Man] < WRanking[Woman][WCurrent_Q2[Woman]]){
                FreeMan_Q2.pop_back();
                FreeMan_Q2.push_back(WCurrent_Q2[Woman]);
                MCurrent_Q2[WCurrent_Q2[Woman]] = -1;
                WCurrent_Q2[Woman] = Man;
                MCurrent_Q2[Man] = Woman;
                Next_Q2[Man]++;
            }else{
                Next_Q2[Man]++;
            }
        }
    }

    int WomanR = MPref[0][0];
    int ans;
    if(WCurrent_Q2[WomanR] == -1) ans = 1;
    else if(WRanking[WomanR][WCurrent_Q2[WomanR]] <= WRanking[WomanR][WCurrent[WomanR]]) ans = 3;
    else ans = 2;
    
    printf("%d\n%d\n", WCurrent[0], ans);

    return 0;
}