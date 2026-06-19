# Kelompok 12

- Aminudin Wijaya 5025241242
- Nabil Irawan 5025241231
- Farras Nazhif Pratikno 5025241260

# Penjelasan Praktikum 1

## Token yang dipakai

| Token             | Contoh                         |
| ----------------- | ------------------------------ |
| `RESERVED WORD`   | `int`, `if`, `while`, `return` |
| `VARIABLE`        | `x` (diikuti `=`)              |
| `IDENTIFIER`      | `x` (tanpa `=`)                |
| `SYMBOL`          | `;` `(` `)` `{` `}`            |
| `OPERATOR`        | `==` `!=` `<=` `&&` `++`       |
| `MATH EXPRESSION` | `a + b`, `x * y`               |
| `VALUE`           | `10`, `"hello"`, `'A'`         |
| `INTEGER NUMBER`  | `42`                           |
| `FLOAT NUMBER`    | `3.14`                         |
| `STRING LITERAL`  | `"hello world"`                |
| `CHAR LITERAL`    | `'A'`                          |
| `COMMENT`         | `// ...` atau `/* ... */`      |

---

## Fungsi Utama

| Fungsi                  | Tugas                                 |
| ----------------------- | ------------------------------------- |
| `isKeyword(str)`        | Cek apakah string adalah keyword C    |
| `isSymbol(c)`           | Cek apakah karakter adalah simbol     |
| `isOperator(c)`         | Cek apakah karakter adalah operator   |
| `isMathExpression(str)` | Cek apakah string mengandung operator |
| `trim(str)`             | Hapus spasi di awal dan akhir string  |

---

## Contoh

**Input:**

```c
int x = a + b;
if (x != 0 && x >= 5) {
    // cek nilai
}
```

**Output:**

```
int:RESERVED WORD
x:VARIABLE
=:SYMBOL
a + b:MATH EXPRESSION
;:SYMBOL
if:RESERVED WORD
(:SYMBOL
x:IDENTIFIER
!=:OPERATOR
0:INTEGER NUMBER
&&:OPERATOR
x:IDENTIFIER
>=:OPERATOR
5:INTEGER NUMBER
):SYMBOL
{:SYMBOL
// cek nilai:COMMENT
}:SYMBOL
```
