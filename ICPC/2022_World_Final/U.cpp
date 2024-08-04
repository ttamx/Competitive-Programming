#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int s,c;
    cin >> s >> c;
    s/=2,c/=2;
    if(s==0){
        c/=2;
        if(c<3){
            cout << "LLLL";
        }else{
            int n=c-3;
            for(int t=0;t<2;t++){
                cout << "RLRRLR";
                for(int i=0;i<n;i++)cout << "RL";
            }
        }
    }else{
        s--;
        if(c%2==0){
            int n=c/2-1;
            for(int t=0;t<2;t++){
                cout << "RRS";
                for(int i=0;i<s;i++)cout << "S";
                for(int i=0;i<n;i++)cout << "RL";
            }
        }else{
            int n=(c-3)/2;
            cout << "RLRRS";
            for(int i=0;i<s;i++)cout << "S";
            for(int i=0;i<n;i++)cout << "RL";
            cout << "RSR";
            for(int i=0;i<s;i++)cout << "S";
            for(int i=0;i<n;i++)cout << "RL";
        }
    }
}