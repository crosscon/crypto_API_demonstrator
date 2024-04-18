/*
 * Copyright 2016-2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file    LPC55S69_PSA_DEMO.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "fsl_debug_console.h"

#include "fsl_power.h"

#include MBEDTLS_CONFIG_FILE

#include "psa/crypto.h"


#define DWT_CONTROL             (*(volatile uint32_t *)0xE0001000)
#define DWT_CYCCNT              (*(volatile uint32_t *)0xE0001004)
#define DWT_CYCCNTENA_BIT       (1UL<<0)

static volatile uint32_t s_MsCount = 0U;

void enableCycleCounter() {
	DWT_CONTROL |= DWT_CYCCNTENA_BIT;
}

uint64_t getClockCycles() {
	return DWT_CYCCNT;
}
void SysTick_Handler(void)
{
    s_MsCount++;
}

static int print_features(void)
{
    char *text;
    PRINTF("Using following implementations:\r\n");
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
    PRINTF("  SHA: %s\r\n", text);
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
    PRINTF("  AES: %s\r\n", text);
    return 0;
}


void test_hash(uint8_t *plaintext, size_t plaintext_length, unsigned int iterations) {

	uint64_t start= getClockCycles();

    psa_status_t status;

    status = psa_crypto_init();

    if (status != PSA_SUCCESS) {
        PRINTF("Failed to initialize PSA Crypto\n");
        return;
    }
    uint8_t hash[32];
    size_t hash_lenght;

    for(int i = 0; i < iterations; i++) {
        status = psa_hash_compute(PSA_ALG_SHA_256, plaintext, plaintext_length, hash, sizeof(hash), &hash_lenght);
        if (status != PSA_SUCCESS) {
            PRINTF("hashing failed\n");
        }
    }
    uint64_t end = getClockCycles();
    uint64_t cycles = end - start;
    double secs = (double) cycles / SystemCoreClock;
    uint64_t ms = secs * 1000;
    //uint64_t millis_per_iteration = (ms * 1000) / iterations;
    PRINTF("%u HASH iterations took %llu milliseconds (%3.3f ms per iteration)\n", iterations, ms, (ms / (double) iterations));

}


void test_aes(uint8_t *plaintext, size_t plaintext_length, int iterations) {

	uint64_t start= getClockCycles();

    psa_status_t status;
    status = psa_crypto_init();

    if (status != PSA_SUCCESS) {
        PRINTF("Failed to initialize PSA Crypto\n");
        return;
    }

    for(int i = 0; i < iterations; i++) {

        psa_key_attributes_t attributes = psa_key_attributes_init();
        psa_set_key_usage_flags(&attributes, PSA_KEY_USAGE_ENCRYPT | PSA_KEY_USAGE_DECRYPT);
        psa_set_key_algorithm(&attributes, PSA_ALG_CBC_PKCS7);
        psa_set_key_type(&attributes, PSA_KEY_TYPE_AES);
        psa_set_key_bits(&attributes, 128);  // AES-128

        // Key data (example key - in a real application, ensure the key is securely handled)
        uint8_t key_data[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };
        psa_key_id_t key_id;

        status = psa_import_key(&attributes, key_data, sizeof(key_data), &key_id);
        if (status != PSA_SUCCESS) {
            PRINTF("Failed to import key\n");
            return;
        }

        uint8_t ciphertext[PSA_CIPHER_ENCRYPT_OUTPUT_SIZE(PSA_KEY_TYPE_AES, PSA_ALG_CBC_PKCS7, plaintext_length)];
        size_t ciphertext_size;
        status = psa_cipher_encrypt(key_id, PSA_ALG_CBC_PKCS7, plaintext, plaintext_length, ciphertext, sizeof(ciphertext), &ciphertext_size );

        uint8_t output[PSA_CIPHER_DECRYPT_OUTPUT_SIZE(PSA_KEY_TYPE_AES, PSA_ALG_CBC_PKCS7, sizeof(ciphertext))];
        size_t output_size;

        status = psa_cipher_decrypt(key_id, PSA_ALG_CBC_PKCS7, ciphertext, sizeof(ciphertext), output, sizeof(output), &output_size );
        psa_destroy_key(key_id);
        if(memcmp(plaintext, output, plaintext_length) != 0) {
            PRINTF("Encryption/Decryption failed");
        } 
    }

    uint64_t end = getClockCycles();
    uint64_t cycles = end - start;
    double secs = (double) cycles / SystemCoreClock;
    uint64_t ms = secs * 1000;
    //uint64_t millis_per_iteration = (ms * 1000) / iterations;
    PRINTF("%u AES iterations took %llu milliseconds ( %3.3f ms per iteration)\n", iterations, ms, (ms / (double) iterations));
}

int main(void) {

    /*Initialization of Hardware*/
    POWER_SetBodVbatLevel(kPOWER_BodVbatLevel1650mv, kPOWER_BodHystLevel50mv, false);
    CLOCK_AttachClk(BOARD_DEBUG_UART_CLK_ATTACH);

    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitDebugConsole();
    enableCycleCounter();
    /* Can be removed if Hardware acceleration is not used*/
    if( CRYPTO_InitHardware() != kStatus_Success )
    {
        PRINTF( "Initialization of crypto HW failed\n" );
    }

    print_features();
    enableCycleCounter();
    /*Example String*/
    uint8_t plaintext[] = "Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.";
    test_aes(plaintext, sizeof(plaintext), 1000);
    test_hash(plaintext, sizeof(plaintext), 500);
    PRINTF("Finished Testbed");
    return 0 ;
}
