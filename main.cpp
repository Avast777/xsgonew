#define NOMINMAX

#include <windows.h> //windows.h has to be before tlhelp32.h
#include <tlhelp32.h> //windows.h has to be before tlhelp32.h

[swap_lines]
#include <iostream>
#include <vector>
#include <unordered_map>
#include <limits>
#include <thread>
#include <functional>
#include <bitset>
#include <memory>
#include <iomanip>
#include <ctime>
#include <filesystem>
#include <shlobj.h>
#include <winerror.h>

#include "fe_aim.h"
#include "fe_silent.h"
#include "fe_bhop.h"
#include "fe_recoil.h"
#include "fe_junk1.h"
#include "fe_junk2.h"
#include "fe_junk3.h"
#include "fe_junk4.h"
#include "fe_sound.h"
#include "func.h"
#include "enc.h"
#include "file_sys.h"
#include "scanner.h"
#include "defines.h"
#include "engine.h"
#include "fe_radar.h"
#include "fe_glow_player.h"
#include "fe_skin.h"
#include "fe_trigger.h"
[/swap_lines]

using namespace std;
using namespace std::experimental::filesystem::v1;

[junk_enable 40 360 /]


void update_console(const bitset<KEY_SIZE> & keys, bool on, bool external = false) {
[add_junk 120 1000 /]

	[swap_blocks]
	[block]
	if (keys[SOUND_SLOT]) {
[add_junk 120 1000 /]

		[swap_blocks]
		[block]
		if (on && !external) {
[add_junk 120 1000 /]

			[swap_lines]
			_Beep(300, 100);
			_Beep(300, 140);
			[/swap_lines]
		}
[add_junk 120 1000 /]
		[/block]

		[block]
		if (!on && !external) {
[add_junk 120 1000 /]
			_Beep(600, 250);
		}
[add_junk 120 1000 /]
		[/block]
		[/swap_blocks]
	}
[add_junk 120 1000 /]
	[/block]

	[block]
	if (!keys[SLOAD_SLOT]) {
[add_junk 120 1000 /]

		[swap_blocks]
		[block]
		system("cls");
		[/block]

		[block]
		unsigned char featon_data[16] = { _CHAR2_, _CHAR1_, 'O', _CHAR3_, _CHAR8_, _CHAR7_, 'N', _CHAR6_,
			_CHAR3_, _CHAR4_, _CHAR5_, _CHAR7_, _CHAR7_, _CHAR4_, _CHAR3_, _CHAR1_ };
		encString featon(featon_data, 0b0010001000000000);
		[/block]

		[block]
		unsigned char featoff_data[16] = { _CHAR7_, _CHAR8_, _CHAR1_, _CHAR3_, _CHAR2_, 'O', _CHAR7_, _CHAR5_,
			_CHAR4_, 'F', _CHAR6_, _CHAR7_, _CHAR8_, 'F', _CHAR3_, _CHAR5_ };
		encString featoff(featoff_data, 0b0000010001000100);
		[/block]
		[/swap_blocks]

		[swap_blocks]
		[block]
		unsigned char norecoil_data[16] = { _CHAR2_, 'R', 'C', _CHAR5_, 'S', _CHAR8_, ':', _CHAR7_,
			' ', _CHAR2_, ' ', _CHAR3_, ' ', ' ', _CHAR1_, ' ' };
		encString norecoil(norecoil_data, 0b0110101010101101);
		cout << norecoil << setw(5) << (keys[KEY_RECOIL] ? featon : featoff) << '\n';
		[/block]

		[block]
		cout << "Radar:   " << setw(5) << (keys[KEY_RADAR] ? featon : featoff) << '\n';
		[/block]

		[block]
		cout << "WH:      " << setw(5) << (keys[KEY_GLOW] ? featon : featoff) << '\n';
		[/block]
		[/swap_blocks]

		cout << endl;
	}
[add_junk 120 1000 /]
	[/block]
	[/swap_blocks]
[add_junk 120 1000 /]
}

