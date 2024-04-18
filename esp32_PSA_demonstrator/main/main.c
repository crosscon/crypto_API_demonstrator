#include <stdio.h>
#include "psa/crypto.h"
#include "esp_timer.h"
#include "esp_system.h"

#include "sdkconfig.h"
//#include "mbedtls/esp_config.h"

static int print_features(void)
{
    char *text;
    printf("Using following implementations:\r\n");
#if defined(MBEDTLS_FREESCALE_LTC_SHA256)
    text = "LTC HW accelerated";
#elif defined(MBEDTLS_FREESCALE_MMCAU_SHA256)
    text = "MMCAU HW accelerated";
#elif defined(MBEDTLS_FREESCALE_LPC_SHA256)
    text = "LPC HW accelerated";
#elif defined(MBEDTLS_FREESCALE_CAU3_SHA256)
    text = "CAU3 HW accelerated";
#elif defined(MBEDTLS_FREESCALE_DCP_SHA256)
    text = "DCP HW accelerated";
#elif defined(MBEDTLS_FREESCALE_HASHCRYPT_SHA256)
    text = "HASHCRYPT HW accelerated";
#elif defined(MBEDTLS_FREESCALE_CAAM_SHA256)
    text = "CAAM HW accelerated";
#elif defined(MBEDTLS_NXP_SENTINEL200)
    text = "S200 HW accelerated";
#elif defined(MBEDTLS_NXP_SENTINEL300)
    text = "S300 HW accelerated";
#elif defined(CONFIG_MBEDTLS_HARDWARE_SHA)
    text = "ESP32 accelerated";
#else
    text = "Software implementation";
#endif
    printf("  SHA: %s\r\n", text);
#if defined(MBEDTLS_FREESCALE_LTC_AES)
    text = "LTC HW accelerated";
#elif defined(MBEDTLS_FREESCALE_MMCAU_AES)
    text = "MMCAU HW accelerated";
#elif defined(MBEDTLS_FREESCALE_LPC_AES)
    text = "LPC HW accelerated";
#elif defined(MBEDTLS_FREESCALE_CAU3_AES)
    text = "CAU3 HW accelerated";
#elif defined(MBEDTLS_FREESCALE_DCP_AES)
    text = "DCP HW accelerated";
#elif defined(MBEDTLS_FREESCALE_HASHCRYPT_AES)
    text = "HASHCRYPT HW accelerated";
#elif defined(MBEDTLS_FREESCALE_CAAM_AES)
    text = "CAAM HW accelerated";
#elif defined(MBEDTLS_NXP_SENTINEL200)
    text = "SW AES, S200 HW accelerated CCM and CMAC";
#elif defined(MBEDTLS_NXP_SENTINEL300)
    text = "SW AES, S300 HW accelerated CCM and CMAC";
#elif defined(CONFIG_MBEDTLS_HARDWARE_AES)
    text = "ESP32 accelerated";
#else
    text = "Software implementation";
#endif
    printf("  AES: %s\r\n", text);
    return 0;
}
void test_hash(uint8_t *plaintext, size_t plaintext_length, unsigned int iterations) {

    psa_status_t status;

    status = psa_crypto_init();

    if (status != PSA_SUCCESS) {
        printf("Failed to initialize PSA Crypto\n");
    }
    uint8_t hash[32];
    size_t hash_lenght;

    uint64_t start = esp_timer_get_time();
    for(int i = 0; i < iterations; i++) {
        status = psa_hash_compute(PSA_ALG_SHA_256, plaintext, plaintext_length, hash, sizeof(hash), &hash_lenght);
        if (status != PSA_SUCCESS) {
            printf("hashing failed\n");
        }
    }
    uint64_t end = esp_timer_get_time();
    //printf("%llu milliseconds execution time\n",(end - start)/1000);
    uint64_t ms = (end - start)/1000;
    printf("%u HASH iterations took %llu milliseconds ( %3.3f milliseconds per iteration)\n",
           iterations, ms, (ms / (double) iterations));
}

void test_aes(uint8_t *plaintext, size_t plaintext_length, int iterations) {

    uint64_t start = esp_timer_get_time();
    psa_status_t status;
    status = psa_crypto_init();

    if (status != PSA_SUCCESS) {
        printf("Failed to initialize PSA Crypto\n");
                    //return -1;
    }

    for(int i = 0; i < iterations; i++) {
        
        psa_key_attributes_t attributes = psa_key_attributes_init();
        psa_set_key_usage_flags(&attributes, PSA_KEY_USAGE_ENCRYPT | PSA_KEY_USAGE_DECRYPT);
        psa_set_key_algorithm(&attributes, PSA_ALG_CBC_PKCS7);
        psa_set_key_type(&attributes, PSA_KEY_TYPE_AES);
        psa_set_key_bits(&attributes, 128);  // Example using AES-128

                    // Key data (example key - in a real application, ensure the key is securely handled)
        uint8_t key_data[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };
        psa_key_id_t key_id;

                    // Import the key
        status = psa_import_key(&attributes, key_data, sizeof(key_data), &key_id);
        if (status != PSA_SUCCESS) {
            printf("Failed to import key\n");
                        //return -1;
        }

        //uint8_t plaintext[] = "Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.";
        uint8_t ciphertext[PSA_CIPHER_ENCRYPT_OUTPUT_SIZE(PSA_KEY_TYPE_AES, PSA_ALG_CBC_PKCS7, plaintext_length)];
        size_t ciphertext_size;
        status = psa_cipher_encrypt(key_id, PSA_ALG_CBC_PKCS7, plaintext, plaintext_length, ciphertext, sizeof(ciphertext), &ciphertext_size );
        //printf("Ciphertext message: %s\n", ciphertext);

        uint8_t output[PSA_CIPHER_DECRYPT_OUTPUT_SIZE(PSA_KEY_TYPE_AES, PSA_ALG_CBC_PKCS7, sizeof(ciphertext))];
        size_t output_size;

        status = psa_cipher_decrypt(key_id, PSA_ALG_CBC_PKCS7, ciphertext, sizeof(ciphertext), output, sizeof(output), &output_size );
        //printf("Decrypted message: %s\n", output);
        psa_destroy_key(key_id);
    }
    uint64_t end = esp_timer_get_time();
    uint64_t ms = (end - start)/1000;
    printf("%u AES iterations took %llu milliseconds ( %3.3f milliseconds per iteration)\n",
           iterations, ms, (ms / (double) iterations));
}

void app_main(void)
{
    
    print_features();

    uint8_t plaintext[] = "Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.";
    test_aes(plaintext, sizeof(plaintext), 1000);
    test_hash(plaintext, sizeof(plaintext), 1000);
    printf("Finished Testbed");
    esp_restart();
}
