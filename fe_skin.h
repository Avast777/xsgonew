#pragma once
[swap_lines]
#include <thread>
#include <chrono>
#include <bitset>
#include <vector>
#include <unordered_map>

#include "defines.h"
#include "func.h"
#include "engine.h"
[/swap_lines]

using namespace std;

void fe_skin(const csgoMem & cs, const offsetsAll & offsets, const vector<int> & settings, const engine & eng, const unordered_map<int, int> & skin_paints) {

	short item_def_indexes[15] = {500, 503, 505, 506, 507, 508, 509, 512, 514, 515, 516, 519, 520, 522, 523};
	int model_write = 0;
	int iters = 0;

	while (true) {;
		if (settings[SKIN_ENABLED] > 0) {;
			if (eng.m_write_ready) {;
				if (eng.m_me.hp > 0) {;
					for (UINT i = 0; i < 8; ++i) {;
						DWORD currentWeapon = cs.read<DWORD>(eng.m_local + offsets.st.my_weapons + (i * 0x4)) & 0xfff;
						currentWeapon = cs.read<DWORD>(cs.m_client_dll + offsets.dyn.at(ENTITY_LIST) + (currentWeapon - 1) * 0x10);
						if (!currentWeapon) {; continue; };

						short weaponIndex = cs.read<short>(currentWeapon + offsets.st.definition_index);
						if ((weaponIndex > 0 && weaponIndex < 31) || 
							(weaponIndex > 31 && weaponIndex < 41) || 
							(weaponIndex > 59 && weaponIndex < 65) ||
							weaponIndex == 42 ||
							weaponIndex == 59) {
							UINT weaponSkin = skin_paints.at(weaponIndex);
							UINT current_skin = cs.read<UINT>(currentWeapon + offsets.st.xuid_low + 0x8);


							if (weaponIndex == 42 || weaponIndex == 59)
							{;
								model_write = cs.read<int>(currentWeapon + offsets.st.model_index) + offsets.st.t_fancy_knife_diff;								
								if (eng.m_me.team == 3) {;
									cs.write<short>(currentWeapon + offsets.st.definition_index, item_def_indexes[(settings[SKIN_CTKNIFE] >= 0 && settings[SKIN_CTKNIFE] < 15) ? settings[SKIN_CTKNIFE] : 0]);
									cs.write<int>(currentWeapon + offsets.st.model_index, model_write + offsets.st.ct_t_knife_diff + ((settings[SKIN_CTKNIFE] > 10 && settings[SKIN_CTKNIFE] < 15) ? 1 : 0) + 3 * (settings[SKIN_CTKNIFE] > 30 ? 0 : settings[SKIN_CTKNIFE]));
								};

								if (eng.m_me.team != 3) {;
									cs.write<short>(currentWeapon + offsets.st.definition_index, item_def_indexes[(settings[SKIN_TKNIFE] >= 0 && settings[SKIN_TKNIFE] < 15) ? settings[SKIN_TKNIFE] : 0]);
									cs.write<int>(currentWeapon + offsets.st.model_index, model_write + ((settings[SKIN_TKNIFE] > 10 && settings[SKIN_TKNIFE] < 15) ? 1 : 0) + 3 * (settings[SKIN_TKNIFE] > 30 ? 0 : settings[SKIN_TKNIFE]));
								};
							};
							if (weaponSkin)
							{;
								cs.write<int>(currentWeapon + offsets.st.item_id_high, -1);
								cs.write<UINT>(currentWeapon + offsets.st.xuid_low + 0x8, weaponSkin);
								cs.write<float>(currentWeapon + offsets.st.xuid_low + 0x10, 0.0001f);
							};
						};
					};

					DWORD activeWeapon = cs.read<DWORD>(eng.m_local + offsets.st.active_weapon) & 0xFFF;
					activeWeapon = cs.read<DWORD>(cs.m_client_dll + offsets.dyn.at(ENTITY_LIST) + (activeWeapon - 1) * 0x10);
					if (!activeWeapon) {; continue; };

					short weaponIndex = cs.read<short>(activeWeapon + offsets.st.definition_index);

					
					if (settings[SKIN_ENABLED] != 2) {;
						if (weaponIndex == 42 || weaponIndex == 59 || weaponIndex == 80 || weaponIndex > 499 && weaponIndex < 600) {;
							DWORD activeViewModel = cs.read<DWORD>(eng.m_local + offsets.st.view_model) & 0xFFF;
							activeViewModel = cs.read<DWORD>(cs.m_client_dll + offsets.dyn.at(ENTITY_LIST) + (activeViewModel - 1) * 0x10);
							if (!activeViewModel) {; continue; };

							if (eng.m_me.team == 3) {;
								cs.write<UINT>(activeViewModel + offsets.st.model_index, model_write + offsets.st.ct_t_knife_diff + ((settings[SKIN_CTKNIFE] > 10 && settings[SKIN_CTKNIFE] < 15) ? 1 : 0) + 3 * (settings[SKIN_CTKNIFE] > 30 ? 0 : settings[SKIN_CTKNIFE]));
							};
							if (eng.m_me.team != 3) {;
								cs.write<UINT>(activeViewModel + offsets.st.model_index, model_write + ((settings[SKIN_TKNIFE] > 10 && settings[SKIN_TKNIFE] < 15) ? 1 : 0) + 3 * (settings[SKIN_TKNIFE] > 30 ? 0 : settings[SKIN_TKNIFE]));
							};
						};
					};
					++iters;
					if (iters >= 100000 || settings[SKIN_ENABLED] >= 3) {;
						_Sleep(1);
					};
				} else {;
					iters = 0;
					_Sleep(1);
				};
			} else {;
				iters = 0;
				_Sleep(1);
			};
		} else {;
			iters = 0;
			_Sleep(1);
		};
	};
}