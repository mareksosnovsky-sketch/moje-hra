#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

// struktury
struct Utok
{
    std::string jmeno;
    int poskozeni;
    int cena_utoku;
};

struct Monstrum
{
    std::string jmeno;
    int max_zivoty;
    int akt_zivoty;
    Utok hlavniUtok;
    Utok sekundarniUtok;

    void vypisKartu()
    {
        std::cout << "--- " << jmeno << " ---\n";
        std::cout << "  Zivoty: " << akt_zivoty << " / " << max_zivoty << "\n";
        std::cout << "  [1] " << hlavniUtok.jmeno << " (" << hlavniUtok.poskozeni << " DMG)\n";
        std::cout << "  [2] " << sekundarniUtok.jmeno << " (" << sekundarniUtok.poskozeni << " DMG)\n";
        std::cout << "-----------------------\n";
    }
};

struct Postava
{
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

    void vypisKartu()
    {
        std::cout << "=== " << jmeno << " (Lvl " << lvl << ") ===\n";
        std::cout << " Zivoty: " << akt_zivoty << " / " << max_zivoty << "\n";
        std::cout << " Mana:   " << akt_mana << " / " << max_mana << "\n";
        std::cout << " Zlato:  " << penize << " | XP: " << xp << " / " << (lvl * 100) << "\n";
        std::cout << " [1] " << hlavniUtok.jmeno << " (" << (hlavniUtok.poskozeni + utok) << " DMG)\n";
        std::cout << " [2] " << sekundarniUtok.jmeno << " (" << (sekundarniUtok.poskozeni + utok) << " DMG, " << sekundarniUtok.cena_utoku << " Mana)\n";
        std::cout << "==========================\n\n";
    }
};

// vyber volby funkce aby fungovalo
int nactiVolbu(int min, int max)
{
    int volba;
    while (true)
    {
        std::cout << "Zadej volbu (" << min << "-" << max << "): ";
        std::cin >> volba;
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Neplatny znak! Zadej cislo.\n";
            continue;
        }
        if (volba >= min && volba <= max)
        {
            return volba;
        }
        std::cout << "Neplatna volba! Zkus to znovu.\n";
    }
}

void zkontrolujLevelUp(Postava &hrac)
{
    int potreba_xp = hrac.lvl * 100;
    if (hrac.xp >= potreba_xp)
    {
        hrac.xp -= potreba_xp;
        hrac.lvl++;
        hrac.max_zivoty += 15;
        hrac.akt_zivoty = hrac.max_zivoty;
        hrac.max_mana += 5;
        hrac.akt_mana = hrac.max_mana;
        std::cout << "\n!!! NOVY LEVEL !!! Dosahl jsi urovne " << hrac.lvl << "!\n";
        std::cout << "Max zivoty zvyseny na " << hrac.max_zivoty << "\n\n";
    }
}

// Zobrazeni bojiste
void vypisStavBojiste(Postava &hrac, Monstrum nepratele[], int pocetNepratel)
{
    std::cout << "\n+++++ AKTUALNI STAV BOJISTE +++++\n";
    hrac.vypisKartu();
    std::cout << "NEPRATELE:\n";
    for (int i = 0; i < pocetNepratel; i++)
    {
        if (nepratele[i].akt_zivoty > 0)
        {
            nepratele[i].vypisKartu();
        }
        else
        {
            std::cout << "--- " << nepratele[i].jmeno << " (PADL V BOJI) ---\n\n";
        }
    }
    std::cout << "+++++++++++++++++++++++++++++++++\n\n";
}

// Vesnice
void navstivVesnici(Postava &hrac)
{
    std::cout << "\n=== VSTOUPIL JSI DO VESNICE ===\n";

    int volba = 0;
    while (volba != 5)
    {
        std::cout << "\nCo chces udelat? (Tvoje zlato: " << hrac.penize << ")\n";
        std::cout << "1) Doplnit zivoty (stoji 10 zlata)\n";
        std::cout << "2) Vylepsit maximalni zivoty +10 (stoji 20 zlata)\n";
        std::cout << "3) Vylepsit maximalni manu +5 (stoji 20 zlata)\n";
        std::cout << "4) Vylepsit utok +2 (stoji 30 zlata)\n";
        std::cout << "5) Odejst z vesnice\n";

        volba = nactiVolbu(1, 5);

        if (volba == 1)
        {
            if (hrac.penize >= 10)
            {
                hrac.penize -= 10;
                hrac.akt_zivoty = hrac.max_zivoty;
                std::cout << "Zivoty byly plne doplneny.\n";
            }
            else
            {
                std::cout << "Nemas dost zlata!\n";
            }
        }
        else if (volba == 2)
        {
            if (hrac.penize >= 20)
            {
                hrac.penize -= 20;
                hrac.max_zivoty += 10;
                hrac.akt_zivoty += 10;
                std::cout << "Maximalni zivoty byly zvyseny.\n";
            }
            else
            {
                std::cout << "Nemas dost zlata!\n";
            }
        }
        else if (volba == 3)
        {
            if (hrac.penize >= 20)
            {
                hrac.penize -= 20;
                hrac.max_mana += 5;
                hrac.akt_mana += 5;
                std::cout << "Maximalni mana byla zvysena.\n";
            }
            else
            {
                std::cout << "Nemas dost zlata!\n";
            }
        }
        else if (volba == 4)
        {
            if (hrac.penize >= 30)
            {
                hrac.penize -= 30;
                hrac.utok += 2;
                std::cout << "Tvuj utok byl permanentne posilen.\n";
            }
            else
            {
                std::cout << "Nemas dost zlata!\n";
            }
        }
    }
    std::cout << "Opustil jsi vesnici.\n";
}
int main()
{

    Monstrum Goblin = {
        "Goblin",
        45,
        45,
        {"Bodnuti dykou", 6, 0},
        {"Skrabnuti", 3, 0}};

    Monstrum KamennyGolem = {// mini boss
                             "Kamenny Golem (Mini Boss)",
                             150,
                             150,
                             {"Rozdrceni pesti", 14, 0},
                             {"Hod balvanem", 22, 0}};

    Monstrum StinovyLovec = {// mini boss
                             "Stinovy Lovec (Mini Boss)",
                             110,
                             110,
                             {"Seknuti ze zalohy", 16, 0},
                             {"Temny sip", 26, 0}};

    Postava mag = {
        "Gandalf",
        100,
        100, // zivoty
        30,
        30, // mana
        50,
        1,
        0,
        5, // penize , lvl , xp , zakladni utok
        {"Machnuti holi", 5, 0},
        {"Fireball", 15, 7}};

    Postava Rytir = {
        "Rytir",
        125,
        125, // zivoty
        15,
        15, // mana
        50,
        1,
        0,
        10, // penize , lvl , xp , zakladni utok
        {"Uppercut", 5, 0},
        {"Svizne seknuti", 15, 5}};

    Postava Ninja = {
        "Ninja",
        100,
        100, // zivoty
        20,
        20, // mana
        50,
        1,
        0,
        5, // penize , lvl , xp , zakladni utok
        {"Hazeci hvezdice", 10, 0},
        {"Seknuti katanou", 15, 10}};

    mag.vypisKartu(); // kontrola vypisu hrdinu
    Rytir.vypisKartu();
    Ninja.vypisKartu();

    Goblin.vypisKartu(); // kontrola vypisu monster
    KamennyGolem.vypisKartu();
    StinovyLovec.vypisKartu();

    return 0;
}
