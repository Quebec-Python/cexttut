from distutils.core import setup, Extension

setup(
    ext_modules = [
        Extension('hello', sources=['hello.c']),
    ]
)
