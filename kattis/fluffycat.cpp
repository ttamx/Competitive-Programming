#include<bits/stdc++.h>

using namespace std;

const int X=1e6;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    vector<int> cnt(X+1);
    for(int i=-1000;i<=1000;i++){
        for(int j=-1000;j<=1000;j++){
            int x=i*i+j*j;
            if(x<=X)cnt[x]++;
        }
    }
    int id=max_element(cnt.begin(),cnt.end())-cnt.begin();
    cout << id << "\n";
}