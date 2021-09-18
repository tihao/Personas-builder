#include "personas.h"
#include <iostream>
#include <fstream>

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
    outFile.open("data.csv");
    if(outFile.is_open()) {
        std::cout << "File is opened\n";
    }
    else
        std::cout << "File is not opened\n";

    outFile << user_name + "," + pwd + ",";
    outFile.close();
}

void Personas::Create_Persona() {
    // About about;
    std::cout << "Enter first name: ";
    std::cin >> about.first_name;
    std::cout << "Enter last name: ";
    std::cin >> about.last_name;
    std::cout << "Enter age: ";
    std::cin >> about.age;
    std::cout << "Enter occupation: ";
    std::cin >> about.occupation;
    std::cout << "Enter status: ";
    std::cin >> about.status;
    std::cout << "Enter location: ";
    std::cin >> about.location;
    std::cout << "Bio Description: ";
    std::cin >> about.description;
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