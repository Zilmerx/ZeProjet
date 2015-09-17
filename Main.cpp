/*
Cree par Jean-Philippe Doyon,

Le 15 Septembre 2015.
*/

#include <iostream>
#include <chrono>

#include "KeyboardReader.h"

void FonctionHERP()
{
   std::cout << "HERP";
}

void FonctionDERP()
{
   std::cout << "DERP";
}

int main()
{
   KeyboardReader &reader = KeyboardReader::Instance();

   reader.setFunction(75,FonctionHERP);
   reader.setFunction(75, FonctionDERP);

   reader.setFunction(77, FonctionDERP);
   reader.setFunction(77, FonctionHERP);

   reader.start();

   std::cout << "DEBUT" << std::endl;

   std::this_thread::sleep_for(std::chrono::seconds(3));

   std::cout << "CLEAR" << std::endl;

   reader.clearFunction(75);

   std::this_thread::sleep_for(std::chrono::seconds(3));

   std::cout << "FIN" << std::endl;

   reader.stop();
}