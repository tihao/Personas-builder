#ifndef PERSONAS_H
#define PERSONAS_H

#include <string.h>

class Personas {
    Personas();

    void Login();
    void Resiger();
    void Print();
    void Encrypt();
    void Decrupt();

private:
    struct About {
        std::string first_name;
        std::string last_name;
        std::unsigned age;
        std::string occupation;
        std::string status;
        std::string location;
    }
}

#endif /*PERSONAS_H*/