bool setTimerCaps() {;
	[swap_lines]
	TIMECAPS tc;
	UINT wTimerRes;
	[/swap_lines]
	if (timeGetDevCaps(&tc, sizeof(TIMECAPS)) != TIMERR_NOERROR) {;
		return false;
	};
	wTimerRes = std::min(std::max(tc.wPeriodMin, UINT(1)), tc.wPeriodMax);
	timeBeginPeriod(wTimerRes);
	return true;
}

int main(int argc, char ** argv) {
[add_junk 20 50 /]

	[swap_lines]
	offsetsAll offsets;
	vector<int> settings;
	string cfg_name;
	[/swap_lines]

	initialize_functions();
	if (!setTimerCaps()) {;
		cout << "caps error" << endl;
		return 2;
	};

[add_junk 120 1000 /]

[swap_blocks]	
[block]
	/* CONFIG FILE INPUT SCOPE */
	{
		unsigned char enter_cfg_data[16] = { _CHAR1_, 'c', _CHAR2_, _CHAR3_, 'o', _CHAR6_, _CHAR6_, 'n',
			'f', _CHAR3_, 'i', _CHAR4_, 'g', _CHAR7_, _CHAR2_, _CHAR8_ };
		encString enter_cfg(enter_cfg_data, 0b0100100110101000);

		cfg_name = enter_cfg.str() + ".txt";

		for (int i = 0; !f_exists(cfg_name); ++i) {
[add_junk 120 1000 /]

			[swap_blocks]
			[block]
			if (i == 0) {
[add_junk 120 1000 /]
				cout << "cfg name:" << endl;
			}
[add_junk 120 1000 /]
			[/block]

			[block]
			if (i != 0) {
[add_junk 120 1000 /]
				cout << "error, try again:" << endl;
			}
[add_junk 120 1000 /]
			[/block]
			[/swap_blocks]

			cin >> cfg_name;
			cfg_name += ".txt";
		}
[add_junk 120 1000 /]

	}
[/block]
	
[block]
	/*  OFFSET FILE INPUT SCOPE */
	{
		unsigned char ofs_name_data[16] = { 'd', _CHAR1_, _CHAR2_, _CHAR5_, _CHAR8_, 'a', _CHAR7_, _CHAR6_,
			_CHAR4_, 't', _CHAR2_, _CHAR1_, _CHAR5_, _CHAR8_, 'a', _CHAR4_ };
		encString ofs_name(ofs_name_data, 0b1000010001000010);

		[swap_blocks]
		[block]
		if (!f_exists(ofs_name)) {
[add_junk 120 1000 /]

			ofstream ofs(ofs_name.str(), ios::binary);
			if (ofs.is_open()) {
[add_junk 120 1000 /]

				ofs.write((char*)&offsets.st, sizeof(offsets.st));
				ofs.close();
			}
[add_junk 120 1000 /]
		}
[add_junk 120 1000 /]
		[/block]

		[block]
		if (f_exists(ofs_name)) {
[add_junk 120 1000 /]

			ifstream ofs(ofs_name.str(), ios::binary);
			if (ofs.is_open()) {
[add_junk 120 1000 /]

				ofs.read((char*)&offsets.st, sizeof(offsets.st));
				ofs.close();
			}
[add_junk 120 1000 /]
		}
[add_junk 120 1000 /]
		[/block]
		[/swap_blocks]
	}
[/block]
[/swap_blocks]

	/*  CONFIG FILE  */
	{
		ifstream cfg(cfg_name);
		cfg.ignore(numeric_limits<streamsize>::max(), '=');
		for (int tmp; cfg >> tmp; ) {
[add_junk 120 1000 /]

			settings.push_back(tmp);
			cfg.ignore(numeric_limits<streamsize>::max(), '=');
		}
[add_junk 120 1000 /]
		cfg.close();

		if (settings.size() != CFG_SIZE) {
[add_junk 120 1000 /]

			cout << settings.size() << " =!= " << CFG_SIZE << endl;
			_Sleep(5000);
			return 1;
		}
[add_junk 120 1000 /]
	}
		
[swap_blocks]
[block]
	/* SILENT LOAD */
	if (settings[OTR_SLOAD] == 1) {
[add_junk 120 1000 /]
		FreeConsole();
	}
[add_junk 120 1000 /]
[/block]

[block]
	/* SKIN PARSING */
	unordered_map<int, int> skin_paintkits;

	for (int i = SKIN_START, j = 1; i < SKIN_START + SKIN_SIZE; ++i, ++j) {
[add_junk 40 250 /]

		[swap_blocks]
		[block]
		if (j == 5) {
[add_junk 40 250 /]
			j += 2;
		}
[add_junk 40 250 /]
		[/block]

		[block]
		if (j == 12) {
[add_junk 40 250 /]
			++j;
		}
[add_junk 40 250 /]
		[/block]

		[block]
		if (j == 15) {
[add_junk 40 250 /]
			++j;
		}
[add_junk 40 250 /]
		[/block]

		[block]
		if (j == 18) {
[add_junk 40 250 /]
			++j;
		}
[add_junk 40 250 /]
		[/block]

		[block]
		if (j == 20) {
[add_junk 40 250 /]

			j += 4;
			skin_paintkits[j - 1] = settings[i];
		}
[add_junk 40 250 /]
		[/block]

		[block]
		if (j == 31) {
[add_junk 40 250 /]
			++j;
		}
[add_junk 40 250 /]
		[/block]

		[block]
		if (j == 37) {
[add_junk 40 250 /]
			++j;
		}
[add_junk 40 250 /]
		[/block]

		[block]
		if (j == 41) {
[add_junk 40 250 /]
			++j;
		}
[add_junk 40 250 /]
		[/block]

		[block]
		if (j == 43) {
[add_junk 40 250 /]
			j += 16;
		}
[add_junk 40 250 /]
		[/block]

		[block]
		if (j == 62) {
[add_junk 40 250 /]
			++j;
		}
[add_junk 40 250 /]
		[/block]
		[/swap_blocks]

		skin_paintkits[j] = settings[i];
	}
[add_junk 40 250 /]
[/block]

[block]
	/* WPN PARSING */
	unordered_map<int, shared_ptr<weaponCfg>> weapon_cfg;

	for (int i = 0; i < AIM_SECT; ++i) {
[add_junk 120 1000 /]

		
		shared_ptr<weaponCfg> tmp(new weaponCfg(settings[AIM_START + (i * SECTION_ITEMS) + 0], settings[AIM_START + (i * SECTION_ITEMS) + 1], settings[AIM_START + (i * SECTION_ITEMS) + 2],
			settings[AIM_START + (i * SECTION_ITEMS) + 3], 0, settings[AIM_START + (i * SECTION_ITEMS) + 4],
			20, settings[AIM_START + (i * SECTION_ITEMS) + 5], settings[AIM_START + (i * SECTION_ITEMS) + 6],
			settings[AIM_START + (i * SECTION_ITEMS) + 7], settings[AIM_START + (i * SECTION_ITEMS) + 8], settings[AIM_START + (i * SECTION_ITEMS) + 9], settings[AIM_START + (i * SECTION_ITEMS) + 10]));

		[swap_blocks]
		[block]
		if (i == 0) {
[add_junk 120 1000 /]
			weapon_cfg[7] = tmp;
		}
[add_junk 120 1000 /]
		[/block]

		[block]
		if (i == 1) {
[add_junk 120 1000 /]

			[swap_lines]
			weapon_cfg[16] = tmp;
			weapon_cfg[60] = tmp;
			[/swap_lines]
		}
[add_junk 120 1000 /]
		[/block]

		[block]
		if (i == 2) {
[add_junk 120 1000 /]

			weapon_cfg[9] = tmp;
		}
[add_junk 120 1000 /]
		[/block]

		[block]
		if (i == 3) {
[add_junk 120 1000 /]

			weapon_cfg[1] = tmp;
		}
[add_junk 120 1000 /]
		[/block]

		[block]
		if (i == 4) {
[add_junk 120 1000 /]

			weapon_cfg[40] = tmp;
		}
[add_junk 120 1000 /]
		[/block]

		[block]
		if (i == 5) {
[add_junk 120 1000 /]

			[swap_lines]
			weapon_cfg[8] = tmp;
			weapon_cfg[10] = tmp;
			weapon_cfg[13] = tmp;
			weapon_cfg[39] = tmp;
			[/swap_lines]
		}
[add_junk 120 1000 /]
		[/block]

		[block]
		if (i == 6) {
[add_junk 120 1000 /]

			[swap_lines]
			weapon_cfg[2] = tmp;
			weapon_cfg[3] = tmp;
			weapon_cfg[4] = tmp;
			weapon_cfg[30] = tmp;
			weapon_cfg[31] = tmp;
			weapon_cfg[32] = tmp;
			weapon_cfg[36] = tmp;
			weapon_cfg[61] = tmp;
			weapon_cfg[63] = tmp;
			weapon_cfg[64] = tmp;
			[/swap_lines]
		}
[add_junk 120 1000 /]
		[/block]

		[block]
		if (i == 7) {
[add_junk 120 1000 /]

			[swap_lines]
			weapon_cfg[17] = tmp;
			weapon_cfg[19] = tmp;
			weapon_cfg[23] = tmp;
			weapon_cfg[24] = tmp;
			weapon_cfg[26] = tmp;
			weapon_cfg[33] = tmp;
			weapon_cfg[34] = tmp;
			[/swap_lines]
		}
[add_junk 120 1000 /]
		[/block]

		[block]
		if (i == 8) {
[add_junk 120 1000 /]

			[swap_lines]
			weapon_cfg[25] = tmp;
			weapon_cfg[27] = tmp;
			weapon_cfg[29] = tmp;
			weapon_cfg[35] = tmp;
			[/swap_lines]
		}
[add_junk 120 1000 /]
		[/block]

		[block]
		if (i == 9) {
[add_junk 120 1000 /]

			[swap_lines]
			weapon_cfg[11] = tmp;
			weapon_cfg[14] = tmp;
			weapon_cfg[28] = tmp;
			weapon_cfg[38] = tmp;
			[/swap_lines]
		}
[add_junk 120 1000 /]
		[/block]
		[/swap_blocks]
	}
[add_junk 120 1000 /]
[/block]

[block]
	{
		if (settings[OTR_SLOAD] != 1) {
[add_junk 120 1000 /]
			unsigned char run_csgo_data[16] = { _CHAR2_, 'r', _CHAR4_, _CHAR6_, 'u', _CHAR8_, 'n', _CHAR1_,
				' ', _CHAR3_, 'c', _CHAR4_, 's', ' ', _CHAR4_, ' ' };
			encString run_csgo(run_csgo_data, 0b0100101010101101);

			cout << run_csgo << endl;
		}
[add_junk 120 1000 /]
	}
[/block]
[/swap_blocks]

[swap_lines]
	HANDLE csgo_handle = NULL;
	DWORD client_ofs;
	DWORD client_s;
	DWORD engine_ofs;
	DWORD engine_s;
[/swap_lines]

	/* ATTACH TO CSGO */
	{
		unsigned char csgo_process_data[16] = { _CHAR4_, _CHAR5_, 'c', _CHAR3_, 's', _CHAR7_, 'g', _CHAR8_,
			'o', _CHAR6_, '.', _CHAR2_, 'e', 'x', _CHAR1_, 'e' };
		encString csgo_process(csgo_process_data, 0b0010101010101101);

		[swap_lines]
		bool csgo_found = false;
		PROCESSENTRY32 process_entry;
		[/swap_lines]

		process_entry.dwSize = sizeof(PROCESSENTRY32);

		while (!csgo_found) {
[add_junk 120 1000 /]
			HANDLE process_snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
			for (bool first = Process32First(process_snap, &process_entry); first && Process32Next(process_snap, &process_entry); ) {
[add_junk 120 1000 /]
				if (csgo_process == process_entry.szExeFile) {
[add_junk 120 1000 /]
					csgo_found = true;
					break;
				}
[add_junk 120 1000 /]
			}
[add_junk 120 1000 /]
			CloseHandle(process_snap);
			_Sleep(300);
		}
[add_junk 120 1000 /]

		[swap_lines]
		int modules_found = 0;
		MODULEENTRY32 module_entry;
		[/swap_lines]


		module_entry.dwSize = sizeof(MODULEENTRY32);

		while (modules_found != 0b11) {
[add_junk 120 1000 /]
			HANDLE module_snap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, process_entry.th32ProcessID);
			for (bool first = Module32First(module_snap, &module_entry); first && Module32Next(module_snap, &module_entry); ) {
[add_junk 120 1000 /]

				[swap_blocks]
				[block]
				if ("ient.dl" == string(module_entry.szModule).substr(2, 7)) {
[add_junk 120 1000 /]
					[swap_lines]
					modules_found |= 0b01;
					client_ofs = (DWORD)module_entry.hModule;
					client_s = module_entry.modBaseSize;
					[/swap_lines]
				}
[add_junk 120 1000 /]
				[/block]

				[block]
				if ("gine.dll" == string(module_entry.szModule).substr(2, 8)) {
[add_junk 120 1000 /]
					[swap_lines]
					modules_found |= 0b10;
					engine_ofs = (DWORD)module_entry.hModule;
					engine_s = module_entry.modBaseSize;
					[/swap_lines]
				}
[add_junk 120 1000 /]
				[/block]
				[/swap_blocks]
			}
[add_junk 120 1000 /]
			CloseHandle(module_snap);
			_Sleep(1000);
		}
[add_junk 120 1000 /]

		csgo_handle = _OpenProcess(0b111000, false, process_entry.th32ProcessID);
	}

	if (csgo_handle == NULL) {
[add_junk 120 1000 /]

		cout << "XX" << endl;
		_Sleep(5000);
		return 1;
	}
