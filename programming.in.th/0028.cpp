#include<bits/stdc++.h>

using namespace std;

struct Info{
    string name;
    int score,win,loss;
    friend bool operator<(Info lhs,Info rhs){
        if(lhs.score!=rhs.score){
            return lhs.score>rhs.score;
        }
        if(lhs.win-lhs.loss!=rhs.win-rhs.loss){
            return lhs.win-lhs.loss>rhs.win-rhs.loss;
        }
        return lhs.win>rhs.win;
    }
};

Info teams[4];

int points[4][4];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    for(int i=0;i<4;i++){
        cin >> teams[i].name;
    }
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            cin >> points[i][j];
        }
    }
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(i==j){
                continue;
            }
            teams[i].win+=points[i][j];
            teams[j].loss+=points[i][j];
            if(points[i][j]>points[j][i]){
                teams[i].score+=3;
            }else if(points[i][j]==points[j][i]){
                teams[i].score+=1;
            }
        }
    }
    cout << (teams[0]<teams[1]);
    sort(teams,teams+4);
    for(int i=0;i<4;i++){
        cout << teams[i].name << " " << teams[i].score << "\n";
    }
}