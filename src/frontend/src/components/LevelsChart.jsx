import React, { useEffect, useState, useMemo } from 'react';
import {
  LineChart,
  Line,
  XAxis,
  YAxis,
  Tooltip,
  CartesianGrid,
  ResponsiveContainer
} from 'recharts';
import { fetchLevels } from '../services/api';

function LevelsChart() {
  const [data, setData] = useState([]);
  const [loading, setLoading] = useState(true);
  const [startTime, setStartTime] = useState('');
  const [endTime, setEndTime] = useState('');

  // Função para buscar os dados do backend
  const fetchData = async () => {
    try {
      const levels = await fetchLevels();
      setData(levels);
    } catch (error) {
      console.error('Erro ao buscar níveis de água:', error);
    } finally {
      setLoading(false);
    }
  };

  useEffect(() => {
    fetchData();                        // Busca inicial
    const interval = setInterval(fetchData, 5000); // Atualiza a cada 5s

    return () => clearInterval(interval);
  }, []);

  const formattedData = useMemo(() => {
    return data
      .filter(item => {
        const ts = new Date(item.timestamp);
        if (startTime && ts < new Date(startTime)) return false;
        if (endTime && ts > new Date(endTime)) return false;
        return true;
      })
      .map(item => ({
        time: new Date(item.timestamp)
          .toLocaleTimeString([], { hour: '2-digit', minute: '2-digit' }),
        level: item.level_cm,
      }));
  }, [data, startTime, endTime]);

  return (
    <div>
      <h2 className="text-xl font-semibold mb-2">Níveis de Água</h2>

      {/* timeline filter inputs */}
      <div className="flex space-x-4 mb-4">
        <div>
          <label className="block text-sm">Início:</label>
          <input type="datetime-local" value={startTime} onChange={e => setStartTime(e.target.value)} className="border p-1 rounded" />
        </div>
        <div>
          <label className="block text-sm">Fim:</label>
          <input type="datetime-local" value={endTime} onChange={e => setEndTime(e.target.value)} className="border p-1 rounded" />
        </div>
      </div>

      {loading ? (
        <div className="flex justify-center items-center h-72">
          <div className="w-16 h-16 border-4 border-blue-500 border-t-transparent rounded-full animate-spin"></div>
        </div>
      ) : (
        <ResponsiveContainer width="100%" height={300}>
          <LineChart data={formattedData}>
            <CartesianGrid strokeDasharray="3 3" />
            <XAxis dataKey="time" />
            <YAxis label={{ value: 'Nível (cm)', angle: -90, position: 'insideLeft' }} />
            <Tooltip />
            <Line type="monotone" dataKey="level" stroke="#3b82f6" dot={{ r: 3 }} />
          </LineChart>
        </ResponsiveContainer>
      )}
    </div>
  );
}

export default LevelsChart;
