from pca import PCAImplementation
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

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
