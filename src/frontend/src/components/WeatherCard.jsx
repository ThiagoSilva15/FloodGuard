import React from 'react';

function WeatherCard({ data }) {
  const { city, temperature, weather, humidity, wind_speed } = data;
  return (
    <div>
      <h2 className="text-xl font-semibold mb-2">Previsão do Tempo - {city}</h2>
      <div className="grid grid-cols-2 gap-4">
        <div>
          <p><strong>Temperatura:</strong> {temperature}°C</p>
          <p><strong>Condição:</strong> {weather}</p>
        </div>
        <div>
          <p><strong>Umidade:</strong> {humidity}%</p>
          <p><strong>Vento:</strong> {wind_speed} m/s</p>
        </div>
      </div>
    </div>
  );
}

export default WeatherCard;
