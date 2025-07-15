#pragma once
[swap_lines]
#include <thread>
#include <chrono>
#include <bitset>
#include <limits>
#include <vector>
#include <cmath>

#include "defines.h"
#include "func.h"
#include "engine.h"
#include "vec.h"
[/swap_lines]

#define M_PI 3.14159265358979323846

using namespace std;

[junk_enable 40 360 /]


int getBone(int enemy_hp, int my_wep) {
[add_junk 120 1000 /]
	
[swap_blocks]
[block]
	if (
		[swap_lines]
		my_wep == 7 ||
		my_wep == 39 ||
		[/swap_lines]
		false) {
[add_junk 120 1000 /]

		[swap_blocks]
		[block]
		if (enemy_hp > 80) {
[add_junk 120 1000 /]
			return BONE_HEAD;
		}
[add_junk 120 1000 /]
		[/block]

		[block]

		[swap_blocks]
		[block]
		if (enemy_hp > 40) {
[add_junk 120 1000 /]
		[/block]

		[block]
			if (enemy_hp <= 80) {
[add_junk 120 1000 /]
		[/block]
		[/swap_blocks]

				return BONE_NECK;
			}
[add_junk 120 1000 /]
		}
[add_junk 120 1000 /]
		[/block]
		[/swap_blocks]
		
		return BONE_CHEST;
	}
[add_junk 120 1000 /]
[/block]

[block]
	if (
		[swap_lines]
		my_wep == 9 || 
		my_wep == 31 ||
		[/swap_lines]
		false) {
[add_junk 120 1000 /]

		return BONE_CHEST;
	}
[add_junk 120 1000 /]
[/block]
	
[block]
	if (
		[swap_lines]
		my_wep == 16 ||
		my_wep == 60 ||
		my_wep == 8 ||
		my_wep == 10 ||
		my_wep == 13 ||
		[/swap_lines]
		false) {
[add_junk 120 1000 /]

		[swap_blocks]
		[block]
		if (enemy_hp > 65) {
[add_junk 120 1000 /]
			return BONE_HEAD;
		}
[add_junk 120 1000 /]
		[/block]

		[block]

		[swap_blocks]
		[block]
		if (enemy_hp > 30) {
[add_junk 120 1000 /]
		[/block]

		[block]
			if (enemy_hp <= 65) {
[add_junk 120 1000 /]
		[/block]
		[/swap_blocks]
				return BONE_NECK;
			}
[add_junk 120 1000 /]
		}
[add_junk 120 1000 /]
		[/block]
		[/swap_blocks]

		return BONE_CHEST;
	}
[add_junk 120 1000 /]
[/block]

[block]
	if (my_wep == 40) {
[add_junk 120 1000 /]

		if (enemy_hp > 73) {
[add_junk 120 1000 /]
			return BONE_HEAD;
		}
[add_junk 120 1000 /]

		return BONE_CHEST;
	}
[add_junk 120 1000 /]
[/block]

[block]
	if (my_wep == 1) {
[add_junk 120 1000 /]

		if (enemy_hp > 40) {
[add_junk 120 1000 /]
			return BONE_HEAD;
		}
[add_junk 120 1000 /]

		return BONE_CHEST;
	}
[add_junk 120 1000 /]
[/block]

[block]
	if (
		[swap_lines]
		(my_wep > 1 && my_wep < 5) ||
		(my_wep > 29 && my_wep < 33) ||
		my_wep == 36 ||
		(my_wep > 60 && my_wep < 65) ||
		[/swap_lines]
		false) {
[add_junk 120 1000 /]

		[swap_blocks]
		[block]
		if (enemy_hp > 45) {
[add_junk 120 1000 /]
			return BONE_HEAD;
		}
[add_junk 120 1000 /]
		[/block]

		[block]

		[swap_blocks]
		[block]
		if (enemy_hp > 15) {
[add_junk 120 1000 /]
		[/block]

		[block]
			if (enemy_hp <= 45) {
[add_junk 120 1000 /]
		[/block]
		[/swap_blocks]
				return BONE_NECK;
			}
[add_junk 120 1000 /]
		}
[add_junk 120 1000 /]
		[/block]
		[/swap_blocks]

		return BONE_CHEST;
	}
[add_junk 120 1000 /]
[/block]
[/swap_blocks]

	[swap_blocks]
	[block]
	if (enemy_hp > 60) {
[add_junk 120 1000 /]
		return BONE_HEAD;
	}
[add_junk 120 1000 /]
	[/block]

	[block]

	[swap_blocks]
	[block]
	if (enemy_hp > 35) {
[add_junk 120 1000 /]
	[/block]

	[block]
		if (enemy_hp <= 60) {
[add_junk 120 1000 /]
	[/block]
	[/swap_blocks]

			return BONE_NECK;
		}
[add_junk 120 1000 /]
	}
[add_junk 120 1000 /]
	[/block]
	[/swap_blocks]
	
	return BONE_CHEST;
}

