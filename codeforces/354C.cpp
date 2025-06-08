#include<bits/stdc++.h>

using namespace std;

const int N=1e6+5;

int n,k;
int cnt[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        cnt[x]++;
    }
    for(int i=1;i<N;i++)cnt[i]+=cnt[i-1];
    for(int i=N-1;i>=1;i--){
        int cur=0;
        for(int j=i;j<N;j+=i){
            cur+=cnt[min(j+min(k,i-1),N-1)]-cnt[j-1];
        }
        if(cur==n){
            cout << i << "\n";
            exit(0);
        }
    }
    assert(false);
}