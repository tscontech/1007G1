﻿/*******************************************************************************
 * Copyright ITE Tech. Inc. All Rights Reserved.
 *
 * FreqInfo
 *******************************************************************************/

#include "config.h"
#include "wmadec.h"
#include "freqinfo.h"

#if defined(FREQINFO)

extern WMADecodeContext wmadec;

// Set the USE_SCALE_FUNC on "freqinfo.h"
// Scale function 0: No scale
// Scale function 1: ((i==0) ? 0 : (int)(log(i)*256/log(256)))
// Scale function 2: ((i*4/3 > 255) ? 255 : i*4/3)
// Scale function 3: (int)(255/pow(255,0.45))*pow(i,0.45)
// #define USE_SCALE_FUNC 3

#ifndef abs
#define abs(x)  (((x)>=0) ? (x):-(x))
#endif

/***********************************************************************************
// The generator for tab[], sacle[]
#include <math.h>
#define RANGE (2.0/3)
int main(void) {
    int i, j;
    double M;
    int block_size[] = {128, 256, 512, 1024, 2048};

    // Generate tab[]
    printf("static short tab[5][FREQINFOCNT+1] = {\n");
    for(j=0; j<sizeof(block_size)/sizeof(int); j++) {
        M = (log(block_size[j]*RANGE) - log(0.7)) / log(21);
        printf("// block length = %d\n", block_size[j]);
        printf("// by equation 0.7 * (N+1)^(%4.2f) + 0.5, N = 0 ... 20\n", M);
        printf(" {\n  ");
        for(i=0; i<21; i++) {
            printf(" %4d,", (int)((double)0.7 * pow(i+1, M)+.5));
            if ((i+1)%11 == 0) printf(" \n  ");
        }
        printf(" \n},\n\n");
    }
    printf("\n};\n");

    // Generate scale[]
    printf("\n");
    printf("static unsigned char scale[] = {\n");
    for(i=0; i<256; i++) {
        printf(" %3d,", (i==0) ? 0 : (int)(log(i)*256/log(256)));
        if ((i+1)%16 == 0) printf("\n");
    }
    printf("};\n");

    return 0;
}

For Example:

    for equation: 0.7 * (N+1)^M + 0.5, N = 0 ... 20
    solve the equation: 0.7 * (20 + 1)^M + 0.5 = K, K = 128, 256, 512, 1024, and 2048
    so M = (ln(K-0.5) - ln(0.7)) / ln(21)
       M = 1.71, 1.94, 2.17, 2.39 and 2.62 repectively for K = 128, 256 ....

 ***********************************************************************************/
char freqinfo[FREQINFOCNT];
static short tab[5][FREQINFOCNT+1] = {
// block length = 128
// by equation 0.7 * (N+1)^(1.58) + 0.5, N = 0 ... 20
{
    1,    2,    4,    6,    9,   12,   15,   19,   22,   26,   31,
   35,   40,   45,   50,   56,   61,   67,   73,   79,   85,
},

// block length = 256
// by equation 0.7 * (N+1)^(1.81) + 0.5, N = 0 ... 20
{
    1,    2,    5,    9,   13,   18,   23,   30,   37,   45,   53,
   62,   72,   82,   93,  104,  117,  129,  142,  156,  171,
},

// block length = 512
// by equation 0.7 * (N+1)^(2.03) + 0.5, N = 0 ... 20
{
    1,    3,    7,   12,   18,   27,   37,   48,   61,   76,   92,
  109,  129,  150,  172,  196,  222,  250,  278,  309,  341,
},

// block length = 1024
// by equation 0.7 * (N+1)^(2.26) + 0.5, N = 0 ... 20
{
    1,    3,    8,   16,   27,   40,   57,   77,  101,  128,  158,
  193,  231,  273,  319,  369,  423,  482,  544,  611,  683,
},

// block length = 2048
// by equation 0.7 * (N+1)^(2.49) + 0.5, N = 0 ... 20
{
    1,    4,   11,   22,   38,   60,   89,  124,  166,  215,  273,
  339,  414,  498,  591,  694,  807,  930, 1064, 1209, 1365,
},
};

