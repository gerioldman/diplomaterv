opentestloader = executable(
    'opentestloader',
    sources: [
        'src/main.c'
    ],
    dependencies: [
        dependency('openblt_lib')
    ]
)

meson.override_find_program('opentestloader',opentestloader)