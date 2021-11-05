#pragma once
#define NOMINMAX
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <assert.h>



#pragma warning(push)
#pragma warning(disable:4005)

#include <d3d11.h>
#include <d3dx9.h>
#include <d3dx11.h>
#include "DirectXMath.h"
using namespace DirectX;

#pragma warning(pop)

#include "debugLog.h"

#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment(lib, "dxguid.lib")

#define SCREEN_WIDTH	(960)
#define SCREEN_HEIGHT	(540)

static const char* CLASS_NAME = "AppClass";
static const char* WINDOW_NAME = "DX11ÉQÅ[ÉÄ";

HWND GetWindow();
bool JudgeActiveWindow();