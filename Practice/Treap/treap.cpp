#include <bits/stdc++.h>

using namespace std;

struct item{
	int key;
	int prio;
	item* l;
	item* r;
	item(){};
	item(int key):key(key),prio(rand()),l(nullptr),r(nullptr){};
	item(int key,int prio):key(key),prio(prio),l(nullptr),r(nullptr){};
};
typedef item* pitem;

void split(pitem t,int key,pitem &l,pitem &r){
	if(t==nullptr)l=r=nullptr;
	else if(t->key<=key)split(t->r,key,t->r,r),l=t;
	else split(t->r,key,l,t->l),r=t;
}

void merge(pitem &t,pitem l,pitem r){
	if(l==nullptr)t=r;
	else if(r==nullptr)t=l;
	else if(l->prio>r->prio)merge(l->r,l->r,r),t=l;
	else merge(r->l,r,r->l),t=r;
}

int main(){
	cin.tie(nullptr)->sync_with_stdio(false);
}