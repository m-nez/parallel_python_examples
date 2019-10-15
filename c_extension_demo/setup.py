from distutils.core import setup, Extension

module1 = Extension('para',
                    sources = ['para.cpp'])

setup (name = 'ParaByMN',
       version = '0.1',
       description = 'Example of parallel computing in a C extension',
       ext_modules = [module1])
