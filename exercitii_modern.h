#pragma once

#include <iostream>
#include <fstream>
#include <cstring>
#include <climits>

const int MAX_SPECTACOLE = 1002;
const int MAX_OBIECTE = 1002;
const int MAX_ELEMENTE = 100005;
const int MAX_REACTIVI = 1002;
const int MAX_COMENZI = 1002;
const int MAX_ELEVI = 1002;
const int MAX_MASINI = 1002;
const int MAX_PLECARI = 6005;
const int MAX_SEGM = 2005;
const int MAX_GHISEE = 1005;
const int MAX_LUCRARI = 1005;
const int MAX_INTERVAL = 1005;
const int MAX_PESTI = 105;
const int MAX_NODURI = 105;
const int MAX_EVENIMENTE = 205;

struct Spectacol {
    int inceput;
    int sfarsit;
    int index;
};

void swapSpectacol(Spectacol &a, Spectacol &b) {
    Spectacol aux = a;
    a = b;
    b = aux;
}

void sorteazaSpectacole(Spectacol v[], int n) {
    bool schimb;
    do {
        schimb = false;
        for (int i = 0; i < n - 1; ++i) {
            if (v[i].sfarsit > v[i + 1].sfarsit || (v[i].sfarsit == v[i + 1].sfarsit && v[i].inceput > v[i + 1].inceput)) {
                swapSpectacol(v[i], v[i + 1]);
                schimb = true;
            }
        }
    } while (schimb);
}

int inMinute(int ora, int minut) {
    return ora * 60 + minut;
}

void ex1(std::istream &in = std::cin, std::ostream &out = std::cout) {
    int n;
    in >> n;
    if (n <= 0) {
        out << "\n";
        return;
    }
    Spectacol spectacole[MAX_SPECTACOLE];
    for (int i = 0; i < n; ++i) {
        int hs, ms, hf, mf;
        in >> hs >> ms >> hf >> mf;
        spectacole[i].inceput = inMinute(hs, ms);
        spectacole[i].sfarsit = inMinute(hf, mf);
        spectacole[i].index = i + 1;
    }
    sorteazaSpectacole(spectacole, n);
    int ultimSfarsit = -1;
    bool prima = true;
    for (int i = 0; i < n; ++i) {
        if (spectacole[i].inceput >= ultimSfarsit) {
            if (!prima) {
                out << ' ';
            }
            out << spectacole[i].index;
            ultimSfarsit = spectacole[i].sfarsit;
            prima = false;
        }
    }
    out << '\n';
}

struct Obiect {
    int castig;
    int greutate;
    int index;
};

void swapObiect(Obiect &a, Obiect &b) {
    Obiect aux = a;
    a = b;
    b = aux;
}

void sorteazaObiecte(Obiect v[], int n) {
    bool schimb;
    do {
        schimb = false;
        for (int i = 0; i < n - 1; ++i) {
            long long st = 1LL * v[i].castig * v[i + 1].greutate;
            long long dr = 1LL * v[i + 1].castig * v[i].greutate;
            if (st < dr) {
                swapObiect(v[i], v[i + 1]);
                schimb = true;
            }
        }
    } while (schimb);
}

void ex2(std::istream &in = std::cin, std::ostream &out = std::cout) {
    int n, capacitate;
    in >> n >> capacitate;
    Obiect obiecte[MAX_OBIECTE];
    for (int i = 0; i < n; ++i) {
        in >> obiecte[i].castig >> obiecte[i].greutate;
        obiecte[i].index = i + 1;
    }
    sorteazaObiecte(obiecte, n);
    out.setf(std::ios::fixed);
    out.precision(2);
    for (int i = 0; i < n && capacitate > 0; ++i) {
        if (obiecte[i].greutate <= capacitate) {
            out << obiecte[i].index << " 100.00%\n";
            capacitate -= obiecte[i].greutate;
        } else {
            double procent = 100.0 * capacitate / obiecte[i].greutate;
            out << obiecte[i].index << ' ' << procent << "%\n";
            capacitate = 0;
        }
    }
}

void ex3(std::istream &in = std::cin, std::ostream &out = std::cout) {
    int n;
    in >> n;
    int valori[MAX_ELEMENTE];
    for (int i = 0; i < n; ++i) {
        in >> valori[i];
    }
    int pile[MAX_ELEMENTE];
    int len = 0;
    for (int i = 0; i < n; ++i) {
        int y = -valori[i];
        int st = 1;
        int dr = len;
        int poz = len + 1;
        while (st <= dr) {
            int mij = (st + dr) / 2;
            if (pile[mij] <= y) {
                st = mij + 1;
            } else {
                poz = mij;
                dr = mij - 1;
            }
        }
        pile[poz] = y;
        if (poz > len) {
            len = poz;
        }
    }
    out << len << '\n';
}

