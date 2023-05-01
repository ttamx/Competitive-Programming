#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    if(n==1)return void(cout << "1\n");
    if(n&1)return void(cout << "-1\n");
    for(int i=n;i>0;i-=2)cout << i-1 << " " << i << " \n"[i==2];
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}