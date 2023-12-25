# PCA Final Project

* **Install Dependencies**
    - Python
    ```bash
    pip install pandas scikit-learn openpyxl
    ```
    ```bash
    pip install -r requirements.txt
    ```
    - C++
    ```bash
    sudo apt install libvtk9-dev # debian/ubuntu
    ```
    ```bash
    sudo dnf install vtk-devel # fedora
    ```

* **Only Run Project**
    ```bash
    python runner.py
    ```

* **To Execute Project step by step**
    ```bash
    python main.py
    ```
    ```bash
    cd KDTree
    mkdir build
    cd build && cmake .. && make && ./pca_kdtree
    ```