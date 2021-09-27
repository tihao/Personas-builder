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
    info.first_name = "";
    info.last_name = "";
    info.age = 0;
    info.occupation = "";
    info.education = "";
    info.status = "";
    info.location = "";
    info.description = "";
    // info.first_name = "Hao";
    // info.last_name = "Le";
    // info.age = 23;
    // info.occupation = "Student";
    // info.education = "Computer Science";
    // info.status = "single";
    // info.location = "Satnon, CA";
    // info.description = "Hao Le is UX Designer jdhssfdjk kjsdfkjs dkfj skdfjksdf dsk fjkdsj fkdsjfksdf ksdfj ksdfjsiue8iu fiseufidsuif udsi fusdfu isdfuisudfi sdifsdi fhsjkdhf dskjfhdsjk jhf dsfksjdhfjksdhfjs hkfjhdsk jhfdskjfh sdjkfh dskjdsjfh s.";
    for (int i = 0; i < MAX_LINE; i++)
    {
        info.goal[i] = "";
        info.need[i] = "";
        info.tech[i] = "";
        info.tech_rate[i] = 0;
        info.favorite[i] = "";
        info.pain_points[i] = "";
    }
    // info.tech[0] = "facebook";
    // info.tech[1] = "instagram";
    // info.tech[2] = "whatsapp";
    // info.tech_rate[0] = 3;
    // info.tech_rate[1] = 5;
    // info.tech_rate[2] = 5;
    // info.goal[0] = "Discovering new books/authors to read";
    // info.goal[1] = "Finding unique stores";
    // info.goal[2] = "Become a designer who communicates";
    // info.goal[3] = "Bec aksdjkasjd iasdiasdua";
    // info.pain_points[0] = "Keeping track of diffrerent series";
    // info.pain_points[1] = "Forgetting a book lauch date";
    // info.pain_points[2] = "Cannot rely";
    // info.pain_points[3] = "Forgetting a book lauch date 202130504054";
    // info.need[0] = "jfdhgdj hgdjh gdfjghdf";
    // info.need[1] = "jfdhgdj hgdjh gdfjghdf";
    // info.need[2] = "jfdhgdj hgdjh gdfjghdf";
    // info.favorite[0] = "orrooko";
    // info.favorite[1] = "dfpdsf";
    // info.favorite[2] = "dkoefks";
    // info.favorite[3] = "3003kkfg";
    
    // info.user_quote = "The book is way better than the movie";
}

bool Personas::Login(){
    std::string user_name;
    std::string pwd;
    std::string line;
    bool check_pwd = false;
    bool check_usr = false;
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
            std::cout << line;
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
        check_usr = true;
        std::getline(inFile, line, ',');
        std::cout << line << std::endl;
        std::cout << "Password: ";
        std::cin >> pwd;
        if(line != pwd) {
            std::cout << "Wrong password\n";
            check_pwd = true;
            continue;
        }
        else {
            std::getline(inFile, line, ',');

            //Copy primary key from user account
            primary_key = line.substr(10, 10);   
        }
            
    }
    if (inFile.eof() == true && check_usr == false)
    {
        std::cout << "Not correct user name\n";
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
    std::cout << primary_key << " ";
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
    std::cout << "Enter user gender: ";
    std::cin >> info.gender;

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
    std::cout << "Fill out information about user favorite\n";
    std::cout << "press \"Enter\" when the line is empty or type \"None\" to finish fill out \n";
    std::cout << "Maximum 4 text line\n";
    std::cout << "=============================================\n";    
    Take_Text_Line(info.favorite);

    std::cout << "=============================================\n";
    std::cout << "Fill out information about user paint points\n";
    std::cout << "press \"Enter\" when the line is empty or type \"None\" to finish fill out \n";
    std::cout << "Maximum 4 text line\n";
    std::cout << "=============================================\n";
    Take_Text_Line(info.pain_points);

    std::cout << "Enter user quote: ";
    getline(std::cin, info.user_quote);

    info.created = true;
    Save_to_file();

    system("CLS");
    std::cout << "Completed\n";
    
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
        std::cout << "File is not open\n";
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
    Write_buf_file(outFile, info.favorite);
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
    
    std::cout << "================================================================================================\n";
    std::cout << info.first_name << " " << info.last_name << " | " << info.occupation << std::endl;
    std::cout << "\"" + info.user_quote + "\"\n\n";
    std::cout << "AGE: " << info.age << std::endl;
    // std::cout << "OCCUPATION: " + info.occupation << std::endl;
    std::cout << "STATUS: " + info.status << std::endl;
    std::cout << "LOCATION: " + info.location << std::endl;
    std::cout << "================================================================================================\n";
    std::cout << "\nABOUT\n";
    std::cout << "------------------------------------------------------------------------------------------------\n";
    unsigned num_line = info.description.length() / MAX_CHAR_DES;
  
    unsigned init = 0;
    if(num_line == 0) {
        std::cout << info.description << std::endl;
    }
    else {
        for(unsigned i = 1; i <= num_line; i++) {
            for(unsigned j = init  + MAX_CHAR_DES; j > init; j--) {
                if(info.description[j] == ' ') {
                    j = j - init;
                    std::cout << info.description.substr(init, j + 1);
                    std::cout << std::endl;
                    init = j + init + 1;
                    j = 1;
                }
            }
        }
        std::cout << info.description.substr(init, info.description.length() - init);
        if(info.description[info.description.length() - 1] != '.') {
            std::cout << ".";
        }
        std::cout << std::endl;
    }
 
    std::cout << "------------------------------------------------------------------------------------------------\n";
    std::cout << std::endl << std::endl;
    Display_Same_Row(info.goal, info.pain_points, "GOALS", "Paint Points");
    std::cout << "------------------------------------------------------------------------------------------------\n";
    std::cout << std::endl << std::endl;
    Display_Same_Row(info.need, info.favorite, "NEEDS", "FAVORITE");
    std::cout << std::endl;

    unsigned left_length = Min_Length(info.tech);

    std::cout << "TECH\n";
    std::cout << "------------------------------------------------------------------------------------------------\n";

    for(int i = 0; i < MAX_LINE; i++) {
        if(info.tech[i] != "") {
            std::cout << info.tech[i] << ": " << std::setw(10 - (info.tech[i].length() - left_length));
            for(unsigned j = 0; j < 5; j++) {
                if (j < info.tech_rate[i]) {
                    std::cout << "[x]";
                }
                else
                    std::cout << "[ ]";

            }
            std::cout << std::endl; 
        }
    }


}

