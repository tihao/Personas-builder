#include "personas.h"
#include <iostream>
#include <ctime>
#include <stdio.h>




int main(){

    Personas persona;
    // persona.Create_Persona();

    
    // persona.Export_File("file.txt");

    // persona.Save_to_file();
    // persona.Register();
    

    char user_input;
    bool check;
    srand(time(NULL));
    do {
        std::cout << "[L]ogin\n";
        std::cout << "[R]egister\n";
        std::cout << "[E]xit\n";
        std::cout << "Enter: ";
        std::cin >> user_input;
        user_input = toupper(user_input);
        
        switch (user_input)
        {
        case 'L':
            check = persona.Login();
            if (check == true) persona.Menu();
            continue;
        case 'R':
            persona.Register();
            continue;
        case 'E':
            break;
        default:
            system("CLS");
            std::cout << "Wrong input\n\n";
        }
    } while (user_input != 'E');

    system("Pause");
    return 0;
}
