#ifndef CARTEAROSIE_H
#define CARTEAROSIE_H
#include <iostream>
#include <fstream>
using namespace std;

///premiul
//la o festivitate de premiere, dirigintele clasei ar n obiecte de val. cunoscute mai mici decat 100 lei. Stiind ca elevului care a
//obtinut premiul I, ii va inmana m obiecte, realizati un program care identifica valoarea maxima a premiului I si care obiecte au fost alege


void bubbleSortDescresc(int v[],  int n) {
    for(int i = 0; i < n-1; i++) {
        for(int j = i + 1; j < n; j++) {
            if(v[i] < v[j]) {
                int x = v[i];
                v[i] = v[j];
                v[j] = x;
            }
        }
    }
}


void bubbleSortCresc( int v[1001], int n) {
    for(int i = 0; i < n - 1; i++) {
        for(int j = i + 1; j < n; j++) {
            if(v[i] > v[j]) {
                int x = v[i];
                v[i] = v[j];
                v[j] = x;
            }
        }
    }
}

void ex1() {
    ifstream fin("D:/info/c++/clion/metodaGreedy/exercitii.txt");
    int n, m, v[10001], i, j, s = 0;
    fin >> n >> m;
    for (i = 0; i < n; i++) {
        fin >> v[i];
    }
    bubbleSortDescresc(v, n);

    for(i = 0; i < m; i++) {
        s += v[i];
        cout << v[i] << " ";
    }
    cout << endl << s << endl;
}

///Timp de asteptare
//la o statie de banzina functioneaza o singura pompa, la care urmeaza sa fie serviti n clienti. Cunoscandu-se timpul necesar
//servirii fiecarui client realizati un program care det o ordine de servire a lor, a. i. timpul mediu de asteptare sa fie minim

void ex2() {
    ifstream fin("D:/info/c++/clion/metodaGreedy/exercitii.txt");
    int n, v[1001], i, j, t = 0;
    fin >> n;
    for (i = 0; i < n; i++) {
        fin >> v[i];
    }

    bubbleSortCresc(v, n);

    for(i = 0; i < n - 1; i++) {
        cout << v[i]<< " ";
        t += (n-i-1)*v[i];
    }
    printf("%d\n%d/%d\n",v[n-1],t,n);
}

///Modalitate de plata
//se considera n tipuri de bancnote, de val. dif., din fiecare existand un nr. nelimitat de bucati. Sa se det. o modalitate de
//plata a valorii S, folosind un nr. min. de bancnote

void ex3() {
    ifstream fin("D:/info/c++/clion/metodaGreedy/exercitii.txt");
    int n, s, v[1001], x, i, j;
    fin >> n >> s;
    for(i = 0; i < n; i++) {
        fin >> v[i];
    }

    bubbleSortDescresc(v,n);

    for(i = 0; i < n; i++) {
        if(v[i] <= s) {
            cout << s/v[i] << "*" << v[i] << endl;
            s-= (s/v[i]) * v[i];
        }
        if(!s) return;
    }
    if(s > 0) cout << "Raspuns eronat" << endl;
}

///Rucsac-varianta discreta(0/1)
//se considera un rucsac cu care se poate transporta o greutate maxima Gmax si mai multe obiecte de greutati g1,g2,..,gn
//la trans. carora se obtin castigurile c1,c2,..,cn. Sa se incarce rucsacul a. i. sa se obtina un castig maxim. Rez. va fi
//afis pe ecran printr-un sir de 0 sau 1, daca obiectul i este sau nu in rucsac

struct Obiect{
    int g, c, nr, x;
};

void load(Obiect ob[], int&n, int&gm) {
    cin >> n >> gm;
    for(int i = 0; i < n; i++) {
        cin >> ob[i].g >> ob[i].c;
        ob[i].nr = i;
    }
}

void ex4() {
    int n, m, gm, g = 0, c = 0;
    Obiect ob[100], x;
    load(ob, n, gm);
    for(int i = 0; i < n - 1; i++) {
        for(int j = i + 1; j < n; j++) {
            if(ob[i].g * ob[j].c > ob[i].c * ob[j].g) {
                x = ob[i];
                ob[i] = ob[j];
                ob[j] = x;
            }
        }
    }

    for(int i = 0; i < n; i++) {
        if(g + ob[i].g <= gm) {
            g += ob[i].g;
            c += ob[i].c;
            ob[i].x = 1;
        }else {
            ob[i].x = 0;
        }
    }
    cout << c << endl;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(ob[j].nr == i) {
                cout << ob[j].x;
            }
        }
    }
}


#endif //CARTEAROSIE_H
