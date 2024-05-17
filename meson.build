project(
    'opentestloader',
    ['c', 'cpp'],
    version: '0.1.0',
    default_options: {'warning_level': 'everything', 'optimization': 'g', 'c_std' : 'c11'},
)

subdir('common')

if meson.is_cross_build()

subdir('target')

else

subdir('client')
subdir('host')

endif