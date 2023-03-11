#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<int> odd,even;
    int st=0;
    for(int i=1;i<=n;++i){
        int x;
        cin >> x;
        if(i==1)st=x%2;
        if(x%2==0)even.emplace_back(i);
        else odd.emplace_back(i);
    }
    if(st==0){
        int fi=even[even.size()-1];
        int se=even[0];
        even.pop_back();
        reverse(even.begin(),even.end());
        cout << n-1 << '\n';
        for(auto x:even){
            cout << x << " " << fi << '\n';
        }
        for(auto x:odd){
            cout << se << " " << x << '\n';
        }
    }else{
        int fi=odd[odd.size()-1];
        int se=odd[0];
        odd.pop_back();
        reverse(odd.begin(),odd.end());
        cout << n-1 << '\n';
        for(auto x:odd){
            cout << x << " " << fi << '\n';
        }
        for(auto x:even){
            cout << se << " " << x << '\n';
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