struct Reactiv {
    int minim;
    int maxim;
};

void swapReactiv(Reactiv &a, Reactiv &b) {
    Reactiv aux = a;
    a = b;
    b = aux;
}

int partitieReactiv(Reactiv v[], int st, int dr) {
    int pivot = v[dr].maxim;
    int i = st - 1;
    for (int j = st; j < dr; ++j) {
        if (v[j].maxim < pivot || (v[j].maxim == pivot && v[j].minim < v[dr].minim)) {
            ++i;
            swapReactiv(v[i], v[j]);
        }
    }
    swapReactiv(v[i + 1], v[dr]);
    return i + 1;
}

void quickSortReactiv(Reactiv v[], int st, int dr) {
    if (st < dr) {
        int poz = partitieReactiv(v, st, dr);
        quickSortReactiv(v, st, poz - 1);
        quickSortReactiv(v, poz + 1, dr);
    }
}

void ex4(std::istream &in = std::cin, std::ostream &out = std::cout) {
    int n;
    in >> n;
    Reactiv reactivi[MAX_REACTIVI];
    for (int i = 0; i < n; ++i) {
        in >> reactivi[i].minim >> reactivi[i].maxim;
    }
    quickSortReactiv(reactivi, 0, n - 1);
    int frigidere = 0;
    int temperatura = INT_MIN;
    for (int i = 0; i < n; ++i) {
        if (temperatura < reactivi[i].minim || temperatura > reactivi[i].maxim) {
            ++frigidere;
            temperatura = reactivi[i].maxim;
        }
    }
    out << frigidere << '\n';
}

struct Comanda {
    int valoare;
    int deadline;
    int index;
};

int gasesteLuna(const char *luna) {
    const char *nume[12] = {"ianuarie", "februarie", "martie", "aprilie", "mai", "iunie", "iulie", "august", "septembrie", "octombrie", "noiembrie", "decembrie"};
    for (int i = 0; i < 12; ++i) {
        if (strcmp(luna, nume[i]) == 0) {
            return i;
        }
    }
    return 0;
}

