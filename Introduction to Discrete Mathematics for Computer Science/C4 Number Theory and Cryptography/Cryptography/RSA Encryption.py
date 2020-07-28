import random as rand

'''
RSA Encryption : A frequently used Encryption Technique
1. Reciever generates Two huge Prime Numbers P and Q
   This makes our Private Key [P,Q] which is known to Receiver only
   Anyone knowing Private Key can Decrypt Message encrypted using Public Key
2. let N = PQ
3. Calc Phi(N) = (P-1)(Q-1) as P,Q both Prime
4. Calc E such that 1<E<Phi(N) and gcd(E,Phi)==1
5. This makes our Public Key [N,E]
   Message Receiver share this publicly, 
   and everyone is allowed to Encrypt Message using Public Key
   Message M can be encrypted into Cipher C using Formula :
   		C = M^E mod N
6. Calc D such that ED = 1 mod Phi 
   i.e, D is Module Multiplicative Inverse of E modulo Phi
7. Receiver now Decrypts Message using Formula :
		   M = C^D mod N
   as Only Reciever know Private Key, and hence can Calculate D
   to Decrypt Message instantly
   D cannot be found easily without knowing P,Q,
   potentially takes hundreds of Years for 2048 bit long Prime Numbers
   
Security Advices
1. Keep Prime Numbere huge, otherwise if any of Prime is low,
   the P,Q can be easily guessed in small time
2. Keep the difference between P,Q high
   if it is small, then we can try R = Q-P
   P < sqrt(N) < Q === sqrt(N)-P = R
3. Dont use redundant messages, as Hacker can try them one by one
   and can crack Private Key
'''

def extGcd(a:int,b:int):
	if b==0:
		return 1,0,a
	x1,y1,g=extGcd(b,a%b)
	x=y1
	y=x1-(a//b)*y1
	return x,y,g
	
def modExp(x:int,y:int,m:int):
	x%=m
	ans=1
	while y>=1:
		if (y&1)==1:
			ans=(ans*x)%m
		x=(x*x)%m
		y>>=1
	return (ans+m)%m

def nBitRandInt(n:int):
	# Generate High N Bit Random Number
	return rand.randrange(2**(n-1)+1,2**n-1)
	
def isPrime(n:int):
	# Fermants Little Theorm
	if n<=4:
		return n==3 or n==2
	for i in range(5):
		a=rand.randrange(2,n-2)
		if n%a==0:
			return False
		if modExp(a,n-1,n)!=1:
			return False
	return True
	
def getRandPrimes():
	n=nBitRandInt(128) # Random Integer
	diff=rand.randrange(10**6,10**10)
	p=n-diff # Keep difference above 1Mn in to Primes
	q=n+diff
	p|=1 # Make them Odd
	q|=1
	doneP,doneQ=False,False
	while not(doneP and doneQ):
		doneP=isPrime(p)
		doneQ=isPrime(q)
		if doneP==False:
			p-=2
		if doneQ==False:
			q+=2
	return p,q
	
def getE(phi):
	t=rand.randrange(0,1000) # Take Random E
	e=1
	# Get E such that 1<E<Phi and E and Phi are Coprime
	while t>0:
		for i in range(e+1,phi):
			x,y,g=extGcd(i,phi)
			if g==1:
				e=i
				break
		t-=1
	return e			

if __name__=='__main__':
	print("Receivers End")
	print("---------------------------")
	p,q=getRandPrimes()
	#print("Prime P : ",p)
	#print("Prime Q : ",q)
	n=p*q
	#print("N : ",n)
	phi=(p-1)*(q-1)
	#print("Phi : ",phi)
	e=getE(phi)
	#print("E : ",e)
	print("Calculated P,Q,N,Phi,E\n")
	
	print("Receiver published Public Key : ")
	print("N",n)
	print("E",e)
	print('')
	
	print("Senders End")
	print("---------------------------")
	msg=input("Sender Enter Your Message : ")
	#print("Message : ",msg)
	msg_hex=''
	for i in msg:
		h=hex(ord(i)) # will take form OxAB
		if len(h)<4:
			h=h[0:2]+'0'+h[2:]
		msg_hex+=h[2:]
	print("Message Hex : ",msg_hex)
	enc_msg=int(msg_hex,16)
	# Encrypt Message Code as C = M**E mod N
	enc_msg=modExp(enc_msg,e,n)
	print("Encrypted Message Code : ",enc_msg,'\n')
	
	
	print("Receivers End")
	print("---------------------------")
	# Generate D, D is Mod Inverse of E and Phi modulo n
	d,y,g=extGcd(e,phi)
	if d<0:
		d+=phi
	#print("D : ",d)
	print("Calculated D")
	
	
	# Decrypt Message Code as M = C**D mod N
	dec_msg=modExp(enc_msg,d,n)
	print("Decrypted Message Code : ",dec_msg)
	dec_msg_hex=hex(dec_msg)
	dec_msg_hex=dec_msg_hex[2:]
	print("Decrypted Message Hex : ",dec_msg_hex)
	dec_msg=''
	for i in range(0,len(dec_msg_hex),2):
		h=dec_msg_hex[i:i+2]
		dec_msg+=chr(int(h,16))
	print("\nDecoded Message : ",dec_msg)
	
	