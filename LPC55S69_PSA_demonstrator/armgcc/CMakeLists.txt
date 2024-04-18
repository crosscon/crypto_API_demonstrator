# CROSS COMPILER SETTING
SET(CMAKE_SYSTEM_NAME Generic)
CMAKE_MINIMUM_REQUIRED (VERSION 3.10.0)

# THE VERSION NUMBER
SET (Tutorial_VERSION_MAJOR 1)
SET (Tutorial_VERSION_MINOR 0)

if (DEFINED ENV{SdkRootDirPath})
	SET(SdkRootDirPath "$ENV{SdkRootDirPath}")
endif()

if (NOT DEFINED SdkRootDirPath)
	MESSAGE(FATAL_ERROR "SDK path could not be determined. Please update SdkRootDirPath value from cmake-kits.json.")
endif()

# ENABLE ASM
ENABLE_LANGUAGE(ASM)

# RESET FLAG VALUES
SET(CMAKE_ASM_FLAGS_DEBUG "")
SET(CMAKE_ASM_FLAGS_RELEASE "")
SET(CMAKE_C_FLAGS_DEBUG "")
SET(CMAKE_C_FLAGS_RELEASE "")
SET(CMAKE_CXX_FLAGS_DEBUG "")
SET(CMAKE_CXX_FLAGS_RELEASE "")
SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "")
SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "")

SET(CMAKE_STATIC_LIBRARY_PREFIX)
SET(CMAKE_STATIC_LIBRARY_SUFFIX)

SET(CMAKE_EXECUTABLE_LIBRARY_PREFIX)
SET(CMAKE_EXECUTABLE_LIBRARY_SUFFIX)

# CURRENT DIRECTORY
SET(ProjDirPath ${CMAKE_CURRENT_SOURCE_DIR})
include(${ProjDirPath}/ide_overrides.cmake)

SET(EXECUTABLE_OUTPUT_PATH ${ProjDirPath}/${CMAKE_BUILD_TYPE})
SET(LIBRARY_OUTPUT_PATH ${ProjDirPath}/${CMAKE_BUILD_TYPE})

set(CMAKE_USER_MAKE_RULES_OVERRIDE "user_override.cmake")

project(LPC55S69_PSA_demonstrator)
set(MCUX_SDK_PROJECT_NAME LPC55S69_PSA_demonstrator.elf)

include(${ProjDirPath}/flags.cmake)

