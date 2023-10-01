#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    int cnt=0;
    int st;
    cin >> st;
    cout << 1;
    int pre=st;
    for(int i=1;i<n;i++){
        int x;
        cin >> x;
        if(cnt>1){
            cout << 0;
            continue;
        }
        if(x>=pre){
            if(cnt==0){
                cout << 1;
                pre=x;
            }else if(x<=st){
                cout << 1;
                pre=x;
            }else{
                cout << 0;
            }
        }else if(x<=st&&cnt==0){
            cnt++;
            cout << 1;
            pre=x;
        }else{
            cout << 0;
        }
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}