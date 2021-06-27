#ifndef __SPHF_H__
#define __SPHF_H__

#include <stdio.h>
#include <ap_int.h>


typedef ap_uint<32> data_t;
typedef ap_uint<2> pn_t;

void sphf_RTL(data_t &key, pn_t &pn);

#endif