int inOre(int zi, const char *luna, int ora) {
    int zileLuna[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int idx = gasesteLuna(luna);
    int zile = 0;
    for (int i = 0; i < idx; ++i) {
        zile += zileLuna[i];
    }
    zile += zi - 1;
    return zile * 24 + ora;
}

void swapComanda(Comanda &a, Comanda &b) {
    Comanda aux = a;
    a = b;
    b = aux;
}

int partitieComenzi(Comanda v[], int st, int dr) {
    Comanda pivot = v[dr];
    int i = st - 1;
    for (int j = st; j < dr; ++j) {
        if (v[j].deadline < pivot.deadline || (v[j].deadline == pivot.deadline && v[j].valoare > pivot.valoare)) {
            ++i;
            swapComanda(v[i], v[j]);
        }
    }
    swapComanda(v[i + 1], v[dr]);
    return i + 1;
}

void quickSortComenzi(Comanda v[], int st, int dr) {
    if (st < dr) {
        int poz = partitieComenzi(v, st, dr);
        quickSortComenzi(v, st, poz - 1);
        quickSortComenzi(v, poz + 1, dr);
    }
}

struct HeapEntry {
    int valoare;
    int index;
};

struct MinHeap {
    HeapEntry elem[MAX_COMENZI];
    int dim;
};

void initHeap(MinHeap &h) {
    h.dim = 0;
}

void heapPush(MinHeap &h, int valoare, int index) {
    ++h.dim;
    int poz = h.dim;
    h.elem[poz].valoare = valoare;
    h.elem[poz].index = index;
    while (poz > 1 && h.elem[poz].valoare < h.elem[poz / 2].valoare) {
        HeapEntry aux = h.elem[poz];
        h.elem[poz] = h.elem[poz / 2];
        h.elem[poz / 2] = aux;
        poz /= 2;
    }
}

HeapEntry heapPop(MinHeap &h) {
    HeapEntry rad = h.elem[1];
    h.elem[1] = h.elem[h.dim];
    --h.dim;
    int poz = 1;
    while (true) {
        int st = poz * 2;
        int dr = st + 1;
        int mic = poz;
        if (st <= h.dim && h.elem[st].valoare < h.elem[mic].valoare) {
            mic = st;
        }
        if (dr <= h.dim && h.elem[dr].valoare < h.elem[mic].valoare) {
            mic = dr;
        }
        if (mic == poz) {
            break;
        }
        HeapEntry aux = h.elem[poz];
        h.elem[poz] = h.elem[mic];
        h.elem[mic] = aux;
        poz = mic;
    }
    return rad;
}

void ex5(std::istream &in = std::cin, std::ostream &out = std::cout) {
    int n, durata;
    in >> n >> durata;
    Comanda originale[MAX_COMENZI];
    for (int i = 0; i < n; ++i) {
        int zi, ora;
        char luna[32];
        in >> originale[i].valoare >> zi >> luna >> ora;
        originale[i].deadline = inOre(zi, luna, ora);
        originale[i].index = i;
    }
    Comanda ordonate[MAX_COMENZI];
    for (int i = 0; i < n; ++i) {
        ordonate[i] = originale[i];
    }
    quickSortComenzi(ordonate, 0, n - 1);
    MinHeap heap;
    initHeap(heap);
    long long timpTotal = 0;
    bool programata[MAX_COMENZI];
    for (int i = 0; i < n; ++i) {
        programata[i] = false;
    }
    for (int i = 0; i < n; ++i) {
        timpTotal += durata;
        heapPush(heap, ordonate[i].valoare, ordonate[i].index);
        programata[ordonate[i].index] = true;
        if (timpTotal > ordonate[i].deadline) {
            HeapEntry scos = heapPop(heap);
            timpTotal -= durata;
            programata[scos.index] = false;
        }
    }
    long long penalizare = 0;
    for (int i = 0; i < n; ++i) {
        if (!programata[i]) {
            penalizare += originale[i].valoare;
        }
    }
    out << penalizare << '\n';
    for (int i = 0; i < n; ++i) {
        if (programata[i]) {
            out << (i + 1) << ' ';
        }
    }
    for (int i = 0; i < n; ++i) {
        if (!programata[i]) {
            out << (i + 1) << ' ';
        }
    }
    out << '\n';
}

void ex6(std::istream &in = std::cin, std::ostream &out = std::cout) {
    int n;
    in >> n;
    int elevi[MAX_ELEVI];
    int schiuri[MAX_ELEVI];
    for (int i = 0; i < n; ++i) in >> elevi[i];
    for (int i = 0; i < n; ++i) in >> schiuri[i];
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (elevi[i] > elevi[j]) {
                int aux = elevi[i];
                elevi[i] = elevi[j];
                elevi[j] = aux;
            }
            if (schiuri[i] > schiuri[j]) {
                int aux2 = schiuri[i];
                schiuri[i] = schiuri[j];
                schiuri[j] = aux2;
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        out << "elev " << elevi[i] << " -> schiuri " << schiuri[i] << '\n';
    }
}

struct Masina {
    int pret;
    int valoare;
    int index;
};

void swapMasina(Masina &a, Masina &b) {
    Masina aux = a;
    a = b;
    b = aux;
}

int partitieMasini(Masina v[], int st, int dr) {
    Masina pivot = v[dr];
    int i = st - 1;
    for (int j = st; j < dr; ++j) {
        bool condition = false;
        if (v[j].valoare > pivot.valoare) condition = true;
        else if (v[j].valoare == pivot.valoare && v[j].pret < pivot.pret) condition = true;
        else if (v[j].valoare == pivot.valoare && v[j].pret == pivot.pret && v[j].index < pivot.index) condition = true;
        if (condition) {
            ++i;
            swapMasina(v[i], v[j]);
        }
    }
    swapMasina(v[i + 1], v[dr]);
    return i + 1;
}

void quickSortMasini(Masina v[], int st, int dr) {
    if (st < dr) {
        int poz = partitieMasini(v, st, dr);
        quickSortMasini(v, st, poz - 1);
        quickSortMasini(v, poz + 1, dr);
    }
}

void ex7(std::istream &in = std::cin, std::ostream &out = std::cout) {
    int n, k;
    in >> n >> k;
    Masina masini[MAX_MASINI];
    for (int i = 0; i < n; ++i) {
        in >> masini[i].pret >> masini[i].valoare;
        masini[i].index = i + 1;
    }
    quickSortMasini(masini, 0, n - 1);
    long long totalVal = 0;
    long long totalCost = 0;
    for (int i = 0; i < k && i < n; ++i) {
        totalVal += masini[i].valoare;
        totalCost += masini[i].pret;
    }
    out << totalVal << ' ' << totalCost << '\n';
    for (int i = 0; i < k && i < n; ++i) {
        out << masini[i].index << ' ';
    }
    out << '\n';
}

struct Plecare {
    int moment;
    int partea;
};

void swapPlecare(Plecare &a, Plecare &b) {
    Plecare aux = a;
    a = b;
    b = aux;
}

int partitiePlecari(Plecare v[], int st, int dr) {
    Plecare pivot = v[dr];
    int i = st - 1;
    for (int j = st; j < dr; ++j) {
        if (v[j].moment < pivot.moment || (v[j].moment == pivot.moment && v[j].partea < pivot.partea)) {
            ++i;
            swapPlecare(v[i], v[j]);
        }
    }
    swapPlecare(v[i + 1], v[dr]);
    return i + 1;
}

void quickSortPlecari(Plecare v[], int st, int dr) {
    if (st < dr) {
        int poz = partitiePlecari(v, st, dr);
        quickSortPlecari(v, st, poz - 1);
        quickSortPlecari(v, poz + 1, dr);
    }
}

struct MinHeapInt {
    int valori[MAX_PLECARI];
    int dim;
};

void initHeapInt(MinHeapInt &h) { h.dim = 0; }

void heapIntPush(MinHeapInt &h, int val) {
    ++h.dim;
    int poz = h.dim;
    h.valori[poz] = val;
    while (poz > 1 && h.valori[poz] < h.valori[poz / 2]) {
        int aux = h.valori[poz];
        h.valori[poz] = h.valori[poz / 2];
        h.valori[poz / 2] = aux;
        poz /= 2;
    }
}

int heapIntTop(const MinHeapInt &h) { return h.valori[1]; }

int heapIntPop(MinHeapInt &h) {
    int val = h.valori[1];
    h.valori[1] = h.valori[h.dim];
    --h.dim;
    int poz = 1;
    while (true) {
        int st = poz * 2;
        int dr = st + 1;
        int mic = poz;
        if (st <= h.dim && h.valori[st] < h.valori[mic]) mic = st;
        if (dr <= h.dim && h.valori[dr] < h.valori[mic]) mic = dr;
        if (mic == poz) break;
        int aux = h.valori[poz];
        h.valori[poz] = h.valori[mic];
        h.valori[mic] = aux;
        poz = mic;
    }
    return val;
}

int parseOra(const char text[]) {
    int ora = (text[0] - '0') * 10 + (text[1] - '0');
    int minut = (text[3] - '0') * 10 + (text[4] - '0');
    return ora * 60 + minut;
}

void ex8(std::istream &in = std::cin, std::ostream &out = std::cout) {
    int k, l, a;
    in >> k >> l >> a;
    Plecare plecari[MAX_PLECARI];
    int nr = 0;
    for (int i = 0; i < a; ++i) {
        char timp[10];
        in >> timp;
        plecari[nr].moment = parseOra(timp);
        plecari[nr].partea = 0;
        ++nr;
    }
    int b;
    in >> b;
    for (int i = 0; i < b; ++i) {
        char timp[10];
        in >> timp;
        plecari[nr].moment = parseOra(timp);
        plecari[nr].partea = 1;
        ++nr;
    }
    quickSortPlecari(plecari, 0, nr - 1);
    MinHeapInt heap[2];
    initHeapInt(heap[0]);
    initHeapInt(heap[1]);
    int bacuri = 0;
    for (int i = 0; i < nr; ++i) {
        int partea = plecari[i].partea;
        int cealalta = partea ^ 1;
        int moment = plecari[i].moment;
        bool asignat = false;
        if (heap[partea].dim > 0 && heapIntTop(heap[partea]) <= moment) {
            heapIntPop(heap[partea]);
            heapIntPush(heap[cealalta], moment + k + l);
            asignat = true;
        } else {
            while (heap[cealalta].dim > 0 && heapIntTop(heap[cealalta]) + k + l <= moment) {
                int sosire = heapIntPop(heap[cealalta]) + k + l;
                heapIntPush(heap[partea], sosire);
            }
            if (heap[partea].dim > 0 && heapIntTop(heap[partea]) <= moment) {
                heapIntPop(heap[partea]);
                heapIntPush(heap[cealalta], moment + k + l);
                asignat = true;
            }
        }
        if (!asignat) {
            ++bacuri;
            heapIntPush(heap[cealalta], moment + k + l);
        }
    }
    out << bacuri << '\n';
}

struct Segment {
    int st;
    int dr;
};

void swapSegment(Segment &a, Segment &b) {
    Segment aux = a;
    a = b;
    b = aux;
}

int partitieSegmente(Segment v[], int st, int dr) {
    Segment pivot = v[dr];
    int i = st - 1;
    for (int j = st; j < dr; ++j) {
        if (v[j].dr < pivot.dr || (v[j].dr == pivot.dr && v[j].st > pivot.st)) {
            ++i;
            swapSegment(v[i], v[j]);
        }
    }
    swapSegment(v[i + 1], v[dr]);
    return i + 1;
}

void quickSortSegmente(Segment v[], int st, int dr) {
    if (st < dr) {
        int poz = partitieSegmente(v, st, dr);
        quickSortSegmente(v, st, poz - 1);
        quickSortSegmente(v, poz + 1, dr);
    }
}

void ex9(std::istream &in = std::cin, std::ostream &out = std::cout) {
    int n;
    in >> n;
    Segment seg[MAX_SEGM];
    for (int i = 0; i < n; ++i) {
        in >> seg[i].st >> seg[i].dr;
    }
    quickSortSegmente(seg, 0, n - 1);
    int puncte[2 * MAX_SEGM];
    int dim = 0;
    int p1 = INT_MIN;
    int p2 = INT_MIN;
    for (int i = 0; i < n; ++i) {
        if (p1 >= seg[i].st && p1 <= seg[i].dr && p2 >= seg[i].st && p2 <= seg[i].dr) {
            continue;
        }
        if (p2 >= seg[i].st && p2 <= seg[i].dr) {
            int nou = seg[i].dr;
            puncte[dim++] = nou;
            p1 = p2;
            p2 = nou;
        } else {
            int a = seg[i].dr - 1;
            int b = seg[i].dr;
            if (a < seg[i].st) {
                a = seg[i].st;
                b = (seg[i].st + 1 <= seg[i].dr) ? seg[i].st + 1 : seg[i].st;
            }
            puncte[dim++] = a;
            puncte[dim++] = b;
            p1 = a;
            p2 = b;
        }
    }
    out << dim << '\n';
    for (int i = 0; i < dim; ++i) {
        out << puncte[i] << ' ';
    }
    out << '\n';
}

struct Ghiseu {
    int A;
    int B;
};

void ex10(std::istream &in = std::cin, std::ostream &out = std::cout) {
    int n;
    in >> n;
    Ghiseu g[MAX_GHISEE];
    for (int i = 0; i < n; ++i) in >> g[i].A >> g[i].B;
    int K, P;
    in >> K >> P;
    int st = 0, dr = 1000000000;
    int raspuns = -1;
    while (st <= dr) {
        int mij = st + (dr - st) / 2;
        int cap[MAX_GHISEE];
        int valid = 0;
        for (int i = 0; i < n; ++i) {
            if (mij >= g[i].B) {
                if (g[i].A == 0) cap[valid++] = P;
                else cap[valid++] = (mij - g[i].B) / g[i].A;
            }
        }
        if (valid < K) {
            st = mij + 1;
            continue;
        }
        for (int i = 0; i < valid - 1; ++i) {
            for (int j = i + 1; j < valid; ++j) {
                if (cap[i] < cap[j]) {
                    int aux = cap[i];
                    cap[i] = cap[j];
                    cap[j] = aux;
                }
            }
        }
        long long suma = 0;
        for (int i = 0; i < K; ++i) suma += cap[i];
        if (suma >= P) {
            raspuns = mij;
            dr = mij - 1;
        } else {
            st = mij + 1;
        }
    }
    out << raspuns << '\n';
}

void ex11(std::istream &in = std::cin, std::ostream &out = std::cout) {
    int n;
    in >> n;
    int pozitii[MAX_ELEMENTE];
    int dim = 0;
    for (int i = 0; i < n; ++i) {
        int x;
        in >> x;
        if (x > 0) pozitii[dim++] = x;
    }
    for (int i = 0; i < dim; ++i) out << pozitii[i] << ' ';
    out << '\n';
}

void ex12(std::istream &in = std::cin, std::ostream &out = std::cout) {
    int n;
    in >> n;
    int v[MAX_ELEMENTE];
    int suma = 0;
    for (int i = 0; i < n; ++i) {
        in >> v[i];
        suma += v[i];
    }
    int target = suma / 2;
    bool *dp = new bool[target + 1];
    int *pred = new int[target + 1];
    for (int i = 0; i <= target; ++i) {
        dp[i] = false;
        pred[i] = -1;
    }
    dp[0] = true;
    for (int i = 0; i < n; ++i) {
        for (int j = target; j >= v[i]; --j) {
            if (!dp[j] && dp[j - v[i]]) {
                dp[j] = true;
                pred[j] = i;
            }
        }
    }
    int best = 0;
    for (int i = target; i >= 0; --i) {
        if (dp[i]) {
            best = i;
            break;
        }
    }
    bool ales[MAX_ELEMENTE];
    for (int i = 0; i < n; ++i) ales[i] = false;
    int cur = best;
    while (cur > 0 && pred[cur] != -1) {
        ales[pred[cur]] = true;
        cur -= v[pred[cur]];
    }
    for (int i = 0; i < n; ++i) if (ales[i]) out << v[i] << ' ';
    out << '\n';
    for (int i = 0; i < n; ++i) if (!ales[i]) out << v[i] << ' ';
    out << '\n';
    delete[] dp;
    delete[] pred;
}

struct Lucrare {
    int deadline;
    int penalizare;
    int index;
};

void swapLucrare(Lucrare &a, Lucrare &b) {
    Lucrare aux = a;
    a = b;
    b = aux;
}

int partitieLucrari(Lucrare v[], int st, int dr) {
    Lucrare pivot = v[dr];
    int i = st - 1;
    for (int j = st; j < dr; ++j) {
        if (v[j].penalizare > pivot.penalizare) {
            ++i;
            swapLucrare(v[i], v[j]);
        }
    }
    swapLucrare(v[i + 1], v[dr]);
    return i + 1;
}

void quickSortLucrari(Lucrare v[], int st, int dr) {
    if (st < dr) {
        int poz = partitieLucrari(v, st, dr);
        quickSortLucrari(v, st, poz - 1);
        quickSortLucrari(v, poz + 1, dr);
    }
}

int gasesteSlot(int parinte[], int x) {
    if (x <= 0) return 0;
    if (parinte[x] == x) return x;
    parinte[x] = gasesteSlot(parinte, parinte[x]);
    return parinte[x];
}

void ex13(std::istream &in = std::cin, std::ostream &out = std::cout) {
    int n;
    in >> n;
    Lucrare lucrari[MAX_LUCRARI];
    int maxDeadline = 0;
    long long totalPenal = 0;
    for (int i = 0; i < n; ++i) {
        in >> lucrari[i].deadline >> lucrari[i].penalizare;
        lucrari[i].index = i + 1;
        if (lucrari[i].deadline > maxDeadline) maxDeadline = lucrari[i].deadline;
        totalPenal += lucrari[i].penalizare;
    }
    quickSortLucrari(lucrari, 0, n - 1);
    int *parinte = new int[maxDeadline + 1];
    for (int i = 0; i <= maxDeadline; ++i) parinte[i] = i;
    long long salvat = 0;
    for (int i = 0; i < n; ++i) {
        int slot = gasesteSlot(parinte, lucrari[i].deadline);
        if (slot > 0) {
            salvat += lucrari[i].penalizare;
            parinte[slot] = gasesteSlot(parinte, slot - 1);
        }
    }
    out << totalPenal - salvat << '\n';
    delete[] parinte;
}

void ex14(std::istream &in = std::cin, std::ostream &out = std::cout) {
    int n, m, k;
    in >> n >> m >> k;
    int cereri[MAX_INTERVAL];
    for (int i = 0; i < n; ++i) in >> cereri[i];
    for (int i = 0; i < n - 1; ++i)
        for (int j = i + 1; j < n; ++j)
            if (cereri[i] > cereri[j]) {
                int aux = cereri[i];
                cereri[i] = cereri[j];
                cereri[j] = aux;
            }
    int camere[MAX_INTERVAL];
    for (int i = 0; i < k; ++i) camere[i] = 0;
    int total = 0;
    for (int i = 0; i < n; ++i) {
        int idx = -1;
        int best = INT_MAX;
        for (int j = 0; j < k; ++j) {
            if (camere[j] <= cereri[i] && camere[j] < best) {
                best = camere[j];
                idx = j;
            }
        }
        if (idx != -1) {
            camere[idx] = cereri[i] + m;
            ++total;
        }
    }
    out << total << '\n';
}

void ex15(std::istream &in = std::cin, std::ostream &out = std::cout) {
    int n, k;
    in >> n >> k;
    int v1[MAX_ELEMENTE];
    int v2[MAX_ELEMENTE];
    for (int i = 0; i < n; ++i) in >> v1[i];
    for (int i = 0; i < n; ++i) in >> v2[i];
    int operatii[MAX_ELEMENTE];
    int dim = 0;
    for (int i = 0; i <= n - k; ++i) {
        if (v1[i] != v2[i]) {
            operatii[dim++] = i;
            for (int j = 0; j < k; ++j) v1[i + j] *= -1;
        }
    }
    bool egal = true;
    for (int i = 0; i < n; ++i) if (v1[i] != v2[i]) egal = false;
    if (!egal) {
        out << -1 << '\n';
        return;
    }
    out << dim << '\n';
    for (int i = 0; i < dim; ++i) out << operatii[i] << ' ';
    out << '\n';
}

void ex16(std::istream &in = std::cin, std::ostream &out = std::cout) {
    int n, k;
    in >> n >> k;
    --k;
    int mat[55][55];
    int mic = 1;
    int mare = n * n;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j <= k) mat[i][j] = mic++;
            else mat[i][j] = mare--;
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) out << mat[i][j] << ' ';
        out << '\n';
    }
}