void Personas::Export_File(std::string name_file) {
    
    std::ofstream outFile;
    outFile.open(name_file, std::ios::out);
    
    transform(info.first_name.begin(), info.first_name.end(), info.first_name.begin(), ::toupper);
    transform(info.last_name.begin(), info.last_name.end(), info.last_name.begin(), ::toupper);
    
    outFile << "================================================================================================\n";
    outFile << info.first_name << " " << info.last_name << " | " << info.occupation << std::endl;
    outFile << "\"" + info.user_quote + "\"\n\n";
    outFile << "AGE: " << info.age << std::endl;

    outFile << "STATUS: " + info.status << std::endl;
    outFile << "LOCATION: " + info.location << std::endl;
    outFile << "================================================================================================\n";
    outFile << "\nABOUT\n";
    outFile << "------------------------------------------------------------------------------------------------\n";
    unsigned num_line = info.description.length() / MAX_CHAR_DES;
  
    unsigned init = 0;
    if(num_line == 0) {
        outFile << info.description << std::endl;
    }
    else {
        for(unsigned i = 1; i <= num_line; i++) {
            for(unsigned j = init  + MAX_CHAR_DES; j > init; j--) {
                if(info.description[j] == ' ') {
                    j = j - init;
                    outFile << info.description.substr(init, j + 1);
                    outFile << std::endl;
                    init = j + init + 1;
                    j = 1;
                }
            }
        }
        outFile << info.description.substr(init, info.description.length() - init);
        if(info.description[info.description.length() - 1] != '.') {
            outFile << ".";
        }
        outFile << std::endl;
    }
 
    outFile << "------------------------------------------------------------------------------------------------\n";
    outFile << std::endl << std::endl;
    Display_Same_Row(outFile, info.goal, info.pain_points, "GOALS", "Paint Points");
    outFile << "------------------------------------------------------------------------------------------------\n";
    outFile << std::endl << std::endl;
    Display_Same_Row(outFile, info.need, info.favorite, "NEEDS", "FAVORITE");
    outFile << std::endl;

    unsigned left_length = Min_Length(info.tech);

    outFile << "TECH\n";
    outFile << "------------------------------------------------------------------------------------------------\n";

    for(int i = 0; i < MAX_LINE; i++) {
        if(info.tech[i] != "") {
            outFile << info.tech[i] << ": " << std::setw(10 - (info.tech[i].length() - left_length));
            for(unsigned j = 0; j < 5; j++) {
                if (j < info.tech_rate[i]) {
                    outFile << "[x]";
                }
                else
                    outFile << "[ ]";

            }
            outFile << std::endl; 
        }
    }

    outFile.close();

}

void Personas::Display_Same_Row(std::string str1[MAX_LINE], std::string str2[MAX_LINE], std::string category1, std::string category2) {
    
    unsigned left_length = Min_Length(str1); 
    unsigned right_length = Min_Length(str2); 
    if (category1.length() < left_length) {
        if (category2.length() < right_length) {
            std::cout <<category1 << std::setw(42 - (category1.length() - left_length) + (category2.length() - right_length)) << category2 << std::endl;
        }
        else
            std::cout <<category1 << std::setw(42 - (category1.length() - left_length) + (category2.length() - right_length)) << category2 << std::endl;
    }
    else
        std::cout <<category1 << std::setw(42 - (category1.length() - left_length) + (category2.length() - right_length)) << category2 << std::endl;
    std::cout << "------------------------------------------------------------------------------------------------\n";
    for(int i = 0; i < MAX_LINE; i++) {
        if(str1[i] != "") {
            std::cout << "- " + str1[i];
        }
        else
            std::cout << "  ";
        if(str2[i] != "") {
            unsigned left_width = str1[i].length() - left_length;
            unsigned rigt_width = str2[i].length() - right_length;
            std::cout << std::setw(40 - left_width + rigt_width);
            std::cout << "- " + str2[i] << std::endl;
        }
        else
            std::cout << std::endl;
    }
}

