#include<bits/stdc++.h>

using namespace std;

using ll = long long;

void runcase(){
    int n,m,d1,d2;
    cin >> n >> m >> d1 >> d2;
    vector<string> a(n);
    for(auto &x:a){
        cin >> x;
    }
    for(auto &v:a){
        for(auto &x:v){
            if(x=='.')x='0';
        }
    }
    auto work=[&](int i,int j,int v){
        if(i<0||i>=n||j<0||j>=m||a[i][j]=='V')return;
        a[i][j]=max(a[i][j],char(v+'0'));
    };
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(a[i][j]=='V'){
                for(int dx=-1;dx<=1;dx++){
                    for(int dy=-1;dy<=1;dy++){
                        work(i+dx,j+dy,(abs(dx)+abs(dy)==2?d2:d1));
                    }
                }
            }
        }
    }
    for(auto x:a){
        cout << x << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    for(int i=1;i<=t;i++){
        cout << "Airplane #" << i << ":\n";
        runcase();
    }
}