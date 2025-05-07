#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>

using namespace std;

class Task {
protected:
    string nume;
public:
    Task(string n) : nume(n) {}
    virtual void afisare() const = 0;
    virtual ~Task() {}
};

class TaskCuTermen : public Task {
    string termen;
public:
    TaskCuTermen(string n, string t) : Task(n), termen(t) {}
    void afisare() const override {
        cout << "Task: " << nume << ", Termen: " << termen << endl;
    }
};

class TaskCuBuget : public Task {
    double buget;
public:
    TaskCuBuget(string n, double b) : Task(n), buget(b) {}
    void afisare() const override {
        cout << "Task: " << nume << ", Buget: " << buget << endl;
    }
};

class TaskComplet : public Task {
    double buget;
    string termen;
public:
    TaskComplet(string n, double b, string t) : Task(n), buget(b), termen(t) {}
    void afisare() const override {
        cout << "Task: " << nume << ", Buget: " << buget << ", Termen: " << termen << endl;
    }
};

class Angajat {
protected:
    string nume;
    double salariu;
    string functie;
    string departament;
    vector<shared_ptr<Task>> taskuri;

public:
    Angajat(string n, double s, string f, string d) :
        nume(n), salariu(s), functie(f), departament(d) {
    }

    virtual void afisare() const = 0;
    virtual double getSalariu() const { return salariu; }
    virtual void setSalariu(double s) { salariu = s; }
    virtual string getNume() const { return nume; }

    void adaugaTask(shared_ptr<Task> task) {
        taskuri.push_back(task);
    }

    void eliminaTask(int index) {
        if (index >= 0 && index < taskuri.size())
            taskuri.erase(taskuri.begin() + index);
    }

    void afisareTaskuri() const {
        cout << "Taskuri pentru " << nume << ":\n";
        for (auto& task : taskuri) task->afisare();
    }

    virtual ~Angajat() {}
};

class Muncitor : public Angajat {
public:
    Muncitor(string n, double s, string d)
        : Angajat(n, s, "Muncitor", d) {
    }

    void afisare() const override {
        cout << "[Muncitor] " << nume << ", Salariu: " << salariu
            << ", Departament: " << departament << endl;
        afisareTaskuri();
    }
};

class Manager : public Angajat {
    vector<shared_ptr<Angajat>> subordonati;

public:
    Manager(string n, double s, string f, string d)
        : Angajat(n, s, f, d) {
    }

    void adaugaSubordonat(shared_ptr<Angajat> a) {
        subordonati.push_back(a);
    }

    void afisare() const override {
        cout << "[Manager - " << functie << "] " << nume << ", Salariu: " << salariu
            << ", Departament: " << departament << endl;
        afisareTaskuri();
        cout << "Subordonati:\n";
        for (auto& sub : subordonati)
            sub->afisare();
    }

    vector<shared_ptr<Angajat>>& getSubordonati() { return subordonati; }
};

#endif
