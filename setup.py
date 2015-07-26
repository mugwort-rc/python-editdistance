# -*- coding: utf-8 -*-

import os, sys

from distutils.core import setup, Extension
from distutils.command import build_ext

libraries = ["boost_python", "stdc++"]
sources = ["src/editdistance.cpp"]

ext = Extension(name="editdistance.__editdistance",
                libraries=libraries,
                sources=sources,
                extra_compile_args=['-std=c++11'])

# for distutils c++ bug.
from distutils.sysconfig import get_config_vars
(opt,) = get_config_vars('OPT')
os.environ['OPT'] = " ".join([flag for flag in opt.split() if flag != '-Wstrict-prototypes'])

# ccache
for path in os.environ['PATH'].split(os.pathsep):
    path = path.strip('"')
    exe = os.path.join(path, 'ccache')
    if os.path.isfile(exe) and os.access(exe, os.X_OK):
        os.environ['CC'] = 'ccache gcc'
        break

setup(name="editdistance",
      version="1.0",
      author="mugwort_rc",
      author_email="mugwort rc at gmail com",
      url="https://github.com/mugwort-rc/python-editdistance",
      classifiers = [
        "Development Status :: 5 - Production/Stable",
        "Intended Audience :: Developers",
        "License :: OSI Approved :: Apache Software License",
        "Programming Language :: C++",
        "Programming Language :: Python",
        "Programming Language :: Python :: 2.7",
      ],
      license = "Apache Software License, Version 2.0",
      packages = ["editdistance"],
      ext_modules = [ext])
