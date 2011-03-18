
#include "kiwi/text/PlainTextLoader.hpp"
#include "kiwi/text/PlainTextContainer.hpp"
#include "kiwi/text/PlainTextLine.hpp"
#include "kiwi/core/Node.hpp"
#include "kiwi/utils/Factory.hpp"


using namespace kiwi;
using namespace kiwi::text;

void plainTextLoaderTest(){

  utils::NodeFactory factory;
  PlainTextLoader::registerToFactory(factory,"TextLoader");
  
  kiwi::core::Node* loader = factory.newObject("TextLoader");
  assert( loader->nbReaderPorts() == 1 );
  assert( loader->nbWriterPorts() == 1 );
  assert( loader->nbDataPorts() == 1 );

  PlainTextContainer path;
  //PlainTextContainer result;

  path.insertLine(PlainTextLine("inputText.txt"), 0 );

  
  kiwi::core::Node pathNode( &path );
  //kiwi::core::Node resultNode( &result );
  
  pathNode.dataPort(0) >> loader->readerPort(0);
  //resultNode.dataPort(0) >> loader->writerPort(0);

  assert( loader->readerPort(0).isConnected() );
  //assert( loader->writerPort(0).isConnected() );

  loader->update(); //equivalent to process() for filters

  PlainTextContainer* result
    = loader->dataPort().safeDownCastContainer<PlainTextContainer>();

  assert(result);

  for(kiwi::uint32_t i = 0; i < result->nbLines(); ++i ){
    Debug::print() << result->line(i).str() << "\n";
  }
  
}



int main(){
  ScopedBlockMacro("PlainTextLoader::Test")
  plainTextLoaderTest();
  return 0;
}
