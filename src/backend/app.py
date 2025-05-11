from fastapi import FastAPI, HTTPException
from fastapi.middleware.cors import CORSMiddleware
from pydantic import BaseModel
import httpx
import os
import csv

# Inicializar FastAPI
app = FastAPI()

app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],  # ou especifique ["http://localhost:3000"]
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

# Modelos de dados
class Alert(BaseModel):
    sensor_id: str
    level_cm: float
    location: str
    timestamp: str

class LevelData(BaseModel):
    sensor_id: str
    level_cm: float
    location: str
    timestamp: str

# Simulação de base de dados em memória
levels_db = [
  { "timestamp": "2025-04-26T12:00:00", "level": 10 },
  { "timestamp": "2025-04-26T12:05:00", "level": 15 },
  { "timestamp": "2025-04-26T12:10:00", "level": 20 },
  { "timestamp": "2025-04-26T12:15:00", "level": 18 },
  { "timestamp": "2025-04-26T12:20:00", "level": 22 }
]


# API KEY do OpenWeather (defina sua própria ou via variáveis de ambiente)
OPENWEATHER_API_KEY = os.getenv("OPENWEATHER_API_KEY", "7d472316d7ad76b5d015d96a713bfcd9")
OPENWEATHER_URL = "https://api.openweathermap.org/data/2.5/weather"

@app.get("/levels")
async def get_levels():
    """
    Retorna todos os níveis de água registrados.
    """
    # Read synthetic data from CSV
    csv_path = os.path.join(os.path.dirname(__file__), "../../data/synthetic/flood_synthetic.csv")
    levels = []
    with open(csv_path, newline='') as f:
        reader = csv.DictReader(f)
        for row in reader:
            levels.append({
                "timestamp": row["timestamp"],
                "level_cm": float(row["water_level_cm"])
            })
    return {"levels": levels}

@app.post("/levels")
async def post_level(level: LevelData):
    """
    Recebe dados dos sensores de nível de água.
    """
    levels_db.append(level.dict())
    return {"status": "nível registrado", "level": level}

@app.get("/weather/{city}")
async def get_weather(city: str):
    """
    Consulta previsão do tempo para a cidade informada usando OpenWeather.
    """
    try:
        async with httpx.AsyncClient() as client:
            params = {
                "q": city,
                "appid": OPENWEATHER_API_KEY,
                "units": "metric",
                "lang": "pt_br"
            }
            response = await client.get(OPENWEATHER_URL, params=params)
            response.raise_for_status()
            weather_data = response.json()
            return {
                "city": city,
                "temperature": weather_data["main"]["temp"],
                "weather": weather_data["weather"][0]["description"],
                "humidity": weather_data["main"]["humidity"],
                "wind_speed": weather_data["wind"]["speed"]
            }
    except httpx.HTTPError as e:
        raise HTTPException(status_code=500, detail=str(e))

@app.post("/alerts")
async def post_alert(alert: Alert):
    """
    Recebe alertas críticos enviados por sensores.
    """
    # Aqui poderia integrar com sistemas de notificação (email, sms, etc.)
    print(f"Alerta recebido: {alert}")
    return {"status": "alerta recebido", "alert": alert}
