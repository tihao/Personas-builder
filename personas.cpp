#include "personas.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <ctime>
#include <stdlib.h>
Personas::Personas(){

}

bool Personas::Login(){
    std::string user_name;
    std::string pwd;
    std::string line;
    bool check_pwd = false;
    std::ifstream inFile;
    inFile.open("data.csv");
    if(inFile.is_open()) {
        std::cout << "File is opened\n";
    }
    else
        std::cout << "File is not opened\n";


    std::cout << "Username: ";
    std::cin >> user_name;

    while(inFile.good()) {
        if (check_pwd == false) {

            std::getline(inFile, line, ',');
            if(line != user_name){
                inFile.ignore(1000, '\n');
                continue;
            }
        }
        else if(check_pwd == true){
            std::cout << "Password: ";
            std::cin >> pwd;
            if(line != pwd) {
                std::cout << "Wrong password\n";
                continue;
            }
            else
                break;
        }
        
        std::getline(inFile, line, ',');
        std::cout << line << std::endl;
        std::cout << "Password: ";
        std::cin >> pwd;
        if(line != pwd) {
            std::cout << "Wrong password\n";
            check_pwd = true;
            continue;
        }
        else
            break;
    }
    if (inFile.eof() == true)
    {
        std::cout << "Not correct user name";
        inFile.close();
        return false;
    }
    
    inFile.close();
    return true;
}

void Personas::Register() {
    std::string user_name;
    std::string pwd;
    std::string confirm_pwd;

    std::cout << "Enter user name: ";
    std::cin >> user_name;
    std::cout << "Enter password: ";
    std::cin >> pwd;
    
    do {
        std::cout << "Confirm password: ";
        std::cin >> confirm_pwd; 
    } while(pwd != confirm_pwd);

    std::ofstream outFile;
    outFile.open("data.csv", std::ios::app);
    if(outFile.is_open()) {
        std::cout << "File is opened\n";
    }
    else
        std::cout << "File is not opened\n";

    outFile << user_name + "," + pwd + ",";
    primary_key = Generate_Key();
    // std::srand(static_cast<unsigned int>(std::time(nullptr)));

    outFile << Generate_Key() + primary_key + Generate_Key() + "\n";
    outFile.close();
}
bool Take_Text_Line(std::string text[MAX_LINE]);
void Personas::Create_Persona() {
    // Demographics;
    // std::cin.clear();
    std::cout << "=============================================\n";
    std::cout << "Fill out information about user demograpghics\n";
    std::cout << "=============================================\n";
    std::cout << "Enter first name: ";
    std::cin >> info.first_name;
    std::cout << "Enter last name: ";
    std::cin >> info.last_name;

    // Make sure user input is numeric
    std::cout << "Enter age: ";
    while (true)
    {
        std::cin >> info.age;
        if (!info.age)
        {
            std::cin.clear();
            std::cout << "Error!! Please enter number for age\n";
            std::cout << "Enter age: ";
            std::cin.ignore();
            continue;
        }
        break;
    }

    std::cin.ignore();
    std::cout << "Enter occupation: ";
    getline(std::cin, info.occupation);
    std::cout << "Enter education: ";
    getline(std::cin, info.education);    
    std::cout << "Enter status: ";
    std::cin >> info.status;
    std::cin.ignore();
    std::cout << "Enter location: ";
    getline(std::cin, info.location);
    std::cout << "Bio Description: ";
    getline(std::cin, info.description);

    //Technology
    std::cout << "=============================================\n";
    std::cout << "Fill out information about user technology\n";
    std::cout << "press \"Enter\" when the line is empty or type \"None\" to finish fill out \n"; 
    std::cout << "Maximum 4 text line\n";
    std::cout << "=============================================\n";
    Take_Text_Line(info.tech);

    std::cout << "Rate user tech in scale 1 to 5\n";
    std::cout << "=============================================\n";
    int i = 0;
    while(!info.tech[i].empty()) {
        std::cout << info.tech[i] << ": ";
        std::cin >> info.tech_rate[i];
        if((!info.tech_rate[i]) || (info.tech_rate[i] > 5) ){
            std::cin.clear();
            std::cout << "Error!! Rating is nummeric and in range from 1 to 5\n";
            std::cin.ignore();
            continue;
        }

        i++;
        if (i == MAX_LINE) {
            break;
        }
    }

    std::cin.ignore();
    //Goals
    std::cout << "=============================================\n";
    std::cout << "Fill out information about user goals\n";
    std::cout << "press \"Enter\" when the line is empty or type \"None\" to finish fill out \n";    
    std::cout << "Maximum 4 text line\n";
    std::cout << "=============================================\n";
    Take_Text_Line(info.goal);
    //Needs
    std::cout << "=============================================\n";
    std::cout << "Fill out information about user needs\n";
    std::cout << "press \"Enter\" when the line is empty or type \"None\" to finish fill out \n";
    std::cout << "Maximum 4 text line\n";
    std::cout << "=============================================\n";
    Take_Text_Line(info.need);
   
    std::cout << "=============================================\n";
    std::cout << "Fill out information about user favorite apps\n";
    std::cout << "press \"Enter\" when the line is empty or type \"None\" to finish fill out \n";
    std::cout << "Maximum 4 text line\n";
    std::cout << "=============================================\n";    
    Take_Text_Line(info.favorite_app);

    std::cout << "=============================================\n";
    std::cout << "Fill out information about user paint points\n";
    std::cout << "press \"Enter\" when the line is empty or type \"None\" to finish fill out \n";
    std::cout << "Maximum 4 text line\n";
    std::cout << "=============================================\n";
    Take_Text_Line(info.pain_points);

    std::cout << "Enter user quote: ";
    getline(std::cin, info.user_quote);
}

bool Take_Text_Line(std::string text[MAX_LINE]) {
    std::string temp_text;

    for (int i = 0; i < MAX_LINE; i++)
    {
        std::cout << "- ";
        getline(std::cin, text[i]);
        temp_text = text[i];
        transform(temp_text.begin(), temp_text.end(), temp_text.begin(), ::toupper);
        if ((temp_text == "NONE") || (text[i] == ""))
        {
            text[i] = "";
            return false;
        }
    }

    return true;
}

std::string Personas::Generate_Key() {
    std::string primary_key = "";
    unsigned length = 10;
    char ch;
    // std::srand(static_cast<unsigned int>(std::time(nullptr)));
    for(int i = 0; i < length; i++) {
        ch = '!' + std::rand() % 93;
        primary_key += ch;
    }
    // std::srand(static_cast<unsigned int>(std::time(nullptr)));
    return primary_key;
}
void Personas::Menu() {
    char user_input;
    std::cout << "[C]reate a new persona\n";
    std::cout << "[O]pen an exist persona\n";
    std::cout << "[E]dit a persona\n";
    std::cout << "[D]elete a persona\n";
    std::cout << "[L]og out\n";
    std::cout << "Enter: ";
    std::cin >> user_input;
    user_input = toupper(user_input);
    switch (user_input)
    {
    case 'C':
        Create_Persona();
        break;
    
    default:
        break;
    }

    
}