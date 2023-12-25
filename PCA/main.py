import pandas as pd
from sklearn.decomposition import PCA
from sklearn.preprocessing import StandardScaler
from sklearn.impute import SimpleImputer
import seaborn as sns
import matplotlib.pyplot as plt
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
df_selected = df[selected_columns]
print(df_selected.head())

imputer = SimpleImputer(strategy='mean') # mean, median, most_frequent or other values set
pca_data_imputed = pd.DataFrame(imputer.fit_transform(df_selected), columns=df_selected.columns)
print(pca_data_imputed.head())

ss = StandardScaler()
pca_data_imputed[selected_columns] = ss.fit_transform(pca_data_imputed[selected_columns])
print(pca_data_imputed.head())

pca3 = PCA(n_components=3, random_state=42)
pca_3 = pca3.fit_transform(pca_data_imputed[selected_columns])
print( "PCA componentes => " , pca3.explained_variance_ratio_)

df_3 = pd.DataFrame({"PCA1":pca_3[:,0], "PCA2":pca_3[:,1], "PCA3":pca_3[:,2]})
print(df_3.head())



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