#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <limits>
#include <bitset>
#include <cstdint>
#include <unordered_map>
#define deb(x) cout << #x << " : " << x << '\n'
#define logn(x) cout << x << '\n'
#define logs(x) cout << x << ' '
#define log(x) cout << x
#define MOD 1000000007
#define uInt unsigned long long int
#define Int long long int

using namespace std;

template <typename T, typename U>
void debArr(T arr[], U n)
{
	for (U i = 0; i <= n - 1; i++)
	{
		logs(arr[i]);
	}
	log(endl);
}

template <typename T>
void debVect(vector<T> arr)
{
	for (auto i : arr)
	{
		logs(i);
	}
	log(endl);
}

char intToHex(uint8_t n)
{
	if (n <= 9)
		return '0' + n;
	else
		return 'A' + (n - 10);
}
uint8_t hexToInt(char n)
{
	if (n >= '0' and n <= '9')
		return n - '0';
	else
		return n - 'A' + 10;
}

string decToHex(const string &d)
{
	Int len = d.length();
	string hex;
	hex.reserve(2 * len);
	for (auto i : d)
	{
		bitset<8> h1((uint8_t)i);
		bitset<8> h2 = h1;
		h1 >>= 4;
		h2 <<= 4;
		h2 >>= 4;
		hex += intToHex((uint8_t)h1.to_ulong());
		hex += intToHex((uint8_t)h2.to_ulong());
	}
	return hex;
}
string hexToDec(const string &h)
{
	Int len = h.length();
	string dec;
	dec.reserve(len >> 1);
	for (size_t i = 0; i < len; i += 2)
	{
		bitset<8> bin;
		bitset<8> h1(hexToInt(h[i]));
		bitset<8> h2(hexToInt(h[i + 1]));
		h1 <<= 4;
		bin |= h1;
		bin |= h2;
		dec += (char)((uint8_t)bin.to_ulong());
	}
	return dec;
}

string strXOR(const string &s1, const string &s2)
{
	Int len = s1.length();
	string x;
	x.reserve(len);
	for (size_t i = 0; i < len; i++)
	{
		bitset<4> b1(hexToInt(s1[i]));
		bitset<4> b2(hexToInt(s2[i]));
		x += (intToHex((uint8_t)(b1 ^ b2).to_ulong()));
	}
	return x;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	/*
	One Time Pad
	is a secure encryption technique using Hex Codes and XOR Encryption
	both parties share a common key
	message is encrypted/decrypted using that key
	if the same key is not used for multiple messages,
	this method provides EveDropping,
	bt if used for more than one message, 
	Eve can partially decode messages without help of key
	using trying ans guessing method (called as Crib Drag Method)
	*/

	string key = "supersecret";
	deb(key);
	string key_hex = decToHex(key);
	deb(key_hex);
	log('\n');

	logn("Party 1 : \n");
	string msg = "Hello World!";
	deb(msg);
	string msg_hex = decToHex(msg);
	deb(msg_hex);
	string msg_enc_hex = strXOR(msg_hex, key_hex);
	deb(msg_enc_hex);
	log('\n');

	logn("Party 2 : \n");
	deb(msg_enc_hex);
	string msg_dec_hex = strXOR(msg_enc_hex, key_hex);
	deb(msg_dec_hex);
	string msg_dec = hexToDec(msg_dec_hex);
	deb(msg_dec);
	log('\n');

	return 0;
}
