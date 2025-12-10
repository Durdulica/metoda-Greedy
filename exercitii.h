#ifndef EXERCITII_H
#define EXERCITII_H
#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>
using namespace std;

///Problema spectacolelor
//managerul artistic al unui festival tb. sa selecteze o multime cat mai ampla de spectacole ce pot fi jucate in
//singura sala pe care o are la dispozitie. Stiind ca i s-au propus n spectacole si pentru fiecare spectacol i
//i-a fost anuntat intervalul in care se poate desfasura(si,fi) (si repr ora si minutul de inceput, fi ora si minutul de final),
//scrieti un program care sa det. o lista cat mai ampla de spectacole care pot fi jucate
const int NMAX = 1002;
struct Spectacol {
    int ts, tf, nr;
};

void ex1() {
    Spectacol S[NMAX], aux;
    int n, hs, ms, hf, mf, schimb, ultim;
    ifstream fin("D:/info/c++/clion/metodaGreedy/exercitii.txt");
    fin >> n;

    for(int i = 1; i <= n; i++) {
        fin >> hs >> ms >> hf >> mf;
        S[i].ts = hs * 60 + ms;
        S[i].tf = hf * 60 + mf;
        S[i].nr = i;
    }

    do {
        schimb = 0;
        for(int i = 1; i < n; i++) {
            if(S[i].tf > S[i + 1].tf) {
                aux = S[i];
                S[i] = S[i + 1];
                S[i + 1] = aux;
                schimb = 1;
            }
        }
    }while(schimb != 0);

    cout << S[1].nr, ultim = 1;
    for(int i = 2; i <= n; i++) {
        if(S[i].ts >= S[ultim].tf) {
            cout << " " << S[i].nr;
            ultim = i;
        }
    }
}

///Problema rucsacului
//un hot neprevazator are la dispozitie un singur rucsac cu care poate transporta o greutate maxima Gmax. Hotul are de ales
//dintre n obiecte si, evident, intentioneaza sa obtina un castig maxim in urma singurului transport pe care il poate face.
//Cunoscand pentru fiecare obiect i greutatea gi si castigul ci pe care hotul l-ar obtine transportand obiectul respectiv
//in intregime, scrieti un program care sa det. o incarcare optima a rucsacului, in ipoteza ca hotul poate incarca in rucsac
//iruce oarte dubtr-un obiect

struct Obiect {
    int c, g, nr;
};

void ex2() {
    Obiect v[NMAX], aux;
    int n, Gmax, Gr, schimb, i;
    ifstream fin("D:/info/c++/clion/metodaGreedy/exercitii.txt");
    fin >> n >> Gmax;
    for(i = 1; i <= n; i++) {
        fin >> v[i].c >> v[i].g;
        v[i].nr = i;
    }

    do {
        schimb = 0;
        for(i = 1; i < n; i++) {
            if(v[i].c * v[i+1].g < v[i + 1].c * v[i].g) {
                aux = v[i];
                v[i] = v[i + 1];
                v[i + 1] = aux;
                schimb = 1;
            }
        }
    }while(schimb != 0);

    for(i = 1, Gr = Gmax; i <= n && v[i].g <= Gr; i++) {
        cout << v[i].nr << " 100%\n";
        Gr-=v[i].g;
    }

    if(i <= n && Gr) {
        cout << v[i].nr << " " << Gr*100.0/v[i].g << "%\n";
    }
}

///Culmi
//se considera un vector cu n(1<=n<=100000) componente nr. intregi. Sa se partitioneze acest vector in cat mai putine subsiruri
//str cresc.

void ex3() {
    ifstream fin("D:/info/c++/clion/metodaGreedy/exercitii.txt");
    int ultim[NMAX];
    int n, nr, crt, i, st, dr, mij;
    fin >> n;
    for(i = 0; i < n; i++) {
        fin >> crt;
        st = 0, dr = nr + 1;
        while(dr - st > 1) {
            mij = (st + dr) / 2;
            if(ultim[mij] >= crt) st = mij;
            else dr = mij;
        }
        ultim[dr] = crt;
        if(dr > nr)nr++;
    }

    cout << endl;
    cout << nr;
}

