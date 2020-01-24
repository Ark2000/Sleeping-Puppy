#include <cstring>
#include <cassert>

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

char* decode(const char* code, int* filesize)
{
	int len = strlen(code);
	assert(len % 4 == 0);
	
	int flag = 0;
	if (code[len - 1] == '=') {
		flag = 1;
		if (code[len - 2] == '=') {
			flag = 2;
		}
	}

	*filesize = len / 4 * 3 - flag;
	char* file = new char[*filesize];

	char table[256];
	for (int i = 0; i < 256; ++i) table[i] = -1;
	for (int i = 'A'; i <= 'Z'; ++i) table[i] = i - 'A';
	for (int i = 'a'; i <= 'z'; ++i) table[i] = i - 'a' + 26;
	for (int i = '0'; i <= '9'; ++i) table[i] = i - '0' + 52;
	table['+'] = 62; table['/'] = 63;

	int loop = len / 4; if (flag > 0) loop -=1;
	int i = 0;
	for (; i < loop; ++i) {
		char c0 = table[code[i * 4 + 0]]; assert(c0 >= 0);
		char c1 = table[code[i * 4 + 1]]; assert(c1 >= 0);
		char c2 = table[code[i * 4 + 2]]; assert(c2 >= 0);
		char c3 = table[code[i * 4 + 3]]; assert(c3 >= 0);

		file[i * 3 + 0] = ((c0 << 2) & 0xfc) | ((c1 >> 4) & 0x03);
		file[i * 3 + 1] = ((c1 << 4) & 0xf0) | ((c2 >> 2) & 0x0f);
		file[i * 3 + 2] = ((c2 << 6) & 0xc0) | ((c3 >> 0) & 0x3f);
	}
	if (flag > 0) {
		char c0 = table[code[i * 4 + 0]]; assert(c0 >= 0);
		char c1 = table[code[i * 4 + 1]]; assert(c1 >= 0);
		file[i * 3 + 0] = ((c0 << 2) & 0xfc) | ((c1 >> 4) & 0x03);
		if (flag < 2) {
			char c2 = table[code[i * 4 + 2]]; assert(c2 >= 0);
			file[i * 3 + 1] = ((c1 << 4) & 0xf0) | ((c2 >> 2) & 0x0f);
		}
	}
	return file;
}
/*
int main()
{
	string code;
	cin >> code;

	int filesize;
	char* file = decode(code.c_str(), &filesize);
	ofstream fstrm("file", ios::binary);

	fstrm.write(file, filesize);
	fstrm.close();

	delete[] file;

	return 0;
}
*/