#ifndef PERSONAS_H
#define PERSONAS_H

#include <string>
#define MAX_LINE 4

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
    struct Info{
        std::string first_name;
        std::string last_name;
        unsigned age;
        std::string occupation;
        std::string education;
        std::string status;
        std::string location;
        std::string description;
        std::string goal[MAX_LINE];
        std::string need[MAX_LINE];
        std::string tech[MAX_LINE];
        unsigned tech_rate[MAX_LINE];
    };

    Info info;
};

#endif // PERSONAS_H