///Reactivi
//intr-un laborator de analize chimice se utilizeaza N reactivi. Se stie ca, pt. a evita accidentele sau deprecierea reactivilor,
//acestia trebuie sa fie stoacti in conditii de mediu speciale. Mai exact, pt. fiecare reactiv x se precizeaza intervalul
//[tmin, tmax] in care tb. sa se incadreze temp. de stocare a acestuia. Reactivii vor fi plasati in frigidere. Orice frigider are
//un dispozitiv cu ajutorul caruia putem stabili temp.(const) ce va fi in interiorul acestuia. Scrieti un program care sa det. nr min
//de frigidere necesare pt. stocarea reactivilor chimici

struct reactiv {
    int minx, maxx;
};

bool compar(reactiv a, reactiv b) {
    return a.maxx < b.maxx;
}

void ex4() {
    ifstream fin("D:/info/c++/clion/metodaGreedy/exercitii.txt");
    reactiv r[NMAX];
    int i, temp, n, nr;
    fin >> n;
    for(i = 1; i <= n; i++) {
        fin >> r[i].minx >> r[i].maxx;
    }
    sort(r + 1,r + n + 1, compar);

    nr = 1;
    temp = r[1].maxx;
    for(i = 2; i <= n; i++) {
        if(!(r[i].minx <= temp && temp <= r[i].maxx)) {
            nr++;
            temp = r[i].maxx;
        }
    }
    cout << nr << endl;
}

///Venus
//Casa de moda Venus l-a angajat pe robotul Vasile. Acesta poate executa orice comanda in exact T ore, indiferent de complexitatea
//acesteia. Casa de moda a lansat o campanie publicitara cu sloganul "Daca am intarziat, primesti produsul comandat gratis!". Campania
//si-a atins scopul, ca urmare casa a primit N comenzi. Pentru fiecare comanda sunt specificate valorile acesteia, precum si data si ora
//la care produsul comandat tb. sa fie gata de predare. Daca Vasile preda produsul exact la data si ora specificate in comanda(sau inainte)
//el incaseaza valoarea comenzii. Daca nu, el tot tb. sa execute comanda respective, dar nu va primi suma repr. val. ei. Numim planificare
//optimala succesiunea in care Vasile tb. sa execute cele N comenzi, a. i. pierderea sa fie minima.
//Scrieti un program care, cunoscand informatiile referitoare la cele N comenzi, det. pierderea minima, precum si o planificare optimala
//todo
char Luni[12][50] = {"ianuarie","februarie","martie","aprilie","mai","iunie","iulie","august","septembrie","octombrie","noiembrie","decembrie"};
int zl[12] = {31,29,31,30,31,30,31,31,30,31,30,31};
int sz[12];

struct Comanda {
    int v, p, nr, tc;
};

void ex5() {
    ifstream fin("D:/info/c++/clion/metodaGreedy/exercitii.txt");
    int n, lg, t, pmin;
    Comanda C[NMAX], aux;
    int L[NMAX];
    int i, zi, ora, k, j, sch;
    char luna[50];
    fin >> n >> t;
    for(i = 1; i < 12; i++) {
        sz[i] = sz[i-1] + zl[i-1];
    }
    for(i = 1; i <= n; i++) {
        fin >> C[i].v >> zi >> luna >> ora;
        for(j = 0; j < 12; j++) {
            if(!strcmp(Luni[j], luna)) break;
            C[i].p = (sz[j]+zi-1)*24 + ora;
            C[i].nr = i;
        }
    }

    do {
        sch = 0;
        for(i =1; i < n; i++) {
            if(C[i].v < C[i+1].v) {
                aux = C[i];
                C[i] = C[i+1];
                C[i+1] = aux;
                sch = 1;
            }
        }
    }while(sch);

    for(i = 1; i <= n && t > C[i].p; i++)
        C[i].tc = -1;
    if(i <= n) {
        L[1] = i;
        lg = 1;
        C[i].tc = t;
        for(i++; i <= n; i++) {
            for(j = lg; j >= 1 && C[L[j]].tc + t <= C[L[j]].p && C[L[j]].p >= C[i].p; j--);
            if(j == 0 && C[i].p >= t || C[L[j]].p <= C[i].p && C[L[j]].tc + t <= C[i].p) {
                for(k = lg; k > j; k--) {
                    C[L[k]].tc += t;
                    L[k+1] = L[k];
                }
                lg++;
                L[j+1] = i;
                C[i].tc = C[L[j]].tc + t;
            }else {
                C[i].tc = -1;
            }
        }
    }
    pmin = 0;
    for(i = 1; i <= n; i++) {
        if(C[i].tc == -1) pmin += C[i].v;
    }
    cout << pmin << endl;
    for(i = 1; i <= lg; i++) {
        cout << C[L[i]].nr << " ";
    }
    for(i = 1; i <= n; i++) {
        if(C[i].tc == -1) {
            cout << C[i].nr << " ";
        }
    }
    cout << endl;
}

