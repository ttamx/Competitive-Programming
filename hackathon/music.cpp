#include<bits/stdc++.h>

using namespace std;

const int N=1005;

int a,b,cnt;
bool f[5];
array<char,4> c;
vector<array<char,4>> ans;

void sol(int i,int j){
    if(i<0)return;
    if(j>3){
        if(i==0){
            cnt++;
            for(int x=0;x<4;x++)cout << c[x] << ' ';
            cout << '\n';
        }
        return;
    }
    if(!f[j])return sol(i,j+1);
    if(i>=8){
        c[j]='W';
        sol(i-8,j+1);
    }
    if(i>=4){
        c[j]='H';
        sol(i-4,j+1);
    }
    if(i>=2){
        c[j]='Q';
        sol(i-2,j+1);
    }
    if(i>=1){
        c[j]='E';
        sol(i-1,j+1);
    }
    c[j]='-';
    sol(i,j+1);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> a >> b;
    a*=(8/b);
    for(int i=0;i<4;i++){
        cin >> c[i];
        if(c[i]=='W')a-=8;
        if(c[i]=='H')a-=4;
        if(c[i]=='Q')a-=2;
        if(c[i]=='E')a-=1;
        if(c[i]=='X')f[i]=true;
    }
    sol(a,0);
    if(cnt==0)cout << "Impossible";
}