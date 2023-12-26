import pandas as pd
from sklearn.decomposition import PCA
from sklearn.preprocessing import StandardScaler
from sklearn.impute import SimpleImputer
import seaborn as sns
import matplotlib.pyplot as plt
import os
import numpy as np
from numpy.linalg import eig
from matplotlib.patches import Ellipse

df = pd.read_excel('../data/covid_DB.xlsx')

selected_columns = [
            'SARS-Cov-2 exam result',
            'Patient age quantile',
            'Hematocrit',
            'Platelets',
            'Mean platelet volume ',
            'Mean corpuscular hemoglobin concentration (MCHC)',
            'Leukocytes',
            'Basophils',
            'Eosinophils',
            'Monocytes',
            'Proteina C reativa mg/dL'
        ]

df['SARS-Cov-2 exam result'].replace({'negative': 0, 'positive': 1}, inplace=True)
df.fillna(pd.NA, inplace=True)
df_selected = df[selected_columns]
# print(df_selected.head())

imputer = SimpleImputer(strategy='mean') # mean, median, most_frequent or other values set
pca_data_imputed = pd.DataFrame(imputer.fit_transform(df_selected), columns=df_selected.columns)
print(pca_data_imputed.head())

ss = StandardScaler()
pca_data_imputed[selected_columns] = ss.fit_transform(pca_data_imputed[selected_columns])
print(pca_data_imputed.head())

# covarianza
matrix_cov = pca_data_imputed.cov()
print( "COV\n" , matrix_cov)

# eigenvalues and eigenvectors
eigenvalues, eigenvectors = eig(matrix_cov)
print("Eigenvalues\n", eigenvalues)
print("Eigenvectors\n", eigenvectors)


pca3 = PCA(n_components=3, random_state=42)
pca_3 = pca3.fit_transform(pca_data_imputed[selected_columns])
print( "PCA proporciones de la varianza total => " , pca3.explained_variance_ratio_)

df_3 = pd.DataFrame({"PCA1":pca_3[:,0], "PCA2":pca_3[:,1], "PCA3":pca_3[:,2]})
print(df_3.head())





# Transpuesta
pca_data_imputed_transposed = pca_data_imputed.transpose()
print("Transpuesta => \n",pca_data_imputed_transposed.head(11))

pca3_transposed = PCA(n_components=3, random_state=42)
pca_3_transposed = pca3_transposed.fit_transform(pca_data_imputed_transposed)
print( "PCA Trans proporciones de la varianza total => " , pca3_transposed.explained_variance_ratio_)

df_3_transposed = pd.DataFrame({"PCA1":pca_3_transposed[:,0], "PCA2":pca_3_transposed[:,1], "PCA3":pca_3_transposed[:,2]})

print(df_3_transposed.head(11))


# Graficar Grafico de correlacion 2D
sns.scatterplot(x="PCA1", y="PCA2", data=df_3_transposed, color="green")
# Agregar un círculo con radio 80 y centro en el origen
circle = plt.Circle((0, 0), 70, color='blue', fill=False, linestyle="-")
plt.gca().add_patch(circle)
# Configurar la proporción de los ejes para que sean iguales
plt.axis('equal')
# Configuración adicional
plt.axhline(0, color='black', linewidth=0.5)
plt.axvline(0, color='black', linewidth=0.5)
plt.title('Círculo de correlacion')
plt.xlabel('PCA1')
plt.ylabel('PCA2')

# Agregar un vector desde el origen a cada punto
for i in range(len(df_3_transposed)):
    plt.quiver(0, 0, df_3_transposed['PCA1'][i], df_3_transposed['PCA2'][i], angles='xy', scale_units='xy', scale=1, color='red', width=0.005)

plt.show()



# Graficar Grafico de correlacion 3D
fig = plt.figure()
ax = fig.add_subplot(111,projection="3d")
x = df_3_transposed["PCA1"]
y = df_3_transposed["PCA2"]
z = df_3_transposed["PCA3"]
ax.scatter(x,y,z)
# Agregar quivers desde el origen a cada punto
ax.quiver(0, 0, 0, x, y, z, color='red', arrow_length_ratio=0.05, linewidth=1, linestyle='dashed')
# Agregar una elipse tridimensional con radio 80
ellipse = Ellipse((0, 0), width=80, height=80, edgecolor='yellow', facecolor='none', linestyle='dashed', linewidth=2, alpha=0.3)
# Crear una elipse en 3D con radio 80
u = np.linspace(0, 2 * np.pi, 100)
v = np.linspace(0, np.pi, 100)
x_elipse = 80 * np.outer(np.cos(u), np.sin(v))
y_elipse = 80 * np.outer(np.sin(u), np.sin(v))
z_elipse = 80 * np.outer(np.ones(np.size(u)), np.cos(v))
ax.plot_wireframe(x_elipse, y_elipse, z_elipse, color='skyblue', linewidth=1, alpha=0.1)
# Configurar la proporción de los ejes para que sean iguales
# ax.set_aspect('equal')
ax.set_xlabel("PCA1")
ax.set_ylabel("PCA2")
ax.set_zlabel("PCA3")

plt.show()



# Guardar en un archivo csv
folder_path = '../KDTree/'
if not os.path.exists(folder_path):
    os.makedirs(folder_path)
csv_path = os.path.join(folder_path, 'pca_result.csv')
df_3.to_csv(csv_path, index=False, header=None)


sns.barplot(x=["PCA1","PCA2","PCA3"], y=pca3.explained_variance_ratio_)
# plt.show()
plt.savefig('PCA_barplot.png', dpi=300, bbox_inches='tight', pad_inches=0.1, format='png')

fig = plt.figure()
ax = fig.add_subplot(111,projection="3d")
x = df_3["PCA1"]
y = df_3["PCA2"]
z = df_3["PCA3"]

ax.scatter(x,y,z)
ax.set_xlabel("PCA1")
ax.set_ylabel("PCA2")
ax.set_zlabel("PCA3")

# plt.show()


# # muestra tres diagramas
# # Círculo de correlación
# fig, ax = plt.subplots()

# # Dibuja el círculo
# circle = plt.Circle((0, 0), 1, fill=False, color='black', linewidth=1)
# ax.add_patch(circle)

# # Dibuja las variables (vectores) en el círculo
# for i, var in enumerate(selected_columns[2:]):
#     ax.arrow(0, 0, eigenvectors[0, i], eigenvectors[1, i], head_width=0.05, head_length=0.05, fc='r', ec='r')
#     ax.text(eigenvectors[0, i]*1.2, eigenvectors[1, i]*1.2, var, color='r')

# # Ajusta los límites del gráfico
# ax.set_xlim(-1, 1)
# ax.set_ylim(-1, 1)

# # Etiqueta los ejes
# ax.set_xlabel("PCA1")
# ax.set_ylabel("PCA2")

# # Muestra el gráfico
# plt.show()