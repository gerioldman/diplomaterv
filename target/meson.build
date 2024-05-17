target_common_test_dep = declare_dependency(
    include_directories: [
        'common/test/include'
    ],
    sources: [
        'common/test/src/opentestloader_struct.c',
        'common/test/src/syscalls.c'
    ]
)

meson.override_dependency('target_common_test', target_common_test_dep)

target_common_testloader_dep = declare_dependency(
    include_directories: [
        'common/test/include', # required for opentestloader_struct.h
        'common/testloader/include'
    ],
    sources: [
        'common/testloader/src/test_run.c',
        'common/testloader/src/xcp_verifyhook.c'
    ]
)

meson.override_dependency('target_common_testloader', target_common_testloader_dep)

if get_option('target') == 'ARMCM4_STM32F4'
subdir('stm32f446re')
endif