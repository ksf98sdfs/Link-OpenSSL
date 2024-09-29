#include <iostream>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <windows.h>

EVP_PKEY *generate_key_pair() {
    EVP_PKEY_CTX *ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_RSA, nullptr);
    if (!ctx) {
        std::cerr << "Failed to create EVP_PKEY_CTX" << std::endl;
        return nullptr;
    }

    if (EVP_PKEY_keygen_init(ctx) <= 0) {
        std::cerr << "Failed to initialize keygen" << std::endl;
        EVP_PKEY_CTX_free(ctx);
        return nullptr;
    }

    if (EVP_PKEY_CTX_set_rsa_keygen_bits(ctx, 2048) <= 0) {
        std::cerr << "Failed to set key length" << std::endl;
        EVP_PKEY_CTX_free(ctx);
        return nullptr;
    }

    EVP_PKEY *key = nullptr;
    if (EVP_PKEY_keygen(ctx, &key) <= 0) {
        std::cerr << "Failed to generate key pair" << std::endl;
        EVP_PKEY_CTX_free(ctx);
        return nullptr;
    }

    EVP_PKEY_CTX_free(ctx);
    return key;
}

int main()
{
  Sleep(5000);
  OpenSSL_add_all_algorithms();
  OPENSSL_cleanup();
  
  std::cout << "Hello, World!" << std::endl;
  
  EVP_PKEY* key = generate_key_pair();
  if (key) {
    std::cout << "Generated key pairs!" << std::endl;
  } else {
    std::cout << "Error, could not generate key pairs." << std::endl;
  }
  
  return 0;
}
