n=int(input())
count=0
coins=(10,5,1)
for c in coins:
	count+=(n//c)
	n%=c
print(count)