import axios from 'axios';

const API_BASE = process.env.REACT_APP_API_URL || 'http://localhost:8000';

export async function fetchLevels() {
  const res = await axios.get(`${API_BASE}/levels`);
  return res.data.levels;
}

export async function fetchWeather(city) {
  const res = await axios.get(`${API_BASE}/weather/${city}`);
  return res.data;
}
