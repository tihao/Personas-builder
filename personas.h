#ifndef PERSONAS_H
#define PERSONAS_H

#include <string>
#include <cmath>
#define MAX_LINE 4
#define MAX_CHAR_DES 100
#define MAX_ARR 34
class Personas {

public:
    Personas();

    bool Login();
    void Register();
    void Menu();
    void Display();
    void Export_File(std::string name_file);
    void Display_Same_Row(std::string str1[MAX_LINE], std::string str2[MAX_LINE], 
                          std::string category1, std::string category2);
    void Display_Same_Row(std::ofstream &outFile, std::string str1[MAX_LINE], std::string str2[MAX_LINE], 
                          std::string category1, std::string category2);
    void Create_Persona();
    void Open_Persona();
    std::string Generate_Key();
    void Save_to_file();
    void Write_buf_file(std::ofstream &outFile, std::string str[MAX_LINE]);
    std::string Encrypt(std::string str);
    std::string Decrupt(std::string str);

    
private:
    struct Info{
        std::string first_name;
        std::string last_name;
        std::string gender;
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
        std::string favorite[MAX_LINE];
        std::string pain_points[MAX_LINE];
        std::string user_quote;
        bool created;
    };

    Info info;
    std::string primary_key;
};

#endif // PERSONAS_H