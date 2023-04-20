#include<bits/stdc++.h>

using namespace std;

int ask(int x,int y){
    cout << "? " << x << " " << y << endl;
    int res;
    cin >> res;
    return res;
}

void runcase(){
    int n,m;
    cin >> n >> m;
    int a=ask(1,1),b=ask(n,1);
    if(a+b!=n-1&&a!=b){
        int x=a+1,y=b+1;
        if(b>a)x=n-b,y=a+1;
        cout << "! " << x << " " << y << endl;
    }else if(a+b==n-1){
        int x=a+1;
        int y=ask(x,1)+1;
        cout << "! " << x << " " << y << endl;
    }else{
        int y=a+1;
        int x=ask(1,y)+1;
        cout << "! " << x << " " << y << endl;
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}