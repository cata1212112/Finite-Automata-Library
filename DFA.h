//
// Created by Cata on 4/5/2022.
//

#ifndef LFA_TEMA_2_DFA_H
#define LFA_TEMA_2_DFA_H

#include "Automata.h"

class DFA : public Automata{
private:
    map<pair<int, char>, int> tabel_tranzitii;

public:
    DFA();

    DFA(int nrStari, int stareInitiala, const map<int, bool> &stariFinale, const vector<int> &stari,
        const set<char> &language, const map<pair<int, char>, int> &tabelTranzitii);

    istream &read(istream &is) override;

    ostream &write(ostream &os) const override;

    void Check_Word(string word);

    DFA Minimization();

    void stari_bune();
};


#endif //LFA_TEMA_2_DFA_H
