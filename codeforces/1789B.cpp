#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    string s;
    cin >> s;
    int l=0,r=n-1;
    int res=0,cnt=0;
    while(l<r){
        if(s[l]-48!=((s[r]-48)^res)){
            cnt++;
            res^=1;
            if(cnt>2)return void(cout << "No\n");
        }
        l++,r--;
    }
    cout << "Yes\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}