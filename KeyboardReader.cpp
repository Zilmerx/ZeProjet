#include <conio.h>
#include "KeyboardReader.h"

// PUBLIC

#pragma region Constructeur / Destructeur
KeyboardReader::KeyboardReader()
: m_RunThread{ false }, m_ThreadIsRunning{ false }, m_Thread{}, m_CallbackList((KeyboardReader::MAXKEYVALUE - KeyboardReader::MINKEYVALUE))
{
}

KeyboardReader::~KeyboardReader()
{
   stop();
}
#pragma endregion

#pragma region Debuter / Arreter la detection de touches
void KeyboardReader::start()
{
   if (!m_ThreadIsRunning)
   {
      m_RunThread = true;
      m_Thread = std::thread(&KeyboardReader::callFuncOnKeyPress, this);
      m_ThreadIsRunning = true;
   }
}

void KeyboardReader::stop()
{
   m_RunThread = false;
   try
   {
      m_Thread.join();
   }
   catch (...)
   {
   }
   m_ThreadIsRunning = false;
}
#pragma endregion

#pragma region Gerer les fonctions
void KeyboardReader::addFunction(int keyValue, std::function<void(void)> func)
{
   validateKeyValue(keyValue);
   m_CallbackList[keyValue - MINKEYVALUE].push_back(func);
}

void KeyboardReader::clearFunction(int keyValue)
{
   validateKeyValue(keyValue);
   m_CallbackList[keyValue - MINKEYVALUE].clear();
}
#pragma endregion

// PRIVATE

void KeyboardReader::validateKeyValue(int& keyValue)
{
   if (keyValue < MINKEYVALUE)
   {
      keyValue = MINKEYVALUE;
   }
   else if (keyValue > MAXKEYVALUE)
   {
      keyValue = MAXKEYVALUE;
   }
}

void KeyboardReader::callFuncOnKeyPress() const
{
   while (m_RunThread)
   {
      executeKeyValue(waitForKeypress());
   }
}

int KeyboardReader::waitForKeypress() const
{
   int c = 0;

   do
   {
      if (!m_RunThread)
         break;

      if (_kbhit())
      {
         c = _getch();
      }
   } while (c == 224 || c == 0); // _getch() retourne (0 ou 224), puis la valeur de la touche du clavier. Nous n'avons pas besoin de la premiere information.

   return c;
}

void KeyboardReader::executeKeyValue(int keyValue) const
{
   validateKeyValue(keyValue);
   for (std::function<void(void)> f : m_CallbackList[keyValue - MINKEYVALUE])
   {
      if (!m_RunThread)
         break;

      f();
   }
}


// SINGLETON

KeyboardReader KeyboardReader::m_instance = KeyboardReader();

KeyboardReader& KeyboardReader::Instance()
{
   return m_instance;
}