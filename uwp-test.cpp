// uwp-test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "builder.h"

int main ( )
{
  LoadLibraryA ( "user32.dll" );
  auto uwd_caller = new uwd_engine::uwd_builder ( L"USER32.dll" );
  if ( !uwd_caller )
    throw std::runtime_error ( "Failed to find user32!" );

  /* TO TEST IF EVERYTHING WORKS CORRECTLY:
  - Place a bp on EmptyClipboard
  - Check callstack to see if it replaced your dll with calls from the same dll/kernel32.dll
  */

  auto cfg = uwd_caller->generate ( ( void* ) EmptyClipboard );
  std::cout << OpenClipboard ( NULL ) << std::endl;
  std::cout << uwd_caller->call<bool> ( &cfg ) << std::endl;
  CloseClipboard ( );

  std::cin.get ( );
}
