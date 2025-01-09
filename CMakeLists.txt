cmake_minimum_required(VERSION 3.22)

# Core project settings
project(ArtNetNode_STM32F446RE)
enable_language(C CXX ASM)
message("Build type: " ${CMAKE_BUILD_TYPE})

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# Core MCU flags, CPU type, instruction set and FPU setup
set(cpu_PARAMS 
    -mthumb
    -mcpu=cortex-m4
    -mfpu=fpv4-sp-d16
    -mfloat-abi=hard
)

# Linker script
set(linker_script_SRC ${CMAKE_CURRENT_SOURCE_DIR}/stm32f446retx_FLASH.ld)

# Sources
set(sources_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/Src/spi_dma.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Src/uart_dma.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Src/enc28j60.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Src/interrupts.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Startup/startup_stm32f446retx.s
)

# Include directories
set(include_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/Inc            
    ${CMAKE_CURRENT_SOURCE_DIR}/Device     
)

# Include directories for each compiler
set(include_c_DIRS ${include_DIRS})
set(include_cxx_DIRS ${include_DIRS})
set(include_asm_DIRS ${include_DIRS})

# Symbols definitions (macros) for all compilers
set(symbols_SYMB
    # You can add common symbols here if necessary
)

# Link directories
set(link_DIRS)

# Link libraries
set(link_LIBS)

# Compiler options
set(compiler_OPTS)

# Linker options
set(linker_OPTS)

# Now set up CMake's configurations and the project itself
add_executable(${CMAKE_PROJECT_NAME})

# Add sources to executable
target_sources(${CMAKE_PROJECT_NAME} PUBLIC ${sources_SRCS})

# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    ${include_DIRS}
    $<$<COMPILE_LANGUAGE:C>: ${include_c_DIRS}>
    $<$<COMPILE_LANGUAGE:CXX>: ${include_cxx_DIRS}>
    $<$<COMPILE_LANGUAGE:ASM>: ${include_asm_DIRS}>
)

# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    ${symbols_SYMB}
    $<$<COMPILE_LANGUAGE:C>: ${symbols_c_SYMB}>
    $<$<COMPILE_LANGUAGE:CXX>: ${symbols_cxx_SYMB}>
    $<$<COMPILE_LANGUAGE:ASM>: ${symbols_asm_SYMB}>

    # Configuration specific
    $<$<CONFIG:Debug>:DEBUG>
    $<$<CONFIG:Release>: >
)

# Link directories setup
link_directories(${CMAKE_PROJECT_NAME} ${link_DIRS})

# Link libraries
target_link_libraries(${CMAKE_PROJECT_NAME} ${link_LIBS})

# Compiler options
target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE
    ${cpu_PARAMS}
    ${compiler_OPTS}
    -Wall
    -Wextra
    -Wpedantic
    -Wno-unused-parameter
    $<$<COMPILE_LANGUAGE:C>: >
    $<$<COMPILE_LANGUAGE:CXX>: >
    $<$<COMPILE_LANGUAGE:ASM>:-x assembler-with-cpp -MMD -MP>
    $<$<CONFIG:Debug>:-Og -g3 -ggdb>
    $<$<CONFIG:Release>:-Og -g0>
)

# Linker options
target_link_options(${CMAKE_PROJECT_NAME} PRIVATE
    -T${linker_script_SRC}
    ${cpu_PARAMS}
    ${linker_OPTS}
    -Wl,-Map=${CMAKE_PROJECT_NAME}.map
    -u _printf_float # STDIO float formatting support (remove if not used)
    --specs=nosys.specs
    -Wl,--start-group
    -lc
    -lm
    -lstdc++
    -lsupc++
    -Wl,--end-group
    -Wl,-z,max-page-size=8 # Allow good software remapping across address space (with proper GCC section making)
    -Wl,--print-memory-usage
)

# Execute post-build commands to print size, generate hex and bin
add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${CMAKE_PROJECT_NAME}>
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${CMAKE_PROJECT_NAME}> ${CMAKE_PROJECT_NAME}.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${CMAKE_PROJECT_NAME}> ${CMAKE_PROJECT_NAME}.bin
)
