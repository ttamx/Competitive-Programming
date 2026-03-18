def check(x):
    if x==1:return False
    d=2
    while d*d<=x:
        if x%d==0:
            return False
        d+=1
    return True
for _ in range(int(input())):
    a,b=map(int,input().split())
    print("Y" if a+2==b and check(a) and check(b) else "N")