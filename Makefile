LIBRARY_PATH=/usr/local/lib64
LIBRARY_NAME=libcrypto.so.3
all: ok fail
 
a.out: main.c $(LIBRARY_PATH)/$(LIBRARY_NAME)
	gcc main.c -ldl -L $(LIBRARY_PATH) -l:$(LIBRARY_NAME)
	LD_LIBRARY_PATH=$(LIBRARY_PATH) ldd ./${@}

ok: a.out
	LD_LIBRARY_PATH=$(LIBRARY_PATH) ./${^}
	@echo if you read this, that is ok
	@echo

fail: a.out
	@echo should segfault
	LD_LIBRARY_PATH=$(LIBRARY_PATH) ./${^} dl
	@echo wont be able to read this
	echo

