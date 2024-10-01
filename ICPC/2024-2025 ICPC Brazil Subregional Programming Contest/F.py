n=int(input())
a=1
b=1
for i in range(n-1):
    a,b=[a+b,a]
print(a)