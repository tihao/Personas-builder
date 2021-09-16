#ifndef PERSONAS_H
#define PERSONAS_H

#include <string>

class Personas {

public:
    Personas();

    bool Login();
    void Register();
    void Print();
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
    };
};

#endif // PERSONAS_H