#pragma once
[swap_lines]
#include <windows.h>
#include <vector>
#include <algorithm>

#include "func.h"
[/swap_lines]

using namespace std;

[junk_enable 40 360 /]

[junk_enable_declares /]

class ofsScanner {
[swap_blocks]
[block]
public:
	[swap_lines]
	ofsScanner(csgoMem *, bool);
	DWORD scan(const vector<BYTE> &);
	[/swap_lines]
	
[/block]

[block]
private:
	[swap_lines]
	vector<BYTE> m_csgo_memory;
	bool m_is_client;
	csgoMem * m_cs_mem;
	[/swap_lines]

[/block]
[/swap_blocks]
};

[junk_disable_declares /]

[swap_blocks]
[block]
ofsScanner::ofsScanner(csgoMem * cs_mem, bool is_client) : m_csgo_memory(is_client ? cs_mem->m_client_size : cs_mem->m_engine_size), m_is_client(is_client), m_cs_mem(cs_mem) {
[add_junk 120 1000 /]
	m_cs_mem->read_bytes(m_is_client ? m_cs_mem->m_client_dll : m_cs_mem->m_engine_dll, &m_csgo_memory[0], m_is_client ? m_cs_mem->m_client_size : m_cs_mem->m_engine_size);
}
[/block]

[block]
struct comparator {
	bool operator()(const BYTE & a, const BYTE & b)	const {
[add_junk 120 1000 /]
		if (b == 0x00) {
[add_junk 120 1000 /]
			return true;
		}
[add_junk 120 1000 /]

		return a == b;
	}

[junk_disable /]
};
[junk_enable 40 360 /]

DWORD ofsScanner::scan(const vector<BYTE> & pattern) {
	auto res = search(m_csgo_memory.begin(), m_csgo_memory.end(), pattern.begin(), pattern.end(), comparator());

	if (res == m_csgo_memory.end()) {
[add_junk 120 1000 /]
		return 0;
	}
[add_junk 120 1000 /]

	return res - m_csgo_memory.begin();
}
[/block]
[/swap_blocks]