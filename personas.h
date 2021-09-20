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
    std::string Generate_Key();
    void Save_to_file();
    void Write_buf_file(std::ofstream &outFile, std::string str[MAX_LINE]);
    std::string Encrypt(std::string str);
    std::string Decrupt(std::string str);

    
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
        std::string favorite_app[MAX_LINE];
        std::string pain_points[MAX_LINE];
        std::string user_quote;
    };

    Info info;
    std::string primary_key;
};

#endif // PERSONAS_H