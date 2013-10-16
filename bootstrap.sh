#!/bin/bash

command -v python3 -m venv >/dev/null 2>&1 || { echo >&2 "Python 3.3 required. Install it and try again. Aborting"; exit 1; }

if [ ! -d "env" ]; then
    echo "No virtualenv. Creating one"
    command -v curl >/dev/null 2>&1 || { echo >&2 "curl required. Install it and try again. Aborting"; exit 1; }
    python3 -m venv env
    source env/bin/activate
    curl https://bitbucket.org/pypa/setuptools/raw/bootstrap/ez_setup.py | python
    easy_install pip
else
    echo "There's already an env. Activating it"
    source env/bin/activate
fi

echo "Installing pip requirements"
pip install pytest
pip install cython

echo "Bootstrapping complete! Activate your venv with 'source env/bin/activate'"
