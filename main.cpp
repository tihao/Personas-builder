#include "personas.h"
#include <iostream>


int main(){
    Personas persona;
    persona.Create_Persona();

    // char user_input;
    // bool check;
    // do {
    //     std::cout << "[L]ogin\n";
    //     std::cout << "[R]egister\n";
    //     std::cout << "[E]xit\n";
    //     std::cout << "Enter: ";
    //     std::cin >> user_input;
    //     user_input = toupper(user_input);
    //     switch (user_input)
    //     {
    //     case 'L':
    //         check = persona->Login();
    //         if (check == true) persona->Menu();
    //         break;
    //     case 'R':
    //         persona->Register();
    //         break;
    //     case 'E':
    //         break;
    //     default:
    //         system("CLS");
    //         std::cout << "Wrong input\n\n";
    //     }
    // } while (user_input != 'E');

    
    return 0;
}
