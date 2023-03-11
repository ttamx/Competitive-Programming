#include<bits/stdc++.h>

using namespace std;

struct item{
	int idx,prio;
	char c;
	item *l,*r;
	item(){};
	item(int idx,char c):idx(idx),prio(rand()),c(c){};
};
typedef item* pitem;

void split(pitem t,pitem &l,pitem &r,int idx){
	if(t==nullptr)l=r=t;
	else if(t->idx<=idx)split(t->r,t->r,r,idx),l=t;
	else split(t->l,l,t->l,idx),r=t;
}

void merge(pitem &t,pitem l,pitem r){
	if(l==nullptr)t=r;
	else if(r==nullptr)t=l;
	else if(l->prio>r->prio)merge(l->r,l->r,r),t=l;
	else merge(r->l,l,r->l),t=r;
}

void dfs(pitem u){
	if(u->l)dfs(u->l);
	cout << u->c;
	if(u->r)dfs(u->r);
}

void rdfs(pitem u){
	if(u->r)dfs(u->r);
	cout << u->c;
	if(u->l)dfs(u->l);
}

int main(){
	cin.tie(nullptr)->sync_with_stdio(false);
	string str;
	cin >> str;
	int n=str.size();
	pitem root=new item(1,str[0]);
	for(int i=1;i<n;i++){
		merge(root,root,new item(i+1,str[i]));
	}
	bool rev=false;
	int q;
	cin >> q;
	while(q--){
		char o;
		cin >> o;
		if(o=='I'){
			int idx;
			cin >> idx;
			string s;
			cin >> s;
			pitem l=nullptr,r=nullptr;
			split(root,l,r,idx);
			for(int i=0;i<s.size();i++){
				merge(l,l,new item(i+1,s[i]));
			}
			merge(root,l,r);
		}
	}
	dfs(root);
}