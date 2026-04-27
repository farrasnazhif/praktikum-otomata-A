import { useState } from "react";
import styles from "./App.module.css";

export default function App() {
  const [code, setCode] = useState("");
  const [tokens, setTokens] = useState([]);
  const [loading, setLoading] = useState(false);

  const analyze = async () => {
    setLoading(true);
    try {
      const res = await fetch("http://localhost:3001/analyze", {
        method: "POST",
        headers: {
          "Content-Type": "application/json",
        },
        body: JSON.stringify({ code }),
      });

      const data = await res.json();
      setTokens(data);
    } catch (err) {
      console.error(err);
      alert("Error analyzing code");
    }
    setLoading(false);
  };

  return (
    <div className={styles.container}>
      <h1 className={styles.title}>Token Analyzer</h1>

      <div className={styles.card}>
        <textarea
          className={styles.textarea}
          placeholder="Type your code here..."
          value={code}
          onChange={(e) => setCode(e.target.value)}
        />

        <button className={styles.button} onClick={analyze}>
          {loading ? "Analyzing..." : "Analyze"}
        </button>
      </div>

      <div className={styles.card}>
        <h2 className={styles.subtitle}>Result</h2>

        {tokens.length === 0 ? (
          <p className={styles.empty}>No tokens yet</p>
        ) : (
          <table className={styles.table}>
            <thead>
              <tr>
                <th>Token</th>
                <th>Type</th>
              </tr>
            </thead>
            <tbody>
              {tokens.map((t, i) => (
                <tr key={i}>
                  <td>{t.value}</td>
                  <td
                    className={`${styles.type} ${styles[t.type.toLowerCase()]}`}
                  >
                    {t.type}
                  </td>
                </tr>
              ))}
            </tbody>
          </table>
        )}
      </div>
    </div>
  );
}
