#! /usr/bin/python
x,y=raw_input().split()
d=range(99)
for a in x:
 c=d;d=[d[0]+1]
 for b,p,q in zip(y,c[1:],c):d+=[min(d[-1]+1,p+1,q+2*(a!=b))]
print d[-1]
