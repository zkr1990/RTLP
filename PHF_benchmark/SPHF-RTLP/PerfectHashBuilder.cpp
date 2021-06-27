//---------------------------------------------------------------------------
#include <stdio.h>
#include "PerfectHashBuilder.h"
#include "PerfectHash.h"
#include "IntUtils.h"
//---------------------------------------------------------------------------
struct TSlotInfo
{
	uint64_t startPos;
	int64_t  nItem;
};
//---------------------------------------------------------------------------
int CmpSlot(const void *d1,const void *d2)
{
	// We assume nItem is much less than INT_MAX
	return (int)( ((TSlotInfo*)d2)->nItem - ((TSlotInfo*)d1)->nItem ); //Reverse order
}
//---------------------------------------------------------------------------
bool TPerfectHashBuilder::Build(uint64_t *hash,uint64_t nHash,int nBucket,int nSlot,int nSpace)
{
	// if( (nHash==0) || (nPerSlot<=0) || ((uint64_t)nPerSlot>nHash) )
	// 	return false;
	// int64_t nSlot = RoundUpPrime(nHash*100/nPerSlot);

	// if(nSlot==0)
	// 	return false;

	// if(nBucket==0)
	// 	nBucket = RoundUpPrime(nHash);

    // if(nBucket==0){
	// 	fprintf(stderr,"nBucket: %d, too small to round up prime. \r\n", nBucket);
    //     return false;
	// }

    if(nSpace==0)
        nSpace = nBucket;

	TArray<TSlotInfo> slots;
	slots.AllocFill(nSlot);
	slots.InitZero();
	
	for(uint64_t i=0;i<nHash;i++){
		slots[hash[i]%nSlot].nItem ++;
	}

	slots[0].startPos = slots[0].nItem-1;

	for(int64_t i=1;i<nSlot;i++){
		slots[i].startPos = slots[i].nItem+slots[i-1].startPos;
	}

	TArray<uint64_t> sortedHash;
	sortedHash.AllocFill(nHash);

	for(uint64_t i=0;i<nHash;i++)
	{
		uint64_t inx = hash[i]%nSlot;

		sortedHash[slots[inx].startPos] = hash[i];
		slots[inx].startPos --;
	}

	slots.QSort(CmpSlot);
	data.AllocFill(nSlot*sizeof(TPerfectHashData::d[0]));
	// data.AllocFill(16+nSlot*sizeof(TPerfectHashData::d[0]));
	data.InitZero();

	// TPerfectHashData *p = (TPerfectHashData *)data();
	// p->r = nSlot;
	// p->m = nBucket;

	TBitArray maskBits;
	maskBits.Alloc(nBucket);

	TArray<uint64_t> bitStack;
	bitStack.AllocFill(slots[0].nItem);

	for(int64_t i=0;i<nSlot;i++)
	{
		int      nItem    = (int) slots[i].nItem;

		if(nItem==0)
            continue;

		uint64_t startPos = slots[i].startPos+1;

		bool fail;

		//int64_t maxD = (1ull<<(sizeof(p->d[0])*8))-1;
		// fprintf(stderr,"maxD = %ld. \r\n", maxD);
		int64_t maxD = 512;
		for(int64_t d=0;d<maxD;d++)
		{
			fail = false;
			for(int j=0;j<nItem;j++)
			{
				// for PHF task
				// sol 1: with city hash
				// int f = FastIntHash(sortedHash[startPos+j],d)%nSpace;
				uint64_t vL = sortedHash[startPos+j];
				uint64_t vH = d;
				// uint64_t kMul = 0x9ddfea08eb382d69ULL
				int kMul1 = 29947;
				int kMul2 = 29959;
				int kMul3 = 29983;
				int kMul4 = 29989;
				int k1 = 29881;
				int k2 = 29917;
				int k3 = 29921;
				int k4 = 29927;
				uint64_t a = (vH ^ (vL-k1)) * kMul1;
				uint64_t b = (vH ^ (vL-k2)) * kMul2;
				uint64_t c = (vH ^ (vL-k3)) * kMul3;
				uint64_t d1 = (vH ^ (vL-k4)) * kMul4;
				a ^= (d1 >> 7);
				b ^= (a >> 8);
				c ^= (b >> 9);
				d1 ^= (c >> 10);
				// b ^= (b >> 47);
				// b *= kMul;
				uint64_t e = a ^ b ^ c ^ d1;


				// uint64_t b = ((vL>>1) ^ vH) * kMul;
				// b ^= (b >> 6);
				// int f = (a ^ b)%nSpace;

				int f = (e)%nSpace;
				
				// for Routing Table Lookup task
				// uint32_t x_key = sortedHash[startPos+j];
				// sol 2: without city hash
				// int f = (((x_key >> 7) + (uint32_t)d) ^ ((x_key >> 8) ^ x_key)) %nSpace;
				// sol x not used:
				// int64_t x_key1 = (x_key * d);
				// int f = (((x_key1 >> 7) + (uint32_t)d) ^ ((x_key1 >> 8) ^ x_key1)) %nSpace;
				
				if( (f>=nBucket) || (maskBits[f]) )
				{					
					while(j>0)
					{
						j--;
						maskBits.ClearBit(bitStack[j]);
					}
					fail = true;
					break;
				}

				maskBits.SetBit(f);
				bitStack[j] = f;
			}

			if(fail==false)
			{
				// p->d[sortedHash[startPos]%nSlot] = (uint16_t)d;
				data[sortedHash[startPos]%nSlot] = (uint16_t)d;
				break;
			}
		}

		if(fail)
			return false; // we can't find suitable d in [0,65535]
	}

	return true;
}

//---------------------------------------------------------------------------
