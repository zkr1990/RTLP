#ifndef __bdz_PH_H__
#define __bdz_PH_H__

#include <stdio.h>
#include <ap_int.h>

#define GETVALUE(array, i) ((unsigned char)((array[i >> 2] >> ((i & 0x00000003U) << 1U)) & 0x00000003U))

typedef ap_uint<32> data_t;
typedef ap_uint<2> pn_t;
typedef ap_uint<8> uint8_t;
typedef ap_uint<16> uint16_t;
typedef ap_uint<10> uint10_t;

//void bdz_PH(data_t key, data_t r, uint8_t g[], pn_t res[], pn_t pn);
void bdz_PH(data_t &key, data_t &r, pn_t &pn);

#endif
