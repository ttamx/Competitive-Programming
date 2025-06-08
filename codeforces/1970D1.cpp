#include<bits/stdc++.h>

using namespace std;

mt19937 rng(0);

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    vector<string> vec;
    map<int,pair<int,int>> ans;
    while(true){
        vector<string> v(3,string(30,'X'));
        for(auto &x:v){
            for(auto &c:x){
                if(rng()&1){
                    c='O';
                }
            }
        }
        map<int,pair<int,int>> mp;
        for(int x=0;x<3;x++){
            for(int y=0;y<3;y++){
                string s=v[x]+v[y];
                set<string> st;
                for(int i=0;i<s.size();i++){
                    for(int j=1;i+j<=s.size();j++){
                        st.emplace(s.substr(i,j));
                    }
                }
                mp[(int)st.size()]={x,y};
            }
        }
        if(mp.size()==9){
            vec=v;
            ans=mp;
            break;
        }
    }
    int n;
    cin >> n;
    for(int i=0;i<n;i++){
        cout << vec[i] << endl;
    }
    int q;
    cin >> q;
    while(q--){
        int x;
        cin >> x;
        cout << ans[x].first+1 << " " << ans[x].second+1 << endl;
    }
}