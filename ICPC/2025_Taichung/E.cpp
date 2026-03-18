#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        string s;
        cin >> s;
        auto get=[&](){
            int k;
            cin >> k;
            k--;
            string t=s;
            for(int i=0;i<k;i++){
                next_permutation(t.begin(),t.end());
            }
            return t;
        };
        int n=s.size();
        auto a=get();
        auto b=get();
        int x=0,y=0;
        bool ok[4]={};
        for(int i=0;i<n;i++){
            if(a[i]==b[i]){
                x++;
            }else{
                if(ok[a[i]-'1'])y++;
                if(ok[b[i]-'1'])y++;
                ok[a[i]-'1']=true;
                ok[b[i]-'1']=true;
            }
        }
        cout << x << "A" << y << "B\n";
    }
}