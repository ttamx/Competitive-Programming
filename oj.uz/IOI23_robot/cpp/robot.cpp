#include "robot.h"
#include<bits/stdc++.h>

using namespace std;

const int BLANK=0;
const int PATH=1;
const int WEST=2;
const int SOUTH=3;
const int EAST=4;
const int NORTH=5;

string dir_char="WSENTH";
int dir_col[4]={WEST,SOUTH,EAST,NORTH};

int getDir(int col){
    return col>=2?col-2:-1;
}

void solve(vector<int> state,int &next_col,int &next_dir){
    bool is_start=state[1]==-2&&state[4]==-2;
    bool is_end=state[2]==-2&&state[3]==-2;
    int cur_dir=getDir(state[0]);
    if(cur_dir!=-1){
        bool cleanup=state[cur_dir+1]!=BLANK&&getDir(state[cur_dir+1])!=(cur_dir^2);
        if(!cleanup){
            for(int i=1;i<=4;i++){
                int new_dir=(cur_dir+i)%4;
                if(state[new_dir+1]==BLANK||getDir(state[new_dir+1])==(new_dir^2)){
                    next_col=dir_col[new_dir];
                    next_dir=new_dir;
                    return;
                }
            }
            return;
        }
        for(int i=1;i<=4;i++){
            int new_dir=(cur_dir+i)%4;
            if(getDir(state[new_dir+1])==(new_dir^2)){
                next_dir=new_dir;
                return;
            }
        }
        bool fillup=is_start;
        for(int i=1;i<=4;i++)if(state[i]==PATH)fillup=true;
        if(fillup){
            next_col=PATH;
            next_dir=is_end?4:cur_dir;
            return;
        }
        next_col=BLANK;
        next_dir=cur_dir;
        return;
    }
    if(is_start){
        next_col=state[2]==BLANK?SOUTH:EAST;
        next_dir=state[2]==BLANK?1:2;
        return;
    }
    if(is_end){
        next_col=EAST;
        return;
    }
    for(int new_dir=0;new_dir<4;new_dir++){
        if(getDir(state[new_dir+1])==(new_dir^2)){
            next_col=dir_col[new_dir];
            next_dir=new_dir;
            return;
        }
    }
}

void program_pulibot(){
    for(int c=0;c<=5;c++){
        for(int w=-2;w<=5;w++){
            for(int s=-2;s<=5;s++){
                for(int e=-2;e<=5;e++){
                    for(int n=-2;n<=5;n++){
                        vector<int> state={c,w,s,e,n};
                        int next_col=c,next_dir=5;
                        solve(state,next_col,next_dir);
                        set_instruction(state,next_col,dir_char[next_dir]);
                    }
                }
            }
        }
    }
};