from forecast import train_model, make_forecast
import pandas as pd

df_hist = pd.read_csv('../../data/synthetic/flood_synthetic.csv', parse_dates=['timestamp'])
model = train_model(df_hist)

# Se tiver previsão de chuva
df_chuva = pd.DataFrame({
    'timestamp': pd.date_range(start="2025-04-27", periods=24, freq='H'),
    'rainfall_mm': [0.0]*24  # ou valores reais
})
pred = make_forecast(model, df_chuva, periods=24)
print(pred.tail())

