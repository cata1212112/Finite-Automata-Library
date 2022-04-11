//
// Created by Cata on 4/5/2022.
//

#ifndef LFA_TEMA_2_AUTOMATA_H
#define LFA_TEMA_2_AUTOMATA_H

#include <vector>
#include <map>
#include <set>
#include "IoBase.h"

using namespace std;

class Automata : public IoBase{
protected:
    int nr_stari, stare_initiala;
    map<int, bool> stari_finale;
    vector<int> stari;
    set<char> language;
    set<int> stari_valabile;
public:
    Automata();

    Automata(int nrStari, int stareInitiala, const map<int, bool> &stariFinale, const vector<int> &stari,
             const set<char> &language);

    istream &read(istream &is) override;

    ostream &write(ostream &os) const override;
};

#endif //LFA_TEMA_2_AUTOMATA_H
