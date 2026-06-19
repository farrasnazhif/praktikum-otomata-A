import { useState } from "react";
import styles from "./App.module.css";
import Header from "./components/Header";
import InputForm from "./components/InputForm";
import ResultCard from "./components/ResultCard";
import SimulationTable from "./components/SimulationTable";
import { simulate } from "./services/api";

export default function App() {
  const [result, setResult] = useState(null);
  const [steps, setSteps] = useState([]);
  const [loading, setLoading] = useState(false);
  const [error, setError] = useState("");

  const handleSimulate = async (language, input) => {
    setLoading(true);
    setError("");
    try {
      const data = await simulate(language, input);
      setResult(data.accepted);
      setSteps(data.steps || []);
    } catch (err) {
      setError("Simulation failed. Is the backend running?");
    } finally {
      setLoading(false);
    }
  };

  const handleReset = () => {
    setResult(null);
    setSteps([]);
    setError("");
  };

  return (
    <div className={styles.container}>
      <Header />
      <InputForm
        onSimulate={handleSimulate}
        onReset={handleReset}
        loading={loading}
      />
      {error && <p className={styles.error}>{error}</p>}
      <ResultCard result={result} />
      <SimulationTable steps={steps} />
    </div>
  );
}
