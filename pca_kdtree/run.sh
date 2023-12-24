# copy and paste
mkdir build
cd build && cmake .. && make && ./pca_kdtree

# run sh
if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    # Comandos para Linux
    mkdir -p build
    cd build && cmake .. && make && ./pca_kdtree
elif [[ "$OSTYPE" == "msys"* ]]; then
    # Comandos para Windows
    mkdir build
    cd build
    cmake ..
    make
    ./pca_kdtree