///Problema instructorului de schi
//un instructor are la dispozitie n perechi de schiuri pe care tb. sa le distribuie la n elevi incepatori. Scrieti un program
//care sa distribuie cele n perechi de schiuri a. i. suma dif. absolute dintre inaltimea elevului si lungimea schiurilor atribuite sa fie min.

void afisVec(int v[], int n) {
    for(int i = 0; i < n; i++) {
        cout << v[i] << " ";
    }
    cout << endl;
}

void ex6() {
    ifstream fin("D:/info/c++/clion/metodaGreedy/exercitii.txt");
    int n, i;
    int elevi[100], schiuri[100]; //cm
    fin >> n;

    for(i = 0; i < n; i++) {
        fin >> elevi[i];
    }
    for(i = 0; i < n; i++) {
        fin >> schiuri[i];
    }

    sort(elevi, elevi + n);
    sort(schiuri, schiuri + n);

    for(i = 0; i < n; i++) {
        cout << "elev: " << elevi[i] << ", schiuri: " << schiuri[i] << endl;
    }
}

//un om bogat vrea sa achizitioneze k masini pentru colectia sa dintr-o lista de n masini. Fiecare masina are un cost si
//o valoare de colectie. Omul doreste sa cumpere k masini dintre cele n, a. i. val. totala de colectie a acestora sa fie
//maxima. Dar, evident, vrea sa faca acest lucru cu cat mai putini bani. Scrieti un program care sa il ajute pe om.

struct Masina {
    int pret;
    int val;
    int nr;
};

bool cmp(Masina a, Masina b) {
    if(a.val != b.val) return a.val > b.val;
    return a.pret < b.pret;
}

void ex7() {
    int n, k, i;
    Masina m[1000];
    ifstream fin("D:/info/c++/clion/metodaGreedy/exercitii.txt");
    fin >> n >> k;
    for(i = 0; i < n; i++) {
        fin >> m[i].pret >> m[i].val;
        m[i].nr = i + 1;
    }

    sort(m, m + n, cmp);

    int pt = 0, vt = 0;

    for(i = 0; i < k; i++) {
        pt += m[i].pret;
        vt += m[i].val;
    }

    cout << vt << " " << pt << endl;
    for(i = 0; i < k; i++) {
        cout << m[i].nr << " ";
    }
}

///bac
//Orasul  A este situat pe un mal al Dunarii, iar orasul B pe celalalt mal. Leg. dintre orasele A si B se poate realiza cu bacul
//Compania X a primit autorizatie de trans. fluvial, cu conditia sa asigure si leg. cu bacul intre orasele A si B. Primariile celor
//doua orase au stabilit de comun acord programul sosiri-plecari pe care tb. sa il respecte compania X. Sa se det. nr. min. de bacuri
//necesare commpaniei, a. i. programul sa poata fi respectat. Se da K-durata traversarii, L-durara de imbarcare si debarcare, expr. in min.
//A-nr. de plecari din orasul A, urmat de A linii ce contin timpul plecarii din orasul A
//B-nr. de plecari din orasul B, urmat de B linii ce contin timpul plecarii din orasul B

struct Plecari {
    int ora = 0;
    int partea = 0;
};

bool cmp2(Plecari a, Plecari b) {
    return a.ora < b.ora;
}

