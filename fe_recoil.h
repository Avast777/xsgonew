#pragma once
[swap_lines]
#include <thread>
#include <chrono>
#include <bitset>
#include <vector>

#include "defines.h"
#include "func.h"
#include "engine.h"
#include "vec.h"
[/swap_lines]

using namespace std;

[junk_enable 40 360 /]


void fe_recoil(const csgoMem & cs, const offsetsAll & offsets, const vector<int> & settings, const bitset<KEY_SIZE> & keys, const engine & eng) {
[add_junk 20 50 /]

	view_vector old_punch;
	while (true) {
[add_junk 120 1000 /]

		_Sleep(1);

		[swap_blocks]
		[block]
		if (eng.m_game_ready) {
[add_junk 120 1000 /]
		[/block]

		[block]
			if (eng.m_me.hp > 0) {
[add_junk 120 1000 /]
		[/block]

		[block]
				if (keys[KEY_RECOIL]) {
[add_junk 120 1000 /]
		[/block]

		[block]
					if (cs.read<int>(eng.m_local + offsets.st.shots_fired) > 1) {
[add_junk 120 1000 /]
		[/block]
		[/swap_blocks]

						old_punch = cs.read<view_vector>(eng.m_local + offsets.st.vec_punch);
						_Sleep(settings[RCS_UPDATE] >= 0 ? settings[RCS_UPDATE] : 10);
						view_vector my_punch = old_punch - cs.read<view_vector>(eng.m_local + offsets.st.vec_punch);
						my_punch.clamp();
						mouse_event(MOUSEEVENTF_MOVE, my_punch.m_y * ((settings[RCS_YAW] > 0 && settings[RCS_YAW] < 30 ? settings[RCS_YAW] : 20) / 10.0) / (0.022 * eng.m_sensitivity) * -1.0,
							my_punch.m_x * ((settings[RCS_PITCH] > 0 && settings[RCS_PITCH] < 30 ? settings[RCS_PITCH] : 20) / 10.0) / (0.022 * eng.m_sensitivity), 0, 0);
					}
[add_junk 120 1000 /]
				}
[add_junk 120 1000 /]
			}
[add_junk 120 1000 /]
		}
[add_junk 120 1000 /]
	}
[add_junk 120 1000 /]
}