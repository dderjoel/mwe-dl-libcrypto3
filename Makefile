LIBRARY_PATH=/usr/local/lib64
LIBRARY_NAME=libcrypto.so.3
all: ok fail

a.out: main.c $(LD_LIBRARY_PATH)/$(LIBRARY_NAME)
	gcc main.c -ldl -L $(LD_LIBRARY_PATH) -l:$(LIBRARY_NAME)

ok: a.out
	@echo sould be ok
	LD_LIBRARY_PATH=$(LIBRARY_PATH) ./${^}
	@echo ok
	@echo

fail: a.out
	@echo should segfault
	LD_LIBRARY_PATH=$(LIBRARY_PATH) ./${^} dl
	@echo wont be able to read this
	echo

