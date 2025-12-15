#pragma once

#include <iostream>
#include <sstream>
#include <cstring>
#include <string>

#include "exercitii_modern.h"

std::string curataSir(const std::string &text) {
    std::string rezultat;
    rezultat.reserve(text.size());
    for (char c : text) {
        if (c == '\r') {
            continue;
        }
        if (c == '\n') {
            while (!rezultat.empty() && rezultat.back() == ' ') {
                rezultat.pop_back();
            }
            rezultat.push_back('\n');
        } else {
            rezultat.push_back(c);
        }
    }
    while (!rezultat.empty() && (rezultat.back() == ' ' || rezultat.back() == '\n' || rezultat.back() == '\t')) {
        rezultat.pop_back();
    }
    return rezultat;
}

bool ruleazaTest(const char *nume, const char *input, const char *asteptat, void (*functie)(std::istream &, std::ostream &)) {
    std::stringstream in;
    std::stringstream out;
    in << input;
    functie(in, out);
    std::string rezultat = out.str();
    std::string curatat = curataSir(rezultat);
    std::string asteptatStr = curataSir(asteptat);
    bool corect = (curatat == asteptatStr);
    std::cout << "=== Test " << nume << " (" << (corect ? "OK" : "FAIL") << ") ===\n";
    std::cout << "Input:\n" << input;
    std::size_t lg = std::strlen(input);
    if (lg == 0 || input[lg - 1] != '\n') {
        std::cout << '\n';
    }
    if (!corect) {
        std::cout << "Asteptat:\n" << asteptatStr << '\n';
        std::cout << "Obtinut:\n" << curatat << '\n';
    } else {
        std::cout << "Output corect:\n" << curatat << '\n';
    }
    return corect;
}

void ruleazaToateTestele() {
    const int NR_TESTE = 21;
    const char *nume[NR_TESTE] = {
        "ex1","ex2","ex3","ex4","ex5","ex6","ex7","ex8","ex9","ex10",
        "ex11","ex12","ex13","ex14","ex15","ex16","ex17","ex18","ex19","ex20","ex21"
    };
    const char *inputuri[NR_TESTE] = {
        "3\n10 0 12 0\n12 0 14 0\n11 0 13 0\n",
        "3 50\n60 20\n100 50\n120 30\n",
        "6\n5 1 2 6 4 7\n",
        "3\n0 3\n2 5\n4 7\n",
        "3 4\n100 1 ianuarie 10\n50 2 ianuarie 8\n80 3 ianuarie 9\n",
        "3\n150 130 170\n140 160 180\n",
        "4 2\n10000 5\n8000 4\n12000 6\n9000 3\n",
        "5 5 2\n08:00\n09:00\n2\n08:30\n09:30\n",
        "3\n0 2\n1 3\n2 4\n",
        "3\n1 2\n2 5\n3 7\n2 5\n",
        "5\n-1 3 0 4 -2\n",
        "4\n3 1 4 2\n",
        "3\n2 50\n1 30\n3 40\n",
        "5 2 2\n1 2 3 4 5\n",
        "5 3\n1 -1 1 -1 1\n-1 1 -1 1 -1\n",
        "3 2\n",
        "2\n1 1 0 10 1 0\n5 1 0 20 1 0\n",
        "3\n1 2\n1 3\n0\n",
        "4 3\n1 2\n2 3\n3 4\n",
        "4 5\n1 2\n1 3\n2 3\n2 4\n3 4\n",
        "4\n1 10\n2 5\n3 8\n6 9\n"
    };
    const char *asteptate[NR_TESTE] = {
        "1 2",
        "3 100.00%\n1 100.00%",
        "2",
        "2",
        "0\n1 2 3",
        "elev 130 -> schiuri 140\nelev 150 -> schiuri 160\nelev 170 -> schiuri 180",
        "11 22000\n3 1",
        "1",
        "3\n1 2 4",
        "7",
        "3 4",
        "1 4\n3 2",
        "0",
        "5",
        "-1",
        "1 2 9\n3 4 8\n5 6 7",
        "2 0",
        "1\nOrdine atac: 1\nPesti ramasi: 1",
        "2\n1 3",
        "3\n2 3 1",
        "3"
    };

    void (*functii[NR_TESTE])(std::istream &, std::ostream &) = {
        ex1, ex2, ex3, ex4, ex5, ex6, ex7, ex8, ex9, ex10,
        ex11, ex12, ex13, ex14, ex15, ex16, ex17, ex18, ex19, ex20, ex21
    };

    int reusite = 0;
    for (int i = 0; i < NR_TESTE; ++i) {
        if (ruleazaTest(nume[i], inputuri[i], asteptate[i], functii[i])) {
            ++reusite;
        }
    }
    std::cout << "Rezumat: " << reusite << "/" << NR_TESTE << " teste corecte." << std::endl;
}
