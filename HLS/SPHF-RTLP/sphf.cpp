#include "sphf.h"

// sol 1
//ap_uint<64> k2 = 0x9ae16a3b2f90404fULL;
//ap_uint<64> kMul = 0x9ddfea08eb382d69ULL;
//ap_uint<8> TdArray[2048] = {[0 ... (999)]=1,[1000 ... (1999)]=2,[2000 ... (2047)]=3};
//pn_t res[16384] = {[0 ... (4999)]=1,[5000 ... (8999)]=0,[9000 ... (16383)]=1};

// sol 2
//ap_uint<8> TdArray[5003] = {[0 ... (2999)]=1,[3000 ... (4999)]=2,[5000 ... (5002)]=3};
//pn_t res[11586] = {[0 ... (4999)]=1,[5000 ... (8999)]=2,[9000 ... (11585)]=0};

// sol 3
ap_uint<9> TdArray[2048] = {[0 ... (999)]=1,[1000 ... (1999)]=2,[2000 ... (2047)]=3};
pn_t res[16384] = {[0 ... (4999)]=1,[5000 ... (8999)]=0,[9000 ... (16383)]=1};

void sphf_RTL(data_t &key, pn_t &pn) {

#pragma HLS RESOURCE variable=res core=ROM_2P_BRAM
#pragma HLS RESOURCE variable=TdArray core=ROM_2P_BRAM

#pragma HLS INTERFACE ap_ovld port=pn
#pragma HLS INTERFACE ap_vld port=key

	// step 1: f(key)
	// sol 1: with cityhash64
	ap_uint<11> inx = (ap_uint<11>) key; // 5003 is the nSlot
	// sol 2: without cityhash64
//	ap_uint<13> inx = key % 5003; // 5003 is the nSlot

	// step 2: TdArray[inx]
	ap_uint<9> d = TdArray[inx];

	// step 3: g(key, d)
	// sol 1: with cityhash64
//	ap_uint<64> vL = key - k2;
//	ap_uint<64> vH = d;
//
//	ap_uint<64> a = (vL ^ vH) * kMul;
//	a ^= (a >> 47);
//	ap_uint<64> b = (vH ^ a) * kMul;
//	b ^= (b >> 47);
//	b *= kMul;
//	ap_uint<14> f = (ap_uint<14>)b;

	// sol 2: without cityhash64
//	ap_uint<14> f = (((ap_uint<14>)(key >> 7) + (ap_uint<14>)d) ^ ((ap_uint<14>)(key >> 8) ^ (ap_uint<14>)key))%11586; // 11586 is the nBucket of PHF(m)

	// sol 3: with Keran hash
	ap_uint<14> vL = key;
	ap_uint<9> vH = d;
	ap_uint<15> kMul1 = 29947;
	ap_uint<15> kMul2 = 29959;
	ap_uint<15> kMul3 = 29983;
	ap_uint<15> kMul4 = 29989;
	ap_uint<15> k1 = 29881;
	ap_uint<15> k2 = 29917;
	ap_uint<15> k3 = 29921;
	ap_uint<15> k4 = 29927;
	ap_uint<12> a = (vH ^ (vL-k1)) * kMul1;
	ap_uint<12> b = (vH ^ (vL-k2)) * kMul2;
	ap_uint<12> c = (vH ^ (vL-k3)) * kMul3;
	ap_uint<12> d1 = (vH ^ (vL-k4)) * kMul4;
	a ^= (d1 >> 7);
	b ^= (a >> 8);
	c ^= (b >> 9);
	d1 ^= (c >> 10);
	ap_uint<14> f = (ap_uint<14>) (a ^ b ^ c ^ d1);


	// step 4: get pn
//	pn = (pn_t) (a ^ b ^ c ^ d1);
	pn = res[f];

	return ;
}
