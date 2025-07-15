#pragma once
[swap_lines]
#include <windows.h>

#include "enc.h"
[/swap_lines]

using namespace std;

/* FUNCTION PROXYFYING */

[swap_blocks]
[block]
/* OpenProcess */
typedef HANDLE(WINAPI* __OpenProcess) (
	DWORD dwDesiredAccess,
	BOOL bInheritHandle,
	DWORD dwProcessId);
[/block]

[block]
/* WriteProcessMemory */
typedef BOOL(WINAPI* __WriteProcessMemory) (
	HANDLE  hProcess,
	LPVOID  lpBaseAddress,
	LPCVOID lpBuffer,
	SIZE_T  nSize,
	SIZE_T  *lpNumberOfBytesWritten);
[/block]

[block]
/* ReadProcessMemory */
typedef BOOL(WINAPI* __ReadProcessMemory) (
	HANDLE  hProcess,
	LPVOID  lpBaseAddress,
	LPCVOID lpBuffer,
	SIZE_T  nSize,
	SIZE_T  *lpNumberOfBytesRead);
[/block]

[block]
/* Beep */
typedef BOOL(WINAPI* __Beep) (
	DWORD dwFreq,
	DWORD dwDuration);
[/block]

[block]
/* Sleep */
typedef VOID(WINAPI* __Sleep) (
	DWORD dwMilliseconds);
[/block]

[block]
/* GetAsyncKeyState */
typedef SHORT(WINAPI* __GetAsyncKeyState) (
	int vKey);
[/block]
[/swap_blocks]

[junk_enable 40 360 /]

[junk_enable_declares /]

/* Exported functions kept static */
[swap_lines]
static __OpenProcess sys_op;
static __ReadProcessMemory sys_rpm;
static __WriteProcessMemory sys_wpm;
static __Beep sys_beep;
static __Sleep sys_sleep;
static __GetAsyncKeyState sys_gaks;
[/swap_lines]

[junk_disable_declares /]

[swap_blocks]
[block]
__forceinline HANDLE WINAPI _OpenProcess(DWORD dwDesiredAccess, BOOL bInheritHandle, DWORD dwProcessId) {
[add_junk 120 1000 /]
	return sys_op(dwDesiredAccess, bInheritHandle, dwProcessId);
}
[/block]

[block]
__forceinline BOOL WINAPI _WriteProcessMemory(HANDLE hProcess, LPVOID lpBaseAddress, LPCVOID lpBuffer, SIZE_T nSize, SIZE_T * lpNumberOfBytesWritten) {
[add_junk 120 1000 /]
	return sys_wpm(hProcess, lpBaseAddress, lpBuffer, nSize, lpNumberOfBytesWritten);
}
[/block]

[block]
__forceinline BOOL WINAPI _ReadProcessMemory(HANDLE hProcess, LPVOID lpBaseAddress, LPCVOID lpBuffer, SIZE_T nSize, SIZE_T * lpNumberOfBytesRead) {
[add_junk 120 1000 /]
	return sys_rpm(hProcess, lpBaseAddress, lpBuffer, nSize, lpNumberOfBytesRead);
}
[/block]

[block]
__forceinline BOOL WINAPI _Beep(DWORD dwFreq, DWORD dwDuration) {
[add_junk 120 1000 /]
	return sys_beep(dwFreq, dwDuration);
}
[/block]

[block]
__forceinline VOID WINAPI _Sleep(DWORD dwMilliseconds) {
[add_junk 120 1000 /]
	sys_sleep(dwMilliseconds);
}
[/block]

[block]
__forceinline SHORT WINAPI _GetAsyncKeyState(int vKey) {
[add_junk 120 1000 /]
	return sys_gaks(vKey);
}
[/block]

