#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    int cnt=0;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        cnt+=x&1;
    }
    cout << (cnt&1?"NO":"YES") << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}