void ex8() {
    int k, l, a, b,nrPlecari;
    Plecari p[2880], bac[2880];
    ifstream fin("D:/info/c++/clion/metodaGreedy/exercitii.txt");
    fin >> k >> l >> a;
    for(nrPlecari = 0; nrPlecari < a; nrPlecari++) {
        char nr[10];
        fin >> nr;
        char*aux = strtok(nr,":");
        p[nrPlecari].ora = atoi(aux) * 60;
        aux = strtok(NULL," ");
        p[nrPlecari].ora += atoi(aux);
        p[nrPlecari].partea = 1;
    }
    fin >> b;
    for(int j = 0; j < b; j++, nrPlecari++) {
        char nr[10];
        fin >> nr;
        char*aux = strtok(nr,":");
        p[nrPlecari].ora = atoi(aux) * 60;
        aux = strtok(NULL," ");
        p[nrPlecari].ora += atoi(aux);
        p[nrPlecari].partea = -1;
    }

    sort(p, p + nrPlecari, cmp2);

    int rez = 1;
    bac[0].ora = p[0].ora + k + l;
    if(p[0].partea == 1) {
        bac[0].partea = -1;
    }else {
        bac[0].partea = 1;
    }
    for(int i = 1; i < nrPlecari; i++) {
        int ok = 0;
        for(int j = 0; j < rez; j++) {
            if(ok == 1) {
                break;
            }
            if(bac[j].partea == p[i].partea || bac[j].partea == 0) {
                if(bac[j].ora <= p[i].ora) {
                    ok = 1;
                    bac[j].ora = p[i].ora + k + l;
                    bac[j].partea *= -1;
                }
            }else if(bac[j].partea * -1 == p[i].partea) {
                if(bac[j].ora + k  <= p[i].ora) {
                    ok = 1;
                    bac[j].ora = p[i].ora + k + l;
                }
            }
            else {
                cout << "Error" << endl << rez << endl;
                return;
            }
        }
        if(!ok) {
            bac[rez].ora = p[i].ora + k + l;
            bac[rez].partea = p[i].partea * -1;
            rez++;
        }
    }
    cout << rez;
}

///Segm
//se considera n segm inchise situate pe axa OX. Pt. fiecare segm se cunosc extremitatea initiala x si extremitatea finala y.
//Sa se det. o multime formata dintr-un nr. min. de pct. distincte de abscise intregi situate pe axa OX, cu propr. ca orice segm.
//contine c. p. 2 pct. din multime

struct segm {
    int x;
    int y;
    bool acoperit = false;
    int puncteIn = 0;
};

bool esteInSegm(segm a[], int poz,int punct) {
    return punct>=a[poz].x && punct <= a[poz].y ;
}

void adaugarePct(segm a[], int n, int punct) {
    for(int i = 0; i < n; i++) {
        if(esteInSegm(a, i, punct)) {
            a[i].puncteIn+=1;
            if(a[i].puncteIn == 2) {
                a[i].acoperit = true;
            }
        }
    }
}

void swap(int&i, int&j) {
    int aux = i;
    i = j;
    j = aux;
}

int part(segm a[], int l, int r) {
    int p, i, j;
    p = a[r].x;
    j = l - 1;
    for(i = 0; i < r; i++) {
        if(a[i].x <= p) {
            swap(i, j);
        }
    }
    return j;
}

void quickSort(segm a[], int l, int r) {
    int poz = part(a,l,r);
    if(l < poz - 1) quickSort(a,l, poz - 1);
    if(r > poz + 1) quickSort(a,poz + 1, r);
}

bool cmp3(segm a, segm b) {
    return a.x < b.x;
}

