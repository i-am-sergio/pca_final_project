import os

os.system("cd PCA && python main.py")

os.chdir("KDTree")

if not os.path.exists("build"):
    os.makedirs("build")

os.system("cd build && cmake .. && make && ./pca_kdtree")