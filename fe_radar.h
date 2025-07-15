#pragma once
[swap_lines]
#include <thread>
#include <chrono>
#include <bitset>
#include <vector>
#include <iostream>
#include <string>

#include "defines.h"
#include "func.h"
#include "engine.h"
[/swap_lines]

using namespace std;

[junk_enable 1 200 /]


void fe_radar(const csgoMem & cs, const offsetsAll & offsets, const vector<int> & settings, const bitset<KEY_SIZE> & keys, const engine & eng, void fnc(const bitset<KEY_SIZE> &, bool, bool)) {
[add_junk 20 50 /]

const char* ranks[20] = {
	"Unranked",
	"Silver I",
	"Silver II",
	"Silver III",
	"Silver IV",
	"Silver Elite",
	"Silver Elite Master",
	"Gold Nova I",
	"Gold Nova II",
	"Gold Nova III",
	"Gold Nova Master",
	"Master Guardian I",
	"Master Guardian II",
	"Master Guardian Elite",
	"Distinguished Master Guardian",
	"Legendary Eagle",
	"Legendary Eagle Master",
	"Supreme Master First Class",
	"The Global Elite",
	"Unknown"
};
	
	int j = 0;
	while (true) {
[add_junk 40 250 /]
		_Sleep(100);
		if (eng.m_game_ready) {
[add_junk 40 250 /]

		++j;
		if (settings[RANK_ENABLED] == 1 && (j % 10) == 0) {

			DWORD player_resource = cs.read<DWORD>(cs.m_client_dll + offsets.dyn.at(RESOURCE));
			fnc(keys, false, true);
			for (auto & enemy : eng.m_enemy_players) {
				int rank = cs.read<int>(player_resource + offsets.st.compet_ranking + (enemy.second.id * 4));
				int wins = cs.read<int>(player_resource + offsets.st.compet_wins + (enemy.second.id * 4));
				if (rank < 0 || rank > 18) {
					rank = 19;
				}
				string print = "id: " + to_string(enemy.second.id) + " hp: " + to_string(enemy.second.hp) +
					" ammo: " + to_string(enemy.second.ammo) + " wins: " + to_string(wins) +
					" rank: " + string(ranks[rank]);
				cout << endl << print;
			}
		}

		[swap_blocks]
		[block]
			if (keys[KEY_RADAR]) {
[add_junk 40 250 /]
		[/block]

		[block]
				if (
					[swap_lines]
					settings[RADAR_ALIVE] != 1 || 
					eng.m_me.hp > 0 ||
					[/swap_lines]
					false) {
[add_junk 40 250 /]
		[/block]
		[/swap_blocks]

					for (auto & enemy : eng.m_enemy_players) {
[add_junk 40 250 /]
						if (enemy.second.valid) {
[add_junk 40 250 /]
							if (!cs.read<bool>(enemy.first + offsets.st.spotted)) {
[add_junk 40 250 /]
								cs.write<bool>(enemy.first + offsets.st.spotted, true);
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