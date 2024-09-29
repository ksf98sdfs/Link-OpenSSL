#include <iostream>
#include <openssl/evp.h>

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
  EVP_PKEY* generate_key_pair();
  if (EVP_PKEY) {
    std::cout << "Generated key pairs!" << std::endl;
  } else {
    std::cout << "Error, could not generate key pairs." << std::endl;
  }
  
  return 0;
}