[add_junk 120 1000 /]

	csgoMem cs(csgo_handle, client_ofs, client_s, engine_ofs, engine_s);

	csgo_handle = NULL;

	[swap_blocks]
	[block]
	{ /* CLIENT.DLL SCAN */
		ofsScanner client_scanner(&cs, true);
		DWORD scan_start;

		[swap_blocks]
		[block]
		/* Entity list */
		scan_start = client_scanner.scan({ 0xBB, 0x0, 0x0, 0x0, 0x0, 0x83, 0xFF, 0x01, 0x0F, 0x8C, 0x0, 0x0, 0x0, 0x0, 0x3B, 0xF8 }) + cs.m_client_dll;
		offsets.dyn[ENTITY_LIST] = cs.read<DWORD>(scan_start + 1) - cs.m_client_dll + 0;
		[/block]

		[block]
		/* Local player */
		scan_start = client_scanner.scan({ 0x8D, 0x34, 0x85, 0x00, 0x00, 0x00, 0x00, 0x89, 0x15, 0x00, 0x00, 0x00, 0x00, 0x8B, 0x41, 0x8, 0x8B, 0x48, 0x04, 0x83, 0xF9, 0xFF }) + cs.m_client_dll;
		offsets.dyn[LOCAL_PLAYER] = cs.read<DWORD>(scan_start + 3) - cs.m_client_dll + 4;
		[/block]

		[block]
		/* Glow */
		scan_start = client_scanner.scan({ 0xA1, 0x00, 0x00, 0x00, 0x00, 0xA8, 0x01, 0x75, 0x4B }) + cs.m_client_dll;
		offsets.dyn[GLOW] = cs.read<DWORD>(scan_start + 1) - cs.m_client_dll + 4;
		[/block]

		[block]
		/* Sensitivity */
		scan_start = client_scanner.scan({0x81, 0xF9, 0x0, 0x0, 0x0, 0x0, 0x75, 0x1D, 0xF3, 0x0F, 0x10, 0x05, 0x0, 0x0, 0x0, 0x0, 0xF3, 0x0F, 0x11, 0x44, 0x24, 0x0, 0x8B, 0x44, 0x24, 0x0C, 0x35, 0x0, 0x0, 0x0, 0x0, 0x89, 0x44, 0x24, 0x0C}) + cs.m_client_dll;
		offsets.dyn[SENS] = cs.read<DWORD>(scan_start + 2) - cs.m_client_dll + OFS_SENS;
		[/block]

		[block]
		/* Resources */
		scan_start = client_scanner.scan({ 0x8B, 0x3D, 0x00, 0x00, 0x00, 0x00, 0x85, 0xFF, 0x0F, 0x84, 0x00, 0x00, 0x00, 0x00, 0x81, 0xC7 }) + cs.m_client_dll;
		offsets.dyn[RESOURCE] = cs.read<DWORD>(scan_start + 2) - cs.m_client_dll;
		[/block]

		[block]
		/* Mouse enabled */
		scan_start = client_scanner.scan({ 0xB9, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x50, 0x34, 0x85, 0xC0, 0x75, 0x10 }) + cs.m_client_dll;
		offsets.dyn[MOUSE] = cs.read<DWORD>(scan_start + 1) - cs.m_client_dll + OFS_MOUSE_ENABLE;
		[/block]
		[/swap_blocks]
	}
	[/block]

	[block]
	{ /* ENGINE.DLL SCAN */
		ofsScanner engine_scanner(&cs, false);
		DWORD scan_start;

		[swap_blocks]
		[block]
		/* Engine pointer */
		scan_start = engine_scanner.scan({ 0xA1, 0x0, 0x0, 0x0, 0x0, 0x33, 0xD2, 0x6A, 0x00, 0x6A, 0x00, 0x33, 0xC9, 0x89, 0xB0 }) + cs.m_engine_dll;
		offsets.dyn[ENGINE] = cs.read<DWORD>(scan_start + 1) - cs.m_engine_dll;
		[/block]

		[block]
		/* Viewangles */
		scan_start = engine_scanner.scan({ 0xF3, 0x0F, 0x11, 0x86, 0x0, 0x0, 0x0, 0x0, 0xF3, 0x0F, 0x10, 0x44, 0x24, 0x0, 0xF3, 0x0F, 0x11, 0x86 }) + cs.m_engine_dll;
		offsets.dyn[VIEWANGLES] = cs.read<DWORD>(scan_start + 4);
		[/block]
		[/swap_blocks]
	}
	[/block]
	[/swap_blocks]

	[swap_lines]
	bitset<KEY_SIZE> keys;
	engine eng(&cs, &offsets, settings[DEV_SCAN]);
	[/swap_lines]

	[swap_lines]
	thread abs(fe_aim, ref(cs), ref(offsets), ref(eng), ref(weapon_cfg));
	thread agdfgfdfg(fe_silent, ref(cs), ref(offsets), ref(eng), ref(weapon_cfg));

	thread ewqeqw(fe_junk1, ref(cs), ref(offsets), ref(eng));
	thread ghjhg(fe_junk2, ref(cs), ref(offsets), ref(eng));
	thread nbnbvn(fe_junk3, ref(cs), ref(offsets), ref(eng));
	thread gfhghz(fe_junk4, ref(cs), ref(offsets), ref(eng));

	thread aewqeqw(fe_junk1, ref(cs), ref(offsets), ref(eng));
	thread aghjhg(fe_junk2, ref(cs), ref(offsets), ref(eng));
	thread anbnbvn(fe_junk3, ref(cs), ref(offsets), ref(eng));
	thread agfhghz(fe_junk4, ref(cs), ref(offsets), ref(eng));

	thread bewqeqw(fe_junk1, ref(cs), ref(offsets), ref(eng));
	thread bghjhg(fe_junk2, ref(cs), ref(offsets), ref(eng));
	thread bnbnbvn(fe_junk3, ref(cs), ref(offsets), ref(eng));
	thread bgfhghz(fe_junk4, ref(cs), ref(offsets), ref(eng));

	thread cewqeqw(fe_junk1, ref(cs), ref(offsets), ref(eng));
	thread cghjhg(fe_junk2, ref(cs), ref(offsets), ref(eng));
	thread cnbnbvn(fe_junk3, ref(cs), ref(offsets), ref(eng));
	thread cgfhghz(fe_junk4, ref(cs), ref(offsets), ref(eng));

	thread dewqeqw(fe_junk1, ref(cs), ref(offsets), ref(eng));
	thread dghjhg(fe_junk2, ref(cs), ref(offsets), ref(eng));
	thread dnbnbvn(fe_junk3, ref(cs), ref(offsets), ref(eng));
	thread dgfhghz(fe_junk4, ref(cs), ref(offsets), ref(eng));

	thread eewqeqw(fe_junk1, ref(cs), ref(offsets), ref(eng));
	thread eghjhg(fe_junk2, ref(cs), ref(offsets), ref(eng));
	thread enbnbvn(fe_junk3, ref(cs), ref(offsets), ref(eng));
	thread egfhghz(fe_junk4, ref(cs), ref(offsets), ref(eng));

	thread fewqeqw(fe_junk1, ref(cs), ref(offsets), ref(eng));
	thread fghjhg(fe_junk2, ref(cs), ref(offsets), ref(eng));
	thread fnbnbvn(fe_junk3, ref(cs), ref(offsets), ref(eng));
	thread fgfhghz(fe_junk4, ref(cs), ref(offsets), ref(eng));

	thread gewqeqw(fe_junk1, ref(cs), ref(offsets), ref(eng));
	thread gghjhg(fe_junk2, ref(cs), ref(offsets), ref(eng));
	thread gnbnbvn(fe_junk3, ref(cs), ref(offsets), ref(eng));
	thread ggfhghz(fe_junk4, ref(cs), ref(offsets), ref(eng));

	thread fdgdfg(fe_bhop, ref(cs), ref(offsets), ref(settings), ref(eng));
	thread aqefsdw(fe_recoil, ref(cs), ref(offsets), ref(settings), ref(keys), ref(eng));
	thread aqeeqw(fe_glow, ref(cs), ref(offsets), ref(settings), ref(keys), ref(eng));
	thread aqesdsw(fe_skin, ref(cs), ref(offsets), ref(settings), ref(eng), ref(skin_paintkits));
	thread tretret(fe_sound, ref(cs), ref(offsets), ref(settings), ref(keys), ref(eng));
	thread tretxxret(fe_radar, ref(cs), ref(offsets), ref(settings), ref(keys), ref(eng), update_console);
	thread fdsaxgdfg(fe_trigger, ref(cs), ref(offsets), ref(settings), ref(eng));
	[/swap_lines]

	[swap_lines]
	keys[KEY_RECOIL] = settings[KEY_RECOIL] == -10;
	keys[KEY_SOUND] = settings[KEY_SOUND] == -10;
	keys[KEY_RADAR] = settings[KEY_RADAR] == -10;
	keys[KEY_GLOW] = settings[KEY_GLOW] == -10;
	[/swap_lines]

	if (settings[OTR_SLOAD] != 1) {
[add_junk 120 1000 /]

		update_console(ref(keys), false);
	}
