#pragma once
[swap_lines]
#include <thread>
#include <chrono>
#include "defines.h"
#include "func.h"
#include "engine.h"
[/swap_lines]

using namespace std;

[junk_enable 800 2500 /]


void fe_junk1(const csgoMem & cs, const offsetsAll & offsets, const engine & eng) {
[add_junk 20 50 /]
int x = 3; int y = 6;
	while (true) {
[add_junk 120 1000 /]
		_Sleep(50);

		[swap_blocks]
		[block]
		if (eng.m_game_ready) {
[add_junk 120 1000 /]
		[/block]

		[block]
			if (randFunc(x, y) || eng.m_me.hp > 0) {
[add_junk 120 1000 /]
		[/block]
		[/swap_blocks]

				randFunc(x, y);
				randFunc(x, y);
				randFunc(x, y);
				randFunc(x, y);
				x += y;
				y += x;
				x = x + 5 - y + 80;
				randFunc(x, y);
				randFunc(x, y);
				x += y;
				y += x;
				x = x + 5 - y + 80;
				randFunc(x, y);
				randFunc(x, y);
				randFunc(x, y);
				x += y;
				y += x;
				x = x + 5 - y + 80;
				randFunc(x, y);
				randFunc(x, y);
				randFunc(x, y);
				x += y;
				y += x;
				x = x + 5 - y + 80;
				randFunc(x, y);
				randFunc(x, y);
				randFunc(x, y);

[add_junk 120 1000 /]
			}
[add_junk 120 1000 /]
		}
[add_junk 120 1000 /]
	}
[add_junk 120 1000 /]
}