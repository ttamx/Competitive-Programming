#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int ans=0;
    for(int i=2;i<1000;i++)if(i%3==0||i%5==0||i%7==0)ans++;
    cout << ans;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}