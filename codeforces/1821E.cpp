#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int k;
    string s;
    cin >> k >> s;
    vector<int> a,st{0};
    for(auto x:s){
        if(x=='('){
            st.back()++;
            st.emplace_back(0);
        }else{
            int v=st.back();
            st.pop_back();
            a.emplace_back(v);
            st.back()+=v;
        }
    }
    sort(a.begin(),a.end());
    while(k--&&!a.empty())a.pop_back();
    cout << accumulate(a.begin(),a.end(),0LL) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}