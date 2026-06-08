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

// Souboje
bool spustSouboj(Postava &hrac, Monstrum nepratele[], int pocetNepratel, bool jeTuBoss)
{
    std::cout << "\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
    std::cout << "ZACINA SOUBOJ! Pocet nepratel: " << pocetNepratel << "\n";
    std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";

    bool hracNaTahu = true;
    if (jeTuBoss)
    {
        hracNaTahu = false;
        std::cout << "V bitve je silny nepritel! Monstra utoci jako prvni!\n";
    }

    int tahBosse = 1;
    vypisStavBojiste(hrac, nepratele, pocetNepratel);

    while (hrac.akt_zivoty > 0)
    {

        // Kontrola smrti nepřátel
        bool vsemrtvi = true;
        for (int i = 0; i < pocetNepratel; i++)
        {
            if (nepratele[i].akt_zivoty > 0)
            {
                vsemrtvi = false;
                break;
            }
        }

        if (vsemrtvi)
        {
            std::cout << "\nZavitazil jsi v tomto souboji!\n";

            // Odmeny
            for (int i = 0; i < pocetNepratel; i++)
            {
                if (nepratele[i].jmeno == "Cyclechon (HLAVNI BOSS)")
                    continue;

                if (nepratele[i].jmeno == "Kamenny Golem (Mini Boss)" || nepratele[i].jmeno == "Stinovy Lovec (Mini Boss)")
                {
                    hrac.xp += 150;
                    int zlato = 40 + rand() % 21;
                    hrac.penize += zlato;
                    std::cout << "Za Mini-Bosse ziskavas 150 XP a " << zlato << " zlata.\n";
                }
                else
                {
                    hrac.xp += 50;
                    std::cout << "Za monstrum ziskavas 50 XP. ";
                    if (rand() % 2 == 0)
                    {
                        int zlato = 10 + rand() % 16;
                        hrac.penize += zlato;
                        std::cout << "Nasel jsi u nej " << zlato << " zlata.\n";
                    }
                    else
                    {
                        std::cout << "Monstrum nemelo zadne penize.\n";
                    }
                }
            }
            zkontrolujLevelUp(hrac);
            return true;
        }

        // Muj tah
        if (hracNaTahu)
        {
            std::cout << "\n--- TVUJ TAH ---\n";
            std::cout << "Vyber utok:\n1) " << hrac.hlavniUtok.jmeno << "\n2) " << hrac.sekundarniUtok.jmeno << "\n";
            int volbaUtoku = nactiVolbu(1, 2);

            int dmg = 0;
            if (volbaUtoku == 1)
            {
                dmg = hrac.hlavniUtok.poskozeni + hrac.utok;
            }
            else
            {
                if (hrac.akt_mana >= hrac.sekundarniUtok.cena_utoku)
                {
                    hrac.akt_mana -= hrac.sekundarniUtok.cena_utoku;
                    dmg = hrac.sekundarniUtok.poskozeni + hrac.utok;
                }
                else
                {
                    std::cout << "Nemas dost many! Pouzivam zakladni utok.\n";
                    dmg = hrac.hlavniUtok.poskozeni + hrac.utok;
                }
            }

            // utok postupne
            int cilIndex = -1;
            for (int i = 0; i < pocetNepratel; i++)
            {
                if (nepratele[i].akt_zivoty > 0)
                {
                    cilIndex = i;
                    break;
                }
            }

            if (cilIndex != -1)
            {
                nepratele[cilIndex].akt_zivoty -= dmg;
                std::cout << "Automaticky utocis na " << nepratele[cilIndex].jmeno << " a zpusobujes " << dmg << " DMG!\n";
                if (nepratele[cilIndex].akt_zivoty <= 0)
                {
                    nepratele[cilIndex].akt_zivoty = 0;
                    std::cout << nepratele[cilIndex].jmeno << " byl porazen!\n";
                }
            }

            vypisStavBojiste(hrac, nepratele, pocetNepratel);
            hracNaTahu = false;
        }
        // Jejih tah
        else
        {
            std::cout << "\n--- TAH NEPRATEL ---\n";
            for (int i = 0; i < pocetNepratel; i++)
            {
                if (nepratele[i].akt_zivoty <= 0)
                    continue;

                if (nepratele[i].jmeno == "Cyclechon (HLAVNI BOSS)")
                {
                    std::cout << "\n*** Cyclechon provadi tah cislo " << tahBosse << " ***\n";

                    if (tahBosse % 3 == 0)
                    {
                        nepratele[i].akt_zivoty += 3;
                        std::cout << "-> Kazde treti kolo: Boss se regeneruje o +3 HP.\n";
                    }
                    if (nepratele[i].akt_zivoty > nepratele[i].max_zivoty)
                    {
                        nepratele[i].akt_zivoty = nepratele[i].max_zivoty;
                    }

                    int nahoda = 1 + rand() % 4;
                    int bossDmg = (tahBosse * nahoda) + 5;

                    std::cout << "-> Vzorec (Vyzva): (" << tahBosse << " * " << nahoda << ") + 5 = " << bossDmg << " DMG!\n";
                    hrac.akt_zivoty -= bossDmg;
                    std::cout << "Cyclechon ti udelil " << bossDmg << " poskozeni.\n";

                    tahBosse++;
                }
                else
                {
                    int volbaMonstra = rand() % 2;
                    int mDmg = 0;
                    if (volbaMonstra == 0)
                    {
                        mDmg = nepratele[i].hlavniUtok.poskozeni;
                        std::cout << nepratele[i].jmeno << " pouzil " << nepratele[i].hlavniUtok.jmeno << " a dal ti " << mDmg << " DMG.\n";
                    }
                    else
                    {
                        mDmg = nepratele[i].sekundarniUtok.poskozeni;
                        std::cout << nepratele[i].jmeno << " pouzil " << nepratele[i].sekundarniUtok.jmeno << " a dal ti " << mDmg << " DMG.\n";
                    }
                    hrac.akt_zivoty -= mDmg;
                }

                if (hrac.akt_zivoty <= 0)
                {
                    hrac.akt_zivoty = 0;
                    return false;
                }
            }

            vypisStavBojiste(hrac, nepratele, pocetNepratel);
            hracNaTahu = true;
        }
    }
    return false;
}

