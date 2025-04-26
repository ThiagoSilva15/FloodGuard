import React, { useEffect, useState } from 'react';
import { fetchLevels, fetchWeather } from '../services/api';
import LevelsChart from './LevelsChart';
import WeatherCard from './WeatherCard';

function Dashboard() {
  const [levels, setLevels] = useState([]);
  const [weather, setWeather] = useState(null);

  useEffect(() => {
    async function loadData() {
      try {
        const lvl = await fetchLevels();
        setLevels(lvl);
        const weatherData = await fetchWeather('São Paulo');
        setWeather(weatherData);
      } catch (err) {
        console.error(err);
      }
    }
    loadData();
  }, []);

  return (
    <div className="space-y-6">
      <div className="bg-white rounded-lg shadow p-4">
        <LevelsChart data={levels} />
      </div>
      {weather && (
        <div className="bg-white rounded-lg shadow p-4">
          <WeatherCard data={weather} />
        </div>
      )}
    </div>
  );
}

export default Dashboard;
