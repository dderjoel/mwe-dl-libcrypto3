#define _GNU_SOURCE
#include <assert.h>
#include <dlfcn.h>
#include <openssl/evp.h>

// c.f. objects/objects.pl
#define NID_X25519 1034

// some data to call new with
unsigned const char scalar[] = {
    0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x10, 0x11,
    0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x20, 0x21, 0x22,
    0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x30, 0x31, 0x32,
};

int main(int argc, char **argv) {

  int keylen = 32;
  assert(keylen == sizeof(scalar));

  // open the library
  void *libhandle = dlmopen(LM_ID_NEWLM, "/usr/local/lib64/libcrypto.so.3",
                            RTLD_LAZY | RTLD_DEEPBIND | RTLD_LOCAL);
  assert(libhandle != NULL);

  // declare the pointer to the function
  EVP_PKEY *(*dl_EVP_PKEY_new_raw_private_key)(
      int type, ENGINE *e, const unsigned char *key, size_t keylen);

  // load from libhandle
  if ((dl_EVP_PKEY_new_raw_private_key =
           dlsym(libhandle, "EVP_PKEY_new_raw_private_key")) == NULL) {
    fprintf(stderr, "dlsym  EVP_PKEY_new_raw_private_key: %s\n", dlerror());
  }

  // create a private key form it.
  EVP_PKEY *skey = NULL;
  printf("about to create the skey\n");

  if (argc > 1) {
    // this segfaults somewhere in the library
    skey = dl_EVP_PKEY_new_raw_private_key(NID_X25519, NULL, scalar, keylen);
  } else {
    // this does not
    skey = EVP_PKEY_new_raw_private_key(NID_X25519, NULL, scalar, keylen);
  }
  printf("created the skey\n");
  assert(skey != NULL);

  dlclose(libhandle);
  return 0;
}
