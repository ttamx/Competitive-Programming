#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    string s;
    cin >> s;
    vector<int> a;
    reverse(s.begin(),s.end());
    int carry=0;
    for(auto x:s){
        carry+=(x-'0')*9;
        a.emplace_back(carry%10);
        carry/=10;
    }
    if(carry>0){
        assert(carry<=9);
        a.emplace_back(carry);
    }
    int sum=accumulate(a.begin(),a.end(),0);
    for(int i=0;;i++){
        if(sum<=i*9){
            cout << i << "\n";
            exit(0);
        }
        carry=9;
        for(int j=0;carry>0;j++){
            if(j==a.size()){
                a.emplace_back(0);
            }
            sum-=a[j];
            a[j]+=carry;
            carry=a[j]/10;
            a[j]%=10;
            sum+=a[j];
        }
    }
}