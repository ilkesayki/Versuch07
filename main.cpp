/** @mainpage
 *
 * Praktikum Informatik 1 MMXXIV <BR>
 * Versuch 7: Dynamische Datenstrukturen (mit erweitertem Menü)
 *
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include "Student.h"

// Read student data from a file
void datenEinlesen(std::vector<Student>& liste, const std::string& dateiname) {
    std::ifstream datei(dateiname);
    if (!datei) {
        std::cerr << "Datei konnte nicht geöffnet werden!" << std::endl;
        return;
    }

    liste.clear();
    unsigned int matrikelnummer;
    std::string name, geburtstag, adresse;
    std::string zeile;

    while (std::getline(datei, zeile)) {
        if (zeile.empty()) continue;
        matrikelnummer = std::stoul(zeile);
        std::getline(datei, name);
        std::getline(datei, geburtstag);
        std::getline(datei, adresse);
        liste.push_back(Student(matrikelnummer, name, geburtstag, adresse));
    }

    datei.close();
    std::cout << "Daten wurden erfolgreich eingelesen." << std::endl;
}

// Save student data to a file
void datenSpeichern(const std::vector<Student>& liste, const std::string& dateiname) {
    if (liste.empty()) {
        std::cout << "Liste ist leer, nichts zu speichern." << std::endl;
        return;
    }

    std::ofstream datei(dateiname);
    if (!datei) {
        std::cerr << "Datei konnte nicht geöffnet werden!" << std::endl;
        return;
    }

    for (const Student& s : liste) {
        datei << s.getMatNr() << std::endl;
        datei << s.getName() << std::endl;
        datei << s.getGeburtstag() << std::endl;
        datei << s.getAdresse() << std::endl;
    }

    datei.close();
    std::cout << "Daten wurden gespeichert." << std::endl;
}

// Print students in normal order
void studentenAusgeben(const std::vector<Student>& liste) {
    if (liste.empty()) {
        std::cout << "Liste ist leer." << std::endl;
        return;
    }

    for (const auto& s : liste) {
        std::cout << s << std::endl
                  << "------------------------" << std::endl;
    }
}

// Print students in reverse order
void studentenRueckwaertsAusgeben(const std::vector<Student>& liste) {
    if (liste.empty()) {
        std::cout << "Liste ist leer." << std::endl;
        return;
    }

    for (auto it = liste.rbegin(); it != liste.rend(); ++it) {
        std::cout << *it << std::endl
                  << "------------------------" << std::endl;
    }
}

// Delete the first student in the list
void studentVorneLoeschen(std::vector<Student>& liste) {
    if (liste.empty()) {
        std::cout << "Liste ist leer." << std::endl;
        return;
    }

    liste.erase(liste.begin());
    std::cout << "Erster Student wurde gelöscht." << std::endl;
}

// Sort students by matriculation number
void listeSortieren(std::vector<Student>& liste) {
    if (liste.empty()) {
        std::cout << "Liste ist leer." << std::endl;
        return;
    }

    std::sort(liste.begin(), liste.end());
    std::cout << "Liste wurde nach Matrikelnummer sortiert." << std::endl;
}

// Search and delete student by matriculation number
bool datenelementLoeschen(std::vector<Student>& liste, unsigned int matNr) {
    auto it = std::find_if(liste.begin(), liste.end(), [matNr](const Student& s) {
        return s.getMatNr() == matNr;
    });
    if (it != liste.end()) {
        liste.erase(it);
        return true;
    }
    return false;
}

int main() {
    std::vector<Student> studentenListe;
    Student student;
    char abfrage;
    std::string dateiname;

    do {
        std::cout << "\nMenue:" << std::endl
                  << "-----------------------------" << std::endl
                  << "(1): Datenelement hinten hinzufuegen" << std::endl
                  << "(2): Datenelement vorne entfernen" << std::endl
                  << "(3): Datenbank ausgeben" << std::endl
                  << "(4): Datenbank in umgekehrter Reihenfolge ausgeben" << std::endl
                  << "(5): Datenelement loeschen" << std::endl
                  << "(6): Datenelement vorne hinzufuegen" << std::endl
                  << "(7): Studenten aus Datei einlesen" << std::endl
                  << "(8): Studenten in Datei speichern" << std::endl
                  << "(9): Studentenliste sortieren" << std::endl
                  << "(0): Beenden" << std::endl;
        std::cin >> abfrage;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (abfrage) {
            case '1':
            case '6': {
                unsigned int matNr;
                std::string name, geburtstag, adresse;
                std::cout << "Name: ";
                std::getline(std::cin, name);
                std::cout << "Geburtsdatum: ";
                std::getline(std::cin, geburtstag);
                std::cout << "Adresse: ";
                std::getline(std::cin, adresse);
                std::cout << "Matrikelnummer: ";
                std::cin >> matNr;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                student = Student(matNr, name, geburtstag, adresse);
                if (abfrage == '1')
                    studentenListe.push_back(student);
                else
                    studentenListe.insert(studentenListe.begin(), student);
                break;
            }
            case '2':
                studentVorneLoeschen(studentenListe);
                break;
            case '3':
                studentenAusgeben(studentenListe);
                break;
            case '4':
                studentenRueckwaertsAusgeben(studentenListe);
                break;
            case '5': {
                unsigned int matNr;
                std::cout << "Matrikelnummer zum Loeschen: ";
                std::cin >> matNr;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                if (datenelementLoeschen(studentenListe, matNr)) {
                    std::cout << "Student geloescht." << std::endl;
                    studentenAusgeben(studentenListe);
                }
                else {
                    std::cout << "Student nicht gefunden." << std::endl;
                }
                break;
            }
            case '7':
                std::cout << "Dateiname eingeben: ";
                std::getline(std::cin, dateiname);
                datenEinlesen(studentenListe, dateiname);
                break;
            case '8':
                std::cout << "Dateiname zum Speichern: ";
                std::getline(std::cin, dateiname);
                datenSpeichern(studentenListe, dateiname);
                break;
            case '9':
                listeSortieren(studentenListe);
                break;
            case '0':
                std::cout << "Programm wird beendet." << std::endl;
                break;
            default:
                std::cout << "Ungueltige Eingabe." << std::endl;
        }
    } while (abfrage != '0');

    return 0;
}
