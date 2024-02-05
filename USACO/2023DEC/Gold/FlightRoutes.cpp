#include<bits/stdc++.h>

using namespace std;

const int N=755;

int n,ans;
bitset<N> a[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=0;i<n-1;i++){
        string s;
        cin >> s;
        for(int j=i+1;j<n;j++)a[i][j]=s[j-i-1]-'0';
    }
    for(int i=n-2;i>=0;i--){
        auto b=a[i];
        for(int j=i+1;j<n;j++){
            if(b[j]){
                b^=a[j];
                ans++;
            }
        }
    }
    cout << ans;
}