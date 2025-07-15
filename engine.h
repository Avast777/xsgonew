#pragma once
[swap_lines]
#include <thread>
#include <vector>
#include <map>

#include "func.h"
#include "vec.h"
#include "defines.h"
[/swap_lines]

using namespace std;

[swap_blocks]
[block]

[junk_enable 40 360 /]

[junk_enable_declares /]

struct player {
[swap_lines]
	player();
	player(int, int, int, bool, const cs_vector &, const cs_vector &, const cs_vector &, bool);
	void update(int, int, int, bool, const cs_vector &, const cs_vector &, const cs_vector &, bool);
	int id;
	int team;
	int hp;
	bool is_airborne;
	cs_vector vec_view;
	cs_vector vec_velocity;
	cs_vector vec_origin;
	bool valid;
	bool fell;
	size_t air_count;
[/swap_lines]
};

struct enemy : public player {
[swap_lines]
	enemy(int, int, int, bool, const cs_vector &, const cs_vector &, const cs_vector &, bool, bool, bool, bool, float);
	void update(int, int, int, bool, const cs_vector &, const cs_vector &, const cs_vector &, bool, bool, bool, bool, int, float);
	bool is_visible;
	bool is_defusing;
	bool has_defuser;
	bool falling;
	bool shooting;
	size_t shoot_count;
	size_t jump_count;
	int ammo;
	float distance;
[/swap_lines]
};

class engine {
	[swap_blocks]
	[block]
public:
[swap_lines]
	engine(csgoMem *, offsetsAll *, int);
	void run();

	bool m_panic;
	bool m_mouse;
	bool m_write_ready;
	bool m_game_ready;
	DWORD m_engine_ptr;
	DWORD m_glow_ptr;
	DWORD m_local;
	player m_me;
	float m_sensitivity;
	map<DWORD, enemy> m_enemy_players;
[/swap_lines]
	[/block]

	[block]
private:
[swap_lines]
	void invalidate();
	void dump();

	bool m_teamMode;
	csgoMem * m_cs_mem;
	offsetsAll * m_offs;
	thread e1;
[/swap_lines]
	[/block]
	[/swap_blocks]
};
[junk_disable /]
[/block]

[block]
struct entity_data {
	uint8_t unk1[OFS_ID];
	int id;
	uint8_t unk2[OFS_DORMANT - OFS_ID - 4];
	bool dormant;
	uint8_t unk3[OFS_TEAM - OFS_DORMANT - 1];
	int team;
	uint8_t unk4[OFS_HP - OFS_TEAM - 4];
	int hp;
	int flags;
	cs_vector view;
	cs_vector velocity;
	uint8_t unk7[OFS_VEC_ORIGIN - OFS_VELOCITY - 12];
	cs_vector origin;
};
[/block]

[block]
struct glowObject {	
	WORD m_nNextFreeSlot;
	DWORD base;
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
	char _0x0025[13];
};
[/block]
[/swap_blocks]

[junk_enable 40 360 /]

[junk_disable_declares /]

[swap_blocks]
[block]
player::player() {
[add_junk 120 1000 /]
[swap_lines]
	fell = false;
	air_count = 0;
[/swap_lines]
}
[/block]

[block]
player::player(int i, int te, int h, bool ai, const cs_vector & view, const cs_vector & velocity, const cs_vector & origin, bool va) {
[add_junk 120 1000 /]
[swap_lines]
	id = i;
	team = te;
	hp = h;
	is_airborne = ai;
	vec_view = view;
	vec_velocity = velocity;
	vec_origin = origin;
	valid = va;
	fell = false;
	air_count = 0;
[/swap_lines]
}
[/block]

[block]
void player::update(int i, int te, int h, bool ai, const cs_vector & view, const cs_vector & velocity, const cs_vector & origin, bool va) {
[add_junk 120 1000 /]
[swap_lines]
	id = i;
	team = te;
	hp = h;
	vec_view = view;
	vec_velocity = velocity;
	vec_origin = origin;
	valid = va;
[/swap_lines]

	if (
		[swap_lines]
		fell ||
		(!ai && is_airborne) ||
		[/swap_lines]
		false) {
[add_junk 120 1000 /]

[swap_lines]
		++air_count;
		fell = true;
[/swap_lines]
		if (air_count > 21) {
[add_junk 120 1000 /]

[swap_lines]
			air_count = 0;
			fell = false;
[/swap_lines]
		}
[add_junk 120 1000 /]
	}
[add_junk 120 1000 /]

	is_airborne = ai;
}
[/block]

