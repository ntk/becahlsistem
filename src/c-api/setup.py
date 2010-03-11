from distutils.core import setup, Extension

module1 = Extension('id',
                    libraries = ['nfc'],
                    sources = ['idmodule.c'])

setup (name = 'id',
       version = '1.0',
       description = 'Module offering a methode to get an ID value.',
       ext_modules = [module1])