void fe_aim(const csgoMem & cs, const offsetsAll & offsets, const engine & eng, const unordered_map<int, shared_ptr<weaponCfg>> & weapon_cfg) {
[add_junk 20 50 /]
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
					if (
						[swap_lines]
						_GetAsyncKeyState(weapon_cfg.at(wep_id)->aim_key) & 0x8000 || 
						weapon_cfg.at(wep_id)->aim_key == -10 ||
						[/swap_lines]
						false) {
[add_junk 120 1000 /]
					[/block]

					[block]
						if (cs.read<int>(my_wep_base + offsets.st.clip) > 0) {
[add_junk 120 1000 /]
					[/block]

					[block]
							if (true) {
[add_junk 120 1000 /]
					[/block]
					[/swap_blocks]
					
								[swap_lines]
								cs_vector my_punch = cs.read<cs_vector>(eng.m_local + offsets.st.vec_punch);
								view_vector my_viewangles = cs.read<view_vector>(eng.m_engine_ptr + offsets.dyn.at(VIEWANGLES));
								float closest_aura = numeric_limits<float>::max();
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

												int aim_bone;

												[swap_blocks]
												[block]
												if (eng.m_me.hp <= weapon_cfg.at(wep_id)->adrenaline_rush) {
[add_junk 120 1000 /]
													aim_bone = BONE_HEAD;
												}
[add_junk 120 1000 /]
												[/block]

												[block]
												if (eng.m_me.hp > weapon_cfg.at(wep_id)->adrenaline_rush) {
[add_junk 120 1000 /]
													aim_bone = (weapon_cfg.at(wep_id)->force_bone >= 0 ? weapon_cfg.at(wep_id)->force_bone : getBone(enemy.second.hp, wep_id));
												}
[add_junk 120 1000 /]
												[/block]
												[/swap_blocks]
											
												view_vector angle_diff = calc_ang(eng.m_me.vec_origin, cs.read<bone_vector>(cs.read<DWORD>(enemy.first + offsets.st.matrix_bone) + 0x30 * aim_bone + 0xC).unpad(), my_punch, eng.m_me.vec_view) - my_viewangles;
												angle_diff.clamp();

												view_vector aura = angle_diff.get_aura(enemy.second.distance);
												float enemy_dst = aura.m_x + aura.m_y;

												[swap_blocks]
												[block]
												if (enemy_dst < closest_aura) {
[add_junk 120 1000 /]
												[/block]

												[block]
													if (aura.m_x < weapon_cfg.at(wep_id)->aura_vertical) {
[add_junk 120 1000 /]
												[/block]

												[block]
														if (aura.m_y < weapon_cfg.at(wep_id)->aura_horizontal) {
[add_junk 120 1000 /]
												[/block]
												[/swap_blocks]

															[swap_lines]
															closest_aura = enemy_dst;
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
								}
[add_junk 120 1000 /]

								
								if (target) {
[add_junk 120 1000 /]

									closest.anti_kick();

									view_vector closest_raw = closest;
									closest = closest / weapon_cfg.at(wep_id)->smoothing;
									
									my_viewangles += closest;
									if (my_viewangles.clamp()) {
[add_junk 120 1000 /]
											float modf = (cs.read<bool>(eng.m_local + offsets.st.is_scoped) ? 2.3f : 1.f);
											float m_y = closest.m_y * modf / (0.022 * eng.m_sensitivity) * -1.0;
											float m_x = closest.m_x * modf / (0.022 * eng.m_sensitivity);

											float m_y_raw = closest_raw.m_y * modf / (0.022 * eng.m_sensitivity) * -1.0;
											float m_x_raw = closest_raw.m_x * modf / (0.022 * eng.m_sensitivity);


											if (fabs(m_y) < 1.2f) {
												if (m_y > 0.f) {
													m_y = 1.1f;
												}

												if (m_y < 0.f) {
													m_y = -1.1f;
												}		
											}

											if (fabs(m_x) < 1.2f) {
												if (m_x > 0.f) {
													m_x = 1.1f;
												}

												if (m_x < 0.f) {
													m_x = -1.1f;
												}
											}

											if (fabs(m_y_raw) < 1.2f) {
												m_y = 0.f;											
											}

											if (fabs(m_x_raw) < 1.2f) {
												m_x = 0.f;
											}
[add_junk 120 1000 /]

										mouse_event(MOUSEEVENTF_MOVE, m_y, m_x, 0, 0);
										_Sleep(weapon_cfg.at(wep_id)->update_time);
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
[add_junk 120 1000 /]
}