#if (USE_SCALE_FUNC == 0)
// Scale function 0: No scale
static unsigned char scale[] = {
   0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15,
  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,
  32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,
  48,  49,  50,  51,  52,  53,  54,  55,  56,  57,  58,  59,  60,  61,  62,  63,
  64,  65,  66,  67,  68,  69,  70,  71,  72,  73,  74,  75,  76,  77,  78,  79,
  80,  81,  82,  83,  84,  85,  86,  87,  88,  89,  90,  91,  92,  93,  94,  95,
  96,  97,  98,  99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111,
 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127,
 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143,
 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159,
 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175,
 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191,
 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207,
 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223,
 224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239,
 240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255,
};
#elif (USE_SCALE_FUNC == 1)
// Scale function 1: ((i==0) ? 0 : (int)(log(i)*256/log(256)))
static unsigned char scale[] = {
   0,   0,  32,  50,  64,  74,  82,  89,  95, 101, 106, 110, 114, 118, 121, 125,
 128, 130, 133, 135, 138, 140, 142, 144, 146, 148, 150, 152, 153, 155, 157, 158,
 160, 161, 162, 164, 165, 166, 167, 169, 170, 171, 172, 173, 174, 175, 176, 177,
 178, 179, 180, 181, 182, 183, 184, 185, 185, 186, 187, 188, 189, 189, 190, 191,
 191, 192, 193, 194, 194, 195, 196, 196, 197, 198, 198, 199, 199, 200, 201, 201,
 202, 202, 203, 204, 204, 205, 205, 206, 206, 207, 207, 208, 208, 209, 209, 210,
 210, 211, 211, 212, 212, 213, 213, 213, 214, 214, 215, 215, 216, 216, 217, 217,
 217, 218, 218, 219, 219, 219, 220, 220, 221, 221, 221, 222, 222, 222, 223, 223,
 223, 224, 224, 225, 225, 225, 226, 226, 226, 227, 227, 227, 228, 228, 228, 229,
 229, 229, 230, 230, 230, 231, 231, 231, 231, 232, 232, 232, 233, 233, 233, 234,
 234, 234, 234, 235, 235, 235, 236, 236, 236, 236, 237, 237, 237, 237, 238, 238,
 238, 238, 239, 239, 239, 239, 240, 240, 240, 241, 241, 241, 241, 241, 242, 242,
 242, 242, 243, 243, 243, 243, 244, 244, 244, 244, 245, 245, 245, 245, 245, 246,
 246, 246, 246, 247, 247, 247, 247, 247, 248, 248, 248, 248, 249, 249, 249, 249,
 249, 250, 250, 250, 250, 250, 251, 251, 251, 251, 251, 252, 252, 252, 252, 252,
 253, 253, 253, 253, 253, 253, 254, 254, 254, 254, 254, 255, 255, 255, 255, 255
};
#elif (USE_SCALE_FUNC == 2)
// Scale function 2: ((i*4/3 > 255) ? 255 : i*4/3)
static unsigned char scale[] = {
   0,   1,   2,   4,   5,   6,   8,   9,  10,  12,  13,  14,  16,  17,  18,  20,
  21,  22,  24,  25,  26,  28,  29,  30,  32,  33,  34,  36,  37,  38,  40,  41,
  42,  44,  45,  46,  48,  49,  50,  52,  53,  54,  56,  57,  58,  60,  61,  62,
  64,  65,  66,  68,  69,  70,  72,  73,  74,  76,  77,  78,  80,  81,  82,  84,
  85,  86,  88,  89,  90,  92,  93,  94,  96,  97,  98, 100, 101, 102, 104, 105,
 106, 108, 109, 110, 112, 113, 114, 116, 117, 118, 120, 121, 122, 124, 125, 126,
 128, 129, 130, 132, 133, 134, 136, 137, 138, 140, 141, 142, 144, 145, 146, 148,
 149, 150, 152, 153, 154, 156, 157, 158, 160, 161, 162, 164, 165, 166, 168, 169,
 170, 172, 173, 174, 176, 177, 178, 180, 181, 182, 184, 185, 186, 188, 189, 190,
 192, 193, 194, 196, 197, 198, 200, 201, 202, 204, 205, 206, 208, 209, 210, 212,
 213, 214, 216, 217, 218, 220, 221, 222, 224, 225, 226, 228, 229, 230, 232, 233,
 234, 236, 237, 238, 240, 241, 242, 244, 245, 246, 248, 249, 250, 252, 253, 254,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
};
#elif (USE_SCALE_FUNC == 3)
// Scale function 3: (int)(255/pow(255,0.45))*pow(i,0.45)
static unsigned char scale[] = {
   0,  21,  28,  34,  39,  43,  47,  50,  53,  56,  59,  61,  64,  66,  68,  71,
  73,  75,  77,  79,  80,  82,  84,  86,  87,  89,  90,  92,  94,  95,  97,  98,
  99, 101, 102, 104, 105, 106, 107, 109, 110, 111, 112, 114, 115, 116, 117, 118,
 119, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135,
 136, 137, 138, 139, 140, 141, 142, 142, 143, 144, 145, 146, 147, 148, 149, 150,
 150, 151, 152, 153, 154, 155, 155, 156, 157, 158, 159, 159, 160, 161, 162, 163,
 163, 164, 165, 166, 166, 167, 168, 169, 169, 170, 171, 171, 172, 173, 174, 174,
 175, 176, 176, 177, 178, 179, 179, 180, 181, 181, 182, 183, 183, 184, 185, 185,
 186, 187, 187, 188, 189, 189, 190, 190, 191, 192, 192, 193, 194, 194, 195, 195,
 196, 197, 197, 198, 198, 199, 200, 200, 201, 201, 202, 203, 203, 204, 204, 205,
 206, 206, 207, 207, 208, 208, 209, 210, 210, 211, 211, 212, 212, 213, 214, 214,
 215, 215, 216, 216, 217, 217, 218, 218, 219, 220, 220, 221, 221, 222, 222, 223,
 223, 224, 224, 225, 225, 226, 226, 227, 227, 228, 228, 229, 229, 230, 230, 231,
 231, 232, 232, 233, 233, 234, 234, 235, 235, 236, 236, 237, 237, 238, 238, 239,
 239, 240, 240, 241, 241, 242, 242, 243, 243, 244, 244, 245, 245, 245, 246, 246,
 247, 247, 248, 248, 249, 249, 250, 250, 251, 251, 251, 252, 252, 253, 253, 254,
};
#else
#  error "No define scale functions"
#endif

