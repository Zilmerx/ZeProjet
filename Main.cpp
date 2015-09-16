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
   reader.addFunction(75,FonctionHERP);
   reader.addFunction(75, FonctionDERP);

   reader.addFunction(77, FonctionDERP);
   reader.addFunction(77, FonctionHERP);

   reader.start();

   std::this_thread::sleep_for(std::chrono::seconds(3));

   reader.clearFunction(75);

   std::this_thread::sleep_for(std::chrono::seconds(3));

   reader.stop();
}