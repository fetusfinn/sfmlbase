//
//	defines.h
//
#pragma once

// concatenates the two given strings
#define CONCAT(a, b) a ## b

// paths to our asset folders
#define ASSETS_FOLDER				  "assets/"
#define FONT_FOLDER		ASSETS_FOLDER "fonts/"
#define SAVE_FOLDER		ASSETS_FOLDER "saves/"
#define SCRIPT_FOLDER	ASSETS_FOLDER "scripts/"
#define SPRITE_FOLDER	ASSETS_FOLDER "sprites/"

//
// Prints "Press any key to continue..." to the console and waits
// for user input before continuing
//
#define WAIT_KEYPRESS		std::system("PAUSE")

//
// Sleeps the current thread for the given amount of milliseconds
//
#define SLEEP_THREAD(_ms)	std::this_thread::sleep_for(std::chrono::milliseconds(_ms))
