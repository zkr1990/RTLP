#include "bbHash.h"
//#include "hash64.h"

pn_t res[10000] = {[0 ... (4999)]=1,[5000 ... (6999)]=2,[7000 ... (9999)]=0};
ap_uint<1> A1[10000] = {[0 ... (2499)]=0,[2500 ... (4999)]=1,[5000 ... (7999)]=0,[8000 ... (9999)]=1};
//ap_uint<1> A2[10000] = {[0 ... (2499)]=1,[2500 ... (4999)]=2};
ap_uint<64> seeds[2] = {0xAAAAAAAA55555555ULL,0x33333333CCCCCCCCULL};

void bbHash(data_t &key, pn_t &pn) {

#pragma HLS RESOURCE variable=A1 core=ROM_2P_BRAM
//#pragma HLS RESOURCE variable=A2 core=ROM_2P_BRAM
#pragma HLS RESOURCE variable=res core=ROM_2P_BRAM
#pragma HLS RESOURCE variable=seeds core=ROM_2P_BRAM

	// fake hash1 seed
//	ap_uint<64> seeds[2] = {0xAAAAAAAA55555555ULL,0x33333333CCCCCCCCULL};

	data_t input = key;

	// level1
//	hash64(input, seeds[0]);
	ap_uint<64> hash1 = seeds[0];
	hash1 ^= (hash1 <<  7) ^  key * (hash1 >> 3) ^ (~((hash1 << 11) + (key ^ (hash1 >> 5))));
	hash1 = (~hash1 ) + (hash1 << 21);
	hash1 = hash1 ^ (hash1 >> 24);
	hash1 = (hash1 + (hash1 << 3)) + (hash1 << 8);
	hash1 = hash1 ^ (hash1 >> 14);
	hash1 = (hash1 + (hash1 << 2)) + (hash1 << 4);
	hash1 = hash1 ^ (hash1 >> 28);
	hash1 = hash1 + (hash1 << 31);

	if(A1[hash1] == 1){
		pn = res[hash1];
		return;
	}

	//level2
//	hash64(input, seeds[1]);
	ap_uint<64> hash2 = seeds[1];
	hash2 ^= (hash2 <<  7) ^  key * (hash2 >> 3) ^ (~((hash2 << 11) + (key ^ (hash2 >> 5))));
	hash2 = (~hash2 ) + (hash2 << 21);
	hash2 = hash2 ^ (hash2 >> 24);
	hash2 = (hash2 + (hash2 << 3)) + (hash2 << 8);
	hash2 = hash2 ^ (hash2 >> 14);
	hash2 = (hash2 + (hash2 << 2)) + (hash2 << 4);
	hash2 = hash2 ^ (hash2 >> 28);
	hash2 = hash2 + (hash2 << 31);

	pn = res[hash2];
	return;
}
