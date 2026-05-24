#include <iostream>
#include <string>

struct Utok {
    std::string jmeno;
    int poskozeni;
    int cena_utoku; // Sebrani many
};

struct Monstrum {
    std::string jmeno;
    int max_zivoty;
    int akt_zivoty;


    Utok hlavniUtok;
    Utok sekundarniUtok;


    void vypisKartu() {
        std::cout << "=== " << jmeno << " (Monstrum) ===\n";
        std::cout << " Zivoty: " << akt_zivoty << " / " << max_zivoty << "\n";
        std::cout << "   " << hlavniUtok.jmeno << " (" << hlavniUtok.poskozeni << " DMG)\n";
        std::cout << "   " << sekundarniUtok.jmeno << " (" << sekundarniUtok.poskozeni << " DMG)\n";
        std::cout << "==========================\n\n";
    }
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

    Monstrum Goblin = {
        "Goblin",
        45, 45,
        {"Bodnuti dykou", 6, 0},
        {"Skrabnuti", 3, 0}
    };

    Monstrum KamennyGolem = {   // mini boss
        "Kamenny Golem (Mini Boss)",
        150, 150,
        {"Rozdrceni pesti", 14, 0},
        {"Hod balvanem", 22, 0}
    };

    Monstrum StinovyLovec = {  // mini boss
        "Stinovy Lovec (Mini Boss)",
        110, 110,
        {"Seknuti ze zalohy", 16, 0},
        {"Temny sip", 26, 0}
    };

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
        "Ninja",
        100, 100,    // zivoty
        20, 20,      // mana
        50, 1, 0, 5, // penize , lvl , xp , zakladni utok
        {"Hazeci hvezdice", 10, 0},
        {"Seknuti katanou", 15, 10}
    };


    mag.vypisKartu();//kontrola vypisu hrdinu
    Rytir.vypisKartu();
    Ninja.vypisKartu();


    Goblin.vypisKartu(); //kontrola vypisu monster
    KamennyGolem.vypisKartu();
    StinovyLovec.vypisKartu();

    return 0;
}
