#ifndef __chd_PH_H__
#define __chd_PH_H__

#include <stdio.h>
#include <ap_int.h>

#define GETVALUE(array, i) ((unsigned char)((array[i >> 2] >> ((i & 0x00000003U) << 1U)) & 0x00000003U))

typedef unsigned int data_t;
typedef ap_uint<2> pn_t;

//void bdz_PH(data_t key, data_t r, uint8_t g[], pn_t res[], pn_t pn);
void chd_PH(data_t &key, data_t &ptr, pn_t &pn);

#endif
