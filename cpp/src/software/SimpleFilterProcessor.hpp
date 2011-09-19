#ifndef KIWI_SIMPLEFILTERPROCESSOR_HPP
#define KIWI_SIMPLEFILTERPROCESSOR_HPP

#include "ArgumentProcessor.hpp"
#include "kiwi/core.hpp"

namespace kiwi{
  namespace app{

    class SimpleFilterProcessor
    {
      public:
        SimpleFilterProcessor(const ArgumentProcessor& arguments );
        int run(); 

      protected:
        enum { COUT, FILE, DEFAULT };
        
        void wrapInputs(utils::NodeFactory& factory
            , core::Node& node
            , std::list<string>& inputs );
            
        std::list< std::pair<kiwi::core::Node*,std::string> >
          wrapOutputs(utils::NodeFactory& factory
            , core::Node& node
            , std::list<string>& inputs );

        ArgumentProcessor arguments;
    };


  }//namespace
}//namespace


#endif
