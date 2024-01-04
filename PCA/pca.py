import pandas as pd
from sklearn.decomposition import PCA
from sklearn.impute import SimpleImputer
from sklearn.preprocessing import StandardScaler
from numpy.linalg import eig
import numpy as np

class PCAImplementation:
    def __init__(self, df_original, selected_columns :list):
        self.df_original = df_original
        self.selected_columns = selected_columns
        self.df_selected : pd.DataFrame = self.df_original[self.selected_columns]
        self.df_data_imputed : pd.DataFrame = None
        self.df_data_imputed_transpose : pd.DataFrame = None

        self.pca_result = None
        self.pca_result_transpose = None
        self.matrix_cov  = None
        self.eigenvalues = None
        self.eigenvectors = None

        self.explain_varianza = None
        self.explain_varianza_transpose = None

        self.cosine_squares = None

    def apply_pca(self):
        # Manejo de valores faltantes con imputación por la media
        imputer = SimpleImputer(strategy='mean') # mean, median, most_frequent or other values set
        self.df_data_imputed = pd.DataFrame(imputer.fit_transform(self.df_selected), columns=self.df_selected.columns)
        # Estandarización de los datos
        ss = StandardScaler()
        self.df_data_imputed[self.selected_columns] = ss.fit_transform(self.df_data_imputed[self.selected_columns])
        self.matrix_cov = self.df_data_imputed.cov()
        self.eigenvalues, self.eigenvectors = eig(self.matrix_cov)
        
        pca = PCA(n_components=3, random_state=42)
        self.pca_result = pca.fit_transform(self.df_data_imputed[self.selected_columns])
        self.explain_varianza = pca.explained_variance_ratio_
        
        self.df_data_imputed_transpose = self.df_data_imputed.transpose()
        pca_trans = PCA(n_components=3, random_state=42)
        self.pca_result_transpose = pca_trans.fit_transform(self.df_data_imputed_transpose)
        self.explain_varianza_transpose = pca_trans.explained_variance_ratio_

        # Calcular cosenos cuadrados
        # self.cosine_squares = (self.pca_result ** 2) / self.df_data_imputed.var()


    def get_df_pca2(self):
        return pd.DataFrame({   "PCA1":self.pca_result[:,0], 
                                "PCA2":self.pca_result[:,1] })
    
    def get_df_pca3(self):
        return pd.DataFrame({   "PCA1":self.pca_result[:,0], 
                                "PCA2":self.pca_result[:,1], 
                                "PCA3":self.pca_result[:,2] })
    
    def get_df_pca2_transpose(self):
        return pd.DataFrame({   "PCA1":self.pca_result_transpose[:,0], 
                                "PCA2":self.pca_result_transpose[:,1] })
    
    def get_df_pca3_transpose(self):
        return pd.DataFrame({   "PCA1":self.pca_result_transpose[:,0], 
                                "PCA2":self.pca_result_transpose[:,1], 
                                "PCA3":self.pca_result_transpose[:,2] })
    
    def get_explain_varianza(self):
        return self.explain_varianza
    
    def get_explain_varianza_transpose(self):
        return self.explain_varianza_transpose
    
    def get_eigenvalues(self):
        return self.eigenvalues

    def calculate_cosine_squared(self, pca_result):
        # Calcular los cosenos cuadrados entre cada fila y los resultados de PCA
        cosines_squared = np.zeros(self.df_data_imputed.shape[0])

        for i in range(self.df_data_imputed.shape[0]):
            # Fila original
            row_original = self.df_data_imputed.iloc[i, :].values
            # Resultado de PCA para la fila actual
            pca_row = pca_result[i, :]
            # Calcular coseno cuadrado
            cosine_squared = np.sum((row_original - pca_row) ** 2) / (np.sum(row_original ** 2))
            cosines_squared[i] = cosine_squared

        return cosines_squared

    def get_cosines_squared_pca2(self):
        # Obtener los cosenos cuadrados respecto a pca2
        return pd.DataFrame({"CosenosSquared_PCA2": self.calculate_cosine_squared(self.pca_result_transpose)})

    def get_cosines_squared_pca3(self):
        # Obtener los cosenos cuadrados respecto a pca3
        return pd.DataFrame({"CosenosSquared_PCA3": self.calculate_cosine_squared(self.pca_result_transpose)})
