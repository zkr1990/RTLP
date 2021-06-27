# Vivado HLS 2019.2 benchmark
This is the HLS benchmark code for RTLP algorithms. BBHash-RTLP, BDZ_PH-RTLP, CHD_PH-RTLP, SPHF-RTLP, RHF1 and RHF2 are compared in terms of clock cycle count, BRAM usage, DSP48E usage, LUT usage.

# Settings (10000 32 bit input IPs)
Since the goal of HLS experiment is to estimate the FPGA resource usage,
BBHash-RTLP, BDZ_PH-RTLP, CHD_PH-RTLP and SPHF-RTLP are implemented with reference to the query step of source code.
SPHF-RTLP, RHF1 and RHF2 are optimized designs, which are further compared with PR-TCAM approach in the paper.

# Result

Method       |Cycle count	|BRAM(18Kb)	|DSP48E count	|LUT count
-------------|------------------|:-------------:|:-------------:|:---------:
BDZ-PH-RTL   |85	        |10		|12		|2306
CHD-PH-RTL   |116	        |34		|5		|2110
BBHash-RTL   |31	        |5		|14		|4077
SPHF-RTL     |8		        |2		|4		|297
RHF1	     |5		        |2		|1		|86
RHF2	     |5		        |2		|0		|642

# Citation
The current work is for 17th CoNEXT conference, 2021.
Any questions, please contact keran_zhang@outlook.com
