#pragma once

#ifndef KIWI_RUNTIME_HELP_HPP
#define KIWI_RUNTIME_HELP_HPP

namespace kiwi
{

#include <ostream>

  class Help
  {
    public:


      /**
       * Print help text on the output.
       */
      static void print(std::ostream& out )
      {

        out << std::endl;

        out << "Synopsis:" << std::endl << std::endl;
        out << "     kiwi [--help] [--version] [filterName [-i inputs] [-o outputs]]" 
          << std::endl;


        out <<std::endl << "Description:" << std::endl <<std::endl;
        out << "     @TODO" << std::endl;


        out <<std::endl << "Options:" << std::endl << std::endl;
        out << "     --help" << std::endl;
        out << "        Shows this output" << std::endl;
        out << "     --version"  << std::endl;
        out << "        Prints the installed kiwi version. " << std::endl;
        out << "     -i" << std::endl;
        out << "        Followed by the input arguments." << std::endl;
        out << "     -o " << std::endl;
        out << "        Followed by the output arguments." << std::endl;
        out << std::endl << std::endl;
      }


      /**
       * Print version on the output.
       */
      static void printVersion(std::ostream& out)
      {
        out << "Kiwi version : " 
          << KIWI_VERSION_MAJOR << "." 
          << KIWI_VERSION_MINOR 	<< "." 
          << KIWI_VERSION_PATCH << endl;
      }

  };



}//namespace



#endif
