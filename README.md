# Platform Security Architecture (PSA) Crypto API Demonstrator

This repository hosts a demonstrator for the PSA Crypto API, illustrating basic cryptographic operations including symmetric encryption using AES-128 and SHA-256 hashing. The demonstrator is part of the [CROSSCON](https://crosscon.eu/) project, which contributes to Deliverable 4.2: CROSSCON Extension Primitives to Domain Specific Hardware Architectures — Initial Version.

## Overview

CROSSCON aims to develop a unified software stack for resource-constrained IoT devices. As part of this effort, we seek to provide a unified interface for trusted services within CROSSCON to perform essential cryptographic operations. As IoT devices increasingly integrate domain-specific hardware such as cryptographic accelerators, it is crucial for software stacks to incorporate these hardware components. An important task is to evaluate existing APIs to understand their versatility and potential for integration into the CROSSCON stack.

In this demonstrator, the API facilitates exemplary encryption and decryption using AES-128, as well as data hashing with SHA-256. To demonstrate interoperability, we apply the API across two IoT development boards: the LPC55S69-EVK, equipped with an ARM Cortex-M33 processor, and the ESP32-C3, a RISC-V development board. Both devices are outfitted with hardware accelerators for these operations, allowing the demonstrator to perform the operations either via the cryptographic accelerator or entirely in software, depending on the build configuration.

## How to run the examples

### ESP32-C3

To build and flash the examples on the ESP32-C3 development board, use the [ESP-IDF](https://github.com/espressif/esp-idf) or the corresponding [VS-Code extension](https://docs.espressif.com/projects/esp-idf/en/v4.2.3/esp32/get-started/vscode-setup.html). The examples are configured to utilize the integrated cryptographic accelerator by default. To disable this, either use the SDK Configuration Editor in the IDE (Component config -> Enable hardware AES/SHA acceleration) or directly adjust the settings using the `idf.py menuconfig` command. You can also modify the "sdkconfig.h" file directly. The examples will report execution times, which should be significantly reduced when hardware acceleration is enabled.

### LPC55S69-EVK

The same example setup is provided for the LPC55S69-EVK. Build and flash the program using the [MCUXpresso SDK](https://www.nxp.com/products/processors-and-microcontrollers/arm-microcontrollers/general-purpose-mcus/mcx-arm-cortex-m/mcx-a-series-microcontrollers/mcuxpresso-for-visual-studio-code:MCUXPRESSO-VSC), available as a VS Code extension, or directly via the [MCUXpresso IDE](https://www.nxp.com/design/design-center/software/development-software/mcuxpresso-software-and-tools-/mcuxpresso-integrated-development-environment-ide:MCUXpresso-IDE). To disable hardware acceleration, remove the CMAKE flags **-DMBEDTLS_FREESCALE_HASHCRYPT_AES** and **-DMBEDTLS_FREESCALE_HASHCRYPT_SHA256** found in the `armgcc` folder. Alternatively, MCUXpresso IDE users can adjust settings via the GUI (Properties -> C/C++ Build -> Setting -> MCU C Compiler -> Preprocessor).

## Acknowledgments

The work presented in this repository is part of the [CROSSCON project](https://crosscon.eu/) that received funding from the European Union’s Horizon Europe research and innovation programme under grant agreement No 101070537.

<p align="center">
    <img src="https://crosscon.eu/sites/crosscon/themes/crosscon/images/eu.svg" width=10% height=10%>
</p>

<p align="center">
    <img src="https://crosscon.eu/sites/crosscon/files/public/styles/large_1080_/public/content-images/media/2023/crosscon_logo.png?itok=LUH3ejzO" width=25% height=25%>
</p>
