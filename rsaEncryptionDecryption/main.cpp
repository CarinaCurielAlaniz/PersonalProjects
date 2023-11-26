#include <iostream>
#include <sstream>
#include "commands.h"
int main(int argc, char *argv[]) 
{
  //read primes p and q
  long long p = atoi(argv[1]);         
  long long q = atoi(argv[2]); 
  //user interface         
  std::cout << std::endl << "Command List: " << std::endl; 
  std::cout << "\tEXIT- terminates program" << std::endl;
  std::cout << "\tDECRYPT [input] [output]- opens file at input and decrypts the message and overwrites the file at output" << std::endl;
  std::cout << "\tENCRYPT [filename] [n] [message]- " << std::endl;
  //store and ask for choice
  std::string userCommand = "start";
  //repeat till exit
  while(userCommand!= "EXIT")
  {
    std::string line;
    std::cout << std::endl << "Enter Command: ";
    std::getline(std::cin, line);
    std::stringstream ss(line);
    ss >> userCommand;
    if(userCommand != "EXIT" && userCommand != "DECRYPT" && userCommand != "ENCRYPT")
    {
      std::cout << "ERROR: invalid command" << std::endl << "Reenter: ";
      std::cin >> userCommand;
    }
    commands com(p, q);
    if(userCommand == "ENCRYPT")
    {
      std::string output;
      std::string message;
      long long n;  
      ss >> output >> n;  
      std::getline(ss >> std::ws, message);
      std::cout << message << std::endl;
      com.encryption(output, n, message);
    }
    else if(userCommand == "DECRYPT")
    {
      std::string input;
      std::string output;
      ss >> input >> output;
      com.decryption(input, output);
    }
  }
}