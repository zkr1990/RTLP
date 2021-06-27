# PHF benchmark
This is the benchmark code for PHF/MPHF algorithms. BBHash, cmph and SPHF are compared in terms of constructing time and theoretical storage cost.

# bbhash
BBHash algorithm is MPHF generator mainly designed for massive key sets.

# cmph
cmph is a PHF/MPHF library with multiple different algorithms.

# SPHF
SPHF is PHF designed for satellite applications.

# SPHF-RTLP
SPHF-RTLP is PHF optimized according to hardware features, mainly for input key sets with size smaller than 10000.

All algorithms need compile first in each folder. Please refer to different README.md in each subfolder.
# Input data generation
Input_data folder contains inputs used for generating PHF/MPHF functions and test the correctness of those functions.
Run:
python3 generate_test_data.py 
to generate 1000 input files(mark as 1000 different folders). Example includes 0,1,2 folders.
By default, the size of input key set is 10000, please set n in line 16 accordingly.

# PHF Result
Construction phase:
1, For construction time, 1000 experiments are conducted. The max time and average time are calculated.
2, For storage cost, source code of algorithms is analyzed and storage is estimated with the consideration of data structures used in construction steps.

3, For function space, assume input are 10000 32-bit keys:
BBHash: Estimation based on 2 levels of hash. For input, we allocate a buffer with size 32*10000=320000 bit. The conflict mark array for each level needs 10000 bit. Total is 340000 bit.
CHD_PH, BDZ_PH: The storage is directly calculated by checking the size of function_file.
SPHF: The storage is estimated with consideration of D[].

# RTLP Result (10000 32 bit input IPs)
The analysis is similar to PHF results.
RTLP for these algorithms needs an output array with size m*2bit.
For construction time, an Epsilon time is added.
For storage cost, m*2bit is added.
For function space, m*2bit is added.

# Citation
The current work is for 17th CoNEXT conference, 2021.
Any questions, please contact keran_zhang@outlook.com
