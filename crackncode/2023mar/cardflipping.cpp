#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    a.emplace_back(0);
    stack<int> st;
    for(int i=0;i<n;i++){
        if(a[i]==1){
            cout << i+1 << ' ';
            while(!st.empty()){
                cout << st.top()+1 << ' ';
                st.pop();
            }
            a[i+1]^=1;
        }else{
            st.emplace(i);
        }
    }
}