const express = require("express");
const cors = require("cors");
const { exec } = require("child_process");
const fs = require("fs");

const app = express();
app.use(cors());
app.use(express.json());

app.post("/analyze", (req, res) => {
  const code = req.body.code;

  fs.writeFileSync("input.txt", code);

  exec("./compiler < input.txt", (err, stdout, stderr) => {
    if (err) {
      return res.status(500).send("error");
    }

    const lines = stdout.trim().split("\n");
    const tokens = lines.map((line) => {
      const [value, type] = line.split(":");
      return { value, type };
    });

    res.json(tokens);
  });
});

app.listen(3001, () => console.log("server running"));
