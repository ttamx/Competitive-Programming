#include<bits/stdc++.h>

using namespace std;

//FENWICK TREE
template<class T>
struct fenwick{
    const int n;
    vector<T> t;
    fenwick(int n):n(n+1),t(n+1){}
    void add(int i,T v){
        while(i<n)f[i]+=v,i+=i&-i;
    }
    T read(int i){
        T res=0;
        while(i)res+=f[i],i-=i&-i;
        return res;
    }
};
//--------------------------------------------------------

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);

}