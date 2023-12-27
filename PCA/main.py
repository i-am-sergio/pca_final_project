from pca import PCAImplementation
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
import numpy as np
import os


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


pca_impl = PCAImplementation(df, selected_columns)
pca_impl.apply_pca()


# Guardar en un archivo csv
folder_path = '../KDTree/'
if not os.path.exists(folder_path):
    os.makedirs(folder_path)
csv_path = os.path.join(folder_path, 'pca_result.csv')
pca_impl.get_df_pca3().to_csv(csv_path, index=False, header=None)




# Graficar Grafico de correlacion 2D
sns.scatterplot(data=pca_impl.get_df_pca2_transpose(), x="PCA1", y="PCA2", color="green")
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
#for i in range(len(pca_impl.get_df_pca2_transpose())):
#    plt.quiver(0, 0, pca_impl.get_df_pca3_transpose()['PCA1'][i], pca_impl.get_df_pca3_transpose()['PCA2'][i], angles='xy', scale_units='xy', scale=1, color='red', width=0.005)
#plt.show()
for i in range(len(pca_impl.get_df_pca2_transpose())):
    plt.quiver(0, 0, pca_impl.get_df_pca3_transpose()['PCA1'][i], pca_impl.get_df_pca3_transpose()['PCA2'][i], angles='xy', scale_units='xy', scale=1, color='red', width=0.005)
    plt.text(pca_impl.get_df_pca3_transpose()['PCA1'][i], pca_impl.get_df_pca3_transpose()['PCA2'][i], f'Var. {i+1}', color='blue', fontsize=8)

plt.xlabel('PCA1')
plt.ylabel('PCA2')
plt.title('Circulo de correlacion con 2 componentes')
plt.show()

# Graficar Grafico de tabla 2D

sns.scatterplot(data=pca_impl.get_df_pca2(), x="PCA1", y="PCA2", color="green", s=10)
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
plt.title('Mapa de Factores Individuales')
plt.show()


# Graficar Grafico de correlacion 3D
# Obtener los datos
x = pca_impl.get_df_pca3_transpose()["PCA1"]
y = pca_impl.get_df_pca3_transpose()["PCA2"]
z = pca_impl.get_df_pca3_transpose()["PCA3"]

# Crear un DataFrame
df_points = pd.DataFrame({'X': x, 'Y': y, 'Z': z})

# Directorio donde se guardará el archivo CSV
directory = '../KDTree'
if not os.path.exists(directory):
    os.makedirs(directory)
csv_path = os.path.join(directory, 'puntos.csv')
df_points.to_csv(csv_path, header=False, index=False)
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

ax.scatter(x, y, z, color='blue', marker='o')

ax.quiver(0, 0, 0, x, y, z, color='red', arrow_length_ratio=0.05, linewidth=1, linestyle='dashed')

# Crear una elipse en 3D con radio 80
u = np.linspace(0, 2 * np.pi, 100)
v = np.linspace(0, np.pi, 100)
x_elipse = 80 * np.outer(np.cos(u), np.sin(v))
y_elipse = 80 * np.outer(np.sin(u), np.sin(v))
z_elipse = 80 * np.outer(np.ones(np.size(u)), np.cos(v))
ax.plot_wireframe(x_elipse, y_elipse, z_elipse, color='skyblue', linewidth=1, alpha=0.1)

# Configuraciones adicionales
ax.set_xlabel('PCA1')
ax.set_ylabel('PCA2')
ax.set_zlabel('PCA3')
plt.title('Círculo de correlación con 3 componentes')
plt.show()


explain_varianza = pca_impl.get_explain_varianza()
explain_varianza_transpose = pca_impl.get_explain_varianza_transpose()

# Representación de la varianza de cada componente
print("explain_varianza PCA => " , explain_varianza)
print("explain_varianza_transpose PCA => " , explain_varianza_transpose)

# Colores RGB para cada componente
colors = [(0.91, 0.45, 1.0),
          (0.64, 0.97, 0.26),
          (0.44, 0.77, 0.97)] 


def draw_barplot(explain_varianza, file_name):
    ax = sns.barplot(x=["PCA1","PCA2","PCA3"], y=explain_varianza, hue=["PCA1", "PCA2", "PCA3"], palette=colors)
    # Mostrar los valores en las barras
    for p in ax.patches:
        ax.annotate(f'{p.get_height():.2f}', (p.get_x() + p.get_width() / 2., p.get_height()),
                    ha='center', va='center', xytext=(0, 10), textcoords='offset points', fontsize=10)
    ax.set_title(f"Explained Variance for {file_name}")
    plt.savefig(file_name, dpi=300, bbox_inches='tight', pad_inches=0.1, format='png')
    plt.show()

draw_barplot(explain_varianza, 'PCA_barplot.png')
draw_barplot(explain_varianza_transpose, 'PCA_barplot_transpose.png')

