#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    for(int i=0;i<=n;i++){
        char c='-';
        for(int j=1;j<=9;j++){
            if(n%j!=0)continue;
            if(i%(n/j)==0){
                c='0'+j;
                break;
            }
        }
        cout << c;
    }
}