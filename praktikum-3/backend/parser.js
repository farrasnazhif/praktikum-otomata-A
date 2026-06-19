function parse(output) {
  const lines = output.trim().split('\n');
  const steps = [];
  let accepted = false;

  for (const line of lines) {
    if (line.startsWith('STEP')) {
      const parts = line.split(' ');
      steps.push({
        step: parseInt(parts[1]),
        state: parts[2],
        remainingInput: parts[3],
        stack: parts[4] || ''
      });
    } else if (line === 'ACCEPTED') {
      accepted = true;
    }
  }

  return { accepted, steps };
}

module.exports = { parse };
