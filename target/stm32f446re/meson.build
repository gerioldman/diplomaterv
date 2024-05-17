
stm32f446re_testloader = executable(
    'stm32f446re_testloader',
    name_suffix: 'elf',
    sources: [
        'testloader/App/app.c',
        'testloader/App/hooks.c',
        'testloader/App/led.c',
        # File for ITM printf #########
        #'stm32f446re/Boot/App/debug.c',
        ###############################
        'testloader/Core/Src/main.c',
        'testloader/Core/Src/stm32f4xx_hal_msp.c',
        'testloader/Core/Src/stm32f4xx_it.c',
        'testloader/Core/Src/syscalls.c',
        'testloader/Core/Src/sysmem.c',
        'testloader/Core/Src/system_stm32f4xx.c',
        'testloader/Core/Startup/startup_stm32f446retx.s',
        'testloader/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c',
        'testloader/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.c',
        'testloader/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.c',
        'testloader/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_exti.c',
        'testloader/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.c',
        'testloader/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.c',
        'testloader/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.c',
        'testloader/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c',
        'testloader/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.c',
        'testloader/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.c',
        'testloader/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.c',
        'testloader/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c',
        'testloader/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c',
        'testloader/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_dma.c',
        'testloader/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_exti.c',
        'testloader/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_gpio.c',
        'testloader/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_rcc.c',
        'testloader/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_usart.c',
        'testloader/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_utils.c',
    ],
    include_directories: [
        'testloader/App',
        'testloader/Core/Inc',
        'testloader/Drivers/STM32F4xx_HAL_Driver/Inc',
        'testloader/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy',
        'testloader/Drivers/CMSIS/Device/ST/STM32F4xx/Include',
        'testloader/Drivers/CMSIS/Include',
    ],
    c_args: [
        '-DUSE_HAL_DRIVER',
        '-DSTM32F446xx',
        '-DUSE_FULL_LL_DRIVER',
    ],
    link_args: [
        '-T' + files('testloader/STM32F446RETX_FLASH.ld')[0].full_path(),
        '-specs=nano.specs',
        '-lc',
#        '-lnosys',
    ],
    dependencies: [dependency('openblt_core'), dependency('openblt_target'), dependency('target_common_testloader')],
)

stm32f446re_testloader_hex = custom_target(
    'stm32f446re_testloader',
    input: [stm32f446re_testloader],
    output: ['stm32f446re_testloader.hex'],
    command: [find_program('objcopy'), '-O', 'ihex', '@INPUT@', '@OUTPUT0@'],
    build_by_default: true,
)

stlink = find_program('ST-LINK_CLI', disabler: true, required: false)

run_target('flash_testloader', command: [stlink, '-P', stm32f446re_testloader_hex])

stm32f446re_demotest = executable(
    'stm32f446re_demotest',
    name_suffix: 'elf',
    sources: [
        'demo/src/dummy.c'
    ],
    implicit_include_directories: false,
    link_args: [
        '-nolibc',
        '-nostdlib',
        '-T' + files('demo/STM32F446RETX_FLASH.ld')[0].full_path(),
    ],
    dependencies: [
        dependency('printf', fallback: 'printf'), 
        dependency('common_test'),
        dependency('target_common_test'),
        dependency('demo_test'),
        meson.get_compiler('c').find_library('gcc')
    ],
    link_depends: files('demo/STM32F446RETX_FLASH.ld')
)

#stm32f446re_shared_lib_hex = 
custom_target(
    'stm32f446re_demotest',
    input: [stm32f446re_demotest],
    output: ['stm32f446re_demotest.srec'],
    command: [find_program('objcopy'), '-O', 'srec', '@INPUT@', '@OUTPUT0@'],
    build_by_default: true,
)