#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    set<int> s,s2;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        if(x%10==0)s.insert(x);
        else if(x%5==0)s.insert(x+5);
        else{
            while(x%10!=2)x+=x%10;
            s2.insert((x/10)%2);
        }
    }
    if(s.size()+s2.size()>1)cout << "No\n";
    else cout << "Yes\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}