#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,x,y;
    cin >> n >> x >> y;
    if(x>y)swap(x,y);
    if(x>0){
        cout << -1 << '\n';
    }else if(y==0){
        cout << -1 << '\n';
    }else if((n-1)%y!=0){
        cout << -1 << '\n';
    }else{
        int val=2;
        for(int i=0;i<(n-1)/y;++i){
            for(int j=0;j<y;++j){
                cout << val << ' ';
            }
            val+=y;
        }
        cout << '\n';
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}

