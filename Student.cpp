//////////////////////////////////////////////////////////////////////////////
// Praktikum Informatik 1 MMXXIV
//////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include "Student.h"

// Konstruktor mit Parametern
Student::Student(unsigned int matNr,
                 const std::string& name,
                 const std::string& geburtstag,
                 const std::string& adresse)
    : matNr(matNr), name(name), geburtstag(geburtstag), adresse(adresse)
{ }

// Standardkonstruktor
Student::Student()
    : matNr(0), name(""), geburtstag(""), adresse("")
{ }

// Getter
unsigned int Student::getMatNr() const
{
    return matNr;
}

std::string Student::getName() const
{
    return name;
}

std::string Student::getGeburtstag() const
{
    return geburtstag;
}

std::string Student::getAdresse() const
{
    return adresse;
}

// NEU: Ausgabe in beliebigen ostream (für << Operator oder Datei)
void Student::ausgabe(std::ostream& os) const
{
    os << name << ", MatNr. " << matNr << ", geb. am "
       << geburtstag << ", wohnhaft in " << adresse;
}

// NEU: Operator <
bool Student::operator<(const Student& other) const
{
    return this->matNr < other.matNr;
}

// NEU: Operator >
bool Student::operator>(const Student& other) const
{
    return this->matNr > other.matNr;
}

// NEU: Operator ==
bool Student::operator==(const Student& other) const
{
    return this->matNr == other.matNr;
}

// NEU: Ausgabeoperator <<
std::ostream& operator<<(std::ostream& os, const Student& s)
{
    s.ausgabe(os);
    return os;
}
