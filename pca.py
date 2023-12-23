from sklearn.decomposition import PCA
from sklearn.impute import SimpleImputer
import pandas as pd

class PCACalculator:
    def __init__(self, data):
        self.data = data
        self.pca = None
        self.transformed_data = None

    def apply_pca(self):
        columns_for_pca = [
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

        pca_data = self.data[columns_for_pca]

        # Manejo de valores faltantes con imputación por la media
        imputer = SimpleImputer(strategy='mean')
        pca_data_imputed = pd.DataFrame(imputer.fit_transform(pca_data), columns=pca_data.columns)

        self.pca = PCA(n_components=3)  # Número de componentes principales deseados
        self.transformed_data = self.pca.fit_transform(pca_data_imputed)
        pca_columns = [f"PCA_{i+1}" for i in range(self.transformed_data.shape[1])]
        pca_df = pd.DataFrame(data=self.transformed_data, columns=pca_columns)
        return pca_df