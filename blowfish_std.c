#include <stdio.h>
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <string.h>
#include <unistd.h>

int main (int argc, char *argv[])
{
  /* Set up the key and iv. Do I need to say to not hard code these in a
   * real application? :-)
   */

  /* A 256 bit key */
  unsigned char *key = NULL;

  /* A 128 bit IV */
  unsigned char *iv = NULL;

  /* Message to be encrypted */
  unsigned char *plaintext = NULL;
  unsigned char *base64_encoded = NULL;

  /* Buffer for ciphertext. Ensure the buffer is long enough for the
   * ciphertext which may be longer than the plaintext, dependant on the
   * algorithm and mode
   */
  unsigned char ciphertext[128];

  /* Buffer for the decrypted text */
  unsigned char decryptedtext[128];

  int decryptedtext_len, ciphertext_len;
  int enc = 0;
  int opt;

  while ((opt = getopt(argc, argv, "e:d:k:i")) != -1) 
  {
    switch(opt){
      case 'e':
        enc = 1;
        plaintext = (unsigned char*)optarg; 
        break;
      case 'd':
        enc = 0;
        base64_encoded = (unsigned char*)optarg; 
        break;
      case 'k':
        key = (unsigned char*)optarg;
        break;
      case 'i':
        iv = (unsigned char*)optarg;
        break;
    } 
  }

  /* Initialise the library */
  ERR_load_crypto_strings();
  OpenSSL_add_all_algorithms();
  OPENSSL_config(NULL);

  if ( enc )
  {
    /* Encrypt the plaintext */
    ciphertext_len = encrypt (plaintext, strlen ((char *)plaintext), key, iv, ciphertext);

    /* Do something useful with the ciphertext here */
    printf("inputText:[%s]\n", plaintext);
    char* base64_encoded = NULL;
    //BIO_dump_fp (stdout, (const char *)ciphertext, ciphertext_len);
    Base64Encode(ciphertext, ciphertext_len, &base64_encoded);
    printf("blowfishEncrypt/base64Encode:[%s]\n", base64_encoded);

    free(base64_encoded);
  }
  else
  {

    /* Decrypt the ciphertext */
    char *base64_decoded = NULL;
    size_t test;
    Base64Decode(base64_encoded, &base64_decoded, &test );   //Base-64 decoding.
    printf("inputText:[%s]\n", base64_encoded);
    decryptedtext_len = decrypt(base64_decoded, test, key, iv, decryptedtext);
    /* Add a NULL terminator. We are expecting printable text */
    decryptedtext[decryptedtext_len] = '\0';

    /* Show the decrypted text */
    printf("base64Decode/blowfishDecrypt:[%s]\n", decryptedtext);
    free(base64_decoded);
  }

  /* Clean up */
  EVP_cleanup();
  ERR_free_strings();

  return 0;
}

void handleErrors(void)
{
  ERR_print_errors_fp(stderr);
  abort();
}

int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,
  unsigned char *iv, unsigned char *ciphertext)
{
  EVP_CIPHER_CTX *ctx;

  int len;

  int ciphertext_len;

  /* Create and initialise the context */
  if(!(ctx = EVP_CIPHER_CTX_new())) handleErrors();

  /* Initialise the encryption operation. IMPORTANT - ensure you use a key
   * and IV size appropriate for your cipher
   * IV size for *most* modes is the same as the block size.
   */
  if(1 != EVP_EncryptInit_ex(ctx, EVP_bf_cbc(), NULL, key, iv))
    handleErrors();

  /* Provide the message to be encrypted, and obtain the encrypted output.
   * EVP_EncryptUpdate can be called multiple times if necessary
   */
  if(1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))
    handleErrors();
  ciphertext_len = len;

  /* Finalise the encryption. Further ciphertext bytes may be written at
   * this stage.
   */
  if(1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)) handleErrors();
  ciphertext_len += len;

  /* Clean up */
  EVP_CIPHER_CTX_free(ctx);

  return ciphertext_len;
}

int decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key,
  unsigned char *iv, unsigned char *plaintext)
{
  EVP_CIPHER_CTX *ctx;

  int len;

  int plaintext_len;

  /* Create and initialise the context */
  if(!(ctx = EVP_CIPHER_CTX_new())) handleErrors();

  /* Initialise the decryption operation. IMPORTANT - ensure you use a key
   * and IV size appropriate for your cipher
   * IV size for *most* modes is the same as the block size. */
  if(1 != EVP_DecryptInit_ex(ctx, EVP_bf_cbc(), NULL, key, iv))
    handleErrors();

  /* Provide the message to be decrypted, and obtain the plaintext output.
   * EVP_DecryptUpdate can be called multiple times if necessary
   */
  if(1 != EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len))
    handleErrors();
  plaintext_len = len;

  /* Finalise the decryption. Further plaintext bytes may be written at
   * this stage.
   */
  if(1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len)) handleErrors();
  plaintext_len += len;

  /* Clean up */
  EVP_CIPHER_CTX_free(ctx);

  return plaintext_len;
}
