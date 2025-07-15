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

struct glow_write_obj {
	glow_write_obj(float r, float g, float b, float a, float bloom, bool fill, float zero, float capped, float velocity);

	float m_r;
	float m_g;
	float m_b;
	float m_a;
	float m_bGlowAlphaCappedByRenderAlpha;
    float m_flGlowAlphaFunctionOfMaxVelocity;
	float m_flBloomAmount;
	float m_locIsZero;
	bool m_bRenderWhenOccluded;
	bool m_bRenderWhenUnoccluded;
	bool m_bFullBloom;
};

[junk_enable 1 200 /]


glow_write_obj::glow_write_obj(float r, float g, float b, float a, float bloom, bool fill, float zero, float capped, float velocity) {
[add_junk 40 250 /]
	[swap_lines]
	m_r = r;
	m_g = g;
	m_b = b;
	m_a = a;
	m_bGlowAlphaCappedByRenderAlpha = capped;
	m_flGlowAlphaFunctionOfMaxVelocity = velocity;
	m_flBloomAmount = bloom;
	m_locIsZero = zero;
	m_bRenderWhenOccluded = true;
	m_bFullBloom = fill;
	[/swap_lines]
}

void fe_glow(const csgoMem & cs, const offsetsAll & offsets, const vector<int> & settings, const bitset<KEY_SIZE> & keys, const engine & eng) {
[add_junk 20 50 /]

	while (true) {
[add_junk 40 250 /]
		_Sleep(10);

		[swap_blocks]
		[block]
		if (eng.m_game_ready) {
[add_junk 40 250 /]
		[/block]

		[block]
			if (keys[KEY_GLOW]) {
[add_junk 40 250 /]
		[/block]

		[block]
				if (true) {
[add_junk 40 250 /]
		[/block]
		[/swap_blocks]

					size_t object_count = cs.read<size_t>(cs.m_client_dll + offsets.dyn.at(GLOW) + OFS_GLOW_COUNT);
					vector<glowObject> objects(object_count);
					cs.read_bytes(eng.m_glow_ptr, &objects[0], sizeof(glowObject) * object_count);

					for (auto & glow_obj : objects) {
[add_junk 40 250 /]

						[swap_blocks]
						[block]
						if (glow_obj.base != 0) {
[add_junk 40 250 /]
						[/block]

						[block]
							if (!glow_obj.m_bRenderWhenOccluded) {
[add_junk 40 250 /]
						[/block]
						[/swap_blocks]

								[swap_lines]
								int team = 0;
								auto it = eng.m_enemy_players.find(glow_obj.base);
								[/swap_lines]

								[swap_blocks]
								[block]
								if (it != eng.m_enemy_players.end()) {
[add_junk 40 250 /]

									/*bool is_defusing = cs.read<bool>(glow_obj.base + offsets.st.is_defusing);*/

									[swap_blocks]
									[block]
									/*
									if (is_defusing) {
[add_junk 40 250 /]
										bool has_defus = cs.read<bool>(glow_obj.base + offsets.st.has_defuser);

										[swap_blocks]
										[block]
										if (has_defus) {
[add_junk 40 250 /]
											glow_write_obj object(0.f, 1.f, 1.f, (settings[GLOW_A_E] % 256) / 255.f, (settings[GLOW_C_E] % 256) / 255.f,
												settings[GLOW_F_E] == 1, glow_obj.m_locIsZero, glow_obj.m_bGlowAlphaCappedByRenderAlpha, glow_obj.m_flGlowAlphaFunctionOfMaxVelocity);

											cs.write<glow_write_obj>(eng.m_glow_ptr + ((&glow_obj - &objects[0]) * sizeof(glowObject)) + 0x8, object, OFS_WRITE_SIZE);
										}
[add_junk 40 250 /]
										[/block]

										[block]
										if (!has_defus) {
[add_junk 40 250 /]
											glow_write_obj object(1.f, 0.f, 1.f, (settings[GLOW_A_E] % 256) / 255.f, (settings[GLOW_C_E] % 256) / 255.f,
												settings[GLOW_F_E] == 1, glow_obj.m_locIsZero, glow_obj.m_bGlowAlphaCappedByRenderAlpha, glow_obj.m_flGlowAlphaFunctionOfMaxVelocity);

											cs.write<glow_write_obj>(eng.m_glow_ptr + ((&glow_obj - &objects[0]) * sizeof(glowObject)) + 0x8, object, OFS_WRITE_SIZE);
										}
[add_junk 40 250 /]
										[/block]
										[/swap_blocks]
									}
									*/
[add_junk 40 250 /]
									[/block]

									[block]

									[swap_blocks]
									[block]
									if (true) {
[add_junk 40 250 /]
									[/block]

									[block]
										if (/*!is_defusing*/true) {
[add_junk 40 250 /]
									[/block]
									[/swap_blocks]

											[swap_blocks]
											[block]
											if (it->second.hp >= 50) {
[add_junk 40 250 /]
												glow_write_obj object((it->second.hp > 100 ? 1.f : remap(it->second.hp, 50, 100, 255, 0) / 255.f), 1.f, 0.f,
													0.6f, 1.f, 0, glow_obj.m_locIsZero, glow_obj.m_bGlowAlphaCappedByRenderAlpha, glow_obj.m_flGlowAlphaFunctionOfMaxVelocity);

												cs.write<glow_write_obj>(eng.m_glow_ptr + ((&glow_obj - &objects[0]) * sizeof(glowObject)) + 0x8, object, OFS_WRITE_SIZE);
											}
[add_junk 40 250 /]
											[/block]

											[block]
											if (it->second.hp < 50) {
[add_junk 40 250 /]
												glow_write_obj object(1.f, it->second.hp / 100.f, 0.f, 0.6f,
													1.f, 0, glow_obj.m_locIsZero, glow_obj.m_bGlowAlphaCappedByRenderAlpha, glow_obj.m_flGlowAlphaFunctionOfMaxVelocity);

												cs.write<glow_write_obj>(eng.m_glow_ptr + ((&glow_obj - &objects[0]) * sizeof(glowObject)) + 0x8, object, OFS_WRITE_SIZE);
											}
[add_junk 40 250 /]
											[/block]
											[/swap_blocks]
										}
[add_junk 40 250 /]
									}
[add_junk 40 250 /]
									[/block]
									[/swap_blocks]
								}
[add_junk 40 250 /]
								[/block]

								[block]
								if (
									[swap_lines]
									cs.read<int>(glow_obj.base + OFS_HP) > 0 &&
									it == eng.m_enemy_players.end() &&
									[/swap_lines]
									true) {
[add_junk 40 250 /]

									if (settings[GLOW_ALLY] == 1) {
										//allies
										glow_write_obj object(0.7f, 0.f, 1.f, 0.6f,
											1.f, 0, glow_obj.m_locIsZero, glow_obj.m_bGlowAlphaCappedByRenderAlpha, glow_obj.m_flGlowAlphaFunctionOfMaxVelocity);

										if (glow_obj.base != eng.m_local) {
											cs.write<glow_write_obj>(eng.m_glow_ptr + ((&glow_obj - &objects[0]) * sizeof(glowObject)) + 0x8, object, OFS_WRITE_SIZE);
										}
									}
									
								} else if (cs.read_bytes(glow_obj.base + OFS_TEAM, &team, 4) &&
									[swap_lines]
									(team == 2 || team == 3) &&
									it == eng.m_enemy_players.end() &&
									[/swap_lines]
									true) {
[add_junk 40 250 /]

									if (settings[GLOW_ITEM] == 1) {
										//items
										glow_write_obj object(0.f, 1.f, 1.f, 0.6f,
											1.f, 0, glow_obj.m_locIsZero, glow_obj.m_bGlowAlphaCappedByRenderAlpha, glow_obj.m_flGlowAlphaFunctionOfMaxVelocity);

										cs.write<glow_write_obj>(eng.m_glow_ptr + ((&glow_obj - &objects[0]) * sizeof(glowObject)) + 0x8, object, OFS_WRITE_SIZE);
									}
								} else if (
									[swap_lines]
									cs.read<int>(glow_obj.base + OFS_FLAGS) != 0 && 
									it == eng.m_enemy_players.end() &&
									[/swap_lines]
									true) {
[add_junk 40 250 /]

									if (settings[GLOW_BOMB] == 1) {
										//bomb
										glow_write_obj object(0.f, 0.f, 1.f, 0.6f,
											1.f, 0, glow_obj.m_locIsZero, glow_obj.m_bGlowAlphaCappedByRenderAlpha, glow_obj.m_flGlowAlphaFunctionOfMaxVelocity);

										cs.write<glow_write_obj>(eng.m_glow_ptr + ((&glow_obj - &objects[0]) * sizeof(glowObject)) + 0x8, object, OFS_WRITE_SIZE);
									}
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
[add_junk 40 250 /]
	}
[add_junk 40 250 /]
}