﻿/*
 * This file is part of Libav.
 *
 * Libav is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * Libav is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with Libav; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include "dsputil.h"

#ifndef BIT_DEPTH
#define BIT_DEPTH 8
#endif

#ifdef AVCODEC_H264_HIGH_DEPTH_H
#   undef pixel
#   undef pixel2
#   undef pixel4
#   undef dctcoef
#   undef INIT_CLIP
#   undef no_rnd_avg_pixel4
#   undef rnd_avg_pixel4
#   undef AV_RN2P
#   undef AV_RN4P
#   undef AV_RN4PA
#   undef AV_WN2P
#   undef AV_WN4P
#   undef AV_WN4PA
#   undef CLIP
#   undef FUNC
#   undef FUNCC
#   undef av_clip_pixel
#   undef PIXEL_SPLAT_X4
#else
#   define AVCODEC_H264_HIGH_DEPTH_H
#endif

#if BIT_DEPTH > 8
#   define pixel  uint16_t
#   define pixel2 uint32_t
#   define pixel4 uint64_t
#   define dctcoef int32_t

#   define INIT_CLIP
#   define no_rnd_avg_pixel4 no_rnd_avg64
#   define    rnd_avg_pixel4    rnd_avg64
#   define AV_RN2P  AV_RN32
#   define AV_RN4P  AV_RN64
#   define AV_RN4PA AV_RN64A
#   define AV_WN2P  AV_WN32
#   define AV_WN4P  AV_WN64
#   define AV_WN4PA AV_WN64A
#   define PIXEL_SPLAT_X4(x) ((x)*0x0001000100010001ULL)

#   define av_clip_pixel(a) av_clip_uintp2(a, BIT_DEPTH)
#   define CLIP(a)          av_clip_uintp2(a, BIT_DEPTH)
#else
#   define pixel  uint8_t
#   define pixel2 uint16_t
#   define pixel4 uint32_t
#   define dctcoef int16_t

#   define INIT_CLIP uint8_t *cm = ff_cropTbl + MAX_NEG_CROP;
#   define no_rnd_avg_pixel4 no_rnd_avg32
#   define    rnd_avg_pixel4    rnd_avg32
#   define AV_RN2P  AV_RN16
#   define AV_RN4P  AV_RN32
#   define AV_RN4PA AV_RN32A
#   define AV_WN2P  AV_WN16
#   define AV_WN4P  AV_WN32
#   define AV_WN4PA AV_WN32A
#   define PIXEL_SPLAT_X4(x) ((x)*0x01010101U)

#   define av_clip_pixel(a) av_clip_uint8(a)
#   define CLIP(a) cm[a]
#endif

#define FUNC3(a, b, c)  a ## _ ## b ## c
#define FUNC2(a, b, c)  FUNC3(a, b, c)
#define FUNC(a)  FUNC2(a, BIT_DEPTH,)
#define FUNCC(a) FUNC2(a, BIT_DEPTH, _c)
