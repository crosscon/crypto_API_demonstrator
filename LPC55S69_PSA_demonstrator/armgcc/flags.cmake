if(NOT DEFINED FPU)
	set(FPU "-mfpu=fpv5-sp-d16 -mfloat-abi=hard")
endif()

if(NOT DEFINED SPECS)
	set(SPECS "--specs=nano.specs --specs=nosys.specs")
endif()

if(NOT DEFINED DEBUG_CONSOLE_CONFIG)
	set(DEBUG_CONSOLE_CONFIG "-DSDK_DEBUGCONSOLE=1")
endif()

set(CMAKE_ASM_FLAGS_DEBUG " \
    ${CMAKE_ASM_FLAGS_DEBUG} \
    ${FPU} \
    -mcpu=cortex-m33 \
    -mthumb \
")

set(CMAKE_C_FLAGS_DEBUG " \
    ${CMAKE_C_FLAGS_DEBUG} \
    ${FPU} \
    ${DEBUG_CONSOLE_CONFIG} \
    -DPRINTF_ADVANCED_ENABLE=1 \
    -DMBEDTLS_FREESCALE_HASHCRYPT_AES \
    -DMBEDTLS_FREESCALE_HASHCRYPT_SHA256 \
    -DCPU_LPC55S69JBD100 \
    -DCPU_LPC55S69JBD100_cm33 \
    -DCPU_LPC55S69JBD100_cm33_core0 \
    -DSDK_OS_BAREMETAL \
    -DSERIAL_PORT_TYPE_UART=1 \
    -DMBEDTLS_CONFIG_FILE=\\\"ksdk_mbedtls_config.h\\\" \
    -DPRINTF_FLOAT_ENABLE=1 \
    -DSDK_DEBUGCONSOLE_UART \
    -D__MCUXPRESSO \
    -D__USE_CMSIS \
    -DDEBUG \
    -O0 \
    -fno-common \
    -fmerge-constants \
    -g3 \
     -ffunction-sections -fdata-sections -ffreestanding -fno-builtin \
    -fstack-usage \
    -mcpu=cortex-m33 \
    -mthumb \
")

set(CMAKE_CXX_FLAGS_DEBUG " \
    ${CMAKE_CXX_FLAGS_DEBUG} \
    ${FPU} \
    ${DEBUG_CONSOLE_CONFIG} \
    -O0 \
    -fno-common \
    -fmerge-constants \
    -g3 \
    -Wall \
    -fstack-usage \
    -mcpu=cortex-m33 \
    -mthumb \
")

set(CMAKE_EXE_LINKER_FLAGS_DEBUG " \
    ${CMAKE_EXE_LINKER_FLAGS_DEBUG} \
    ${FPU} \
    ${SPECS} \
    -Xlinker \
    -Map=output.map \
    -Xlinker \
    --gc-sections \
    -Xlinker \
    -print-memory-usage \
    -Xlinker \
    --sort-section=alignment \
    -Xlinker \
    --cref \
    -mcpu=cortex-m33 \
    -mthumb \
    -T\"${ProjDirPath}/LPC55S69_PSA_demonstrator_Debug.ld\" \
")