[block]
enemy::enemy(int i, int te, int h, bool ai, const cs_vector & view, const cs_vector & velocity, const cs_vector & origin, bool va, bool vi, bool de, bool hd, float dist)
	: player(i, te, h, ai, view, velocity, origin, va) {
[add_junk 120 1000 /]
[swap_lines]
		is_visible = vi;
		is_defusing = de;
		has_defuser = hd;
		falling = false;
		shooting = false;
		shoot_count = 0;
		jump_count = 0;
		ammo = 0;
		distance = dist;
[/swap_lines]
	}
[/block]

[block]
void enemy::update(int i, int te, int h, bool ai, const cs_vector & view, const cs_vector & velocity, const cs_vector & origin, bool va, bool vi, bool de, bool hd, int am, float dist) {
[add_junk 120 1000 /]
[swap_lines]
	id = i;
	team = te;
	hp = h;
	is_airborne = ai;
	vec_view = view;
	vec_velocity = velocity;
	vec_origin = origin;
	valid = va;
	is_visible = vi;
	is_defusing = de;
	has_defuser = hd;
	distance = dist;
[/swap_lines]

	[swap_blocks]
	[block]
	if (velocity.m_z < -265.f) {
[add_junk 120 1000 /]
		falling = true;
	}
[add_junk 120 1000 /]
	[/block]

	[block]

	[swap_blocks]
	[block]
	if (falling) {
[add_junk 120 1000 /]
	[/block]

	[block]
		if (velocity.m_z > -5.f) {
[add_junk 120 1000 /]
	[/block]

	[block]
			if (velocity.m_z < 5.f) {
[add_junk 120 1000 /]
	[/block]
	[/swap_blocks]

				++jump_count;
				if (jump_count > 100) {
[add_junk 120 1000 /]
					[swap_lines]
					jump_count = 0;
					falling = false;
					[/swap_lines]
				}
[add_junk 120 1000 /]
			}
[add_junk 120 1000 /]
		}
[add_junk 120 1000 /]
	}
[add_junk 120 1000 /]
	[/block]

	[block]

	[swap_blocks]
	[block]
	if (am >= 0 || shooting) {
[add_junk 120 1000 /]
	[/block]

	[block]
		if (am < ammo || shooting) {
[add_junk 120 1000 /]
	[/block]

	[block]
			if (ammo - am < 5 || shooting) {
[add_junk 120 1000 /]
	[/block]
	[/swap_blocks]

				[swap_lines]
				++shoot_count;
				shooting = true;
				[/swap_lines]
				if (shoot_count > 100) {
[add_junk 120 1000 /]
					[swap_lines]
					shoot_count = 0;
					shooting = false;
					[/swap_lines]
				}
[add_junk 120 1000 /]
			}
[add_junk 120 1000 /]
		}
[add_junk 120 1000 /]
	}
[add_junk 120 1000 /]
	ammo = am;
	[/block]
	[/swap_blocks]
}
[/block]

[block]
engine::engine(csgoMem * cs_mem, offsetsAll * offs, int mode) : e1(&engine::run, this) {
[add_junk 120 1000 /]
[swap_lines]
	m_panic = false;
	m_mouse = false;
	m_write_ready = false;
	m_game_ready = false;
	m_engine_ptr = cs_mem->read<DWORD>(cs_mem->m_engine_dll + offs->dyn.at(ENGINE));
	m_glow_ptr = 0;
	m_local = 0;
	m_sensitivity = 1.f;
	m_cs_mem = cs_mem;
	m_offs = offs;
	m_teamMode = mode == 0;
[/swap_lines]
}
[/block]

[block]
void engine::invalidate() {
[add_junk 120 1000 /]
	for (auto & player : m_enemy_players) {
[add_junk 120 1000 /]
		player.second.valid = false;
	}
[add_junk 120 1000 /]
}
[/block]

[block]
void engine::dump() {
[add_junk 120 1000 /]
	for (auto it = m_enemy_players.begin(); it != m_enemy_players.end(); ) {
[add_junk 120 1000 /]
		if (!it->second.valid) {
[add_junk 120 1000 /]
			m_enemy_players.erase(it++);
		} else {
[add_junk 120 1000 /]
			++it;
		}
[add_junk 120 1000 /]
	}
[add_junk 120 1000 /]
}
[/block]

