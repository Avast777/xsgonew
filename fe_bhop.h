#pragma once
[swap_lines]
#include <thread>
#include <chrono>
#include <bitset>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "defines.h"
#include "func.h"
#include "engine.h"
[/swap_lines]

using namespace std;

[junk_enable 1 50 /]


void fe_bhop(const csgoMem & cs, const offsetsAll & offsets, const vector<int> & settings, const engine & eng) {
[add_junk 20 50 /]

	srand(time(NULL));

	while (true) {;
		_Sleep(1);

		[swap_blocks]
		[block]
		if (eng.m_game_ready) {;
		[/block]

		[block]
			if (eng.m_me.hp > 0) {;
		[/block]
		[/swap_blocks]
				if (GetKeyState(settings[KEY_BHOP]) & 0x8000) {
					keybd_event(0, 0x39, 2, 0);
					if ((cs.read<BYTE>(eng.m_local + OFS_FLAGS) & 0x1)) {
						_Sleep(settings[BHOP_INIT_DELAY]);
						keybd_event(0, 0x39, 0, 0);
						_Sleep(32);
						keybd_event(0, 0x39, 2, 0);
						_Sleep(32);
					};
				};
			};
		};
	};
}