[add_junk 120 1000 /]

	[swap_lines]
	keys[SLOAD_SLOT] = settings[OTR_SLOAD] == 1;
	keys[SOUND_SLOT] = settings[OTR_NOTIF] > 0;
	[/swap_lines]

	[swap_lines]
	int steps = 0;
	time_t stamp = time(NULL);
	[/swap_lines]

	while (!(_GetAsyncKeyState(settings[KEY_EXIT]) & 0x8000)) {
[add_junk 120 1000 /]

		[swap_blocks]
		[block]

		[swap_blocks]
		[block]
		if (eng.m_panic) {
[add_junk 120 1000 /]
		[/block]

		[block]
			if (!eng.m_mouse) {
[add_junk 120 1000 /]
		[/block]
		[/swap_blocks]

				[swap_blocks]
				[block]
				if (_GetAsyncKeyState(VK_INSERTS) & 0x8000) {
[add_junk 120 1000 /]
					[swap_lines]
					stamp = time(NULL);
					steps = 0;
					[/swap_lines]
				}
[add_junk 120 1000 /]
				[/block]

				[block]
				if (difftime(time(NULL), stamp) < 1.98) {
[add_junk 120 1000 /]

					[swap_blocks]
					[block]
					if (steps == 0 && (_GetAsyncKeyState(75) & 0x8000)) {
[add_junk 120 1000 /]
						++steps;
					}
[add_junk 120 1000 /]
					[/block]

					[block]
					if (steps == 1 && (_GetAsyncKeyState(83) & 0x8000)) {
[add_junk 120 1000 /]
						++steps;
					}
[add_junk 120 1000 /]
					[/block]

					[block]
					if (steps == 2 && (_GetAsyncKeyState(69) & 0x8000)) {
[add_junk 120 1000 /]
						++steps;
					}
[add_junk 120 1000 /]
					[/block]

					[block]
					if (steps == 3) {
[add_junk 120 1000 /]
						[swap_lines]
						eng.m_panic = false;
						steps = 0;
						[/swap_lines]
					}
[add_junk 120 1000 /]
					[/block]
					[/swap_blocks]
				}
[add_junk 120 1000 /]
				[/block]
				[/swap_blocks]
			}
[add_junk 120 1000 /]

			_Sleep(50);
		}
[add_junk 120 1000 /]
		[/block]

		[block]
		if (!eng.m_panic) {
[add_junk 120 1000 /]

			[swap_blocks]
			[block]
			if (_GetAsyncKeyState(settings[KEY_PANIC]) & 0x8000) {
[add_junk 120 1000 /]
				[swap_lines]
				eng.m_panic = true;
				_Beep(1000, 100);
				[/swap_lines]
			}
[add_junk 120 1000 /]
			[/block]

			[block]

			[swap_blocks]
			[block]
			if (settings[KEY_RECOIL] > 0) {
[add_junk 120 1000 /]
			[/block]

			[block]
				if (_GetAsyncKeyState(settings[KEY_RECOIL]) & 0x8000) {
[add_junk 120 1000 /]
			[/block]
			[/swap_blocks]

					keys.flip(KEY_RECOIL);
					update_console(ref(keys), keys[KEY_RECOIL]);
				}
[add_junk 120 1000 /]
			}
[add_junk 120 1000 /]
			[/block]

			[block]

			[swap_blocks]
			[block]
			if (settings[KEY_SOUND] > 0) {
[add_junk 120 1000 /]
			[/block]

			[block]
				if (_GetAsyncKeyState(settings[KEY_SOUND]) & 0x8000) {
[add_junk 120 1000 /]
			[/block]
			[/swap_blocks]

					keys.flip(KEY_SOUND);
					update_console(ref(keys), keys[KEY_SOUND]);
				}
[add_junk 120 1000 /]
			}
[add_junk 120 1000 /]
			[/block]

			[block]

			[swap_blocks]
			[block]
			if (settings[KEY_GLOW] > 0) {
[add_junk 120 1000 /]
			[/block]

			[block]
				if (_GetAsyncKeyState(settings[KEY_GLOW]) & 0x8000) {
[add_junk 120 1000 /]
			[/block]
			[/swap_blocks]

					keys.flip(KEY_GLOW);
					update_console(ref(keys), keys[KEY_GLOW]);
				}
[add_junk 120 1000 /]
			}
[add_junk 120 1000 /]
			[/block]

			[block]

			[swap_blocks]
			[block]
			if (settings[KEY_RADAR] > 0) {
[add_junk 120 1000 /]
			[/block]

			[block]
				if (_GetAsyncKeyState(settings[KEY_RADAR]) & 0x8000) {
[add_junk 120 1000 /]
			[/block]
			[/swap_blocks]

					keys.flip(KEY_RADAR);
					update_console(ref(keys), keys[KEY_RADAR]);
				}
[add_junk 120 1000 /]
			}
[add_junk 120 1000 /]
			[/block]
			[/swap_blocks]

			_Sleep(100);
		}
[add_junk 120 1000 /]
		[/block]
		[/swap_blocks]
	}
[add_junk 120 1000 /]

	[swap_lines]
	_Beep(1000, 100);
	_Beep(1000, 90);
	_Beep(1000, 110);
	[/swap_lines]

	exit(0);
	return 0;
}