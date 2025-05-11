from forecast import train_model, make_forecast
import pandas as pd

# Carrega o histórico de chuvas
df = pd.read_csv('../../data/synthetic/flood_synthetic.csv')

# Treina o modelo
model = train_model(df)

# Gera dados fictícios para previsão (ajuste se necessário)
df_future = pd.DataFrame({
    'timestamp': pd.date_range(start=pd.Timestamp.now(), periods=24, freq='H'),
    'rainfall_mm': [5.0] * 24  # valores simulados
})

# Faz a previsão    
result = make_forecast(model, df_future, periods=24)

# Mostra os últimos resultados
print(result.tail())
