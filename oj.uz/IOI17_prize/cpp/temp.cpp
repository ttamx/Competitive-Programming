#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int res=0,cur=0,cnt=0;
    while(true){
        cur*=cur;
        cur++;
        res+=cur;
        cnt++;
        cerr << cur << "\n";
        if(res>2e5){
            cout << cnt-1 << "\n";
            return;
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}