void Personas::Display_Same_Row(std::ofstream &outFile, std::string str1[MAX_LINE], std::string str2[MAX_LINE], std::string category1, std::string category2) {
    
    unsigned left_length = Min_Length(str1); 
    unsigned right_length = Min_Length(str2); 
    if (category1.length() < left_length) {
        if (category2.length() < right_length) {
            outFile <<category1 << std::setw(42 - (category1.length() - left_length) + (category2.length() - right_length)) << category2 << std::endl;
        }
        else
            outFile <<category1 << std::setw(42 - (category1.length() - left_length) + (category2.length() - right_length)) << category2 << std::endl;
    }
    else
        outFile <<category1 << std::setw(42 - (category1.length() - left_length) + (category2.length() - right_length)) << category2 << std::endl;
    outFile << "------------------------------------------------------------------------------------------------\n";
    for(int i = 0; i < MAX_LINE; i++) {
        if(str1[i] != "") {
            outFile << "- " + str1[i];
        }
        else
            outFile << "  ";
        if(str2[i] != "") {
            unsigned left_width = str1[i].length() - left_length;
            unsigned rigt_width = str2[i].length() - right_length;
            outFile << std::setw(40 - left_width + rigt_width);
            outFile << "- " + str2[i] << std::endl;
        }
        else
            outFile << std::endl;
    }
}


void Personas::Open_Persona() {
    std::string str_arry[MAX_ARR];
    std::string text_line;
    std::cout << primary_key << '\n';
    //Open persona after created
    if(info.first_name != "") {
        Display();
        return;
    }

    std::ifstream inFile;
    inFile.open("./data/data.csv");

    if(!inFile.is_open()) {
        std::cout << "File is not open\n";
        return;
    }

    bool match = false;
    int i = 0;

    //Copy information in cvs file to array
    while(inFile.good()) {
        std::getline(inFile, text_line, ',');
        if((match == false) ) {
            std::cout << text_line.substr(10, 10);
            if (text_line.substr(10, 10) == primary_key ) {
                std::cout << "here";
                match = true;
            }
            else {
                inFile.ignore(1000, '\n');
                continue;
            }
        }
        str_arry[i] = text_line;
        i++;
   
    }
    // if(inFile.eof() && match == false) {
    //     std::cout << "Persona have not been created\n";
    //     return;
    // }
    //Take value in array to class attribute
    
    Take_Value(str_arry);
    if (info.created == false) {
        return;
    }
    Display();

       
    
    char user_input;
    std::cout << "[B]ack to menu: ";
    do {
        std::cin >> user_input;
        if(toupper(user_input) == 'B') {
            Menu();
        }
    } while (user_input != 'B');
    
}

void Personas::Take_Value(std::string str_arry[MAX_ARR]) {
    int i = 0;
    info.first_name = Decrupt(str_arry[i]);
    if (info.first_name != "") {
        info.created = true;
    }
    if (info.created == false) {
        std::cout << "Persona have not been created\n";
        return;
    }
    ++i;
    info.last_name = Decrupt(str_arry[i]);
    ++i;
    info.age = stoi(Decrupt(str_arry[i]));
    ++i;
    info.occupation = Decrupt(str_arry[i]);
    ++i;
    info.education = Decrupt(str_arry[i]);
    ++i;
    info.status = Decrupt(str_arry[i]);
    ++i;
    info.location = Decrupt(str_arry[i]);
    ++i;
    info.description = Decrupt(str_arry[i]);
    ++i;

    for(int j = 0; j < MAX_LINE; j++) {
        info.goal[j] = Decrupt(str_arry[i]);
        ++i;
    }

    for(int j = 0; j < MAX_LINE; j++) {
        info.need[j] = Decrupt(str_arry[i]);
        ++i;
    }
    for(int j = 0; j < MAX_LINE; j++) {
        info.tech[j] = Decrupt(str_arry[i]);
        ++i;
    }
    for(int j = 0; j < MAX_LINE; j++) {
        info.tech_rate[j] = stoi(Decrupt(str_arry[i]));
        ++i;
    }
    for(int j = 0; j < MAX_LINE; j++) {
        info.favorite[j] = Decrupt(str_arry[i]);
        ++i;
    }
    for(int j = 0; j < MAX_LINE; j++) {
        info.pain_points[j] = Decrupt(str_arry[i]);
        ++i;
    }

    info.user_quote = Decrupt(str_arry[i]);
    
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
        Menu();
        break;
    case 'O':
        Open_Persona();
        break;
    default:
        break;
    }

}