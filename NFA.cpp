//
// Created by Cata on 4/5/2022.
//

#include "NFA.h"
#include <queue>

using namespace std;

istream &NFA::read(istream &is) {
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
        graf_tranzitii[{x, l}].push_back(y);
    }
    return is;
}

ostream &NFA::write(ostream &os) const {
    Automata::write(os);
    for (const auto& y:graf_tranzitii) {
        for (auto z:y.second) {
            os << y.first.first << " " << z << " " << y.first.second << "\n";
        }
    }
    return os;
}

void NFA::Get_Drum(map<pair<int, int>, int> drum, int acum, int pasi) {
    if (pasi == 0) return;
    Get_Drum(drum, drum[{acum, pasi-1}], pasi-1);
    cout << acum << " ";
}

void NFA::Check_word(string word) {
    set<int> first, second;
    first.insert(stare_initiala);
    map<pair<int, int>, int> de_unde_vin;
    de_unde_vin[{stare_initiala, 0}] = -1;

    for (int i = 0; i < word.length(); ++i) {
        for (auto y:first) {
            for (auto z:graf_tranzitii[{y, word[i]}]) {
                second.insert(z);
                de_unde_vin[{z, i}] = y;
            }
        }
        first = second;
        second.clear();
    }
    int ok = 0;
    int care;
    for (auto fin:first) {
        if (stari_finale[fin]) {
            ok = 1;
            care = fin;
        }
    }

    if (ok == 1) {
        cout << "DA\n";
        cout << "Succesiunea starilor este pentru cuvantul " << word << " este : ";
        cout << stare_initiala << " ";
        Get_Drum(de_unde_vin, care, (int)word.length());
        cout << "\n";
    }
    else cout << "NU\n";
}

DFA NFA::Subset_Construction() {
    queue <set<int> > q;
    map<set<int>, int> mp;
    set<int> tmp, aux;
    tmp.insert(stare_initiala);
    q.push(tmp);
    int cnt = 2;
    mp[tmp] = 1;
    map<pair<int, char>, vector<int> > graf_tranzitii_DFA;
    map<int, bool> stari_finale_DFA;
    if (stari_finale[stare_initiala] == 1) stari_finale_DFA[1] = true;
    vector<int> stari_DFA;
    stari_DFA.push_back(1);
    int stare_initiala_DFA = 1;
    set<char> language_DFA = language;
    while (!q.empty()) {
        tmp = q.front();

        q.pop();

        for (auto c:language) {
            aux.clear();
            for (auto y:tmp) {
                for (auto z: graf_tranzitii[{y, c}]) {
                    aux.insert(z);
                }
            }
            if (mp.find(aux) == mp.end()) {
                stari_DFA.push_back(cnt);
                mp[aux] = cnt++;
                q.push(aux);
            }
            for (auto f:stari) {
                if (stari_finale[f] && aux.find(f) != aux.end()) {
                    stari_finale_DFA[mp[aux]] = true;
                }
            }
            graf_tranzitii_DFA[{mp[tmp], c}].push_back(mp[aux]);
        }
    }
    map<pair<int, char>, int > graf_tranzitii_DFA_bun;
    for (auto y:graf_tranzitii_DFA) {
        graf_tranzitii_DFA_bun[y.first] = y.second[0];
    }
    return {cnt-1, stare_initiala_DFA, stari_finale_DFA, stari_DFA, language_DFA, graf_tranzitii_DFA_bun};
}
