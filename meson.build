project('dimval', 'cpp',
    version: '0.1.0',
    license: 'MIT',
    default_options: [
        'cpp_std=c++23',
        'warning_level=3',
        'werror=false',
    ],
    meson_version: '>=1.3.0',
)

dimval_inc = include_directories('include')

dimval_deps = []
dimval_with_json   = get_option('json')
dimval_with_parcel = get_option('parcel')

if dimval_with_parcel and not dimval_with_json
    message('dimval: parcel option forced OFF because cpp-parcel depends on '
            + 'nlohmann_json (json=false).')
    dimval_with_parcel = false
endif

if dimval_with_json
    json_dep = dependency('nlohmann_json', version: '>=3.12.0',
        fallback: ['nlohmann_json', 'nlohmann_json_dep'])
    dimval_deps += json_dep
    add_project_arguments('-DDIMVAL_WITH_NLOHMANN_JSON=1', language: 'cpp')
endif

if dimval_with_parcel
    parcel_dep = dependency('parcel', version: '>=0.1.0',
        fallback: ['parcel', 'parcel_dep'])
    dimval_deps += parcel_dep
    add_project_arguments('-DDIMVAL_WITH_PARCEL=1', language: 'cpp')
endif

dimval_dep = declare_dependency(
    include_directories: dimval_inc,
    dependencies: dimval_deps,
    version: meson.project_version(),
)

meson.override_dependency('dimval', dimval_dep)

install_subdir('include/dimval', install_dir: get_option('includedir'))

pkg_requires = []
if dimval_with_json
    pkg_requires += 'nlohmann_json'
endif
if dimval_with_parcel
    pkg_requires += 'parcel'
endif

import('pkgconfig').generate(
    name: 'dimval',
    description: 'Modern C++23 header-only library of dimensional values',
    version: meson.project_version(),
    requires: pkg_requires,
)

if get_option('tests')
    subdir('tests')
endif
if get_option('examples')
    subdir('examples')
endif
