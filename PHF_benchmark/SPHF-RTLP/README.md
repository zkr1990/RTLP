# SPHF
Satellite Perfect Hash Function is used to map input keys(IP addresses) on satellite to non-conflict integers.

It is designed to handle small scale datasets. The space cost of function is around 4bits / key.

The query step is friendly to be optimized according to hardware constraints.

# SPHF-RTLP
SPHF-RTLP is the optimized version of SPHF, which targets at 10000 keys mapping with less hardware resource for query step.

Compared with SPHF, it mainly changed the implementation of f() and g().

The option for r and m is power of 2. f() is eliminated and g() is modified with lightweight hash based on prime coefficients.

Refer to the original paper for more information.

Compile, use g++

```
cmake ..
make
```

Check whether all files can be mapped without conflict by SPHF

`./CheckHash FOLDER_PATH/`

# Citation
The current work is for 17th CoNEXT conference, 2021.
Any questions, please contact keran_zhang@outlook.com
