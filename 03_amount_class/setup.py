from distutils.core import setup, Extension

setup(
    ext_modules = [
        Extension('amountc', sources=['amountc.c']),
    ]
)
