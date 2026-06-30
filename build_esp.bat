@echo off
set PATH=C:\Espressif\tools\xtensa-esp-elf\esp-14.2.0_20251107\xtensa-esp-elf\bin;C:\Espressif\tools\idf-git\2.44.0\cmd;C:\Espressif\tools\idf-python\3.11.2\Scripts;C:\Espressif\python_env\idf5.5_py3.11_env\Scripts;C:\Espressif\tools\cmake\3.30.2\bin;C:\Espressif\tools\ninja\1.12.1;%PATH%
set IDF_PATH=C:\Espressif\frameworks\esp-idf-v5.5.2
set IDF_PYTHON_ENV_PATH=C:\Espressif\python_env\idf5.5_py3.11_env
python C:\Espressif\frameworks\esp-idf-v5.5.2\tools\idf.py build
