import styles from './ResultCard.module.css';

export default function ResultCard({ result }) {
  if (!result) return null;
  const accepted = result === 'accepted';
  return (
    <div className={`${styles.card} ${accepted ? styles.accepted : styles.rejected}`}>
      {accepted ? 'Accepted' : 'Rejected'}
    </div>
  );
}
