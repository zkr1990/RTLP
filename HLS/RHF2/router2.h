#ifndef __router3_H__
#define __router3_H__
#include <iostream>
#include <stdio.h>
#include <ap_int.h>
#include <ap_fixed.h>

//#define GETVALUE(array, i) ((unsigned char)((array[i >> 2] >> ((i & 0x00000003U) << 1U)) & 0x00000003U))

typedef ap_uint<32> data_t;
//typedef unsigned int data_t;
typedef ap_uint<2>	pn_t;

void router2(data_t &key, int &s0, int &s1, pn_t &pn);

#endif
