#Minimal working example

To reproduce, run  `make`, and you sould see this: 

```bash
$ make
gcc main.c -ldl -L /usr/local/lib64 -l:libcrypto.so.3
sould be ok
LD_LIBRARY_PATH=/usr/local/lib64 ./a.out
about to create the skey
created the skey
ok

should segfault
LD_LIBRARY_PATH=/usr/local/lib64 ./a.out dl
about to create the skey
make: *** [Makefile:16: fail] Segmentation fault (core dumped)

```


