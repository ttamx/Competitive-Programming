ban=["wu","wo","ji","ti","nn","nm"]
def solve():
    s=input().strip()
    for c in s:
        if c not in "mnptkswjlaeiou":
            print("ike")
            return
    n=len(s)
    t=[0]*n
    for i in range(n):
        if s[i] in "aeiou":
            t[i]=1
    for i in range(n-1):
        if t[i]==1 and t[i+1]==1:
            print("ike")
            return
    for i in range(n-1):
        if s[i:i+2] in ban:
            print("ike")
            return
    for i in range(n-1):
        if t[i]==0 and t[i+1]==0 and s[i]!="n":
            print("ike")
            return
    for i in range(n-2):
        if t[i]==0 and t[i+1]==0 and t[i+2]==0:
            print("ike")
            return
    if t[-1]==0:
        if s[-1]!="n" or (n>=2 and t[-2]==0):
            print("ike")
            return
    if n==1 and t[0]==0:
        print("ike")
        return
    if n>=2 and t[0]==0 and t[1]==0:
        print("ike")
        return
    print("pona")
    

for _ in range(int(input())):
    solve()