//
// Created by Cata on 4/5/2022.
//

#ifndef LFA_TEMA_2_NFA_H
#define LFA_TEMA_2_NFA_H

#include "Automata.h"
#include "DFA.h"

class NFA : public Automata{
private:
    map<pair<int, char>, vector<int> > graf_tranzitii;

    void Get_Drum(map<pair<int, int>, int> drum, int acum, int pasi);
public:
    istream &read(istream &is) override;

    ostream &write(ostream &os) const override;

    void Check_word(string word);

    DFA Subset_Construction();
};

#endif //LFA_TEMA_2_NFA_H
