# SPHF-RTLP
SPHF-RTLP is the optimized version of SPHF, which targets at 10000 keys mapping with less hardware resource for query step.

Different from SPHF in two aspects.

1, The option for r and m is power of 2. 

2, f() is eliminated and g() is modified with lightweight hash based on prime coefficients.

Refer to the original paper for more information.

# Compile and Run
Use cmake with g++ to compile the program.

```
cmake ..
make
```

To test all files in the folder, results will be shown in terminal.

`./CheckHash FOLDER_PATH/`

# Citation
The current work is for 17th CoNEXT conference, 2021.
Any questions, please contact keran_zhang@outlook.com
