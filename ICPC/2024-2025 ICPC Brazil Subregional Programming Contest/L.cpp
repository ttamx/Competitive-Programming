#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    int cnt[30]={};
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        for(int j=0;j<30;j++){
            if(x>>j&1){
                cnt[j]++;
            }
        }
    }
    for(int i=0;i<n;i++){
        int x=0;
        for(int j=0;j<30;j++){
            if(cnt[j]){
                cnt[j]--;
                x|=1<<j;
            }
        }
        cout << x << " ";
    }
}