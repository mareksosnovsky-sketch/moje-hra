#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Struktura pro jednotlivé schopnosti
struct Schopnost {
    string nazev;
    string popis;
    int cenaMany;
};

// Struktura postavy
struct Postava {
    string jmenoClassy;
    int maxZivoty;
    int aktualniZivoty;
    int maxMana;
    int aktualniMana;
    int zlato;
    int level;
    int zkusenosti;
    int utok;
    vector<Schopnost> schopnosti;
};

// postavy
void vypisStatistiky(const Postava& p) {
    cout << "\n--- Class: " << p.jmenoClassy << " ---\n";
    cout << "Zivot: " << p.aktualniZivoty << " / " << p.maxZivoty << "\n";
    cout << "Mana:  " << p.aktualniMana << " / " << p.maxMana << "\n";
    cout << "Utok:  " << p.utok << "\n";
    cout << "Zlato: " << p.zlato << "\n";
    cout << "Level: " << p.level << " (Zkusenosti: " << p.zkusenosti << ")\n";
    cout << "Schopnosti:\n";
    for (size_t i = 0; i < p.schopnosti.size(); i++) {
        cout << "  - " << p.schopnosti[i].nazev << " (" << p.schopnosti[i].popis 
             << ") | Stoji many: " << p.schopnosti[i].cenaMany << "\n";
    }
    cout << "-----------------------\n";
}

int main() {
 
    // 1. Postava: Paladin
    // ==========================================
    Postava paladin;
    paladin.jmenoClassy = "Paladin";
    paladin.maxZivoty = 5;
    paladin.aktualniZivoty = 5;
    paladin.maxMana = 5;
    paladin.aktualniMana = 5;
    paladin.zlato = 0;
    paladin.level = 1;
    paladin.zkusenosti = 0;
    paladin.utok = 3;
    
    // Schopnosti paladin
    paladin.schopnosti.push_back({"Zakladni utok", "Uder za 3 poskozeni", 0});
    paladin.schopnosti.push_back({"Uder svetlem", "1 poskozeni vsem nepratelum", 2});
    paladin.schopnosti.push_back({"Oziveni", "Hrac si prida 1 zivot", 1});

    
    // 2. Postava: Mág
  
    Postava mag;
    mag.jmenoClassy = "Mag";
    mag.maxZivoty = 3;
    mag.aktualniZivoty = 3;
    mag.maxMana = 10;
    mag.aktualniMana = 10;
    mag.zlato = 0;
    mag.level = 1;
    mag.zkusenosti = 0;
    mag.utok = 1;

    // Schponosti mag
    mag.schopnosti.push_back({"Zakladni utok", "Uder hulkou za 1 poskozeni", 0});
    mag.schopnosti.push_back({"Ohniva koule", "Uder za 4 poskozeni", 3});
    mag.schopnosti.push_back({"Ledovy stit", "Zablokuje dalsi utok", 4});

 
    // Výpis pro kontrolu, že proměnné fungují
    // ==========================================
    cout << "Nactene postavy ve hre:\n";
    vypisStatistiky(paladin);
    vypisStatistiky(mag);

    return 0;
}