void ex9() {
    ifstream fin("D:/info/c++/clion/metodaGreedy/exercitii.txt");
    int n;
    fin >> n;
    segm a[n];
    for(int i = 0; i < n; i++) {
        fin >> a[i].x >> a[i].y;
    }

    quickSort(a, 0, n);

    int rez[100] = {}, dim = 0;
    for(int i = 0; i < n; i++) {
        if(!a[i].acoperit) {
            int necesare = 2 - a[i].puncteIn;

            if(necesare >= 2) {
                if(a[i].y - a[i].x >= 1) {
                    adaugarePct(a, n, a[i].y);
                    adaugarePct(a, n, a[i].y - 1);
                    rez[dim++] = a[i].y - 1;
                    rez[dim++] = a[i].y;
                }else {
                    adaugarePct(a, n, a[i].y);
                    adaugarePct(a, n, a[i].x);
                    rez[dim++] = a[i].x;
                    rez[dim++] = a[i].y;
                }
            }else if(necesare == 1) {
                adaugarePct(a, n, a[i].y);
                rez[dim++] = a[i].y;
            }
        }
    }

    cout << dim << endl;
    for(int i = 0; i < dim; i++) {
        cout << rez[i] << " ";
    }
}

///check-in
//ministerul organizeaza o excursie pentru olimpici la Paris. Suntem toti la aeroport, k olimpici avand in total p bagaje.
//Pentru zborul catre Paris au fost deschise n ghisee pentru check-in, numerotate de la 1 la n. La fiecare ghiseu lucreaza
//exact un angajat. Angajatul de la ghiseul i are nevoie de Ai secunde pt. a procesa fiecare bagaj al clientului prezentat
//la ghiseu si Bi secunde pt. a emite toate tichetele de imbarcare solicitate de client. O pers. poate sta la un singur
//ghiseu si poate preda 0,1, sau mai multe bagaje(acestea vor fi trecute pe numele sau). De asemenea, o persoana poate sa-i
//prezinte angajatului de la ghiseu biletele si pasapoartele altor pers., astfel ca poate solicita emiterea mai multor tichete
//de imbarcare. O pers. tb. sa solicite de la ghiseul la care se prezinta c. p. un tichet de imbarcare. Initial, nimeni nu sta
//la coada la ghiseele pt Paris. Timpul necesar pt. a face check-in-ul depinde de strategia adoptata. Olimpicii la info. tb. sa
//gaseasca o strategie prin care cei k olimpici pot preda cele p bagaje si obtine cele k tichete de imbarcare in cel mai scurt timp

struct Ghiseu {
    int A;
    int B;
};

void sorteazaDesc(int cap[], int m) {
    for (int i = 0; i < m - 1; i++) {
        for (int j = i + 1; j < m; j++) {
            if (cap[i] < cap[j]) {
                int temp = cap[i];
                cap[i] = cap[j];
                cap[j] = temp;
            }
        }
    }
}

bool poateFace(Ghiseu g[], int n, int K, int P, int T) {
    int cap[1001];
    int nrValide = 0;

    for (int i = 0; i < n; i++) {
        if (T >= g[i].B) {
            if (g[i].A == 0)
                cap[nrValide] = P + 1;
            else
                cap[nrValide] = (T - g[i].B) / g[i].A;
            nrValide++;
        }
    }

    if (nrValide < K)
        return false;

    sorteazaDesc(cap, nrValide);

    long long suma = 0;
    for (int i = 0; i < K; i++) {
        suma += cap[i];
    }

    return suma >= P;
}

void ex10() {
    ifstream fin("D:/info/c++/clion/metodaGreedy/exercitii.txt");
    int n,k,p,i;
    fin >> n;
    Ghiseu g[n];
    for(i = 0; i < n; i++) {
        fin >> g[i].A >> g[i].B;
    }
    fin >> k >> p;

    int st = 0, dr = 10010001;
    int rezultat = dr;

    while (st <= dr) {
        int mij = (st + dr) / 2;
        if (poateFace(g,n,k,p,mij)) {
            rezultat = mij;
            dr = mij - 1;
        } else {
            st = mij + 1;
        }
    }

    cout << rezultat << endl;
}

///====================Exercitii Cartea Rosie==============================

//se considera un sir de n valori reale. Sa se realizeze un program care det. o submultime a acestuia, care are propr. ca suma
//elem este maxima.


void ex11() {
    ifstream fin("D:/info/c++/clion/metodaGreedy/exercitii.txt");
    int v[100], n, rez[100], dim = 0;
    fin >> n;
    for(int i = 0; i < n; i++) {
        fin >> v[i];
        if(v[i] > 0) {
            rez[dim++] = v[i];
        }
    }

    afisVec(rez,dim);
}

