import pandas as pd

class ExcelDataProcessor:
    def __init__(self, file_path):
        self.file_path = file_path
        self.data = None

    def read_excel_and_process(self):
        try:
            self.data = pd.read_excel(self.file_path)
        except Exception as e:
            print(f"Error al leer el archivo: {e}")
            return

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

        # Reemplazar 'negative' por 0 y 'positive' por 1 en 'SARS-Cov-2 exam result'
        self.data['SARS-Cov-2 exam result'].replace({'negative': 0, 'positive': 1}, inplace=True)
        # Solucionar valores faltantes o NaN
        self.data.fillna(pd.NA, inplace=True)
        # Crear una nueva columna que almacene todos los datos por elemento (concatenar las 11 columnas)
        self.data['All Data'] = self.data[selected_columns].apply(lambda row: ','.join(map(str, row)), axis=1)
        # Crear una estructura con la información requerida por elemento (Patient ID, All Data y las 11 columnas)
        processed_data = self.data[['Patient ID', 'All Data'] + selected_columns]
        return processed_data
