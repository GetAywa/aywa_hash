from distutils.core import setup, Extension

x11_hash_module = Extension('x11_hash',
                                 sources = ['x11module.c',
                                            'x11hash.c',
                                            'yespower/yespower.c',
                                            'yespower/sha256.c',
                                            'yespower/yespower-opt.c',
                                            'sha3/groestl.c',
                                            'sha3/keccak.c'],
                               include_dirs=['.', './yespower','./sha3'])

setup (name = 'x11_hash',
       version = '0.1',
       description = 'Binding for AywaHash proof of work hashing.',
       ext_modules = [x11_hash_module])
