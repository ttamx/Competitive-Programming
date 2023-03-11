#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    int i=0,j=n-1,ans=0;
    while(i<j){
        while(a[i]==0&&i<j)i++;
        while(a[j]==1&&i<j)j--;
        if(i<j)ans++,i++,j--;
    }
    cout << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();   
}