[block]
__forceinline bool initialize_functions() {
[add_junk 120 1000 /]

	[swap_blocks]
	[block]
	/* kernel32.dll */
	unsigned char kernel_data[16] = { 'k', 'e', _CHAR1_, 'r', 'n', _CHAR3_, 'e', 'l',
		_CHAR4_, '3', '2', '.', _CHAR2_, 'd', 'l', 'l' };
	encString kernel(kernel_data, 0b1101101101110111);
	[/block]

	[block]
	/* OpenProcess */
	unsigned char openprocess_data[16] = { 'O', 'p', _CHAR5_, 'e', 'n', 'P', _CHAR8_, 'r',
		_CHAR2_, 'o', _CHAR6_, 'c', 'e', _CHAR7_, 's', 's' };
	encString openprocess(openprocess_data, 0b1101110101011011);
	[/block]

	[block]
	/* WriteProcessMemory */
	unsigned char write_proc_data[16] = { 'W', _CHAR1_, _CHAR4_, 'r', _CHAR5_, 'i', _CHAR3_, 't',
		'e', _CHAR8_, 'P', _CHAR8_, 'r', _CHAR7_, 'o', 'c' };
	encString write_proc(write_proc_data, 0b1001010110101011);
	[/block]

	[block]
	unsigned char ess_memory_data[16] = { _CHAR2_, 'e', _CHAR1_, 's', 's', _CHAR4_, 'M', _CHAR6_,
		'e', _CHAR2_, 'm', _CHAR1_, 'o', 'r', _CHAR5_, 'y' };
	encString ess_memory(ess_memory_data, 0b0101101010101101);
	[/block]

	[block]
	/* ReadProcessMemory */
	unsigned char read_proce_data[16] = { 'R', _CHAR3_, _CHAR2_, 'e', _CHAR1_, 'a', _CHAR4_, 'd',
		'P', _CHAR5_, 'r', 'o', _CHAR6_, 'c', 'e', _CHAR8_ };
	encString read_proce(read_proce_data, 0b1001010110110110);
	[/block]

	[block]
	unsigned char ss_memory_data[16] = { 's', _CHAR4_, 's', _CHAR8_, 'M', _CHAR7_, 'e', _CHAR3_,
		_CHAR1_, 'm', _CHAR2_, 'o', _CHAR5_, 'r', _CHAR5_, 'y' };
	encString ss_memory(ss_memory_data, 0b1010101001010101);
	[/block]

	[block]
	/* Beep */
	unsigned char beep_data[16] = { _CHAR7_, _CHAR7_, 'B', _CHAR7_, _CHAR4_, _CHAR1_, 'e', _CHAR3_,
		_CHAR8_, _CHAR6_, 'e', _CHAR8_, _CHAR3_, _CHAR6_, 'p', _CHAR2_ };
	encString beep(beep_data, 0b0010001000100010);
	[/block]

	[block]
	/* Sleep */
	unsigned char sleep_data[16] = { _CHAR8_, _CHAR7_, 'S', _CHAR6_, _CHAR5_, 'l', _CHAR4_, _CHAR3_,
		'e', _CHAR2_, _CHAR1_, 'e', _CHAR1_, _CHAR5_, _CHAR5_, 'p' };
	encString sleep(sleep_data, 0b0010010010010001);
	[/block]

	[block]
	/* User32.dll */
	unsigned char user_data[16] = { _CHAR3_, 'U', _CHAR3_, 's', 'e', _CHAR4_, 'r', _CHAR6_,
		'3', '2', '.', _CHAR5_, 'd', _CHAR8_, 'l', 'l' };
	encString user(user_data, 0b0101101011101011);
	[/block]

	[block]
	/* GetAsync */
	unsigned char get_async_data[16] = { _CHAR2_, 'G', _CHAR2_, 'e', _CHAR2_, 't', 'A', _CHAR4_,
		's', _CHAR3_, _CHAR3_, 'y', _CHAR6_, 'n', _CHAR5_, 'c' };
	encString get_async(get_async_data, 0b0101011010010101);
	[/block]

	[block]
	/* KeyState */
	unsigned char key_state_data[16] = { _CHAR4_, 'K', _CHAR7_, _CHAR5_, 'e', _CHAR3_, 'y', 'S',
		_CHAR4_, 't', _CHAR6_, 'a', _CHAR5_, 't', _CHAR8_, 'e' };
	encString key_state(key_state_data, 0b0100101101010101);
	[/block]
	[/swap_blocks]

	[swap_blocks]
	[block]
	if (!(sys_op = (__OpenProcess)GetProcAddress(GetModuleHandle(kernel.str().c_str()), openprocess.str().c_str()))) {
[add_junk 120 1000 /]
		return false;
	}
[add_junk 120 1000 /]
	[/block]

	[block]
	if (!(sys_rpm = (__ReadProcessMemory)GetProcAddress(GetModuleHandle(kernel.str().c_str()), (read_proce.str() + ss_memory.str()).c_str()))) {
[add_junk 120 1000 /]
		return false;
	}
[add_junk 120 1000 /]
	[/block]

	[block]
	if (!(sys_wpm = (__WriteProcessMemory)GetProcAddress(GetModuleHandle(kernel.str().c_str()), (write_proc.str() + ess_memory.str()).c_str()))) {
[add_junk 120 1000 /]
		return false;
	}
[add_junk 120 1000 /]
	[/block]

	[block]
	if (!(sys_beep = (__Beep)GetProcAddress(GetModuleHandle(kernel.str().c_str()), beep.str().c_str()))) {
[add_junk 120 1000 /]
		return false;
	}
[add_junk 120 1000 /]
	[/block]

	[block]
	if (!(sys_sleep = (__Sleep)GetProcAddress(GetModuleHandle(kernel.str().c_str()), sleep.str().c_str()))) {
[add_junk 120 1000 /]
		return false;
	}
[add_junk 120 1000 /]
	[/block]

	[block]
	if (!(sys_gaks = (__GetAsyncKeyState)GetProcAddress(GetModuleHandle(user.str().c_str()), (get_async.str() + key_state.str()).c_str()))) {
[add_junk 120 1000 /]
		return false;
	}
[add_junk 120 1000 /]
	[/block]
	[/swap_blocks]

	return true;
}
[/block]
[/swap_blocks]