﻿/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2012 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/
#include "SDL_config.h"

#if SDL_VIDEO_DRIVER_WINDOWS

#include "SDL_main.h"
#include "SDL_video.h"
#include "SDL_mouse.h"
#include "../SDL_sysvideo.h"
#include "../SDL_pixels_c.h"

#include "SDL_windowsvideo.h"
#include "SDL_windowsframebuffer.h"
#include "SDL_windowsshape.h"

/* Initialization/Query functions */
static int WIN_VideoInit(_THIS);
static void WIN_VideoQuit(_THIS);


/* Windows driver bootstrap functions */

static int
WIN_Available(void)
{
    return (1);
}

static void
WIN_DeleteDevice(SDL_VideoDevice * device)
{
    SDL_VideoData *data = (SDL_VideoData *) device->driverdata;

    SDL_UnregisterApp();
#ifdef _WIN32_WCE
    if(data->hAygShell) {
       SDL_UnloadObject(data->hAygShell);
    }
#endif
	if (data->userDLL) {
		SDL_UnloadObject(data->userDLL);
	}

    SDL_free(device->driverdata);
    SDL_free(device);
}

static SDL_VideoDevice *
WIN_CreateDevice(int devindex)
{
    SDL_VideoDevice *device;
    SDL_VideoData *data;

    SDL_RegisterApp(NULL, 0, NULL);

    /* Initialize all variables that we clean on shutdown */
    device = (SDL_VideoDevice *) SDL_calloc(1, sizeof(SDL_VideoDevice));
    if (device) {
        data = (struct SDL_VideoData *) SDL_calloc(1, sizeof(SDL_VideoData));
    } else {
        data = NULL;
    }
    if (!data) {
        SDL_OutOfMemory();
        if (device) {
            SDL_free(device);
        }
        return NULL;
    }
    device->driverdata = data;

#ifdef _WIN32_WCE
    data->hAygShell = SDL_LoadObject("\\windows\\aygshell.dll");
    if(0 == data->hAygShell)
        data->hAygShell = SDL_LoadObject("aygshell.dll");
    data->SHFullScreen = (0 != data->hAygShell ?
        (PFNSHFullScreen) SDL_LoadFunction(data->hAygShell, "SHFullScreen") : 0);
    data->CoordTransform = NULL;
#endif

	data->userDLL = SDL_LoadObject("USER32.DLL");
	if (data->userDLL) {
		data->CloseTouchInputHandle = (BOOL (WINAPI *)( HTOUCHINPUT )) SDL_LoadFunction(data->userDLL, "CloseTouchInputHandle");
		data->GetTouchInputInfo = (BOOL (WINAPI *)( HTOUCHINPUT, UINT, PTOUCHINPUT, int )) SDL_LoadFunction(data->userDLL, "GetTouchInputInfo");
		data->RegisterTouchWindow = (BOOL (WINAPI *)( HWND, ULONG )) SDL_LoadFunction(data->userDLL, "RegisterTouchWindow");
	}

    /* Set the function pointers */
    device->VideoInit = WIN_VideoInit;
    device->VideoQuit = WIN_VideoQuit;
    device->GetDisplayBounds = WIN_GetDisplayBounds;
    device->GetDisplayModes = WIN_GetDisplayModes;
    device->SetDisplayMode = WIN_SetDisplayMode;
    device->PumpEvents = WIN_PumpEvents;

#undef CreateWindow
    device->CreateWindow = WIN_CreateWindow;
    device->CreateWindowFrom = WIN_CreateWindowFrom;
    device->SetWindowTitle = WIN_SetWindowTitle;
    device->SetWindowIcon = WIN_SetWindowIcon;
    device->SetWindowPosition = WIN_SetWindowPosition;
    device->SetWindowSize = WIN_SetWindowSize;
    device->ShowWindow = WIN_ShowWindow;
    device->HideWindow = WIN_HideWindow;
    device->RaiseWindow = WIN_RaiseWindow;
    device->MaximizeWindow = WIN_MaximizeWindow;
    device->MinimizeWindow = WIN_MinimizeWindow;
    device->RestoreWindow = WIN_RestoreWindow;
    device->SetWindowFullscreen = WIN_SetWindowFullscreen;
    device->SetWindowGammaRamp = WIN_SetWindowGammaRamp;
    device->GetWindowGammaRamp = WIN_GetWindowGammaRamp;
    device->SetWindowGrab = WIN_SetWindowGrab;
    device->DestroyWindow = WIN_DestroyWindow;
    device->GetWindowWMInfo = WIN_GetWindowWMInfo;
    device->CreateWindowFramebuffer = WIN_CreateWindowFramebuffer;
    device->UpdateWindowFramebuffer = WIN_UpdateWindowFramebuffer;
    device->DestroyWindowFramebuffer = WIN_DestroyWindowFramebuffer;

    device->shape_driver.CreateShaper = Win32_CreateShaper;
    device->shape_driver.SetWindowShape = Win32_SetWindowShape;
    device->shape_driver.ResizeWindowShape = Win32_ResizeWindowShape;

#if SDL_VIDEO_OPENGL_WGL
    device->GL_LoadLibrary = WIN_GL_LoadLibrary;
    device->GL_GetProcAddress = WIN_GL_GetProcAddress;
    device->GL_UnloadLibrary = WIN_GL_UnloadLibrary;
    device->GL_CreateContext = WIN_GL_CreateContext;
    device->GL_MakeCurrent = WIN_GL_MakeCurrent;
    device->GL_SetSwapInterval = WIN_GL_SetSwapInterval;
    device->GL_GetSwapInterval = WIN_GL_GetSwapInterval;
    device->GL_SwapWindow = WIN_GL_SwapWindow;
    device->GL_DeleteContext = WIN_GL_DeleteContext;
#endif

	device->StartTextInput = WIN_StartTextInput;
    device->StopTextInput = WIN_StopTextInput;
    device->SetTextInputRect = WIN_SetTextInputRect;

    device->SetClipboardText = WIN_SetClipboardText;
    device->GetClipboardText = WIN_GetClipboardText;
    device->HasClipboardText = WIN_HasClipboardText;

    device->_free = WIN_DeleteDevice;

    return device;
}

VideoBootStrap WINDOWS_bootstrap = {
    "windows", "SDL Windows video driver", WIN_Available, WIN_CreateDevice
};

int
WIN_VideoInit(_THIS)
{
    if (WIN_InitModes(_this) < 0) {
        return -1;
    }

    WIN_InitKeyboard(_this);
    WIN_InitMouse(_this);

#ifdef CFG_TOUCH_ENABLE
    Castor3_InitTouch();
#endif

	return 0;
}

void
WIN_VideoQuit(_THIS)
{
    WIN_QuitModes(_this);
    WIN_QuitKeyboard(_this);
    WIN_QuitMouse(_this);
}

#endif /* SDL_VIDEO_DRIVER_WINDOWS */

/* vim: set ts=4 sw=4 expandtab: */
