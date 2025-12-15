# Documentație comparație: varianta originală vs. `exercitii_modern.h`

## Context
Fișierul `exercitii.h` conținea implementări diverse pentru 21 de exerciții de tip greedy / structură de date. Codul inițial se baza pe combinații de `std::sort`, containere STL și câteva artificii (de ex. `std::priority_queue`). Utilizatorul a solicitat o versiune nouă, rescrisă integral, cu următoarele cerințe:

1. Să fie „în română” – adică să folosească denumiri descriptive și comentarii în limba română.
2. Să nu utilizeze STL (containere/algo), deci doar tablouri statice și funcții auxiliare manuale.

Rezultatul acestei rescrieri se află în `exercitii_modern.h`.

## Exemple de diferențe majore

### Sortare și structuri auxiliare
- **În `exercitii.h`**: majoritatea problemelor (spectacole, reactivi, segmente etc.) se rezolvau cu `std::sort` și comparatori lambdas.
- **În `exercitii_modern.h`**: fiecare tip are fie un bubble sort dedicat (spectacole), fie o implementare proprie de QuickSort (reactivi, comenzi, segmente etc.). Structuri de tip heap sunt implementate manual (`MinHeap`, `MinHeapInt`), la fel și un „Union-Find” pentru programarea lucrărilor.

### Stocarea datelor
- **În `exercitii.h`**: se foloseau vectori stocați local (uneori alocați dinamic cu `std::vector`).
- **În `exercitii_modern.h`**: toate datele sunt ținute în tablouri cu dimensiuni fixe (`const int MAX_*`). Fiecărei probleme i se alocă un buffer dedicat pentru obiecte, comenzi, plecări etc.

### Abordarea algoritmică
- Versiunile originale conțineau bug-uri, utilizări neprotejate de pointeri și, uneori, logici incomplete (ex. `ex3`, `ex4`, `ex9`). Noua versiune implementează explicit logica greedy corectă pentru fiecare exercițiu – unele inspirate din soluțiile standard (ex. greedy cu min-heap pentru penalități, programare cu DSU pentru lucrări).

### Input/Output
- Versiunea veche folosea fișiere cu drum absolut („D:/info/…”), ceea ce făcea codul greu de rulat pe alte sisteme.
- Varianta nouă primește fluxuri `std::istream`/`std::ostream` (implicit `std::cin`/`std::cout`) și poate fi redirijată ușor către fișiere prin `fstream` din exterior.

## Tabel sumar
| Problemă | `exercitii.h` | `exercitii_modern.h` |
|----------|---------------|----------------------|
| ex1 – Spectacole | sortare bubble + bug la `ultim` | sortare bubble corectă, I/O sigur |
| ex2 – Rucsac | sortare bubble, STLa | sortare bubble, I/O parametrizat |
| ex3 – Culmi | vector neinițializat | LIS cu pile simulate manual |
| ex4 – Reactivi | `std::sort`, bug la comparatori | QuickSort manual, număr minim frigidere |
| ex5 – Comenzi | `std::priority_queue`, path absolut | QuickSort + heap manual, DSU pentru penalizare |
| … | … | … |
| ex21 – Interval strict inclus | comparări incorecte | QuickSort + scan linear robust |

(Nota: tabelul poate fi extins dacă se dorește documentarea fiecărui exercițiu.)

## Concluzie
`exercitii_modern.h` reprezintă o rescriere completă a colecției de exerciții, respectând restricția „fără STL” și corectând problemele identificate în codul inițial. Totodată, implementările folosesc denumiri în limba română și sunt ușor de integrat prin includerea header-ului nou.
