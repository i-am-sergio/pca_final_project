#!/bin/bash

# Ejecutar el script de Python
source myenv/bin/activate
python main.py
deactivate

# Cambiar al directorio pca_kdtree
cd pca_kdtree || exit

# Crear el directorio build si no existe y entrar en él
mkdir -p build && cd build || exit

# Ejecutar cmake, make y el ejecutable
cmake .. && make && ./pca_kdtree
