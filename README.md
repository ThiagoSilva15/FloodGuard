# FloodGuard IoT

FloodGuard IoT é uma plataforma completa para **monitoramento**, **previsão** e **alerta** de enchentes urbanas, combinando sensores IoT, inteligência artificial e dados meteorológicos.

---

## 🚀 Visão Geral

- **Sensores**: Ultrassônico (HC-SR04) e sensor de nível de água (analógico) lidos por um ESP32.
- **Comunicação**: Dados enviados via LoRaWAN para o backend.
- **Backend**: FastAPI para ingestão de dados, alertas e consulta a APIs de clima (OpenWeather).
- **Modelo de Previsão**: Prophet (com variável externa de chuva) para prever níveis de água nas próximas horas.
- **Frontend**: Dashboard React + Tailwind + Recharts, exibindo histórico de níveis e previsão do tempo.

---

## 📁 Estrutura do Projeto

```text
/
├─ .github/                  → Configurações de CI/CD e templates
├─ docs/                     → Documentação e PDF da pesquisa
│   └─ CP02_GOV.pdf          → Fundamentação teórica e decisões
├─ data/
│   ├─ public/               → (opcional) dados reais
│   └─ synthetic/            → flood_synthetic.csv (dados simulados)
├─ hardware/
│   ├─ schematics.pdf        → Diagrama de circuito ESP32 + sensores
│   └─ firmware/
│       └─ src/
│           └─ main.cpp      → Leitura de sensores + LoRa (binário)
├─ src/
│   ├─ backend/
│   │   ├─ app.py            → FastAPI (levels, alerts, weather)
│   │   └─ requirements-backend.txt
│   ├─ models/
│   │   ├─ forecast.py       → Prophet com variável de chuva
│   │   └─ requirements-forecast.txt
│   └─ frontend/             → React app
│       ├─ package.json
│       ├─ tailwind.config.js
│       ├─ postcss.config.js
│       └─ src/
│           ├─ index.js
│           ├─ index.css
│           ├─ App.jsx
│           ├─ services/api.js
│           └─ components/
│               ├─ Dashboard.jsx
│               ├─ LevelsChart.jsx
│               └─ WeatherCard.jsx
└─ README.md                 → **Você está aqui**

⚙️ Instalação e Uso
Backend
Clone o repositório e navegue até src/backend:

bash
Copiar
Editar
cd src/backend
Crie um virtualenv e instale dependências:

bash
Copiar
Editar
python -m venv venv
source venv/bin/activate  # macOS/Linux
.\\venv\\Scripts\\activate # Windows
pip install -r requirements.txt
Adicione sua chave da OpenWeather em .env:

ini
Copiar
Editar
OPENWEATHER_API_KEY=7d472316d7ad76b5d015d96a713bfcd9
Rode o servidor:

bash
Copiar
Editar
uvicorn app:app --reload
Forecast (Modelos)
Em src/models, ative seu ambiente e instale:

bash
Copiar
Editar
cd src/models
pip install -r requirements-forecast.txt
Use forecast.py importando seu DataFrame histórico:

python
Copiar
Editar
from forecast import train_model, make_forecast
import pandas as pd

df = pd.read_csv('../../data/synthetic/flood_synthetic.csv')
# Suponha que você tenha uma coluna rainfall_mm no df
model = train_model(df)
# Previsão para próximas 24 horas
df_future = pd.DataFrame({
  'timestamp': pd.date_range(...),
  'rainfall_mm': [...]
})
result = make_forecast(model, df_future, periods=24)
print(result.tail())
Frontend
Entre na pasta e instale:

bash
Copiar
Editar
cd src/frontend
npm install
Defina a URL da API no .env.local:

ini
Copiar
Editar
REACT_APP_API_URL=http://localhost:8000
Rode a aplicação:

bash
Copiar
Editar
npm start
Acesse em http://localhost:3000.

🗂️ Dados Sintéticos
Geramos um CSV de exemplo em data/synthetic/flood_synthetic.csv com:

timestamp: carimbo horário

sensor_id: ID do sensor

water_level_cm: nível da água

rainfall_mm: chuva (hopper para incluir manualmente ou via script)

Para regenerar, veja o script em data/synthetic/generate.py.

🔗 Endpoints da API
GET /levels

Retorna lista de leituras: [{sensor_id, level_cm, location, timestamp}, …]

POST /levels

Insere nova leitura (JSON no formato acima).

GET /weather/{city}

Retorna temperature, weather, humidity, wind_speed.

POST /alerts

Insere alerta crítico: {sensor_id, level_cm, location, timestamp}.

📖 Referências
FastAPI Documentation

Prophet by Meta

OpenWeather API

Recharts

📝 Licença
MIT © Sua Empresa / Seu Nome

Última atualização: 26 de Abril de 2025

Copiar
Editar
