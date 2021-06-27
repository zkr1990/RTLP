# RHF
Routing Hash Function(RHF) is used to hash from input IPs to output interface numbers.
The purpose of RHF is not solving conflicts, but manage the conflicts with a proper outcome.

The RHF logic can be optimized with the consideration of hardware constraints.
Targeting 10000 input IPs, We design two RHF Builders and Testers.
PerfectRouterBuilder1 is the same as RHF1 in the original paper.
PerfectRouterBuilder3 is the same as RHF2 in the original paper.

# Implementation
## compile
```
cd router_mega
cmake ..
make
```

## To be used alone, commands in the router_mega folder
With multiple choices, please specify the number of router(n = 1/2/3).

Report construction time:
`./Generate n FolderPath`

Generate function: specify an input file first. An example is the input.txt.
`./Generate n input.txt function.txt`
function.txt is generated with parameters of RHF

Test generated function:
`./Generate n input.txt function.txt -t`
The program use input.txt as test case, and check whether the generated RHF can map correctly.

## To be used for folder with multiple input files, commands in the RHF folder
Generate all function files in routerFuncData folder. 
By default, n = 1.(change line 26 to modify router number)
`sh generate.sh`

Test all function files for files in Input_data
`sh test.sh`

# RTLP Results (10000 32 bit input IPs)
RHF algorithms are calculated as foolow:
1, For construction time, 1000 experiments are conducted. The max time and average time are calculated.

2, For storage cost, source code of algorithms is analyzed and storage is estimated with the consideration of data structures used in construction steps.

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
