#pragma once
[swap_lines]
#include <thread>
#include <chrono>
#include <bitset>
#include <vector>
#include <limits>
#include <cstdlib>
#include <ctime>

#include "defines.h"
#include "func.h"
#include "engine.h"
#include "vec.h"
[/swap_lines]

using namespace std;

[junk_enable 40 360 /]


void fe_silent(const csgoMem & cs, const offsetsAll & offsets, const engine & eng, const unordered_map<int, shared_ptr<weaponCfg>> & weapon_cfg) {
[add_junk 20 50 /]

	srand(time(NULL));

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
		[/swap_blocks]

				int my_wep_base = cs.read<DWORD>(cs.m_client_dll + offsets.dyn.at(ENTITY_LIST) + ((cs.read<int>(eng.m_local + offsets.st.active_weapon) & 0xFFF) - 1) * 0x10);
				short wep_id = cs.read<short>(my_wep_base + offsets.st.definition_index) & 0xFFFF;

				if (
					[swap_lines]
					(wep_id > 0 && wep_id < 41) ||
					(wep_id > 59 && wep_id < 65) ||
					[/swap_lines]
					false) {
[add_junk 120 1000 /]

					[swap_blocks]
					[block]
					if (_GetAsyncKeyState(weapon_cfg.at(wep_id)->silent_key) & 0x8000) {
[add_junk 120 1000 /]
					[/block]

					[block]
						if (cs.read<float>(my_wep_base + offsets.st.next_attack) <= float(cs.read<int>(eng.m_local + offsets.st.tick_base))) {
[add_junk 120 1000 /]
					[/block]

					[block]
							if (cs.read<int>(my_wep_base + offsets.st.clip) > 0) {
[add_junk 120 1000 /]
					[/block]
					[/swap_blocks]
								
								[swap_lines]
								cs_vector my_punch = cs.read<cs_vector>(eng.m_local + offsets.st.vec_punch);
								view_vector my_viewangles = cs.read<view_vector>(eng.m_engine_ptr + offsets.dyn.at(VIEWANGLES));
								float closest_fov = numeric_limits<float>::max();
								view_vector closest;
								bool target = false;
								[/swap_lines]

								for (auto & enemy : eng.m_enemy_players) {
[add_junk 120 1000 /]
									if (enemy.second.valid) {
[add_junk 120 1000 /]

										[swap_blocks]
										[block]
										if (
											[swap_lines]
											!eng.m_me.is_airborne ||
											weapon_cfg.at(wep_id)->aim_inair ||
											[/swap_lines]
											false) {
[add_junk 120 1000 /]
										[/block]

										[block]
											if (
												[swap_lines]
												enemy.second.is_visible ||
												!weapon_cfg.at(wep_id)->vis_check ||
												[/swap_lines]
												false) {
[add_junk 120 1000 /]
										[/block]
										[/swap_blocks]
											
												view_vector angle_diff = calc_ang(eng.m_me.vec_origin, cs.read<bone_vector>(cs.read<DWORD>(enemy.first + offsets.st.matrix_bone) + 0x30 * weapon_cfg.at(wep_id)->silent_bone + 0xC).unpad(), my_punch, eng.m_me.vec_view) - my_viewangles;
												angle_diff.clamp();
												float enemy_dst = fabs(angle_diff.m_x) + fabs(angle_diff.m_y);

												[swap_blocks]
												[block]
												if (enemy_dst < closest_fov) {
[add_junk 120 1000 /]
												[/block]

												[block]
													if (enemy_dst < weapon_cfg.at(wep_id)->silent_fov) {
[add_junk 120 1000 /]
												[/block]
												[/swap_blocks]

														[swap_lines]
														closest_fov = enemy_dst;
														closest = angle_diff;
														target = true;
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

								if (target) {
[add_junk 120 1000 /]

									my_viewangles += closest;


									[swap_blocks]
									[block]
									if (1 != 0) {
[add_junk 120 1000 /]
									[/block]

									[block]
										if (closest.clamp()) {
[add_junk 120 1000 /]
									[/block]
									[/swap_blocks]

											float modf = (cs.read<bool>(eng.m_local + offsets.st.is_scoped) ? 2.3f : 1.f);
											mouse_event(MOUSEEVENTF_MOVE | MOUSEEVENTF_LEFTDOWN, closest.m_y * modf / (0.022 * eng.m_sensitivity) * -1.0, closest.m_x * modf / (0.022 * eng.m_sensitivity), 0, 0);
											_Sleep(15 + rand() % 25);
											mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
											_Sleep(300);

										}
[add_junk 120 1000 /]
									}
[add_junk 120 1000 /]

									_Sleep(10);
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
		}
[add_junk 120 1000 /]
	}
[add_junk 120 1000 /]
}