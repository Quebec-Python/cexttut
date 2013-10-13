from distutils.core import setup, Extension

ext_modules = [
    Extension('fast', sources=['fast.c']),
]

try:
    from Cython.Build import cythonize
    ext_modules.append(cythonize('cython_fast.pyx')[0])
except ImportError:
    pass

setup(
    ext_modules = ext_modules
)
