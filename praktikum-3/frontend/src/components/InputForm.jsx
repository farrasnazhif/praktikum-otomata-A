import { useState } from 'react';
import styles from './InputForm.module.css';

export default function InputForm({ onSimulate, onReset, loading }) {
  const [language, setLanguage] = useState('anbn');
  const [input, setInput] = useState('');
  const [error, setError] = useState('');

  const validate = () => {
    if (!input.trim()) { setError('Input cannot be empty'); return false; }
    if (!/^[ab]+$/.test(input)) { setError('Only characters a and b are allowed'); return false; }
    setError('');
    return true;
  };

  const handleSubmit = (e) => {
    e.preventDefault();
    if (validate()) onSimulate(language, input);
  };

  const handleReset = () => {
    setInput('');
    setError('');
    onReset();
  };

  return (
    <form className={styles.form} onSubmit={handleSubmit}>
      <label className={styles.label}>
        Language
        <select value={language} onChange={(e) => setLanguage(e.target.value)} className={styles.select}>
          <option value="anbn">aⁿbⁿ</option>
        </select>
      </label>
      <label className={styles.label}>
        Input String
        <input
          type="text"
          value={input}
          onChange={(e) => setInput(e.target.value)}
          placeholder="e.g. aabb"
          className={styles.input}
        />
      </label>
      {error && <p className={styles.error}>{error}</p>}
      <div className={styles.buttons}>
        <button type="submit" disabled={loading} className={styles.btn}>
          {loading ? 'Simulating...' : 'Simulate'}
        </button>
        <button type="button" onClick={handleReset} className={styles.btnReset}>Reset</button>
      </div>
    </form>
  );
}
