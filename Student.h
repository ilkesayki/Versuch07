//////////////////////////////////////////////////////////////////////////////
// Praktikum Informatik 1 MMXXV
// Student.h
//////////////////////////////////////////////////////////////////////////////

#ifndef STUDENT_H_
#define STUDENT_H_

#include <string>
#include <fstream>
#include <iostream>

class Student {
public:
    Student();
    Student(unsigned int matNr, const std::string& name, const std::string& geburtstag, const std::string& adresse);

    unsigned int getMatNr() const;
    std::string getName() const;
    std::string getGeburtstag() const;
    std::string getAdresse() const;

    void setMatNr(unsigned int matNr);
    void setName(const std::string& name);
    void setGeburtstag(const std::string& geburtstag);
    void setAdresse(const std::string& adresse);

    void ausgabe(std::ostream& out) const;

    // Operatorüberladung (matNr basiert)	helps you to sort from bigger to smaller
    bool operator==(const Student& other) const;
    bool operator<(const Student& other) const;
    bool operator>(const Student& other) const;

    // Ausgabeoperator als friend	ostream cant overload inside the Student class
    friend std::ostream& operator<<(std::ostream& out, const Student& s);

private:
    unsigned int matNr;
    std::string name;
    std::string geburtstag;
    std::string adresse;
};

#endif
