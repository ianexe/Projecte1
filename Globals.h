#pragma once
#include <windows.h>
#include <stdio.h>

#define LOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);

void log(const char file[], int line, const char* format, ...);

#define CAP(n) ((n <= 0.0f) ? n=0.0f : (n >= 1.0f) ? n=1.0f : n=n)

enum update_status
{
	UPDATE_CONTINUE = 1,
	UPDATE_STOP,
	UPDATE_ERROR
};

// Timers

#define JUMP_TIME 3000
#define PUNCH_TIME 1000
#define HIT_TIME 500



// Configuration -----------
#define SCREEN_WIDTH 384
#define SCREEN_HEIGHT 224
#define SCREEN_SIZE 3
#define WIN_FULLSCREEN false
#define WIN_RESIZABLE false
#define WIN_BORDERLESS false
#define WIN_FULLSCREEN_DESKTOP false
#define VSYNC true
#define TITLE "Super Awesome Game"
#define FADE_TIME 2.5f