# RHF
Routing Hash Function(RHF) is used to hash from input IPs to output interface numbers.
The purpose of RHF is not solving conflicts, but manage the conflicts with a proper outcome.

The RHF logic can be optimized with the consideration of hardware constraints.
Targeting 10000 input IPs, We design two RHF Builders and Testers.
PerfectRouterBuilder1 is the same as RHF1 in the original paper.
PerfectRouterBuilder3 is the same as RHF2 in the original paper.

# compile
cd router_mega
cmake ..
make

# To be used alone, commands in the router_mega folder
With multiple choices, please specify the number of router(n = 1/2/3).

Report construction time:
./Generate n FolderPath

Generate function: specify an input file first. An example is the input.txt.
./Generate n input.txt function.txt
function.txt is generated with parameters of RHF

Test generated function:
./Generate n input.txt function.txt -t
The program use input.txt as test case, and check whether the generated RHF can map correctly.

# To be used for folder with multiple input files, commands in the RHF folder
Generate all function files in routerFuncData folder. 
By default, n = 1.(change line 26 to modify router number)
sh generate.sh

Test all function files for files in Input_data
sh test.sh

# RTLP Result (10000 32 bit input IPs)
RHF algorithms are calculated as foolow:
1, For construction time, 1000 experiments are conducted. The max time and average time are calculated.
2, For storage cost, source code of algorithms is analyzed and storage is estimated with the consideration of data structures used in construction steps.
3, For function space, The storage is estimated with consideration of D[] and I[].

# Citation
The current work is for 17th CoNEXT conference, 2021.
Any questions, please contact keran_zhang@outlook.com
