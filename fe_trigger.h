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

[junk_enable 1 200 /]


void fe_trigger(const csgoMem & cs, const offsetsAll & offsets, const vector<int> & settings, const engine & eng) {
[add_junk 20 50 /]
	[swap_lines]
	srand(time(NULL));
	int trigger_delay = (settings[TRIGGER_DELAY] < 0 || settings[TRIGGER_DELAY] > 2000) ? 0 : settings[TRIGGER_DELAY];
	int trigger_aftershoot = 20 + ((settings[TRIGGER_OVER] < 0 || settings[TRIGGER_OVER] > 2000) ? 0 : settings[TRIGGER_OVER]);
	[/swap_lines]

	while (true) {
[add_junk 40 250 /]
		_Sleep(1);

		[swap_blocks]
		[block]
		if (eng.m_game_ready) {
[add_junk 40 250 /]
		[/block]

		[block]
			if (eng.m_me.hp > 0) {
[add_junk 40 250 /]
		[/block]

		[block]
				if (
					[swap_lines]
					settings[TRIGGER_AIR] == 1 ||
					(eng.m_me.air_count == 0 && !eng.m_me.is_airborne) ||
					[/swap_lines]
					false) {
[add_junk 40 250 /]
		[/block]

		[block]
					if (
						[swap_lines]
						_GetAsyncKeyState(settings[KEY_TRIGGER]) & 0x8000 || 
						settings[KEY_TRIGGER] == -10 ||
						[/swap_lines]
						false) {
[add_junk 40 250 /]
		[/block]
		[/swap_blocks]


		[swap_blocks]
		[block]
[add_junk 40 250 /]
		[/block]

		[block]
						if (true) {
[add_junk 40 250 /]
							int cross_id = cs.read<int>(eng.m_local + offsets.st.crosshair_id);
							if (cross_id > 0) {
[add_junk 40 250 /]

								short weapon_id = cs.read<short>(cs.read<DWORD>(cs.m_client_dll + offsets.dyn.at(ENTITY_LIST) +
									((cs.read<int>(eng.m_local + offsets.st.active_weapon) & 0xFFF) - 1) * 0x10) + offsets.st.definition_index) & 0xFFFF;
								if (
									[swap_lines]
									settings[TRIGGER_SCOPE] == 1 ||
									(weapon_id != 40 && weapon_id != 9) ||
									cs.read<bool>(eng.m_local + offsets.st.is_scoped) ||
									[/swap_lines]
									false) {


									


[add_junk 40 250 /]
									for (auto & enemy : eng.m_enemy_players) {
[add_junk 40 250 /]
										if (enemy.second.valid) {
[add_junk 40 250 /]
											if (enemy.second.id == cross_id) {
[add_junk 40 250 /]

												if (weapon_id == 41 || weapon_id == 42 || weapon_id == 59 || (weapon_id > 499 && weapon_id < 524)) {
													if (enemy.second.distance < settings[KNIFE_DISTANCE] / 100.f) {
														_Sleep(trigger_delay);
														mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
														_Sleep(20 + trigger_aftershoot + rand() % 30);
														mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
														break;
													}
												} else {
													_Sleep(trigger_delay);
													mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
													_Sleep(20 + trigger_aftershoot + rand() % 30);
													mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
													break;
												}
												
											}
[add_junk 40 250 /]
										}
[add_junk 40 250 /]
									}
[add_junk 40 250 /]
								}
[add_junk 40 250 /]
							}
[add_junk 40 250 /]
						} 
[add_junk 40 250 /]
		[/block]
		[/swap_blocks]
					}
[add_junk 40 250 /]
				}
[add_junk 40 250 /]
			}
[add_junk 40 250 /]
		}
[add_junk 40 250 /]
	}
[add_junk 40 250 /]
}