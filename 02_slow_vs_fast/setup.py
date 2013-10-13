from distutils.core import setup, Extension

setup(
    ext_modules = [
        Extension('fast', sources=['fast.c']),
    ]
)
