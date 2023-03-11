#include<bits/stdc++.h>

using namespace std;

int query(int x,int y){
    cout << "? " << x << " " << y << endl;
    int res;
    cin >> res;
    return res;
}

void runcase(){
    int n;
    cin >> n;
    int x=1,y=2;
    int q=query(x,y);
    for(int i=3;i<=n;i++){
        int q1=query(i,x);
        int q2=query(i,y);
        if(q1>=q&&q1>=q2){
            q=q1;
            y=i;
        }else if(q2>=q&&q2>=q1){
            q=q2;
            x=i;
        }
    }
    cout << "! " << x << " " << y << endl;
    cin >> n;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();
}