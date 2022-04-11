#include "DFA.h"
#include <algorithm>

istream &DFA::read(istream &is) {
    Automata::read(is);
    cout << "Numarul de tranzitii : \n";
    int nr_tranzitii;
    is >> nr_tranzitii;
    cout << "Tranzitiile (stare1, stare2, caracter) : \n";
    int x, y;
    char l;
    for (int i = 0; i < nr_tranzitii; ++i) {
        is >> x >> y >> l;
        language.insert(l);
        tabel_tranzitii[{x, l}] = y;
    }
    return is;
}

ostream &DFA::write(ostream &os) const {
    Automata::write(os);
    for (auto y:tabel_tranzitii) {
        if (stari_valabile.find(y.first.first) != stari_valabile.end() && stari_valabile.find(y.second) != stari_valabile.end()) {
            os << y.first.first << " " << y.second << " " << y.first.second << "\n";
        }
    }
    return os;
}

void DFA::Check_Word(string word) {
    vector<int> drum;
    int ok = 1;
    int i = 0;
    int stare_curenta = stare_initiala;
    while (ok && i < word.length()) {
        if (tabel_tranzitii[{stare_curenta, word[i]}] != 0) i++, drum.push_back(stare_curenta);
        else ok = 0;
        if (ok == 0) break;
        stare_curenta = tabel_tranzitii[{stare_curenta, word[i - 1]}];
        if (stare_curenta == 0) ok = 0;
    }
    if (stari_finale[stare_curenta] != 1) ok = 0;
    if (ok) {
        cout << "DA\n";
        cout << "Cuvantul " << word <<" este acceptat, iar succesiunea starilor este : ";
        for (auto y:drum) {
            cout << y << " ";
        }
        cout << stare_curenta;
        cout << "\n";
    } else {
        cout << "NU\n";
        cout << "Cuvantul " << word << " nu este acceptat.\n";
    }
}

DFA::DFA() {}

DFA::DFA(int nrStari, int stareInitiala, const map<int, bool> &stariFinale, const vector<int> &stari,
         const set<char> &language, const map<pair<int, char>, int> &tabelTranzitii) : Automata(nrStari, stareInitiala,
                                                                                                stariFinale, stari,
                                                                                                language),
                                                                                       tabel_tranzitii(
                                                                                               tabelTranzitii) {}


DFA DFA::Minimization() {
    set<set<int>> P, W;
    set<int> finale, nefinale;
    for (auto y:stari) {
        if (stari_finale[y]) finale.insert(y);
        else nefinale.insert(y);
    }
    P.insert(finale);
    P.insert(nefinale);

    W.insert(finale);
    W.insert(nefinale);

    set<set<int>> P_copy;
    set<int> A, X, inter, diff;
    while (!W.empty()) {
        set<int> A = *W.begin();
        W.erase(W.begin());
        for (auto c:language) {
            X.clear();
            for (auto x:stari) {
                if (A.find(tabel_tranzitii[{x, c}]) != A.end()) {
                    X.insert(x);
                }
            }
            P_copy = P;
            for (auto y:P) {
                inter.clear();
                diff.clear();
                set_intersection(X.begin(), X.end(), y.begin(), y.end(), inserter(inter, inter.begin()));
                set_difference(y.begin(), y.end(), X.begin(), X.end(), inserter(diff, diff.begin()));
                if (!inter.empty() && !diff.empty()) {
                    P_copy.erase(P_copy.find(y));
                    P_copy.insert(inter);
                    P_copy.insert(diff);

                    if (W.find(y) != W.end()) {
                        W.erase(W.find(y));
                        W.insert(inter);
                        W.insert(diff);
                    } else {
                        if (inter.size() <= diff.size()) {
                            W.insert(inter);
                        } else {
                            W.insert(diff);
                        }
                    }
                }
            }
            P = P_copy;
        }
    }

    int nr_stari_mini, stare_initiala_mini;
    map<int, bool> stari_finale_mini;
    vector<int> stari_mini;
    set<char> language_mini;
    map<pair<int, char>, int> tabel_tranzitii_mini;

    nr_stari_mini = P.size();
    int cnt = 1;

    map<set<int>, int> mapare;
    for (auto y:P) {
        mapare[y] = cnt++;
    }
    for (auto y:P) {
        if (y.find(stare_initiala) != y.end()) {
            stare_initiala_mini = mapare[y];
        }
        for (auto z:stari) {
            if (stari_finale[z] == true and y.find(z) != y.end()) {
                stari_finale_mini[mapare[y]] = true;
            }
        }
    }

    for (int i=1; i<cnt; i++) {
        stari_mini.push_back(i);
    }

    language_mini = language;

    for (auto y1:P) {
        for (auto y2:P) {
            for (auto c:language) {
                for (auto x1: y1) {
                    for (auto x2: y2) {
                        if (tabel_tranzitii[{x1, c}] == x2) {
                            tabel_tranzitii_mini[{mapare[y1], c}] = mapare[y2];
                        }
                    }
                }
            }
        }
    }
    return {nr_stari_mini, stare_initiala_mini, stari_finale_mini, stari_mini, language_mini, tabel_tranzitii_mini};
}


void DFA::stari_bune() {
    set<int> bune, aux, tmp, aux_2;
    bune.insert(stare_initiala);
    aux.insert(stare_initiala);
    do {
        tmp.clear();
        for (auto q:aux) {
            for (auto c:language) {
                tmp.insert(tabel_tranzitii[{q, c}]);
            }
        }
        for (auto y:tmp) {
            cout << y << " ";
        }
        cout << "\n\n\n\n";
        aux.clear();
        set_difference(tmp.begin(), tmp.end(), bune.begin(), bune.end(), inserter(aux, aux.begin()));
        for (auto y:aux) {
            bune.insert(y);
        }
    } while (!aux.empty());
    stari_valabile = bune;
}