int main()
{
    srand(time(0));

    std::cout << "=============================================\n";
    std::cout << "          VITEJ VE HRE CYCLECHON RPG         \n";
    std::cout << "=============================================\n";

    Monstrum Goblin = {"Goblin", 35, 35, {"Bodnuti dykou", 6, 0}, {"Skrabnuti", 3, 0}};
    Monstrum KamennyGolem = {"Kamenny Golem (Mini Boss)", 85, 85, {"Rozdrceni pesti", 8, 0}, {"Hod balvanem", 11, 0}};
    Monstrum StinovyLovec = {"Stinovy Lovec (Mini Boss)", 100, 100, {"Seknuti ze zalohy", 14, 0}, {"Temny sip", 20, 0}};
    Monstrum Cyclechon = {"Cyclechon (HLAVNI BOSS)", 200, 200, {"Casovy utok", 0, 0}, {"Algoritmus", 0, 0}};

    Postava hrac;
    bool potvrzeno = false;
    while (!potvrzeno)
    {
        std::cout << "\nVyber si svou classu:\n";
        std::cout << "1) Gandalf (Mag)\n2) Rytir\n3) Ninja\n";
        int volba = nactiVolbu(1, 3);

        if (volba == 1)
        {
            hrac = {"Gandalf", 100, 100, 30, 30, 50, 1, 0, 5, {"Machnuti holi", 5, 0}, {"Fireball", 15, 7}};
        }
        else if (volba == 2)
        {
            hrac = {"Rytir", 125, 125, 15, 15, 50, 1, 0, 10, {"Uppercut", 5, 0}, {"Svizne seknuti", 15, 5}};
        }
        else if (volba == 3)
        {
            hrac = {"Ninja", 100, 100, 20, 20, 50, 1, 0, 5, {"Hazeci hvezdice", 10, 0}, {"Seknuti katanou", 15, 10}};
        }

        std::cout << "\nZvolil jsi tuto postavu:\n";
        hrac.vypisKartu();
        std::cout << "Chces potvrdit vyber? \n1) Ano\n2) Ne, vybrat znovu\n";
        if (nactiVolbu(1, 2) == 1)
        {
            potvrzeno = true;
        }
    }

    int aktualniBitva = 1;
    bool hracZije = true;
    bool vyhra = false;

    while (hracZije && aktualniBitva <= 12)
    {
        std::cout << "\n---------------------------------------------\n";
        std::cout << "JSI NA TAHU SVETA. Bitva pred tebou: " << aktualniBitva << " / 12\n";
        std::cout << "---------------------------------------------\n";
        std::cout << "Co chces udelat?\n";
        std::cout << "1) Jit do vesnice (nakoupit / vylecit se)\n";
        std::cout << "2) Vyrazit na utok (posunout se v ceste dregem)\n";

        int akce = nactiVolbu(1, 2);

        if (akce == 1)
        {
            navstivVesnici(hrac);
        }
        else if (akce == 2)
        {
            if (aktualniBitva == 1)
            {
                Monstrum boj[1] = {Goblin};
                hracZije = spustSouboj(hrac, boj, 1, false);
            }
            else if (aktualniBitva == 2)
            {
                Monstrum boj[1] = {Goblin};
                hracZije = spustSouboj(hrac, boj, 1, false);
            }
            else if (aktualniBitva == 3)
            {
                Monstrum boj[2] = {Goblin, Goblin};
                hracZije = spustSouboj(hrac, boj, 2, false);
            }
            else if (aktualniBitva == 4)
            {
                Monstrum boj[1] = {KamennyGolem};
                hracZije = spustSouboj(hrac, boj, 1, true);
            }
            else if (aktualniBitva == 5)
            {
                Monstrum boj[1] = {Goblin};
                hracZije = spustSouboj(hrac, boj, 1, false);
            }
            else if (aktualniBitva == 6)
            {
                Monstrum boj[2] = {Goblin, Goblin};
                hracZije = spustSouboj(hrac, boj, 2, false);
            }
            else if (aktualniBitva == 7)
            {
                Monstrum boj[2] = {Goblin, Goblin};
                hracZije = spustSouboj(hrac, boj, 2, false);
            }
            else if (aktualniBitva == 8)
            {
                Monstrum boj[1] = {StinovyLovec};
                hracZije = spustSouboj(hrac, boj, 1, true);
            }
            else if (aktualniBitva == 9)
            {
                Monstrum boj[2] = {Goblin, Goblin};
                hracZije = spustSouboj(hrac, boj, 2, false);
            }
            else if (aktualniBitva == 10)
            {
                Monstrum boj[2] = {Goblin, Goblin};
                hracZije = spustSouboj(hrac, boj, 2, false);
            }
            else if (aktualniBitva == 11)
            {
                Monstrum boj[3] = {Goblin, Goblin, Goblin};
                hracZije = spustSouboj(hrac, boj, 3, false);
            }
            else if (aktualniBitva == 12)
            {
                Monstrum boj[1] = {Cyclechon};
                hracZije = spustSouboj(hrac, boj, 1, true);
                if (hracZije)
                {
                    vyhra = true;
                }
            }

            if (hracZije && !vyhra)
            {
                aktualniBitva++;
            }
        }
    }

    // Vypis vysledku a nasledne vypnuti PC
    if (vyhra)
    {
        std::cout << "\n==================================================\n";
        std::cout << " OZNAMENI: PORAZIL JSI CYCLECHONA A VYHRAL JSI HRU!\n";
        std::cout << "==================================================\n";
        std::cout << "Pocitac se vypne za 30 sekund jako odmena za tvoje vitezstvi!\n";
    }
    else
    {
        std::cout << "\n==================================================\n";
        std::cout << " PROHRAL JSI! Prisel jsi o vsechny zivoty. Game Over.\n";
        std::cout << "==================================================\n";
        std::cout << "Pocitac se vypne za 30 sekund. Zkus to priste znovu!\n";
    }

    // Příkaz pro vypnutí systému Windows (/s = shutdown, /t 30 = casovac na 30 vterin)
    std::system("shutdown /s /t 30");

    return 0;
}