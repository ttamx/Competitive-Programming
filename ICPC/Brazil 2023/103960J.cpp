#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> c(14,4);
    int a=0,b=0;
    for(int t=0;t<2;t++){
        int x;
        cin >> x;
        a+=min(x,10);
        c[x]--;
    }
    for(int t=0;t<2;t++){
        int x;
        cin >> x;
        b+=min(x,10);
        c[x]--;
    }
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        c[x]--;
        a+=min(x,10);
        b+=min(x,10);
    }
    for(int i=1;i<=13;i++){
        if(c[i]==0)continue;
        if(b+min(i,10)>23)break;
        if(b+min(i,10)==23||a+min(i,10)>23){
            cout << i << "\n";
            exit(0);
        }
    }
    cout << "-1\n";
}