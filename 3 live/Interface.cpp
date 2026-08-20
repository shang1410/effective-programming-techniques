//
// Created by XYZ on 15.11.2025.
//

#include "Interface.h"
#include "ValueList.h"
#include <iostream>
#include <sstream>

using namespace std;

void Interface::printHelp() const {
    cout << "Dostepne polecenia:\n";
    cout << "  enter <formula> - wczytaj wyrazenie w notacji prefiksowej\n";
    cout << "  vars - wyswietl zmienne\n" ;
    cout << "  print - wyswietl drzewo\n";
    cout << "  comp <val1> <val2> ... - oblicz wartosc\n";
    cout << "  join <formula> - polacz z nowym wyrazeniem\n";
    cout << "  help - wyswietl pomoc\n";
    cout << "  exit - zakoncz program\n";
    cout << "  draw - rysowanie\n";
}

void Interface::run() {
    cout << "System drzew wyrazen matematycznych\n";
    cout << "Wpisz 'help' aby uzyskac pomoc\n\n";

    string line;
    while (true) {
        cout << "> ";
        getline(cin, line);

        istringstream iss(line);
        string command;
        iss >> command;

        if (command == "exit" || command == "quit") {
            break;
        } else if (command == "help") {
            printHelp();
        } else if (command == "enter") {
            string formula;
            getline(iss, formula);
            tree.enter(formula);
        } else if (command == "print") {
            tree.print();
        } else if (command == "vars") {
            tree.printVars();
        } else if (command == "comp") {
            ValueList valueList;
            double val;
            while (iss >> val) {
                valueList.add(val);
            }
            tree.compute(valueList.getValues(), valueList.getCount());
        } else if (command == "join") {
            string formula;
            getline(iss, formula);
            Tree newTree;
            newTree.enter(formula);
            tree = tree + newTree;
            cout << "Polaczono drzewa. Nowe drzewo: " << tree.toString() << "\n";
        } else if (command == "draw") {
            cout << (tree.draw());
        }

        else if (!command.empty()) {
            cout << "Nieznane polecenie: " << command << "\n";
        }
    }
}