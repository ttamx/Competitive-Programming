#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    int c1=0,c2=0,c3=0;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        if(x!=i+1&&x!=n-i)c3++;
        else if(x!=i+1)c1++;
        else if(x!=n-i)c2++;
    }
    if(c1+c3<=c2)cout << "First\n";
    else if(c2+c3<c1)cout << "Second\n";
    else cout << "Tie\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();
}