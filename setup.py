from distutils.core import setup, Extension

aywa_hash_module = Extension('aywa_hash',
                                 sources = ['aywamodule.c',
                                            'aywahash.c',                                           
                                            'sha3/groestl.c',
                                            'sha3/keccak.c',
                                            'yespower/yespower.c',
                                            'yespower/sha256.c',
                                            'yespower/yespower-opt.c'],
                               include_dirs=['.', './yespower','./sha3'])

setup (name = 'aywa_hash',
       version = '1.4',
       description = 'Binding for AywaHash proof of work hashing.',
       ext_modules = [aywa_hash_module])
