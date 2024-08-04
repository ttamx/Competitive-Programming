#include<bits/stdc++.h>

using namespace std;

int main(){
    int n;
    cin >> n;
    function<int(int,int)> calc=[&](int x,int y){
        if(y==0)return 0;
        int c=x/y;
        return (c&1)^calc(y,x-y*c);
    };
    auto grundy=[&](int x,int y){
        return calc(x,y)^calc(x,y-1)^calc(x-1,y)^calc(x-1,y-1);
    };
    int cur=0;
    for(int i=0;i<n;i++){
        int x,y;
        cin >> x >> y;
        cur^=grundy(x,y);
    }
    cout << (cur?"FIRST":"SECOND") << "\n";
}