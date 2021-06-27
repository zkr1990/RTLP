# RHF
Routing Hash Function(RHF) is used to hash from input IPs to output interface numbers.

Two RHFdesigns (RHF1, RHF2) are implemented with respect to hardware constraints and different balance points in construction time, lookup latency and resource cost.
Targeting 10000 32-bit input IPs, two RHF design is proposed.

# Implementation
## Compile program
```
cd router_mega
cmake ..
make
```

## Used for single input file, commands in the router_mega folder
Specify the number of router(n = 1/2/3) first. 1 is for RHF1, 3 is for RHF2 in the original paper.

To report construction time:

`./Generate n FolderPath`

To generate function: Specify an input file (input.txt) first, function.txt will be generated with parameters of RHF.

`./Generate n input.txt function.txt`

Test generated function:

`./Generate n input.txt function.txt -t`

The program use input.txt as test case, and check whether the generated RHF can map correctly.

## Used for folder with multiple input files, commands in the RHF folder
Generate all function files in routerFuncData/ folder. By default, n is set to 1.(change line 26 to modify router number)

`sh generate.sh`

Test all function files for files in Input_data/, n is set to 1.

`sh test.sh`

# RTLP Results for RHF1 and RHF2 (10000 32 bit input IPs)
RHF algorithms are calculated as foolow:

1, For construction time, 1000 experiments are conducted. The max time and average time are calculated.

2, For storage cost, the source code of algorithms is analyzed and storage is estimated considering data structures used in construction steps.

3, For function space, The storage is estimated with consideration of D[] and I[].

Method       |AVG time(ms)	|MAX time(ms)	|Storage(Kb)	|Function Space(Kb)
-------------|------------------|:-------------:|:-------------:|:---------:
BDZ-PH-RTL   |3.73+e	        |6.85+e		|3457		|39.6
CHD-PH-RTL   |2.69+e	        |4.79+e		|957		|30
BBHash-RTL   |7.64+e	        |28.62+e	|352		|39.2
SPHF-RTL     |3.05+e	        |5.96+e		|538		|50
RHF1	     |3.34	        |6.31		|421		|43
RHF2	     |268.65	        |1865.24	|405		|29

# Citation
The current work is for 17th CoNEXT conference, 2021.
Any questions, please contact keran_zhang@outlook.com
