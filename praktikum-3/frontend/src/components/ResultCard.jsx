import styles from "./ResultCard.module.css";

export default function ResultCard({ result }) {
  if (result === null) return null;

  return (
    <div
      className={`${styles.card} ${result ? styles.accepted : styles.rejected}`}
    >
      {result ? "Accepted" : "Rejected"}
    </div>
  );
}
