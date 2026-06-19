const express = require('express');
const cors = require('cors');
const { execSync } = require('child_process');
const fs = require('fs');
const path = require('path');
const { parse } = require('./parser');

const app = express();
app.use(cors());
app.use(express.json());

app.post('/simulate', (req, res) => {
  const { input } = req.body;

  if (!input || !/^[ab]+$/.test(input)) {
    return res.status(400).json({ error: 'Input must be non-empty and contain only a,b' });
  }

  const inputPath = path.join(__dirname, 'input.txt');
  fs.writeFileSync(inputPath, input);

  try {
    const output = execSync('./pda < input.txt', { cwd: __dirname, encoding: 'utf-8' });
    const result = parse(output);
    res.json(result);
  } catch (e) {
    res.status(500).json({ error: 'PDA execution failed' });
  }
});

app.listen(3001, () => console.log('Backend running on port 3001'));
