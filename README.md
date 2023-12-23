# PCA Final Project

* **Install Dependencies**
    - Python
    ```bash
    pip install pandas scikit-learn openpyxl
    ```
    - C++
    ```bash
    sudo apt install libvtk9-dev # debian/ubuntu
    ```
    ```bash
    sudo dnf install vtk-devel # fedora
    ```



* **To Execute Project**
    ```bash
    python main.py
    ```
    ```bash
    cd KDTree
    mkdir build
    cd build && cmake .. && make && ./pca_kdtree
    ```