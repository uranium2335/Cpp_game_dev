#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int main() {
    std::vector<std::string> name;
    std::vector<std::string> admin = {"ianek"};

    while(true){
        std::string entered;
        std::string adminadd;
        std::string adminanswer;
        std::string person;

        std::cout << "enter your name(or type 'exit'): ";
        std::cin >> entered;
        if(entered == "exit") {
            std::cout << "adios puta" << std::endl;
            break;
        }

        if(std::find(admin.begin(), admin.end() ,entered) != admin.end()){
            std::cout << "hello admin" << std::endl;
            std::cout << "remove or add: ";
            std::cin >> adminanswer;
            if(adminanswer == "add"){
                std::cout << "name to be added: ";
                std::cin >> person;
                name.push_back(person);
            } else if(adminanswer == "remove"){
                std::cout << "name to be removed: ";
                std::cin >> person;
                name.erase(std::remove(name.begin(), name.end(), person), name.end());
            } else{
                std::cout << "not a valid answer" << std::endl;
            }
        } 
        else if(std::find(name.begin(), name.end() ,entered) != name.end()){
            std::cout << "hello guest" << std::endl;
        } 
        else{
            std::cout << "you arnt in the system" << std::endl;
        }
    }
}
