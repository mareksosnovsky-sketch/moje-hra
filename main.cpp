#include <iostream>
#include <string>

struct Utok {
    std::string jmeno;
    int poskozeni;
    int cena_utoku; // UBERE MANU
};

struct Postava {
    std::string jmeno;
    int max_zivoty;
    int akt_zivoty;
    int max_mana;
    int akt_mana;
    int penize;
    int lvl;
    int xp;
    int utok;


    Utok hlavniUtok;
    Utok sekundarniUtok;

    void vypisKartu() {
        std::cout << "=== " << jmeno << " (Lvl " << lvl << ") ===\n";
        std::cout << " Zivoty: " << akt_zivoty << " / " << max_zivoty << "\n";
        std::cout << " Mana:   " << akt_mana << " / " << max_mana << "\n";
        std::cout << " Zlato:  " << penize << " | XP: " << xp << "\n";
        std::cout << "   " << hlavniUtok.jmeno << " (" << hlavniUtok.poskozeni << " DMG)\n";
        std::cout << "   " << sekundarniUtok.jmeno << " (" << sekundarniUtok.poskozeni << " DMG, " << sekundarniUtok.cena_utoku << " Mana)\n";
        std::cout << "==========================\n\n";
    }
};

int main() {


    Postava mag = {
        "Gandalf",
        100, 100, // zivoty
        30, 30,   // mana
        50, 1, 0, 5, // penize , lvl , xp , zakladni utok
        {"Machnuti holi", 5, 0},
        {"Fireball", 15, 7}
    };


    Postava Rytir = {
        "Rytir",
        125, 125, // zivoty
        15, 15,   // mana
        50, 1, 0, 10, // penize , lvl , xp , zakladni utok
        {"Uppercut", 5, 0},
        {"Svizne seknuti", 15, 5}
    };


    Postava Ninja = {
        "Ninja",     // Tady chybìla èárka!
        100, 100,    // zivoty
        20, 20,      // mana
        50, 1, 0, 5, // penize , lvl , xp , zakladni utok
        {"Hazeci hvezdice", 10, 0},
        {"Seknuti katanou", 15, 10}
    };


    mag.vypisKartu();
    Rytir.vypisKartu();
    Ninja.vypisKartu();

    return 0;
}
