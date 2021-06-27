# SPHF
Satellite Perfect Hash Function is used to map input keys(IP addresses) on satellite to non-conflict integers.

It is designed to handle small scale datasets. The space cost of function is around 4bits / key.

The query step is friendly to be optimized according to hardware constraints.

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