[block]
void engine::run() {
[add_junk 20 50 /]
	int tmp_sens = 0;

	while (true) {
[add_junk 120 1000 /]
		_Sleep(5);
		engine::dump();

		engine::invalidate();
[swap_lines]
		int mouse_enabled = m_cs_mem->read<int>(m_cs_mem->m_client_dll + m_offs->dyn.at(MOUSE)) ^ (m_cs_mem->m_client_dll + m_offs->dyn.at(MOUSE) - OFS_MOUSE_ENABLE);
		int game_state = m_cs_mem->read<int>(m_engine_ptr + m_offs->st.client_state);
		m_glow_ptr = m_cs_mem->read<DWORD>(m_cs_mem->m_client_dll + m_offs->dyn.at(GLOW));
		m_local = m_cs_mem->read<DWORD>(m_cs_mem->m_client_dll + m_offs->dyn.at(LOCAL_PLAYER));
[/swap_lines]
[swap_lines]
		m_game_ready = (mouse_enabled == 1) && (game_state == IN_GAME) && (m_glow_ptr != 0) && (!m_panic);
		m_mouse = (mouse_enabled == 1);
		m_write_ready = (game_state == IN_GAME) && (m_glow_ptr != 0) && (!m_panic);
[/swap_lines]

		if (!m_game_ready) {
[add_junk 120 1000 /]
			engine::dump();
			_Sleep(500);
			continue;
		}
[add_junk 120 1000 /]
		
		tmp_sens = m_cs_mem->read<int>(m_cs_mem->m_client_dll + m_offs->dyn.at(SENS)) ^ (m_cs_mem->m_client_dll + m_offs->dyn.at(SENS) - OFS_SENS);
		m_sensitivity = *reinterpret_cast<float*>(&tmp_sens);

		if (m_sensitivity > 1000.f || m_sensitivity < 0.f) {
[add_junk 120 1000 /]
			m_sensitivity = 1.f;
		}
[add_junk 120 1000 /]
		
		size_t object_count = m_cs_mem->read<size_t>(m_cs_mem->m_client_dll + m_offs->dyn.at(GLOW) + OFS_GLOW_COUNT);
		vector<glowObject> objects(object_count);
		m_cs_mem->read_bytes(m_glow_ptr, &objects[0], sizeof(glowObject) * object_count);
[swap_lines]
		int my_team = m_cs_mem->read<int>(m_local + OFS_TEAM);
		int my_id_dec = m_cs_mem->read<int>(m_local + OFS_ID) - 1;
[/swap_lines]

		for (auto & entity : objects) {
[add_junk 120 1000 /]
			if (entity.base != 0) {
[add_junk 120 1000 /]
				if (entity.base == m_local) {
[add_junk 120 1000 /]

					entity_data ent = m_cs_mem->read<entity_data>(entity.base);
					m_me.update(ent.id, ent.team, ent.hp, !(ent.flags & 0x1), ent.view, ent.velocity, ent.origin, true);
				} else {
[add_junk 120 1000 /]

					int hp = m_cs_mem->read<int>(entity.base + OFS_HP);
					if (hp > 0 && hp < 10000) {
[add_junk 120 1000 /]

						entity_data ent = m_cs_mem->read<entity_data>(entity.base);
						if ((ent.team != my_team || m_teamMode) && !ent.dormant) {
[add_junk 120 1000 /]

							auto it = m_enemy_players.find(entity.base);
							if (it == m_enemy_players.end()) {
[add_junk 120 1000 /]
								m_enemy_players.emplace(entity.base, enemy(ent.id, ent.team, ent.hp, !(ent.flags & 0x1), ent.view, ent.velocity, ent.origin, true,
									(m_cs_mem->read<int>(entity.base + m_offs->st.spotted_mask) & (0x1 << my_id_dec)) != 0 || m_teamMode,
									m_cs_mem->read<int>(entity.base + m_offs->st.is_defusing) == 1, m_cs_mem->read<int>(entity.base + m_offs->st.has_defuser) == 1, m_me.vec_origin * ent.origin));
							} else {
[add_junk 120 1000 /]
								it->second.update(ent.id, ent.team, ent.hp, !(ent.flags & 0x1), ent.view, ent.velocity, ent.origin, true,
									(m_cs_mem->read<int>(entity.base + m_offs->st.spotted_mask) & (0x1 << my_id_dec)) != 0 || m_teamMode,
									m_cs_mem->read<int>(entity.base + m_offs->st.is_defusing) == 1, m_cs_mem->read<int>(entity.base + m_offs->st.has_defuser) == 1,
									m_cs_mem->read<int>(m_cs_mem->read<DWORD>(m_cs_mem->m_client_dll + m_offs->dyn.at(ENTITY_LIST) + ((m_cs_mem->read<int>(it->first + m_offs->st.active_weapon) & 0xFFF) - 1) * 0x10) + m_offs->st.clip), m_me.vec_origin * ent.origin);
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
[/block]
[/swap_blocks]