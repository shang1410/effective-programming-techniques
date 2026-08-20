//
// Created by XYZ on 15.11.2025.
//

#include "Interface.h"
#include "ValueList.h"
#include "ResultSaver.h"
#include <iostream>
#include <sstream>

using namespace std;

void Interface::printHelp() const {
    cout << "Dostepne polecenia:\n";
    cout << "  enter <formula> - wczytaj wyrazenie w notacji prefiksowej\n";
    cout << "  vars - wyswietl zmienne\n";
    cout << "  print - wyswietl drzewo\n";
    cout << "  comp <val1> <val2> ... - oblicz wartosc\n";
    cout << "  join <formula> - polacz z nowym wyrazeniem\n";
    cout << "  save <filename> - zapisz ostatni wynik do pliku\n";
    cout << "  help - wyswietl pomoc\n";
    cout << "  exit - zakoncz program\n";
    cout << "  draw - rysowanie\n";
}

void Interface::run() {
    cout << "System drzew wyrazen matematycznych\n";
    cout << "Wpisz 'help' aby uzyskac pomoc\n\n";

    Result<Tree*, Error>* lastResult = NULL;
    string line;

    while (true) {
        cout << "> ";
        getline(cin, line);

        istringstream iss(line);
        string command;
        iss >> command;

        if (command == "exit" || command == "quit") {
            break;
        }
        else if (command == "help") {
            printHelp();
        }
        else if (command == "enter") {
            string formula;
            getline(iss, formula);

            Result<Tree, Error> result = tree.enter(formula);

            if (result.isSuccess()) {
                tree = result.getValue();
                cout << "Drzewo utworzone pomyslnie: " << tree.toString() << endl;

                // Zapisz sukces do lastResult
                if (lastResult != NULL) delete lastResult;
                lastResult = new Result<Tree*, Error>(Result<Tree*, Error>::okClass(&tree));

            } else {
                vector<Error*>& errors = result.getErrors();
                cout << "Blad tworzenia drzewa:" << endl;
                for (size_t i = 0; i < errors.size(); i++) {
                    cout << "  - " << errors[i]->getDescription() << endl;
                }
                cout << "Drzewo nie zostalo zmienione." << endl;

                // Zapisz bledy do lastResult
                if (lastResult != NULL) delete lastResult;
                vector<Error*> errorsCopy;
                for (size_t i = 0; i < errors.size(); i++) {
                    errorsCopy.push_back(new Error(errors[i]->getDescription()));
                }
                lastResult = new Result<Tree*, Error>(Result<Tree*, Error>::failClass(errorsCopy));
            }
        }
        else if (command == "print") {
            tree.print();
        }
        else if (command == "vars") {
            tree.printVars();
        }
        else if (command == "comp") {
            ValueList valueList;
            double val;
            while (iss >> val) {
                valueList.add(val);
            }

            try {
                tree.compute(valueList.getValues(), valueList.getCount());
            }
            catch (const std::invalid_argument& e) {
                cerr << "Blad podczas obliczen: " << e.what() << endl;
            }
        }
        else if (command == "join") {
            string formula;
            getline(iss, formula);

            Tree tempTree;
            Result<Tree, Error> result = tempTree.enter(formula);

            if (result.isSuccess()) {
                Tree newTree = result.getValue();
                tree = tree + newTree;
                cout << "Polaczono drzewa. Nowe drzewo: " << tree.toString() << endl;

                // Zapisz sukces
                if (lastResult != NULL) delete lastResult;
                lastResult = new Result<Tree*, Error>(Result<Tree*, Error>::okClass(&tree));

            } else {
                vector<Error*>& errors = result.getErrors();
                cout << "Nie mozna polaczyc - blad w nowym wyrazeniu:" << endl;
                for (size_t i = 0; i < errors.size(); i++) {
                    cout << "  - " << errors[i]->getDescription() << endl;
                }

                // Zapisz bledy
                if (lastResult != NULL) delete lastResult;
                vector<Error*> errorsCopy;
                for (size_t i = 0; i < errors.size(); i++) {
                    errorsCopy.push_back(new Error(errors[i]->getDescription()));
                }
                lastResult = new Result<Tree*, Error>(Result<Tree*, Error>::failClass(errorsCopy));
            }
        }
        else if (command == "save") {
            string filename;
            iss >> filename;

            if (filename.empty()) {
                cout << "Podaj nazwe pliku: save <filename>" << endl;
            } else if (lastResult == NULL) {
                cout << "Brak wyniku do zapisania. Najpierw wykonaj operacje enter lub join." << endl;
            } else {
                bool saved = ResultSaver<Tree*>::save(filename, *lastResult);
                if (saved) {
                    cout << "Zapisano wynik do pliku: " << filename << endl;
                } else {
                    cout << "Nie udalo sie zapisac do pliku: " << filename << endl;
                }
            }
        }
        else if (command == "draw") {
            cout << tree.draw();
        }
        else if (!command.empty()) {
            cout << "Nieznane polecenie: " << command << endl;
        }
    }

    if (lastResult != NULL) delete lastResult;
}