//se considera un sir de n valori naturale, repr. val. unor obiecte. Partitionati acest sir in doua submultimi care au propr. ca
//dif. absoluta a sumelor elem. lor este minima.

int part2(int v[], int l, int r) {
    int p, i, j;
    p = v[r];
    j = l - 1;
    for(i = l; i <= r; i++) {
        if(v[i] <= p) {
            swap(v[i], v[++j]);
        }
    }
    return j;
}

void quickSort2(int v[], int l, int r) {
    int poz = part2(v, l, r);
    if(l < poz - 1) quickSort2(v,l,poz-1);
    if(r > poz + 1) quickSort2(v,poz+1, r);
}

void ex12() {
    ifstream fin("D:/info/c++/clion/metodaGreedy/exercitii.txt");
    int v[100], n, s = 0;
    fin >> n;
    for(int i = 0; i < n; i++) {
        fin >> v[i];
        s += v[i];
    }
    s /= 2;
    quickSort2(v, 0, n);

    for(int i = n; i >= 0; i--) {
        if(s - v[i] >= 0) {
            cout << v[i] << " ";
            s -= v[i];
            v[i] = 0;
        }
    }
    cout << endl;
    for(int i = 0; i < n; i++) {
        if(v[i] > 0) {
            cout << v[i] << " ";
        }
    }
}

//se considera n lucrari, ce se pot executa fiecare intr-o singura ora. Pt. fiecare lucrare, se cunosc ora cand tb. predata si
//penalizarea pentru nerespectarea acesteia. Stiind ca nu pot fi executate 2 lucrari simultan, sa se realizeze un program care
//identifica o ordine de executare a lucrarilor, avand penalizare totala minima.

struct Lucrare {
    int oraPredare;
    int penalizare;
};

int part3(Lucrare lu[], int l, int r) {
    int poz = lu[r].oraPredare;
    int i, j = l - 1;
    for(i = l; i < r; i++) {
        if(lu[i].oraPredare <= poz) {
            swap(lu[i],lu[++j]);
        }
    }
    swap(lu[i+1],lu[r]);
    return j + 1;
}

void quickSort3(Lucrare lu[], int l, int r) {
    if(l < r) {
        int poz = part3(lu, l, r);
        quickSort3(lu,l,poz-1);
        quickSort3(lu,poz+1, r);
    }
}

void ex13() {
    ifstream fin("D:/info/c++/clion/metodaGreedy/exercitii.txt");
    int n;
    Lucrare lu[100];
    fin >> n;
    for(int i = 0; i < n; i++) {
        fin >> lu[i].oraPredare >> lu[i].penalizare;
    }

    quickSort3(lu, 0, n - 1);


    int total = 0, ora = 0;
    for(int i = 0; i < n; i++) {
        if(lu[i].oraPredare >= ora + 1) {
            ora+=1;
        }else {
            total += lu[i].penalizare;
        }
    }

    cout << total << endl;
}

//intr-un hotel cu k camere s-au primit pentru anul urmator n solicitari de cazare, fiecare pentru m zile. Pt fiecare cerere se
//cunoaste ziua de inceput a perioadei de cazare. Stiind ca anul urmator are 365 de zile, sa se realizeze un program care det.
//nr. max. de cereri ce pot fi satisfacute.

int part4(int v[], int l, int r) {
    int p = v[r];
    int j = l - 1;
    for(int i = l; i < r; i++) {
        if(v[i] <= p) {
            swap(v[++j], v[i]);
        }
    }
    swap(v[j+1],v[r]);
    return j + 1;
}

void quickSort4(int v[], int l, int r) {
    if(l < r) {
        int poz = part4(v,l,r);
        if(l < poz - 1) quickSort4(v,l,poz-1);
        if(r > poz + 1) quickSort4(v,poz+1, r);
    }
}

