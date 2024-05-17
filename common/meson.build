# Dependency for files common to tests ran on the host and target
common_test_dep = declare_dependency(
    include_directories: include_directories('test/include'),
    sources: [
        'test/src/TAP.c',
        'test/src/UnitTestAssert.c',
        'test/src/UnitTestFramework.c',
    ],
)

meson.override_dependency('common_test', common_test_dep)

# Dummy demo test dep, can be used for building & trying out opentestloader 
demo_test_dep = declare_dependency(
    sources: 'test/src/demotest.c'
)

meson.override_dependency('demo_test', demo_test_dep)