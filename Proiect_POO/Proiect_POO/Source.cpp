#include "Header.h"

int main() {
    vector<shared_ptr<Angajat>> angajati;

    auto ceo = make_shared<Manager>("Popescu Andrei", 15000, "CEO", "Conducere");

    auto sefIT = make_shared<Manager>("Ionescu Maria", 10000, "Sef Departament", "IT");

    auto teamLead1 = make_shared<Manager>("Georgescu Radu", 7000, "Team Leader", "IT");
    auto teamLead2 = make_shared<Manager>("Lazar Ana", 6800, "Team Leader", "IT");

    auto muncitor1 = make_shared<Muncitor>("Dumitru Ion", 4000, "IT");
    auto muncitor2 = make_shared<Muncitor>("Barbu Elena", 4200, "IT");

    teamLead1->adaugaSubordonat(muncitor1);
    teamLead2->adaugaSubordonat(muncitor2);
    sefIT->adaugaSubordonat(teamLead1);
    sefIT->adaugaSubordonat(teamLead2);
    ceo->adaugaSubordonat(sefIT);

    muncitor1->adaugaTask(make_shared<TaskCuTermen>("Reparare server", "2025-05-15"));
    muncitor2->adaugaTask(make_shared<TaskCuBuget>("Achiziție software", 5000));
    teamLead1->adaugaTask(make_shared<TaskComplet>("Raport echipă", 1000, "2025-05-20"));

    angajati.push_back(ceo);

    int opt;
    do {
        cout << "\n1. Afisare angajati\n";
        cout << "2. Total salarii\n";
        cout << "3. Adaugare angajat\n";
        cout << "4. Modificare salariu\n";
        cout << "5. Adaugare task\n";
        cout << "6. Eliminare task\n";
        cout << "0. Iesire\n";
        cout << "Optiune: ";
        cin >> opt;

        if (opt == 1) {
            for (auto& a : angajati)
                a->afisare();
        }
        else if (opt == 2) {
            double total = 0;
            for (auto& a : angajati)
                total += a->getSalariu();
            cout << "Total salarii: " << total << endl;
        }
        else if (opt == 3) {
            string nume, dept;
            double salariu;
            cout << "Nume: "; cin >> ws; getline(cin, nume);
            cout << "Salariu: "; cin >> salariu;
            cout << "Departament: "; cin >> dept;
            angajati.push_back(make_shared<Muncitor>(nume, salariu, dept));
            cout << "Angajat adaugat.\n";
        }
        else if (opt == 4) {
            string nume;
            double nou;
            cout << "Nume angajat: "; cin >> ws; getline(cin, nume);
            bool gasit = false;
            for (auto& a : angajati) {
                if (a->getNume() == nume) {
                    cout << "Salariu nou: "; cin >> nou;
                    a->setSalariu(nou);
                    gasit = true;
                    break;
                }
            }
            if (!gasit) cout << "Angajatul nu a fost gasit.\n";
        }
        else if (opt == 5) {
            string nume;
            cout << "Nume angajat: "; cin >> ws; getline(cin, nume);
            for (auto& a : angajati) {
                if (a->getNume() == nume) {
                    a->adaugaTask(make_shared<TaskCuTermen>("Nou Task", "2025-06-01"));
                    cout << "Task adaugat.\n";
                    break;
                }
            }
        }
        else if (opt == 6) {
            string nume;
            cout << "Nume angajat: "; cin >> ws; getline(cin, nume);
            for (auto& a : angajati) {
                if (a->getNume() == nume) {
                    a->eliminaTask(0);
                    cout << "Primul task eliminat (daca exista).\n";
                    break;
                }
            }
        }

    } while (opt != 0);

    return 0;
}
