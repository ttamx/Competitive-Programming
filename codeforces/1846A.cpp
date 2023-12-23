#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int cnt=0;
    int n;
    cin >> n;
    for(int i=0;i<n;i++){
        int a,b;
        cin >> a >> b;
        if(a>b)cnt++;
    }
    cout << cnt << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}