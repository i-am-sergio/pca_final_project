import pandas as pd
from sklearn.decomposition import PCA
from sklearn.impute import SimpleImputer
from sklearn.preprocessing import StandardScaler
from numpy.linalg import eig

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
