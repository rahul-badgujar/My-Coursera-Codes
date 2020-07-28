#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <limits>
#include <bitset>
#include <cstdint>
#include <unordered_map>
#include <cctype>
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

string inpStr()
{
	string s(" ");
	while (s == " ")
	{
		getline(cin, s);
	}
	return s;
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

bool isGoodGuess(const string &guess)
{
	for (auto i : guess)
	{
		if (!(('a' <= i and i <= 'z') or ('A' <= i and i <= 'Z') or i == ' '))
			return false;
	}
	return true;
}

void tryGuessingWord(const string &ciphers_xor, const string &word)
{
	string word_hex = decToHex(word);
	Int cLen = ciphers_xor.length();
	Int wLen = word_hex.length();
	logs("Good Guesses for :");
	logn("\'" + word + "\'");
	for (size_t i = 0; i <= cLen - wLen; i++)
	{
		string part = ciphers_xor.substr(i, wLen);
		string guess = hexToDec(strXOR(word_hex, part));
		if (isGoodGuess(guess))
		{
			logs("at " + to_string(i) + " -> ");
			string guess_log = "\'" + guess + "\'";
			logn("FOUND : " + guess_log);
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	/*
	Eve Dropping
	Eve captures your messages
	*/
	logn("Eve got : \n");
	string key = "supersecretverys";
	string key_hex = decToHex(key);
	string msg1 = "steal the secret";
	string msg2 = "the boy the girl";
	string msg1_hex = decToHex(msg1);
	string msg2_hex = decToHex(msg2);
	string msg1_enc_hex = strXOR(msg1_hex, key_hex);
	string msg2_enc_hex = strXOR(msg2_hex, key_hex);
	deb(msg1_enc_hex);
	deb(msg2_enc_hex);
	log(endl);

	/*
	Eve trying to Decode
	1. XOR the Encrypted Ciphers
	2. Try guessing most used Common English Words
	3. Look for the Good Guesses
	4. Continue
	*/
	logn("Eve trying to Decode using Crib Dragging : \n");
	string msgs_xor = strXOR(msg1_enc_hex, msg2_enc_hex);
	deb(msgs_xor);
	log(endl);

	while (true)
	{
		log("Enter Your Guess Word : ");
		string word;
		word = inpStr();
		tryGuessingWord(msgs_xor, word);
		string choice;
		log("Want to Continue Guessing (yes/no) : ");
		choice = inpStr();
		if (choice != "yes")
			break;
		log(endl);
	}

	return 0;
}
