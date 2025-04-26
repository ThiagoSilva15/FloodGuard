import pandas as pd
from prophet import Prophet

def train_model(df, use_rainfall: bool = True):
    """
    Treina o modelo Prophet utilizando nível de água e, opcionalmente, chuva como variável externa.
    
    Parâmetros:
    - df: DataFrame com colunas:
        - timestamp (datetime)
        - water_level_cm (float)
        - rainfall_mm (float) → opcional, se não existir será preenchido com 0
    - use_rainfall: se True, adiciona o regressor 'rainfall' (caso não exista, é criado com zeros)
    """
    # Renomeia colunas para o formato do Prophet
    df2 = df.rename(columns={
        'timestamp': 'ds',
        'water_level_cm': 'y',
        'rainfall_mm': 'rainfall'
    }).copy()

    # Se quiser usar chuva como regressor, garante que exista a coluna
    if use_rainfall:
        if 'rainfall' not in df2.columns:
            df2['rainfall'] = 0.0
        else:
            df2['rainfall'] = df2['rainfall'].fillna(0.0)

    # Instancia o modelo Prophet
    model = Prophet()
    if use_rainfall:
        model.add_regressor('rainfall')

    # Fit no modelo
    model.fit(df2)
    return model

def make_forecast(model, df_external=None, periods=24):
    """
    Gera previsões para as próximas 'periods' horas.
    
    Parâmetros:
    - model: modelo retornado por train_model()
    - df_external: DataFrame futuro com colunas:
        - timestamp
        - rainfall_mm
      (se None ou sem chuva, será preenchido com 0)
    - periods: número de horas a prever
    """
    # Gera o DataFrame de datas futuras
    future = model.make_future_dataframe(periods=periods, freq='H')

    # Se foi passado df_external, renomeia e mescla; senão, adiciona rainfall=0
    if df_external is not None and 'rainfall_mm' in df_external.columns:
        ext = df_external.rename(columns={
            'timestamp': 'ds',
            'rainfall_mm': 'rainfall'
        })
        future = future.merge(ext[['ds', 'rainfall']], on='ds', how='left')
        future['rainfall'] = future['rainfall'].fillna(0.0)
    else:
        future['rainfall'] = 0.0

    # Faz a previsão
    forecast = model.predict(future)

    # Retorna data, previsão e chuva usada
    return forecast[['ds', 'yhat', 'rainfall']]
