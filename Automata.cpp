//
// Created by Cata on 4/5/2022.
//

#include "Automata.h"

istream &Automata::read(istream &is) {
    IoBase::read(is);
    cout << "Numarul de stari : \n";
    is >> nr_stari;
    int stare;
    cout << "Starile : \n";
    for (int i = 0; i < nr_stari; ++i) {
        is >> stare;
        stari.push_back(stare);
    }
    cout << "Stare initiala : \n";
    is >> stare_initiala;
    cout << "Numarul de stari finale : \n";
    int nrF, finala;
    is >> nrF;
    cout << "Starile finale : ";
    for (int i = 0; i < nrF; ++i) {
        is >> finala;
        stari_finale[finala] = true;
    }
    return is;
}

ostream &Automata::write(ostream &os) const {
    IoBase::write(os);
    os << "Numarul de stari : " << stari_valabile.size() << "\n";
    os << "Starile : \n";
    for (auto y:stari) {
        if (stari_valabile.find(y) != stari_valabile.end()) {
            os << y << " ";
        }
    }
    os << "\nStare initiala : " << stare_initiala << "\n";
    os << "Starile finale : \n";
    for (auto y:stari_finale) {
        if (stari_valabile.find(y.first) != stari_valabile.end()) {
            os << y.first << " ";
        }
    }
    cout << "\n";
    return os;
}

Automata::Automata() {}

Automata::Automata(int nrStari, int stareInitiala, const map<int, bool> &stariFinale, const vector<int> &stari,
                   const set<char> &language) : nr_stari(nrStari), stare_initiala(stareInitiala),
                                                stari_finale(stariFinale), stari(stari), language(language) {}
