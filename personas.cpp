#include "personas.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <ctime>
#include <stdlib.h>
#include <cstring>
#include <iomanip>
#include <stdlib.h>
Personas::Personas(){
    info.first_name = "Hao";
    info.last_name = "Le";
    info.age = 23;
    info.occupation = "Student";
    info.education = "Computer Science";
    info.status = "single";
    info.location = "Satnon, CA";
    info.description = "Hao Le is UX Designer";
    for (int i = 0; i < MAX_LINE; i++)
    {
        info.goal[i] = "";
        info.need[i] = "";
        info.tech[i] = "";
        info.tech_rate[i] = 0;
        info.favorite_app[i] = "";
        info.pain_points[i] = "";
    }

    info.goal[0] = "Discovering new books/authors to read";
    info.goal[1] = "Finding unique stores";
    info.goal[2] = "Become a designer who communicates";
    // info.goal[3] = "Bec";
    info.pain_points[0] = "Keeping track of diffrerent series";
    info.pain_points[1] = "Forgetting a book lauch date";
    info.pain_points[2] = "Cannot rely";
    // info.pain_points[3] = "Forgetting a book lauch date 202130504054";

    info.user_quote = "The book is way better than the movie";
}

bool Personas::Login(){
    std::string user_name;
    std::string pwd;
    std::string line;
    bool check_pwd = false;
    std::ifstream inFile;
    inFile.open("./data/user-pwd.csv", std::ios::in);

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
    std::string line;
    std::cout << "Enter user name: ";
    while(true) {
        std::cin >> user_name;
        if(user_name.length() < 6 || user_name.length() > 20) {
            std::cout << "User name must be between 6 and 20 characters\n";
            std::cout << "Enter user name: ";
            std::cin.clear();
            continue;
        }
        else
            break;
    }
    
    std::cout << "Enter password: ";
    std::cin >> pwd;
    
    do {
        std::cout << "Confirm password: ";
        std::cin >> confirm_pwd; 
    } while(pwd != confirm_pwd);

    std::ifstream inFile;

    inFile.open("./data/user-pwd.csv", std::ios::in);
    if(!inFile.is_open()) {
        std::cout << "File is not open\n";
    }

    while(inFile.good()) {
       
        std::getline(inFile, line, ',');
        if (line != user_name)
        {
            inFile.ignore(1000, '\n');
            continue;
        }
        else {
            std::cout << "An account is already registered. Try another\n";
            inFile.close();
            Register();
            return;
        }
    }

    inFile.close();
    std::ofstream outFile;

    outFile.open("./data/user-pwd.csv", std::ios::app);

    if(!outFile.is_open()) {
        std::cout << "File is not opene\n";
    }

    outFile << user_name + "," + pwd + ",";
   
    primary_key = Generate_Key();

    outFile << Generate_Key() + primary_key + Generate_Key() + "\n";
    outFile.close();
}
bool Take_Text_Line(std::string text[MAX_LINE]);
void Personas::Create_Persona() {
    // Demographics;
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

//Get 10 characters from 0 to ~ in ASCII Table
std::string Personas::Generate_Key() {
    std::string primary_key = "";
    int length = 10;
    char ch;
    for(int i = 0; i < length; i++) {
        ch = '0' + std::rand() % 78;
        primary_key += ch;
    }

    return primary_key;
}

void Personas::Save_to_file() {
    std::ofstream outFile;
    outFile.open("./data/data.csv", std::ios::app);

    if(!outFile.is_open()) {
        std::cout << "File is not opene\n";
    }

    outFile << Generate_Key() + primary_key + Generate_Key() + ","
            + Encrypt(info.first_name) + "," + Encrypt(info.last_name) + ","
            + Encrypt(std::to_string(info.age)) + "," + Encrypt(info.occupation) + ","
            + Encrypt(info.education) + "," + Encrypt(info.status) + ","
            + Encrypt(info.location) + "," + Encrypt(info.description) + ",";
    Write_buf_file(outFile, info.goal);
    Write_buf_file(outFile, info.need);
    Write_buf_file(outFile, info.tech);
    for (int i = 0; i < MAX_LINE; i ++) {
        outFile << Encrypt(std::to_string(info.tech_rate[i])) + ",";
    }
    Write_buf_file(outFile, info.favorite_app);
    Write_buf_file(outFile, info.pain_points);
    outFile << Encrypt(info.user_quote) + "\n";
    outFile.close();
}

void Personas::Write_buf_file(std::ofstream &outFile, std::string str[MAX_LINE]) {

    for(int i = 0; i < MAX_LINE; i++) {
        outFile << Encrypt(str[i]) + ",";
    }

}
//Caesar Cypher Algorithm
std::string Personas::Encrypt(std::string str) {
    unsigned key_value = 5;
    for(unsigned i = 0; i <= str.length(); i++) {

        //No add key value if symbol is '
        // Avoid ,
        if (str[i] == 39) {
            continue;
        }
        str[i] = str[i] + key_value;
    }

    return str;
}

std::string Personas::Decrupt(std::string str) {
    unsigned key_value = 5;
    for(unsigned i = 0; i <= str.length(); i++) {

        //No subtract key value if symbol is '
        if (str[i] == 39) {
            continue;
        }
        str[i] = str[i] - key_value;
    }
    return str;
}

unsigned Min_Length(std::string str[MAX_LINE]);
void Personas::Display() {
    transform(info.first_name.begin(), info.first_name.end(), info.first_name.begin(), ::toupper);
    transform(info.last_name.begin(), info.last_name.end(), info.last_name.begin(), ::toupper);
    system("CLS");
    std::cout << "======================================================\n";
    std::cout << info.first_name << " " << info.last_name << std::endl;
    std::cout << "\"" + info.user_quote + "\"\n\n";
    std::cout << "AGE: " << info.age << std::endl;
    std::cout << "OCCUPATION: " + info.occupation << std::endl;
    std::cout << "STATUS: " + info.status << std::endl;
    std::cout << "LOCATION: " + info.location << std::endl;
    std::cout << "================================================================================================\n";
    std::cout << "ABOUT\n" + info.description << std::endl;
    std::cout << "------------------------------------------------------------------------------------------------\n";
    std::cout << std::endl;
    
    unsigned left_length = Min_Length(info.goal); 
    unsigned right_length = Min_Length(info.pain_points); 
    if (strlen("GOALS") < left_length) {
        if (strlen("Paint Points") < right_length) {
            std::cout <<"GOALS" << std::setw(42 - (strlen("GOALS") - left_length) + (strlen("Paint Points") - right_length)) << "Paint Points" << std::endl;
        }
        else
            std::cout <<"GOALS" << std::setw(42 - (strlen("GOALS") - left_length) + (right_length - strlen("Paint Points"))) << "Paint Points" << std::endl;
    }
    else
        std::cout <<"GOALS" << std::setw(42 - (strlen("GOALS") - left_length) + (right_length - strlen("Paint Points"))) << "Paint Points" << std::endl;
    std::cout << "------------------------------------------------------------------------------------------------\n";
    for(int i = 0; i < MAX_LINE; i++) {
        if(info.goal[i] != "") {
            std::cout << "- " + info.goal[i];
        }
        if(info.pain_points[i] != "") {
            unsigned left_width = info.goal[i].length() - left_length;
            unsigned rigt_width = info.pain_points[i].length() - right_length;
            std::cout << std::setw(40 - left_width + rigt_width);
            std::cout << "- " + info.pain_points[i] << std::endl;
        }
        else
            std::cout << std::endl;
    }
    


}

//Return min length of array text
unsigned Min_Length(std::string str[MAX_LINE]) {
    unsigned min = str[0].length();
    for(int i = 1; i < MAX_LINE; i++) {
        if((str[i] != "") && (str[i].length() < min)) {
            min = str[i].length();
        }
    }

    return min;
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