#ifndef PERSONAS_H
#define PERSONAS_H

#include <string>


class Personas {

public:
    Personas();

    bool Login();
    void Register();
    void Menu();
    void Print();
    void Create_Persona();
    void Encrypt();
    void Decrupt();

    
private:
    struct About{
        std::string first_name;
        std::string last_name;
        unsigned age;
        std::string occupation;
        std::string status;
        std::string location;
        std::string description;
    };

    About about;
};

#endif // PERSONAS_H