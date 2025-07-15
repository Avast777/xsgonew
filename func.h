#pragma once
[swap_lines]
#include <windows.h>
#include <unordered_map>

#include "proxy.h"
#include "defines.h"
[/swap_lines]

using namespace std;

[swap_blocks]
[block]

[junk_enable 40 360 /]

[junk_enable_declares /]
struct weaponCfg {
	[swap_lines]
	weaponCfg(int, int, int, int, int, int, int, int, int, int, int, int, int);

	float smoothing;
	int update_time;
	float aura_horizontal;
	float aura_vertical;
	int bullet_start;
	int force_bone;
	int adrenaline_rush;
	bool vis_check;
	bool aim_inair;
	int aim_key;
	float silent_fov;
	int silent_bone;
	int silent_key;
	[/swap_lines]
};
[junk_disable /]

[/block]

[block]
struct ofsData {
	DWORD spotted = 0x93D;
	DWORD ct_t_knife_diff = 25;
	DWORD spotted_mask = 0x980;
	DWORD matrix_bone = 0x26A8;
	DWORD model_index = 0x258;
	DWORD active_weapon = 0x2F08;
	DWORD client_state = 0x108;
	DWORD my_weapons = 0x2E08;
	DWORD crosshair_id = 0x11438;
	DWORD clip = 0x3274;
	DWORD vec_punch = 0x303C;
	DWORD shots_fired = 0x103E0;
	DWORD flash_alpha = 0x1046C;
	DWORD is_defusing = 0x997C;
	DWORD has_defuser = 0x113DC;
	DWORD is_scoped = 0x9974;
	DWORD item_id_high = 0x2FD0;
	DWORD xuid_low = 0x31D0;
	DWORD definition_index = 0x2FBA;
	DWORD next_attack = 0x2D80;
	DWORD tick_base = 0x3440;
	DWORD t_fancy_knife_diff = 65;
	DWORD view_model = 0x3308;
	DWORD compet_ranking = 0x1A84;
	DWORD compet_wins = 0x1B88;
};

struct offsetsAll {
[junk_enable 40 360 /]

[junk_enable_declares /]

	[swap_lines]
	unordered_map<int, DWORD> dyn;
	ofsData st;
	[/swap_lines]

[junk_disable /]
};
[/block]

[block]
[junk_enable 40 360 /]

[junk_enable_declares /]
class csgoMem {
[swap_blocks]
[block]
public:
	[swap_blocks]
	[block]
	csgoMem(HANDLE, DWORD, DWORD, DWORD, DWORD);
	[/block]

	[block]
	~csgoMem();
	[/block]

	[block]
	bool read_bytes(DWORD, void *, size_t) const;
	[/block]

	[block]
	template<typename T>
	T read(DWORD) const;
	[/block]

	[block]
	template<typename T>
	void write(DWORD, const T &) const;
	[/block]

	[block]
	template<typename T>
	void write(DWORD, const T &, size_t) const;
	[/block]

	[block]
	DWORD m_client_dll;
	[/block]

	[block]
	DWORD m_client_size;
	[/block]

	[block]
	DWORD m_engine_dll;
	[/block]

	[block]
	DWORD m_engine_size;
	[/block]
	[/swap_blocks]

[/block]

[block]
private:
	HANDLE m_cs_handle;
[/block]
[/swap_blocks]
};
[junk_disable /]

[/block]
[/swap_blocks]

[junk_enable 40 360 /]

[junk_disable_declares /]

[swap_blocks]
[block]
weaponCfg::weaponCfg(int smo, int upd, int auh, int auv, int bul, int fob, int adr, int vis, int air, int aik, int fov, int sbn, int sik) {
[add_junk 120 1000 /]
	[swap_lines]
	smoothing = (smo > 0 ? float(smo) : 1.f);
	update_time = (upd >= 0 ? upd : 1);
	aura_horizontal = (auh > 0 ? float(auh) : 1.f);
	aura_vertical = (auv > 0 ? float(auv) : 1.f);
	bullet_start = bul;
	force_bone = fob;
	adrenaline_rush = adr;
	vis_check = (vis == 1);
	aim_inair = (air == 1);
	aim_key = aik;
	silent_fov = (fov > 0 && fov <= 380 ? float(fov) / 10.f : 38.f);
	silent_bone = (sbn >= 0 ? sbn : BONE_HEAD);
	silent_key = sik;
	[/swap_lines]
}
[/block]

[block]
csgoMem::csgoMem(HANDLE cs_handle, DWORD c_dll, DWORD c_size, DWORD e_dll, DWORD e_size) {
[add_junk 120 1000 /]
	[swap_lines]
	m_client_dll = c_dll;
	m_client_size = c_size;
	m_engine_dll = e_dll;
	m_engine_size = e_size;
	m_cs_handle = cs_handle;
	[/swap_lines]
}
[/block]

[block]
csgoMem::~csgoMem() {
[add_junk 120 1000 /]
	CloseHandle(m_cs_handle);
}
[/block]

[block]
bool csgoMem::read_bytes(DWORD address, void * buffer, size_t size) const {
[add_junk 120 1000 /]
	return _ReadProcessMemory(m_cs_handle, (void*)address, buffer, size, NULL);
}
[/block]

[block]
template<typename T>
T csgoMem::read(DWORD address) const {
[add_junk 120 1000 /]
	T ret;
	_ReadProcessMemory(m_cs_handle, (void*)address, &ret, sizeof(T), NULL);
	return ret;
}
[/block]

[block]
template<typename T>
void csgoMem::write(DWORD address, const T & value) const {
[add_junk 120 1000 /]
	_WriteProcessMemory(m_cs_handle, (void*)address, &value, sizeof(T), NULL);
}
[/block]

[block]
template<typename T>
void csgoMem::write(DWORD address, const T & value, size_t byte_count) const {
[add_junk 120 1000 /]
	_WriteProcessMemory(m_cs_handle, (void*)address, &value, byte_count, NULL);
}
[/block]

[block]
inline int remap(int value, int low1, int high1, int low2, int high2) {
[add_junk 120 1000 /]
	return low2 + (value - low1) * (high2 - low2) / (high1 - low1);
}
[/block]
[/swap_blocks]