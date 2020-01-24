#include <fstream>
#include <iostream>
#include <string>
#include <assert.h>

using namespace std;

const char code[] = {
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
	'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
	'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
	'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
	'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
	'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
	'w', 'x', 'y', 'z', '0', '1', '2', '3',
	'4', '5', '6', '7', '8', '9', '+', '/',
};

void encode(const string& path)
{
	ifstream input(path, ios::binary);
	input.seekg(0, ios::end);
	int sz = input.tellg();
	input.seekg(0, ios::beg);

	char buf[3];
	for (int i = 0; i < sz / 3; ++i) {
		input.read(buf, 3);
		cout << code[(buf[0] >> 2) & 0b00111111];
		cout << code[(buf[0] & 0b00000011) * 16 + (buf[1] >> 4 & 0b00001111)];
		cout << code[(buf[1] & 0b00001111) * 4 + (buf[2] >> 6 & 0b00000011)];
		cout << code[(buf[2] & 0b00111111)];
	}
	buf[0] = buf[1] = buf[2] = 0;
	input.read(buf, sz % 3);
	if (sz % 3 == 1) {
		cout << code[(buf[0] >> 2) & 0b00111111];
		cout << code[(buf[0] & 0b00000011) * 16 + (buf[1] >> 4 & 0b00001111)];
		cout << "==";
	} else
	if (sz % 3 == 2) {
		cout << code[(buf[0] >> 2) & 0b00111111];
		cout << code[(buf[0] & 0b00000011) * 16 + (buf[1] >> 4 & 0b00001111)];
		cout << code[(buf[1] & 0b00001111) * 4 + (buf[2] >> 6 & 0b00000011)];
		cout << "=";
	}
}

int main(int argc, char** argv)
{
	assert(argc > 1);
	encode(argv[1]);

	return 0;
}