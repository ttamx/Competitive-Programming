#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,k;
    cin >> n >> k;
    if(k<n/2||k==n){
        cout << -1;
        exit(0);
    }
    string ans="";
    if(n%4==0){
        k-=n/2;
        if(k%2==1){
            int r=n/2;
            int l=n/2-1;
            ans="(";
            while(k>2){
                ans="()"+ans+")(";
                k-=2;
                l-=2;
                r-=2;
            }
            while(r>0){
                ans=")"+ans+")";
                r-=2;
            }
            while(l>0){
                ans="("+ans;
                l--;
            }
        }else{
            int r=n/2-2;
            int l=n/2;
            ans="))";
            while(k>0){
                ans=")("+ans+"()";
                k-=2;
                l-=2;
                r-=2;
            }
            while(r>0){
                ans=")"+ans+")";
                r-=2;
            }
            while(l>0){
                ans="("+ans;
                l--;
            }
        }
    }else{
        k-=n/2;
        if(k%2==0){
            int r=n/2-1;
            int l=n/2;
            ans=")";
            while(k>0){
                ans=")("+ans+"()";
                k-=2;
                l-=2;
                r-=2;
            }
            while(r>0){
                ans=")"+ans+")";
                r-=2;
            }
            while(l>0){
                ans="("+ans;
                l--;
            }
        }else{
            k++;
            int r=n/2;
            int l=n/2;
            ans="";
            while(k>0){
                ans=")("+ans+"()";
                k-=2;
                l-=2;
                r-=2;
            }
            while(r>2){
                ans=")"+ans+")";
                r-=2;
            }
            ans=ans+")";
            while(l>0){
                ans="("+ans;
                l--;
            }
        }
    }
    cout << ans;
}