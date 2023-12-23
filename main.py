from Reader import ExcelDataProcessor
from pca import PCACalculator
import pandas as pd
import os

def main():
    file_path = 'covid_DB.xlsx'
    processor = ExcelDataProcessor(file_path)
    processed_data = processor.read_excel_and_process()
    
    if processed_data is not None:
        pca_calculator = PCACalculator(processed_data)
        transformed_data_pca = pca_calculator.apply_pca()

        folder_path = 'KDTree/'

        if not os.path.exists(folder_path):
            os.makedirs(folder_path)
        
        csv_path = os.path.join(folder_path, 'pca_result.csv')
        transformed_data_pca.to_csv(csv_path, index=False, header=None)

        #Lo de abajo hace que se agreguedos veces la columna 'Patient ID' y solo una 'All Data'
        #pca_with_patient_data = pd.concat([processed_data[['Patient ID', 'All Data']], transformed_data_pca], axis=1)
        print("\nDatos del PCA junto con 'Patient ID' y 'All Data':")
        print(transformed_data_pca)
        print(f"\nDatos del PCA guardados en '{csv_path}'.")

if __name__ == "__main__":
    main()