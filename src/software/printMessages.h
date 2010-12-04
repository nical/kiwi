#include "kiwi/core/Commons.hpp"
#include <iostream>
using namespace kiwi;
using namespace std;


/**
 * Print version on standard outpur.
 */
void printVersion()
{
  cout << "Kiwi version : " << KIWI_VERSION_MAJOR << "." << KIWI_VERSION_MINOR 	<< "." << KIWI_VERSION_PATCH << endl;
}


/**
 * Print help text on standard output.
 */
void printHelp()
{
  cout << endl;

  cout << "Synopsis:" << endl << endl;
  cout << "     kiwi [--help] [--version] [filterName [-i inputs] [-o outputs]]" << endl;
  cout << endl << "Description:" << endl << endl;
  cout << "     @TODO" << endl;
  cout << endl << "Options:" << endl << endl;
  cout << "     --help" << endl;
  cout << "        Shows this output" << endl;
  cout << "     --version"  << endl;
  cout << "        Prints the installed kiwi version. " << endl;
  cout << "     -i" << endl;
  cout << "        Followed by the input arguments." << endl;
  cout << "     -o " << endl;
  cout << "        Followed by the output arguments." << endl;
  cout << endl << endl;
}

