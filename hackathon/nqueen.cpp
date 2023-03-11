#include<bits/stdc++.h>

using namespace std;

const int N=1005;

int n;
bool done;
bool a[N][N];
bool c[N],x[2*N],y[2*N];

void sol(int i){
    if(i==n||done)return void(done=true);
    for(int j=0;j<n;j++){
        if(c[j]||x[i+j]||y[N+j-i])continue;
        c[j]=true;
        x[i+j]=true;
        y[N+j-i]=true;
        a[i][j]=true;
        sol(i+1);
        if(done)return;
        c[j]=false;
        x[i+j]=false;
        y[N+j-i]=false;
        a[i][j]=false;
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    sol(0);
    if(done){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                cout << a[i][j] << ' ';
            }
            cout << '\n';
        }
    }else{
        cout << "None";
    }
}