void ex14() {
    int n, m, k;
    int v[100]; //cererile
    ifstream fin("D:/info/c++/clion/metodaGreedy/exercitii.txt");
    fin >> n >> m >> k;
    for(int i = 0; i < n; i++) {
        fin >> v[i];
    }

    quickSort4(v, 0, n - 1);
    int c[100] = {}, total = 0; //camerele
    for(int i = 0; i < n; i++) {
        int ok = 0, j = 0;
        while(!ok) {
            if(c[j] >= v[i]) {
                ok = 1;
                c[j] += m;
                total++;
            }
            j++;
        }
    }

    cout << total << endl;
}

//se dau doua siruri de lungime N si un nr. k. Cele doua siruri au numai nr. de 1 si -1. Scopul e sa-l trans. pe primul in al doilea.
//Singura operatie permisa e sa selectam o secventa de k elem. alaturate si sa le inversam semnul la toate nr. curpinse in aceasta zona.
//Sa se afis. nr. min de operatii si pozitia de inceput de unde se aplica operatia.

void ex15() {
    int n, k, v1[100], v2[100];
    ifstream fin("D:/info/c++/clion/metodaGreedy/exercitii.txt");
    fin >> n >> k;
    for(int i = 0; i < n; i++) {
        fin >> v1[i];
    }
    for(int i = 0; i < n; i++) {
        fin >> v2[i];
    }

    int rez[100]{}, ct = 0;

    for(int i = 0; i < n; i++) {
        if(v1[i] * -1 == v2[i]) {
            for(int j = i; j < i + k; j++) {
                v1[j] *= -1;
            }
            rez[ct++] = i;
            i--;
        }
    }

    cout << ct << endl;
    afisVec(rez,ct);
}

//se considera un nr. n si k<=n. Sa se construiasca o matrice patratica de ordin n, ale carei elem. satisfac simultan conditiile:
//-contine toate nr. de la 1 la n la patrat;
//-pe fiecare linie nr. sunt ordonate cresc;
//-suma elem. de pe coloana k este minima.
///todo?????
void ex16() {
    int n, k;
    ifstream fin("D:/info/c++/clion/metodaGreedy/exercitii.txt");
    fin >> n >> k;
    int mat[n][n];
    bool folosit[n*n] = {};
    for(int i = 0; i < n; i++) {
        int ok = 0;
        for(int j = 0; j < n * n; j++) {

        }
    }
}

//se considera n intervale repr. perioadele de viata a n scriitori. Sa se realizeze un program care det. anul cand se aflau
//in viata cei mai multi scriitori

struct Perioada {
    long long int ziN = 0;
    long long int ziD = 0;
};

int part5(Perioada p[], int l, int r) {
    int poz = p[r].ziD;
    int j = l - 1;
    for(int i = l; i < r; i++) {
        if(p[i].ziD <= poz) {
            swap(p[i],p[++j]);
        }
    }
    swap(p[j],p[r]);
    return j + 1;
}

void quickSort5(Perioada p[], int l, int r) {
    int poz = part5(p,l,r);
    if(l < poz - 1) quickSort5(p, l, poz - 1);
    if(r > poz + 1) quickSort5(p, poz + 1, r);
}

void ex17() {
    ifstream fin("D:/info/c++/clion/metodaGreedy/exercitii.txt");
    int n;
    int luna[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    Perioada p[100];
    fin >> n;
    for(int i = 0; i < n; i++) {
        int a, b, c;
        fin >> a >> b >> c;
        p[i].ziN = c * 365;
        int x = 0;
        while(x < b) {
            p[i].ziN += luna[x];
            x++;
        }
        p[i].ziN += a;

        fin >> a >> b >> c;
        p[i].ziD = c * 365;
        x = 0;
        while(x < b) {
            p[i].ziD += luna[x];
            x++;
        }
        p[i].ziD += a;
    }

    for(int i = 0; i < n; i++) {
        cout << p[i].ziN << " " << p[i].ziD << endl;
    }

    quickSort5(p, 0, n - 1);

    int maxim = 0, anMaxim = -1;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            int ct = 0;
            if(i != j && p[j].ziN <= p[i].ziD && p[i].ziD <= p[j].ziD) {
                ct++;
            }
            if(ct > maxim) {
                maxim = ct;
                anMaxim = p[i].ziD / 365;
            }
        }
    }

    cout << maxim << " " << anMaxim << endl;
}
#endif //EXERCITII_H