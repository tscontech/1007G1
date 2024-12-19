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

#ifdef SDL_TIMER_BEOS

#include <be/kernel/OS.h>

#include "SDL_timer.h"

static bigtime_t start;

void
SDL_StartTicks(void)
{
    /* Set first ticks value */
    start = system_time();
}

Uint32
SDL_GetTicks(void)
{
    return ((system_time() - start) / 1000);
}

Uint64
SDL_GetPerformanceCounter(void)
{
    return system_time();
}

Uint64
SDL_GetPerformanceFrequency(void)
{
    return 1000000;
}

void
SDL_Delay(Uint32 ms)
{
    snooze(ms * 1000);
}

#endif /* SDL_TIMER_BEOS */

/* vi: set ts=4 sw=4 expandtab: */
