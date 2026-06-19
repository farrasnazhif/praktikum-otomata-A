import styles from './SimulationTable.module.css';

export default function SimulationTable({ steps }) {
  if (!steps || steps.length === 0) return null;
  return (
    <table className={styles.table}>
      <thead>
        <tr>
          <th>Step</th>
          <th>State</th>
          <th>Remaining Input</th>
          <th>Stack</th>
        </tr>
      </thead>
      <tbody>
        {steps.map((s, i) => (
          <tr key={i}>
            <td>{s.step}</td>
            <td>{s.state}</td>
            <td>{s.remainingInput}</td>
            <td>{s.stack}</td>
          </tr>
        ))}
      </tbody>
    </table>
  );
}