#define BIAS    (0x84)  /* Bias for linear code. */
#define CLIP    (8159)
static short seg_uend[8] = { 0x3F, 0x7F, 0xFF, 0x1FF, 0x3FF, 0x7FF, 0xFFF, 0x1FFF };
static short search(short val, short *table, short size)
{
    short i;

    for (i = 0; i < size; i++) {
        if (val <= *table++)
            return (i);
    }
    return (size);
}

static unsigned char linear2ulaw(short pcm_val)
{                               /* 2's complement (16-bit range) */
    short mask;
    short seg;
    unsigned char uval;

    /* Get the sign and the magnitude of the value. */
    pcm_val = pcm_val >> 2;

    if (pcm_val < 0) {
        pcm_val = -pcm_val;
        mask = 0x7F;
    } else {
        mask = 0xFF;
    }

    if (pcm_val > CLIP) {
        pcm_val = CLIP;         /* clip the magnitude */
    }

    pcm_val += (BIAS >> 2);

    /* Convert the scaled magnitude to segment number. */
    seg = search(pcm_val, seg_uend, 8);

    /*
     * Combine the sign, segment, quantization bits;
     * and complement the code word.
     */
    if (seg >= 8) {             /* out of range, return maximum value. */
        return (unsigned char) (0x7F ^ mask);
    } else {
        uval = (unsigned char) (seg << 4) | ((pcm_val >> (seg + 1)) & 0xF);
        return (uval ^ mask);
    }

}

void updateFreqInfo(WMADecodeContext* wmadec)
{
    int i, j;
    int idx;

    idx = wmadec->block_len_bits - 7;
    idx = (idx > 4) ? 4 : idx;

    // wmadec->coefs[][] is S15.16 formate
    for(i=0; i<FREQINFOCNT; i++){
        unsigned int f = 0;

        for(j=tab[idx][i]; j<tab[idx][i+1]; j++) {
            f += (abs(wmadec->coefs[0][j])>>16);
            if (wmadec->nb_channels == 2)
                f += (abs(wmadec->coefs[1][j])>>16);
        }

        f = f / (tab[idx][i+1] - tab[idx][i]);

        if (wmadec->nb_channels == 2)
            f = (f / 2);

        // enlarge by 12
        f = f * 12;
        if (f > 65536) {
            f = 65536;
        }

        // use ulaw to transform the data from 16-bits to 8-bits.
        f = (unsigned char)~linear2ulaw(f);

        freqinfo[i] = scale[f];
    }
}

#endif // defined(FREQINFO)
