import sys
import fractions

input = sys.stdin.readline

def add(a,b):
    return [a[0]+b[0],a[1]+b[1]]
def sub(a,b):
    return [a[0]-b[0],a[1]-b[1]]
def mul(a,k):
    return [a[0]*k,a[1]*k]
def cross(a,b):
    return a[0]*b[1]-a[1]*b[0]
def dot(a,b):
    return a[0]*b[0]+a[1]*b[1]
def sgn(x):
    if x>0:return 1
    if x<0:return -1
    return 0
def intersect(a,b,c,d):
    oa=sgn(cross(sub(d,c),sub(a,c)))
    ob=sgn(cross(sub(d,c),sub(b,c)))
    oc=sgn(cross(sub(b,a),sub(c,a)))
    od=sgn(cross(sub(b,a),sub(d,a)))
    return oa*ob<0 and oc*od<0
def check(a,b,p):
    return cross(sub(b,a),sub(p,a))==0 and dot(sub(p,a),sub(b,a))>=0 and dot(sub(p,b),sub(a,b))>=0

def solve():
    a=[*map(fractions.Fraction,input().split())]
    b=[*map(fractions.Fraction,input().split())]
    c=[*map(fractions.Fraction,input().split())]
    x,y=[[*map(int,e.split("/"))] for e in input().split()]
    p=[fractions.Fraction(x[0],x[1]),fractions.Fraction(y[0],y[1])]
    
    d=sub(b,a)

    if cross(d,sub(p,a))==0:return True
    if cross(d,sub(p,c))==0:return True
    if check(a,c,p):return True
    if check(b,c,p):return True

    vec=[sub(a,c),sub(b,c)]

    if dot(d,sub(b,c))==0:
        vec.append(add(sub(a,c),mul(sub(b,a),2)))
    elif dot(d,sub(a,c))==0:
        vec.append(add(sub(b,c),mul(sub(a,b),2)))

    for v in vec:
        if sgn(cross(v,d))!=sgn(cross(v,sub(p,c))):
            d=mul(d,-1)
        l=0;r=int(1e8)
        while l<r:
            mid=(l+r)//2
            f=add(c,mul(d,mid))
            if sgn(cross(v,d))!=sgn(cross(v,sub(p,f))):r=mid
            else:l=mid+1
        f=add(c,mul(d,l))
        g=add(f,v)
        if intersect(f,g,a,b) or intersect(f,g,b,c) or intersect(f,g,a,c):continue
        if check(f,g,p):return True

    return False

ans=[]

t=int(input())
for _ in range(t):
    ans.append("Yes" if solve() else "No")

print("\n".join(ans))

