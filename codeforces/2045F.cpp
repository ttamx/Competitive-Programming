#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,m,k;
    cin >> n >> m >> k;
    k++;
    vector<int> nim(k);
    for(int i=0;i<m;i++){
        int x,y,w;
        cin >> x >> y >> w;
        nim[x%k]^=w%k;
    }
    for(auto x:nim){
        if(x){
            cout << "Anda\n";
            return;
        }
    }
    cout << "Kamu\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}