set(sources "${ProjDirPath}/../component/uart/fsl_adapter_usart.c"
"${ProjDirPath}/../component/uart/fsl_adapter_uart.h"
"${ProjDirPath}/../component/serial_manager/fsl_component_serial_port_uart.h"
"${ProjDirPath}/../component/serial_manager/fsl_component_serial_port_uart.c"
"${ProjDirPath}/../component/serial_manager/fsl_component_serial_port_internal.h"
"${ProjDirPath}/../component/serial_manager/fsl_component_serial_manager.h"
"${ProjDirPath}/../component/serial_manager/fsl_component_serial_manager.c"
"${ProjDirPath}/../component/lists/fsl_component_generic_list.h"
"${ProjDirPath}/../component/lists/fsl_component_generic_list.c"
"${ProjDirPath}/../startup/startup_lpc55s69_cm33_core0.c"
"${ProjDirPath}/../startup/boot_multicore_slave.h"
"${ProjDirPath}/../startup/boot_multicore_slave.c"
"${ProjDirPath}/../CMSIS/tz_context.h"
"${ProjDirPath}/../CMSIS/mpu_armv8.h"
"${ProjDirPath}/../CMSIS/core_cm33.h"
"${ProjDirPath}/../CMSIS/cmsis_version.h"
"${ProjDirPath}/../CMSIS/cmsis_gcc.h"
"${ProjDirPath}/../CMSIS/cmsis_compiler.h"
"${ProjDirPath}/../mbedtls/library/xtea.c"
"${ProjDirPath}/../mbedtls/library/x509_csr.c"
"${ProjDirPath}/../mbedtls/library/x509_crt.c"
"${ProjDirPath}/../mbedtls/library/x509_crl.c"
"${ProjDirPath}/../mbedtls/library/x509_create.c"
"${ProjDirPath}/../mbedtls/library/x509write_csr.c"
"${ProjDirPath}/../mbedtls/library/x509write_crt.c"
"${ProjDirPath}/../mbedtls/library/x509.c"
"${ProjDirPath}/../mbedtls/library/version_features.c"
"${ProjDirPath}/../mbedtls/library/version.c"
"${ProjDirPath}/../mbedtls/library/timing.c"
"${ProjDirPath}/../mbedtls/library/threading.c"
"${ProjDirPath}/../mbedtls/library/ssl_tls13_keys.h"
"${ProjDirPath}/../mbedtls/library/ssl_tls13_keys.c"
"${ProjDirPath}/../mbedtls/library/ssl_tls.c"
"${ProjDirPath}/../mbedtls/library/ssl_ticket.c"
"${ProjDirPath}/../mbedtls/library/ssl_srv.c"
"${ProjDirPath}/../mbedtls/library/ssl_msg.c"
"${ProjDirPath}/../mbedtls/library/ssl_cookie.c"
"${ProjDirPath}/../mbedtls/library/ssl_cli.c"
"${ProjDirPath}/../mbedtls/library/ssl_ciphersuites.c"
"${ProjDirPath}/../mbedtls/library/ssl_cache.c"
"${ProjDirPath}/../mbedtls/library/sha512.c"
"${ProjDirPath}/../mbedtls/library/sha256.c"
"${ProjDirPath}/../mbedtls/library/sha1.c"
"${ProjDirPath}/../mbedtls/library/rsa_internal.c"
"${ProjDirPath}/../mbedtls/library/rsa.c"
"${ProjDirPath}/../mbedtls/library/ripemd160.c"
"${ProjDirPath}/../mbedtls/library/psa_its_file.c"
"${ProjDirPath}/../mbedtls/library/psa_crypto_storage.h"
"${ProjDirPath}/../mbedtls/library/psa_crypto_storage.c"
"${ProjDirPath}/../mbedtls/library/psa_crypto_slot_management.h"
"${ProjDirPath}/../mbedtls/library/psa_crypto_slot_management.c"
"${ProjDirPath}/../mbedtls/library/psa_crypto_se.h"
"${ProjDirPath}/../mbedtls/library/psa_crypto_se.c"
"${ProjDirPath}/../mbedtls/library/psa_crypto_rsa.h"
"${ProjDirPath}/../mbedtls/library/psa_crypto_rsa.c"
"${ProjDirPath}/../mbedtls/library/psa_crypto_random_impl.h"
"${ProjDirPath}/../mbedtls/library/psa_crypto_mac.h"
"${ProjDirPath}/../mbedtls/library/psa_crypto_mac.c"
"${ProjDirPath}/../mbedtls/library/psa_crypto_its.h"
"${ProjDirPath}/../mbedtls/library/psa_crypto_invasive.h"
"${ProjDirPath}/../mbedtls/library/psa_crypto_hash.h"
"${ProjDirPath}/../mbedtls/library/psa_crypto_hash.c"
"${ProjDirPath}/../mbedtls/library/psa_crypto_ecp.h"
"${ProjDirPath}/../mbedtls/library/psa_crypto_ecp.c"
"${ProjDirPath}/../mbedtls/library/psa_crypto_driver_wrappers.h"
"${ProjDirPath}/../mbedtls/library/psa_crypto_driver_wrappers.c"
"${ProjDirPath}/../mbedtls/library/psa_crypto_core.h"
"${ProjDirPath}/../mbedtls/library/psa_crypto_client.c"
"${ProjDirPath}/../mbedtls/library/psa_crypto_cipher.h"
"${ProjDirPath}/../mbedtls/library/psa_crypto_cipher.c"
"${ProjDirPath}/../mbedtls/library/psa_crypto_aead.h"
"${ProjDirPath}/../mbedtls/library/psa_crypto_aead.c"
"${ProjDirPath}/../mbedtls/library/psa_crypto.c"
"${ProjDirPath}/../mbedtls/library/poly1305.c"
"${ProjDirPath}/../mbedtls/library/platform_util.c"
"${ProjDirPath}/../mbedtls/library/platform.c"
"${ProjDirPath}/../mbedtls/library/pk_wrap.c"
"${ProjDirPath}/../mbedtls/library/pkwrite.c"
"${ProjDirPath}/../mbedtls/library/pkparse.c"
"${ProjDirPath}/../mbedtls/library/pkcs5.c"
"${ProjDirPath}/../mbedtls/library/pkcs12.c"
"${ProjDirPath}/../mbedtls/library/pkcs11.c"
"${ProjDirPath}/../mbedtls/library/pk.c"
"${ProjDirPath}/../mbedtls/library/pem.c"
"${ProjDirPath}/../mbedtls/library/padlock.c"
"${ProjDirPath}/../mbedtls/library/oid.c"
"${ProjDirPath}/../mbedtls/library/nist_kw.c"
"${ProjDirPath}/../mbedtls/library/net_sockets.c"
"${ProjDirPath}/../mbedtls/library/mps_trace.h"
"${ProjDirPath}/../mbedtls/library/mps_trace.c"
"${ProjDirPath}/../mbedtls/library/mps_reader.h"
"${ProjDirPath}/../mbedtls/library/mps_reader.c"
"${ProjDirPath}/../mbedtls/library/mps_error.h"
"${ProjDirPath}/../mbedtls/library/mps_common.h"
"${ProjDirPath}/../mbedtls/library/memory_buffer_alloc.c"
"${ProjDirPath}/../mbedtls/library/md5.c"
"${ProjDirPath}/../mbedtls/library/md4.c"
"${ProjDirPath}/../mbedtls/library/md2.c"
"${ProjDirPath}/../mbedtls/library/md.c"
"${ProjDirPath}/../mbedtls/library/hmac_drbg.c"
"${ProjDirPath}/../mbedtls/library/hkdf.c"
"${ProjDirPath}/../mbedtls/library/havege.c"
"${ProjDirPath}/../mbedtls/library/gcm.c"
"${ProjDirPath}/../mbedtls/library/error.c"
"${ProjDirPath}/../mbedtls/library/entropy_poll.c"
"${ProjDirPath}/../mbedtls/library/entropy.c"
"${ProjDirPath}/../mbedtls/library/ecp_invasive.h"
"${ProjDirPath}/../mbedtls/library/ecp_curves.c"
"${ProjDirPath}/../mbedtls/library/ecp.c"
"${ProjDirPath}/../mbedtls/library/ecjpake.c"
"${ProjDirPath}/../mbedtls/library/ecdsa.c"
"${ProjDirPath}/../mbedtls/library/ecdh.c"
"${ProjDirPath}/../mbedtls/library/dhm.c"
"${ProjDirPath}/../mbedtls/library/des.c"
"${ProjDirPath}/../mbedtls/library/debug.c"
"${ProjDirPath}/../mbedtls/library/ctr_drbg.c"
"${ProjDirPath}/../mbedtls/library/constant_time_invasive.h"
"${ProjDirPath}/../mbedtls/library/constant_time_internal.h"
"${ProjDirPath}/../mbedtls/library/constant_time.c"
"${ProjDirPath}/../mbedtls/library/common.h"
"${ProjDirPath}/../mbedtls/library/cmac.c"
"${ProjDirPath}/../mbedtls/library/cipher_wrap.c"
"${ProjDirPath}/../mbedtls/library/cipher.c"
"${ProjDirPath}/../mbedtls/library/check_crypto_config.h"
"${ProjDirPath}/../mbedtls/library/chachapoly.c"
"${ProjDirPath}/../mbedtls/library/chacha20.c"
"${ProjDirPath}/../mbedtls/library/certs.c"
"${ProjDirPath}/../mbedtls/library/ccm.c"
"${ProjDirPath}/../mbedtls/library/camellia.c"
"${ProjDirPath}/../mbedtls/library/blowfish.c"
"${ProjDirPath}/../mbedtls/library/bignum.c"
"${ProjDirPath}/../mbedtls/library/base64.c"
"${ProjDirPath}/../mbedtls/library/asn1write.c"
"${ProjDirPath}/../mbedtls/library/asn1parse.c"
"${ProjDirPath}/../mbedtls/library/aria.c"
"${ProjDirPath}/../mbedtls/library/arc4.c"
"${ProjDirPath}/../mbedtls/library/aesni.c"
"${ProjDirPath}/../mbedtls/library/aes.c"
"${ProjDirPath}/../mbedtls/port/ksdk/threading_alt.h"
"${ProjDirPath}/../mbedtls/port/ksdk/sha256_alt.h"
"${ProjDirPath}/../mbedtls/port/ksdk/sha1_alt.h"
"${ProjDirPath}/../mbedtls/port/ksdk/ksdk_mbedtls_config.h"
"${ProjDirPath}/../mbedtls/port/ksdk/ksdk_mbedtls.h"
"${ProjDirPath}/../mbedtls/port/ksdk/ksdk_mbedtls.c"
"${ProjDirPath}/../mbedtls/port/ksdk/ecp_curves_alt.c"
"${ProjDirPath}/../mbedtls/port/ksdk/ecp_alt_ksdk.c"
"${ProjDirPath}/../mbedtls/port/ksdk/ecp_alt.h"
"${ProjDirPath}/../mbedtls/port/ksdk/ecp_alt.c"
"${ProjDirPath}/../mbedtls/port/ksdk/des_alt.h"
"${ProjDirPath}/../mbedtls/port/ksdk/des_alt.c"
"${ProjDirPath}/../mbedtls/port/ksdk/ccm_alt.h"
"${ProjDirPath}/../mbedtls/port/ksdk/aes_alt.h"
"${ProjDirPath}/../mbedtls/port/ksdk/aes_alt.c"
"${ProjDirPath}/../mbedtls/include/psa/crypto_values.h"
"${ProjDirPath}/../mbedtls/include/psa/crypto_types.h"
"${ProjDirPath}/../mbedtls/include/psa/crypto_struct.h"
"${ProjDirPath}/../mbedtls/include/psa/crypto_sizes.h"
"${ProjDirPath}/../mbedtls/include/psa/crypto_se_driver.h"
"${ProjDirPath}/../mbedtls/include/psa/crypto_platform.h"
"${ProjDirPath}/../mbedtls/include/psa/crypto_extra.h"
"${ProjDirPath}/../mbedtls/include/psa/crypto_driver_contexts_primitives.h"
"${ProjDirPath}/../mbedtls/include/psa/crypto_driver_contexts_composites.h"
"${ProjDirPath}/../mbedtls/include/psa/crypto_driver_common.h"
"${ProjDirPath}/../mbedtls/include/psa/crypto_config.h"
"${ProjDirPath}/../mbedtls/include/psa/crypto_compat.h"
"${ProjDirPath}/../mbedtls/include/psa/crypto_builtin_primitives.h"
"${ProjDirPath}/../mbedtls/include/psa/crypto_builtin_composites.h"
"${ProjDirPath}/../mbedtls/include/psa/crypto.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/xtea.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/x509_csr.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/x509_crt.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/x509_crl.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/x509.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/version.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/timing.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/threading.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/ssl_ticket.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/ssl_internal.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/ssl_cookie.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/ssl_ciphersuites.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/ssl_cache.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/ssl.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/sha512.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/sha256.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/sha1.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/rsa_internal.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/rsa.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/ripemd160.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/psa_util.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/poly1305.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/platform_util.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/platform_time.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/platform.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/pk_internal.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/pkcs5.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/pkcs12.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/pkcs11.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/pk.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/pem.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/padlock.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/oid.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/nist_kw.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/net_sockets.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/net.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/memory_buffer_alloc.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/md_internal.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/md5.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/md4.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/md2.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/md.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/hmac_drbg.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/hkdf.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/havege.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/gcm.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/error.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/entropy_poll.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/entropy.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/ecp_internal.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/ecp.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/ecjpake.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/ecdsa.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/ecdh.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/dhm.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/des.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/debug.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/ctr_drbg.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/constant_time.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/config_psa.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/config.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/compat-1.3.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/cmac.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/cipher_internal.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/cipher.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/check_config.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/chachapoly.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/chacha20.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/certs.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/ccm.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/camellia.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/bn_mul.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/blowfish.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/bignum.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/base64.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/asn1write.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/asn1.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/aria.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/arc4.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/aesni.h"
"${ProjDirPath}/../mbedtls/include/mbedtls/aes.h"
"${ProjDirPath}/../source/semihost_hardfault.c"
"${ProjDirPath}/../source/LPC55S69_PSA_demonstrator.c"
"${ProjDirPath}/../utilities/fsl_str.h"
"${ProjDirPath}/../utilities/fsl_str.c"
"${ProjDirPath}/../utilities/fsl_debug_console_conf.h"
"${ProjDirPath}/../utilities/fsl_debug_console.h"
"${ProjDirPath}/../utilities/fsl_debug_console.c"
"${ProjDirPath}/../utilities/fsl_assert.c"
"${ProjDirPath}/../drivers/fsl_usart.h"
"${ProjDirPath}/../drivers/fsl_usart.c"
"${ProjDirPath}/../drivers/fsl_rng.h"
"${ProjDirPath}/../drivers/fsl_rng.c"
"${ProjDirPath}/../drivers/fsl_reset.h"
"${ProjDirPath}/../drivers/fsl_reset.c"
"${ProjDirPath}/../drivers/fsl_power.h"
"${ProjDirPath}/../drivers/fsl_power.c"
"${ProjDirPath}/../drivers/fsl_iocon.h"
"${ProjDirPath}/../drivers/fsl_i2c.h"
"${ProjDirPath}/../drivers/fsl_i2c.c"
"${ProjDirPath}/../drivers/fsl_hashcrypt.h"
"${ProjDirPath}/../drivers/fsl_hashcrypt.c"
"${ProjDirPath}/../drivers/fsl_gpio.h"
"${ProjDirPath}/../drivers/fsl_gpio.c"
"${ProjDirPath}/../drivers/fsl_flexcomm.h"
"${ProjDirPath}/../drivers/fsl_flexcomm.c"
"${ProjDirPath}/../drivers/fsl_common_arm.h"
"${ProjDirPath}/../drivers/fsl_common_arm.c"
"${ProjDirPath}/../drivers/fsl_common.h"
"${ProjDirPath}/../drivers/fsl_common.c"
"${ProjDirPath}/../drivers/fsl_clock.h"
"${ProjDirPath}/../drivers/fsl_clock.c"
"${ProjDirPath}/../drivers/fsl_casper.h"
"${ProjDirPath}/../drivers/fsl_casper.c"
"${ProjDirPath}/../device/system_LPC55S69_cm33_core0.h"
"${ProjDirPath}/../device/system_LPC55S69_cm33_core0.c"
"${ProjDirPath}/../device/LPC55S69_cm33_core0_features.h"
"${ProjDirPath}/../device/LPC55S69_cm33_core0.h"
"${ProjDirPath}/../device/fsl_device_registers.h"
"${ProjDirPath}/../board/pin_mux.h"
"${ProjDirPath}/../board/pin_mux.c"
"${ProjDirPath}/../board/peripherals.h"
"${ProjDirPath}/../board/peripherals.c"
"${ProjDirPath}/../board/clock_config.h"
"${ProjDirPath}/../board/clock_config.c"
"${ProjDirPath}/../board/board.h"
"${ProjDirPath}/../board/board.c"
)


add_executable(${MCUX_SDK_PROJECT_NAME} ${sources})



if(${LIBRARY_TYPE} STREQUAL "REDLIB")
    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE $ENV{ARMGCC_DIR}/redlib/include)
endif()

set(include_directories "${ProjDirPath}/../board"
"${ProjDirPath}/../source"
"${ProjDirPath}/../drivers"
"${ProjDirPath}/../device"
"${ProjDirPath}/../CMSIS"
"${ProjDirPath}/../utilities"
"${ProjDirPath}/../component/uart"
"${ProjDirPath}/../component/serial_manager"
"${ProjDirPath}/../mbedtls/include"
"${ProjDirPath}/../mbedtls/library"
"${ProjDirPath}/../mbedtls/port/ksdk"
"${ProjDirPath}/../component/lists"
"${ProjDirPath}/../startup"
)


target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE ${include_directories})

set(include_files "")


target_precompile_headers(${MCUX_SDK_PROJECT_NAME} PRIVATE ${include_files})

set(link_directories "")


set(link_libraries "")


target_link_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE ${link_directories})
target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--start-group)
target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE ${TARGET_LINK_SYSTEM_LIBRARIES} ${link_libraries})
target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--end-group)