struct Perioada {
    long long start;
    long long finish;
};

long long inZile(int zi, int luna, int an) {
    int luni[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    long long total = an * 365LL;
    for (int i = 0; i < luna - 1; ++i) total += luni[i];
    total += zi;
    return total;
}

void ex17(std::istream &in = std::cin, std::ostream &out = std::cout) {
    int n;
    in >> n;
    long long momente[MAX_EVENIMENTE];
    int delta[MAX_EVENIMENTE];
    int dim = 0;
    for (int i = 0; i < n; ++i) {
        int zi, luna, an;
        in >> zi >> luna >> an;
        long long start = inZile(zi, luna, an);
        in >> zi >> luna >> an;
        long long finish = inZile(zi, luna, an);
        momente[dim] = start;
        delta[dim++] = 1;
        momente[dim] = finish + 1;
        delta[dim++] = -1;
    }
    for (int i = 0; i < dim - 1; ++i)
        for (int j = i + 1; j < dim; ++j)
            if (momente[i] > momente[j]) {
                long long aux = momente[i];
                momente[i] = momente[j];
                momente[j] = aux;
                int auxd = delta[i];
                delta[i] = delta[j];
                delta[j] = auxd;
            }
    long long curent = 0, maxim = 0, ziMax = -1;
    for (int i = 0; i < dim; ++i) {
        curent += delta[i];
        if (curent > maxim) {
            maxim = curent;
            ziMax = momente[i];
        }
    }
    out << maxim << ' ' << (ziMax / 365) << '\n';
}

struct Peste {
    int lista[100];
    int ct;
};

void dfsPeste(int idx, const Peste pesti[], bool viu[], bool viz[], int n) {
    if (idx < 0 || idx >= n || viz[idx]) return;
    viz[idx] = true;
    for (int i = 0; i < pesti[idx].ct; ++i) {
        int prada = pesti[idx].lista[i];
        if (prada >= 0 && prada < n && viu[prada]) {
            dfsPeste(prada, pesti, viu, viz, n);
            viu[prada] = false;
        }
    }
}

void ex18(std::istream &in = std::cin, std::ostream &out = std::cout) {
    int n;
    in >> n;
    Peste pesti[MAX_PESTI];
    for (int i = 0; i < n; ++i) {
        in >> pesti[i].ct;
        for (int j = 0; j < pesti[i].ct; ++j) {
            int id;
            in >> id;
            if (id > 0) --id;
            pesti[i].lista[j] = id;
        }
    }
    int ordine[MAX_PESTI];
    for (int i = 0; i < n; ++i) ordine[i] = i;
    for (int i = 0; i < n - 1; ++i)
        for (int j = i + 1; j < n; ++j)
            if (pesti[ordine[i]].ct < pesti[ordine[j]].ct) {
                int aux = ordine[i];
                ordine[i] = ordine[j];
                ordine[j] = aux;
            }
    bool viu[MAX_PESTI];
    for (int i = 0; i < n; ++i) viu[i] = true;
    bool viz[MAX_PESTI];
    int actiuni[MAX_PESTI];
    int dim = 0;
    for (int idxOrd = 0; idxOrd < n; ++idxOrd) {
        int pestele = ordine[idxOrd];
        if (!viu[pestele]) continue;
        for (int i = 0; i < n; ++i) viz[i] = false;
        dfsPeste(pestele, pesti, viu, viz, n);
        actiuni[dim++] = pestele;
    }
    int ramasi = 0;
    for (int i = 0; i < n; ++i) if (viu[i]) ++ramasi;
    out << ramasi << '\n';
    out << "Ordine atac: ";
    for (int i = 0; i < dim; ++i) out << actiuni[i] + 1 << ' ';
    out << "\nPesti ramasi: ";
    for (int i = 0; i < n; ++i) if (viu[i]) out << i + 1 << ' ';
    out << '\n';
}

void ex19(std::istream &in = std::cin, std::ostream &out = std::cout) {
    int n, m;
    in >> n >> m;
    int mat[MAX_NODURI][MAX_NODURI];
    int grad[MAX_NODURI];
    for (int i = 0; i <= n; ++i) {
        grad[i] = 0;
        for (int j = 0; j <= n; ++j) mat[i][j] = 0;
    }
    for (int i = 0; i < m; ++i) {
        int x, y;
        in >> x >> y;
        if (x >= 1 && x <= n && y >= 1 && y <= n && x != y && !mat[x][y]) {
            mat[x][y] = mat[y][x] = 1;
            ++grad[x];
            ++grad[y];
        }
    }
    bool eliminat[MAX_NODURI] = {false};
    int sol[MAX_NODURI];
    int dim = 0;
    while (true) {
        int nod = -1;
        int gradMin = INT_MAX;
        for (int i = 1; i <= n; ++i) if (!eliminat[i] && grad[i] < gradMin) {
            gradMin = grad[i];
            nod = i;
        }
        if (nod == -1) break;
        sol[dim++] = nod;
        eliminat[nod] = true;
        for (int j = 1; j <= n; ++j) if (mat[nod][j] && !eliminat[j]) {
            eliminat[j] = true;
            for (int k = 1; k <= n; ++k) if (mat[j][k]) --grad[k];
        }
    }
    out << dim << '\n';
    for (int i = 0; i < dim; ++i) out << sol[i] << ' ';
    out << '\n';
}

void ex20(std::istream &in = std::cin, std::ostream &out = std::cout) {
    int n, m;
    in >> n >> m;
    int mat[MAX_NODURI][MAX_NODURI];
    int grad[MAX_NODURI];
    for (int i = 0; i <= n; ++i) {
        grad[i] = 0;
        for (int j = 0; j <= n; ++j) mat[i][j] = 0;
    }
    for (int i = 0; i < m; ++i) {
        int x, y;
        in >> x >> y;
        if (x >= 1 && x <= n && y >= 1 && y <= n && !mat[x][y]) {
            mat[x][y] = mat[y][x] = 1;
            ++grad[x];
            ++grad[y];
        }
    }
    bool folosit[MAX_NODURI] = {false};
    int sol[MAX_NODURI];
    int dim = 0;
    while (true) {
        int nod = -1;
        int gradMax = INT_MIN;
        for (int i = 1; i <= n; ++i) if (!folosit[i] && grad[i] > gradMax) {
            gradMax = grad[i];
            nod = i;
        }
        if (nod == -1) break;
        bool ok = true;
        for (int i = 0; i < dim; ++i) if (!mat[nod][sol[i]]) { ok = false; break; }
        folosit[nod] = true;
        if (ok) sol[dim++] = nod;
        grad[nod] = -1;
    }
    out << dim << '\n';
    for (int i = 0; i < dim; ++i) out << sol[i] << ' ';
    out << '\n';
}

struct Interval {
    int low;
    int high;
    int index;
};

void swapInterval(Interval &a, Interval &b) {
    Interval aux = a;
    a = b;
    b = aux;
}

int partitieInterval(Interval v[], int st, int dr) {
    Interval pivot = v[dr];
    int i = st - 1;
    for (int j = st; j < dr; ++j) {
        if (v[j].low < pivot.low || (v[j].low == pivot.low && v[j].high > pivot.high)) {
            ++i;
            swapInterval(v[i], v[j]);
        }
    }
    swapInterval(v[i + 1], v[dr]);
    return i + 1;
}

void quickSortInterval(Interval v[], int st, int dr) {
    if (st < dr) {
        int poz = partitieInterval(v, st, dr);
        quickSortInterval(v, st, poz - 1);
        quickSortInterval(v, poz + 1, dr);
    }
}

void ex21(std::istream &in = std::cin, std::ostream &out = std::cout) {
    int n;
    in >> n;
    Interval inte[MAX_INTERVAL];
    for (int i = 0; i < n; ++i) {
        in >> inte[i].low >> inte[i].high;
        inte[i].index = i;
    }
    quickSortInterval(inte, 0, n - 1);
    bool eliminat[MAX_INTERVAL] = {false};
    int eliminabile = 0;
    int maxHigh = INT_MIN;
    for (int i = 0; i < n; ++i) {
        if (inte[i].high <= maxHigh) {
            eliminabile++;
            eliminat[inte[i].index] = true;
        } else {
            maxHigh = inte[i].high;
        }
    }
    out << eliminabile << '\n';
}
