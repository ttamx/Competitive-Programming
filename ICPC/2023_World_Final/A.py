import sys
input=sys.stdin.readline
flush=sys.stdout.flush
def ask(a,b,c):
    print(a,b,c)
    flush()
    return int(input())
a=ask(1,0,0)
b=ask(0,1,0)
c=ask(0,0,1)
d=ask(1,1,1)
e=ask(1,2,3)
if a+b+c==d:
    print(a,b,c)
elif a+b*2+c*3==e:
    print(a,b,c)
elif d+b+c*2==e:
    print(d-b-c,b,c)
elif d*2-a+c==e:
    print(a,d-a-c,c)
elif d*3-2*a-b==e:
    print(a,b,d-a-b)
else:
    exit(1)
flush()