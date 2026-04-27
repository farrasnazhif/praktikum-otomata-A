# Penjelasan Praktikum 2 (FSM)

Praktikum 2 berisi implementasi program **Finite State Machine (FSM)** menggunakan bahasa Python. Mesin FSM ini dirancang untuk membaca input berupa string biner (hanya memuat karakter `0` dan `1`) dan mengevaluasi apakah string tersebut diterima (*accepted*) atau ditolak (*rejected*).

## Tujuan FSM
Program mesin otomatis ini dirancang khusus untuk mengenali pola string dengan 2 aturan utama:
1. String **harus berakhiran dengan angka `1`**.
2. String **tidak boleh mengandung angka `00`** (dua angka nol berturut-turut).

## Komponen FSM
Berdasarkan kode sumbernya, FSM didefinisikan dengan komponen berikut:
- **Himpunan State**: `{S, A, B, C}`
- **State Awal (Start State)**: `S`
- **State Akhir Diterima (Accept State)**: `B`
- **State Akhir Ditolak (Trap/Dead State)**: `C`
- **Alfabet Input**: `{'0', '1'}`

## Makna dari Setiap State
- **State `S` (Start)**: State kondisi awal ketika belum ada input karakter yang dibaca.
- **State `A`**: State ini dicapai ketika string saat ini berakhiran dengan tepat satu angka `0`. Pola terlarang (`00`) belum ditemukan.
- **State `B` (Accept)**: State ini dicapai ketika string saat ini berakhiran dengan angka `1`. Jika pembacaan input berakhir di state ini, string akan **DITERIMA** (*Accepted*) karena memenuhi semua syarat.
- **State `C` (Trap / Dead State)**: State ini dicapai ketika program mendeteksi adanya `00`. Sekali mesin masuk ke state ini, mesin tidak akan bisa keluar lagi (Trap di looping state `C`). Ini memastikan bahwa setiap string yang mengandung `00` pasti akan **DITOLAK**.

## Fungsi Transisi (Perpindahan State)
Aturan transisi dari satu state ke state lainnya adalah sebagai berikut:

| Current State | Input `0` | Input `1` |
| :---: | :---: | :---: |
| **S** | Pindah ke **A** | Pindah ke **B** |
| **A** | Pindah ke **C** | Pindah ke **B** |
| **B** | Pindah ke **A** | Pindah ke **B** |
| **C** | Tetap di **C** | Tetap di **C** |

## Cara Kerja Program
1. Saat program dijalankan, pengguna akan diminta memasukkan sebuah string biner (contoh: `10101`).
2. Program akan membaca setiap karakter (dari kiri ke kanan) dan berpindah dari state awal (`S`) menuju state berikutnya sesuai dengan fungsi transisi.
3. Selama proses membaca, program akan merekam dan menampilkan jalur perpindahan state (contoh jejak: `S -> B -> A -> B -> A -> B`).
4. Setelah seluruh input selesai dibaca, program mengecek di state manakah ia berhenti:
   - Jika berhenti di state **`B`**, maka program mencetak status **ACCEPTED**.
   - Jika berhenti di state **`S`**, **`A`**, atau **`C`**, program mencetak status **REJECTED**.
5. Jika ada karakter selain `0` atau `1` yang dimasukkan, program akan langsung memberhentikan proses dengan pesan error.
6. Program berjalan dalam *infinite loop* interaktif dan baru akan berhenti jika user menginputkan kata `exit` atau `quit`.
