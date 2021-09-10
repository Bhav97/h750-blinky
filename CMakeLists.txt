cmake_minimum_required(VERSION 3.10)
project(blinky_c
VERSION 1
LANGUAGES C ASM CXX
DESCRIPTION "Blink LED on board"
)

set(TARGET_NAME ${PROJECT_NAME}.elf)
add_executable(${TARGET_NAME} "")
set(CMSIS_DIR ${CMAKE_SOURCE_DIR}/lib/st/cmsis_device_h7)
set(HAL_DIR ${CMAKE_SOURCE_DIR}/lib/st/stm32h7xx_hal_driver)

target_include_directories(${TARGET_NAME} PRIVATE ${CMSIS_DIR}/Include)
target_include_directories(${TARGET_NAME} PRIVATE ${HAL_DIR}/Inc)
target_include_directories(${TARGET_NAME} PRIVATE lib/CMSIS_5/CMSIS/Core/Include)
target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_SOURCE_DIR})

target_sources(${TARGET_NAME} PRIVATE
${CMSIS_DIR}/Source/Templates/system_stm32h7xx.c
${CMSIS_DIR}/Source/Templates/gcc/startup_stm32h750xx.s
${HAL_DIR}/Src/stm32h7xx_hal_gpio.c
${HAL_DIR}/Src/stm32h7xx_hal_cortex.c
${HAL_DIR}/Src/stm32h7xx_hal_rcc.c
${HAL_DIR}/Src/stm32h7xx_hal_rcc_ex.c
${HAL_DIR}/Src/stm32h7xx_hal_pwr.c
${HAL_DIR}/Src/stm32h7xx_hal_pwr_ex.c
${HAL_DIR}/Src/stm32h7xx_hal.c
${CMAKE_SOURCE_DIR}/main.c
)

target_compile_definitions(${TARGET_NAME} PRIVATE "STM32H750xx")
target_compile_definitions(${TARGET_NAME} PRIVATE "HSE_VALUE=25000000U")

set(C_OPTS, "")
set(C_OPTS "${C_OPTS} -mcpu=cortex-m4")
set(C_OPTS "${C_OPTS} -mthumb")
set(C_OPTS "${C_OPTS} -O0")
set(C_OPTS "${C_OPTS} -funsigned-char")
set(C_OPTS "${C_OPTS} -funsigned-bitfields")
set(C_OPTS "${C_OPTS} -ffunction-sections")
set(C_OPTS "${C_OPTS} -fdata-sections")
set(C_OPTS "${C_OPTS} -fno-jump-tables")
set(C_OPTS "${C_OPTS} -g")
set(C_OPTS "${C_OPTS} -mfloat-abi=hard")
set(C_OPTS "${C_OPTS} -mfpu=fpv4-sp-d16")
set(C_OPTS "${C_OPTS} -Wall")
set(C_OPTS "${C_OPTS} -Wextra")
set(C_OPTS "${C_OPTS} -Wstrict-prototypes")
set(C_OPTS "${C_OPTS} -Wunused")
set(C_OPTS "${C_OPTS} -Werror")
set(C_OPTS "${C_OPTS} -Wsign-compare")
set(C_OPTS "${C_OPTS} -fstack-usage")
set(C_OPTS "${C_OPTS} -Wno-error=unused-parameter")
set(C_OPTS "${C_OPTS} -Wno-error=sign-compare")
set(C_OPTS "${C_OPTS} -Wno-error=implicit-function-declaration")

set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/stm32h750xx_flash_CM7.ld)

set(LINKER_OPTS "")
set(LINKER_OPTS "${LINKER_OPTS} -T ${LINKER_SCRIPT}")
set(LINKER_OPTS "${LINKER_OPTS} -mcpu=cortex-m4")
set(LINKER_OPTS "${LINKER_OPTS} -mfloat-abi=hard")
set(LINKER_OPTS "${LINKER_OPTS} -mfpu=fpv4-sp-d16")
set(LINKER_OPTS "${LINKER_OPTS} -Xlinker --gc-sections")
set(LINKER_OPTS "${LINKER_OPTS} -Wl,-Map=${PROJECT_NAME}.map")
set(LINKER_OPTS "${LINKER_OPTS} --specs=nosys.specs")
set(LINKER_OPTS "${LINKER_OPTS} --specs=nano.specs")
set(LINKER_OPTS "${LINKER_OPTS} -Wl,--print-memory-usage")

set_target_properties(${TARGET_NAME}
PROPERTIES
C_STANDARD 11
CXX_STANDARD 11
C_STANDARD_REQUIRED ON
CXX_STANDARD_REQUIRED ON
C_EXTENSIONS OFF
LINK_DEPENDS ${LINKER_SCRIPT}
LINK_FLAGS ${LINKER_OPTS}
COMPILE_FLAGS ${C_OPTS}
)