# PDA Simulator

Simulator berbasis web untuk Pushdown Automata yang mensimulasikan bahasa **L = { aⁿbⁿ | n ≥ 1 }**.

## Cara Menjalankan

### 1. Kompilasi Program C

```bash
cd backend
gcc -o pda pda.c
```

### 2. Jalankan Backend

```bash
cd backend
npm install
npm start
```

Backend berjalan di `http://localhost:3001`.

### 3. Jalankan Frontend

```bash
cd frontend
npm install
npm run dev
```

Frontend berjalan di `http://localhost:5173`. Buka URL tersebut di browser.

## Cara Kerja

### Cara Kerja Program C (`pda.c`)

Program ini mensimulasikan PDA dengan 3 state:

| State | Deskripsi                                         |
| ----- | ------------------------------------------------- |
| q0    | State awal — membaca huruf `a`, push `A` ke stack |
| q1    | Membaca huruf `b`, pop `A` dari stack             |
| q2    | State akhir (accept)                              |

**Aturan transisi:**

- Di state `q0`: jika baca `a` → push `A`, tetap di `q0`
- Di state `q0`: jika baca `b` → pindah ke `q1`, pop `A`
- Di state `q1`: jika baca `b` → pop `A`, tetap di `q1`
- Jika semua input habis dan stack hanya berisi `Z` (simbol awal) → **ACCEPTED**
- Selain itu → **REJECTED**

**Contoh eksekusi untuk input "aabb":**

```
STEP 0 q0 aabb Z        ← Kondisi awal, stack berisi Z
STEP 1 q0 abb AZ        ← Baca 'a', push A
STEP 2 q0 bb AAZ        ← Baca 'a', push A
STEP 3 q1 b AZ          ← Baca 'b', pop A
STEP 4 q1 ε Z           ← Baca 'b', pop A
STEP 5 q2 ε Z           ← Input habis, stack hanya Z → Accept
ACCEPTED
```

## Contoh Input

| Input    | Hasil    | Alasan                                              |
| -------- | -------- | --------------------------------------------------- |
| `ab`     | Accepted | 1 huruf a, 1 huruf b                                |
| `aabb`   | Accepted | 2 huruf a, 2 huruf b                                |
| `aaabbb` | Accepted | 3 huruf a, 3 huruf b                                |
| `aab`    | Rejected | Jumlah a ≠ jumlah b                                 |
| `abb`    | Rejected | Jumlah a ≠ jumlah b                                 |
| `abab`   | Rejected | Urutan tidak valid (b muncul sebelum semua a habis) |
