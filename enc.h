#pragma once

#define windows_retarded %

[swap_lines]
#include <string>
#include <fstream>
#include <sstream>
[/swap_lines]

using namespace std;

[junk_enable 40 360 /]

[junk_enable_declares /]

class encString {
[swap_blocks]
[block]
public:
[swap_lines]
	encString(unsigned char *, uint16_t);
	friend ostream & operator<<(ostream & os, const encString & str);
	bool operator==(const string & str);
	string str() const;
	wstring wstr() const;
[/swap_lines]
[/block]

[block]
private:
[swap_lines]
	unsigned char * m_data;
	uint16_t m_mask;
[/swap_lines]
[/block]
[/swap_blocks]
};

[junk_disable_declares /]

[swap_blocks]
[block]
encString::encString(unsigned char * data, uint16_t mask) {
[add_junk 120 1000 /]

[swap_lines]
	m_data = data;
	m_mask = mask;
[/swap_lines]
}
[/block]

[block]
string encString::str() const {
[add_junk 120 1000 /]

[swap_lines]
	stringstream tmp;
	uint16_t and_data = 0b1000000000000000;
[/swap_lines]
	for (size_t i = 0; i < 16; ++i) {
[add_junk 120 1000 /]
		if (m_mask & and_data) {
[add_junk 120 1000 /]
			tmp << m_data[i];
		}
[add_junk 120 1000 /]
		and_data >>= 1u;
	}
[add_junk 120 1000 /]
	return tmp.str();
}
[/block]

[block]
wstring encString::wstr() const {
[add_junk 120 1000 /]

[swap_lines]
	wstring tmp(L"                ");
	uint16_t and_data = 0b1000000000000000;
	size_t it = 0;
[/swap_lines]
	for (size_t i = 0; i < 16; ++i) {
[add_junk 120 1000 /]
		if (m_mask & and_data) {
[add_junk 120 1000 /]
			tmp[it++] = m_data[i];
		}
[add_junk 120 1000 /]
		and_data >>= 1u;
	}
[add_junk 120 1000 /]

	tmp.resize(it);
	return tmp;
}
[/block]

[block]
ostream & operator<<(ostream & os, const encString & str) {
[add_junk 120 1000 /]

	uint16_t and_data = 0b1000000000000000;
	for (size_t i = 0; i < 16; ++i) {
[add_junk 120 1000 /]
		if (str.m_mask & and_data) {
[add_junk 120 1000 /]
			os << str.m_data[i];
		}
[add_junk 120 1000 /]
		and_data >>= 1u;
	}
[add_junk 120 1000 /]

	return os;
}
[/block]

[block]
bool encString::operator==(const string & str) {
[add_junk 120 1000 /]

[swap_lines]
	uint16_t and_data = 0b1000000000000000;
	size_t j = 0;
[/swap_lines]
	for (size_t i = 0; i < 16; ++i) {
[add_junk 120 1000 /]
		if (m_mask & and_data) {
[add_junk 120 1000 /]
			if (
				[swap_lines]
				j >= str.size() ||
				str[j] != m_data[i] ||
				[/swap_lines]
				false) {
[add_junk 120 1000 /]
				return false;
			}
[add_junk 120 1000 /]
			++j;
		}
[add_junk 120 1000 /]
		and_data >>= 1u;
	}
[add_junk 120 1000 /]

	if (j < str.size()) {
[add_junk 120 1000 /]
		return false;
	}
[add_junk 120 1000 /]

	return true;
}
[/block]
[/swap_blocks]