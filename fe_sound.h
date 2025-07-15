#pragma once
[swap_lines]
#include <thread>
#include <chrono>
#include <bitset>
#include <vector>
#include <windows.h>
#include <limits>

#include "defines.h"
#include "func.h"
#include "engine.h"
#include "vec.h"
[/swap_lines]

using namespace std;

[junk_enable 40 360 /]


void fe_sound(const csgoMem & cs, const offsetsAll & offsets, const vector<int> & settings, const bitset<KEY_SIZE> & keys, const engine & eng) {
[add_junk 20 50 /]
	while (true) {
[add_junk 120 1000 /]
		_Sleep(20);

		[swap_blocks]
		[block]
		if (eng.m_game_ready) {
[add_junk 120 1000 /]
		[/block]

		[block]
			if (keys[KEY_SOUND]) {
[add_junk 120 1000 /]
		[/block]

		[block]
				if (eng.m_me.hp > 0) {
[add_junk 120 1000 /]
		[/block]
		[/swap_blocks]

					[swap_lines]
					view_vector my_viewangles = cs.read<view_vector>(eng.m_engine_ptr + offsets.dyn.at(VIEWANGLES));
					float closest_distance = numeric_limits<float>::max();
					float closest_aura = numeric_limits<float>::max();
					[/swap_lines]

					for (auto & enemy : eng.m_enemy_players) {
[add_junk 120 1000 /]
						if (enemy.second.valid) {
[add_junk 120 1000 /]

							[swap_blocks]
							[block]
							if (settings[SOUND_MODE] == 1) {
[add_junk 120 1000 /]
							[/block]

							[block]
								if (enemy.second.distance < settings[SOUND_RANGE]) {
[add_junk 120 1000 /]
							[/block]

							[block]
									if (enemy.second.distance < closest_distance) {
[add_junk 120 1000 /]
							[/block]
							[/swap_blocks]

										closest_distance = enemy.second.distance;
									}
[add_junk 120 1000 /]
								}
[add_junk 120 1000 /]
							} 
[add_junk 120 1000 /]
							
							if (settings[SOUND_MODE] != 1) {
[add_junk 120 1000 /]

								view_vector angle_diff = calc_ang(eng.m_me.vec_origin, cs.read<bone_vector>(cs.read<DWORD>(enemy.first + offsets.st.matrix_bone) + 0x30 * BONE_CHEST + 0xC).unpad(), cs_vector(0.f, 0.f, 0.f), eng.m_me.vec_view) - my_viewangles;
								angle_diff.clamp();
								view_vector aura = angle_diff.get_aura(enemy.second.distance);

								[swap_blocks]
								[block]
								if (aura.m_x + aura.m_y < closest_aura) {
[add_junk 120 1000 /]
								[/block]

								[block]
									if (aura.m_x < settings[SOUND_RANGE]) {
[add_junk 120 1000 /]
								[/block]

								[block]
										if (aura.m_y < settings[SOUND_RANGE]) {
[add_junk 120 1000 /]
								[/block]
								[/swap_blocks]

											[swap_lines]
											closest_aura = aura.m_x + aura.m_y;
											closest_distance = enemy.second.distance;
											[/swap_lines]
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
[add_junk 120 1000 /]

					[swap_blocks]
					[block]

					[swap_blocks]
					[block]

					[swap_blocks]
					[block]
					if (closest_distance < 10e9f) {
[add_junk 120 1000 /]
					[/block]

					[block]
						if (true) {
[add_junk 120 1000 /]
					[/block]
					[/swap_blocks]

							_Beep(800, remap(closest_distance >= 0.f && closest_distance < 1300.f ? closest_distance : 1300.f, 0, 1300, 10, 800) / 2);
							_Sleep(remap(closest_distance >= 0.f && closest_distance < 1300.f ? closest_distance : 1300.f, 0, 1300, 10, 800) / 2);
						}
[add_junk 120 1000 /]
					}
[add_junk 120 1000 /]
					[/block]
					[/swap_blocks]
				}
[add_junk 120 1000 /]
			}
[add_junk 120 1000 /]
		}
[add_junk 120 1000 /]
	}
[add_junk 120 1000 /]
}