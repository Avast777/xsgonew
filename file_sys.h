#pragma once
[swap_lines]
#include <sys/stat.h>
#include <string>
#include "enc.h"
[/swap_lines]

using namespace std;

[junk_enable 40 360 /]


[swap_blocks]
[block]
inline bool f_exists(const encString & name) {
[add_junk 120 1000 /]
	struct stat buffer;
	return (stat(name.str().c_str(), &buffer) == 0);
}
[/block]

[block]
inline bool f_exists(const string & name) {
[add_junk 120 1000 /]
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}
[/block]
[/swap_blocks]