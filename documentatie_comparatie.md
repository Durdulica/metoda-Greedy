# Comparație punct cu punct: `exercitii.h` vs `exercitii_modern.h`

| Exercițiu | Probleme în `exercitii.h` | Îmbunătățiri în `exercitii_modern.h` |
|-----------|---------------------------|--------------------------------------|
| **ex1** (Spectacole) | Sortare bubble ok, dar `ultim` setat cu operator `,` (mimând bug) și folosire directă a `cout`. | Sortare bubble menținută, dar `ultimSfarsit` setat explicit; funcția primește `std::istream`/`std::ostream` și produce listă corectă. |
| **ex2** (Rucsac fracț.) | Folosește STL implicit, output fixat la 100%, nu controlează precizia. | Tablouri statice, sortare manuală, output cu precizie `setprecision(2)` și percent calculat manual. |
| **ex3** (Culmi) | `nr` și `ultim` neinițializate; algoritm invalid. | Implementare corectă LIS cu pile (simulare `std::multiset`), fără STL. |
| **ex4** (Reactivi) | `std::sort` și comparator care nu tratează egalități, poate rata intervale. | QuickSort manual după `maxim`, greedy corect (temperatura setată pe `maxim`). |
| **ex5** (Comenzi Venus) | Folosește string-uri greșite, nu calculează corect deadline-urile, `priority_queue`. | QuickSort + heap manual; calculează orele din dată + lună; `programata[]` marchează ce comenzi sunt executate. |
| **ex6** (Instructor schi) | Folosește `std::sort`; output la `cout`. | Bubble sort manual pentru elevi/schiuri; output ordonat „elev X -> schiuri Y”. |
| **ex7** (Mașini) | `std::sort` după valoare; nu verifică clar costul minim. | QuickSort manual cu criteriu: valoare desc, preț asc, index asc. |
| **ex8** (Bac) | Folosește `strtok`, combinații fragile; logică greu de urmărit. | Parsează `hh:mm`, folosește două heap-uri min manuale pentru bacuri pe ambele maluri; greedily reusește bacurile. |
| **ex9** (Segmente) | Implementare QuickSort greșită, nu asigură două puncte per segment; poate cădea în UB. | QuickSort corect + greedily adaugă 2 puncte din capătul drept dacă segmentul nu este acoperit. |
| **ex10** (Check-in) | Combinație de `std::sort` și `vector`; nu tratează bine cazurile cu `A = 0`. | Binary search manual pe timp, calcul capacități și sortare desc manuală; asigură `A=0` => capacitate nelimitată. |
| **ex11** (Submulțime pozitivă) | Filtrează doar numere pozitive, dar folosind `std::vector`. | Tablou static și afișare directă, tot fără STL. |
| **ex12** (Partajare minimă) | QuickSort și alocare inconsistentă; nu garantează reconstituirea subsetelor. | DP 0/1 manual cu `dp[j]` și `pred` pentru reconstrucție, respectând cerința. |
| **ex13** (Lucrări) | QuickSort greșit (`swap(lu[i],lu[++j])`), penalizare calculată informal. | QuickSort manual după penalizare desc + DSU simplu pentru sloturi (cronologic). |
| **ex14** (Hotel) | Bucle infinite (condiția `if (c[j] >= v[i])` cu `c[j] = 0` nu se satisface). | Sortare manuală + alocare greedy pe camere folosind valori minime; evită loop-uri infinite. |
| **ex15** (Flip semne) | Folosește vectori, fără validare finală. | Tablouri statice, verifică final dacă `v1 == v2`, altfel `-1`. |
| **ex16** (Matrice ordonată) | Hardcode `n = 5, k = 1`; nu citește input. | Primește `n`, `k` din stream și construiește matricea conform cerinței (colona k minimă). |
| **ex17** (Scriitori) | Folosește conversie greșită și numără incorect suprapunerile. | Transformă datele în „zile absolute”, folosește evenimente start/stop și sweep-line pentru max. |
| **ex18** (Pesti) | Recursie greșită (`mananca(p, i, …)` în loc de prada), marcaje incorecte. | Listă de prăzi convertită la indice zero-based, DFS corect cu marcaje `viz` și `viu`. |
| **ex19** (Set noduri neadiacente) | Folosește `INT_MAX`, dar nu actualizează corect gradele; pot rămâne noduri netestate. | Scanner greedy clar: alege nodul cu grad minim, elimină vecinii și actualizează gradele. |
| **ex20** (Clique) | Greedy rudimentar, nu păstrează compatibilitatea; bug-uri la `testat`/`grad`. | Greedy determinist: alege nod cu grad mare și verifică compatibilitatea cu cliqua curentă. |
| **ex21** (Intervale eliminate) | Sortarea se oprește la primul interval, nu deosebește corect cuprinderile. | Sortare manuală după `low` și `high` desc; parcurgere menține `maxHigh` și numără intervalele strict cuprinse. |

**Bonus**: Varianta nouă se livrează cu `tests.h`, `main.cpp` (runner), `.gitignore` complet și o documentație clară. |
