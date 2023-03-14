#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,b,a;
    cin >> n >> b >> a;
    int c=a;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        if(x==1&&b>0&&a<c){
            b--;
            a++;
        }else if(a>0){
            a--;
        }else if(b>0){
            b--;
        }else{
            return void(cout << i);
        }
    }
    cout << n;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}