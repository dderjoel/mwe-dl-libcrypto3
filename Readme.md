# Minimal working example

For [this issue on Stackoverflow](https://stackoverflow.com/questions/70030529/manually-loading-libcrypto-dlmopen-dlsym-segfaults-dynamically-linked-works)

To reproduce, run `make -B`, and you sould see this: 

```bash
$ make -B
gcc main.c -ldl -L /usr/local/lib64 -l:libcrypto.so.3
LD_LIBRARY_PATH=/usr/local/lib64 ldd ./a.out
        linux-vdso.so.1 (0x00007ffc803e7000)
        libdl.so.2 => /usr/lib/libdl.so.2 (0x00007f7a6a18f000)
        libcrypto.so.3 => /usr/local/lib64/libcrypto.so.3 (0x00007f7a69d71000)
        libc.so.6 => /usr/lib/libc.so.6 (0x00007f7a69ba5000)
        /lib64/ld-linux-x86-64.so.2 => /usr/lib64/ld-linux-x86-64.so.2 (0x00007f7a6a1bd000)
        libpthread.so.0 => /usr/lib/libpthread.so.0 (0x00007f7a69b84000)
LD_LIBRARY_PATH=/usr/local/lib64 ./a.out
about to create the skey
created the skey
if you read this, that is ok

should segfault
LD_LIBRARY_PATH=/usr/local/lib64 ./a.out dl
about to create the skey
make: *** [Makefile:16: fail] Segmentation fault (core dumped)
```
