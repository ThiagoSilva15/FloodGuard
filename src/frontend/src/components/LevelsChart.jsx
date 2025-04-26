import React from 'react';
import {
  LineChart,
  Line,
  XAxis,
  YAxis,
  Tooltip,
  CartesianGrid,
  ResponsiveContainer
} from 'recharts';

function LevelsChart({ data }) {
  const formatted = data.map(item => ({
    time: new Date(item.timestamp).toLocaleTimeString(),
    level: item.level_cm,
  }));

  return (
    <div>
      <h2 className="text-xl font-semibold mb-2">Níveis de Água</h2>
      <ResponsiveContainer width="100%" height={300}>
        <LineChart data={formatted}>
          <CartesianGrid strokeDasharray="3 3" />
          <XAxis dataKey="time" />
          <YAxis />
          <Tooltip />
          <Line type="monotone" dataKey="level" stroke="#3b82f6" />
        </LineChart>
      </ResponsiveContainer>
    </div>
  );
}

export default LevelsChart;
