#include "chd_PH.h"
//#include "jenkins_hash.h"


// fake values for probe[] and res[]
data_t probe[10000] = {[0]=0,[1]=2,[2]=4,[3]=8,[4]=16,[5]=32,[6]=64,[7]=128,\
		[8]=256,[9]=512,[10]=1024,[11]=2048,[12]=4096,[13]=8192,[14]=16384,[15]=65536,[16]=1073741824,[17]=2147483648,[18 ... (9998)]=2147483647,[9999]=2147483647};

pn_t res[10000] = {[0 ... (4999)]=1,[5000 ... (6999)]=2,[7000 ... (9999)]=0};

//data_t hl[3] = {24,18,12315};

void chd_PH(data_t &key, data_t &ptr, pn_t &pn) {
//#pragma HLS ARRAY_PARTITION variable=probe cyclic factor=2 dim=1
//#pragma HLS ARRAY_RESHAPE variable=res cyclic factor=16 dim=1
//#pragma HLS ARRAY_MAP variable=probe instance=BRAM1 horizontal
//#pragma HLS ARRAY_MAP variable=res instance=BRAM1 horizontal
// merge two arrays to reduce the cost of BRAM
#pragma HLS RESOURCE variable=probe core=ROM_2P_BRAM
#pragma HLS RESOURCE variable=res core=ROM_2P_BRAM

#pragma HLS INTERFACE ap_ovld port=pn
#pragma HLS INTERFACE ap_vld port=ptr
#pragma HLS INTERFACE ap_vld port=key

	data_t hl[3] = {24,18,12315};
	// fake hash logic here, the hash consists of a simple XOR operation
	//hash(key, hl);
	//hl[0] += k >> 1;
	hl[0] ^= k;
	//hl[1] += k >> 2;
	hl[1] ^= k;
	//hl[2] += k >> 3;
	hl[2] ^= k;
	// end of fake hash logic

	data_t g = hl[0] % 10000;
	data_t f = hl[1] % 10000;
	data_t h = (hl[2] % 9999) + 1;

	data_t disp = probe[ptr + g];
	data_t probe0_num = disp % 10000;
	data_t probe1_num = disp/10000;
	ap_uint<64> mul_res = h*probe0_num;

	unsigned long long sum = (ap_uint<64>)f + mul_res;
	sum = sum + (ap_uint<64>)probe1_num;
	ap_uint<14> res_idx = sum % 10000;

	pn = res[res_idx];
	return ;
}
