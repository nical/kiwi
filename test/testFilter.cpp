
#include "Commons.hpp"

#include "Filter.hpp"

#include <vector>

#include <boost/scoped_ptr.hpp>


using namespace kiwi::core;
using namespace kiwi;



template <typename ValueType>
class StlVector : public Resource
{
public:
	class Reader : public Resource::Reader
	{
	public:
		Reader(std::vector<ValueType>* data) : _data(data){}
		inline ValueType at(unsigned pos){return (*_data)[pos];}
		inline unsigned size() {return _data->size();}
	protected:
		std::vector<ValueType>* _data;
	};
	class Writer : public Resource::Writer
	{
	public:
		Writer(std::vector<ValueType>* data) : _data(data){}
		inline ValueType& at(unsigned pos){return (*_data)[pos];}
		inline unsigned size() {return _data->size();}
	protected:
		std::vector<ValueType>* _data;
	};

	Reader* newReader(unsigned index) { return new Reader(&_data);}
	Writer* newWriter(unsigned index) { return new Writer(&_data);}
	
	StlVector(unsigned initialSize)
	: Resource()
	{
		_data.resize(initialSize);
		for(unsigned i = 0; i < initialSize; ++i) _data[i] = 1;
		addReaderOutputPort("Read");
		addWriterOutputPort("Read/Write");
	}
	bool isReaderCompatible(Resource::portIndex_t inputIndex, Resource::Reader* reader) {return false;}
	bool isWriterCompatible(Resource::portIndex_t inputIndex, Resource::Writer* writer) {return false;}

	inline unsigned int size() {return _data.size();}
	
protected:
	std::vector<ValueType> _data;
};


class TestFilter : public Filter
{
public:
	class Reader : public Resource::Reader
	{
		public:
		Reader(int a) {}
	};

	class Writer : public Resource::Writer
	{
		public:
		Writer(int a) {}
	};

	TestFilter() : Filter()
	{
		addReaderInputPort("A");
		addReaderInputPort("B");
		
		addWriterInputPort("< Result");
	}
	~TestFilter() {}

	void process()
	{
		ScopedBlockMacro(proc_block, "TestFilter::process()");

		debug.print() << "Allocate Reader #0" << endl;
		AllocateReaderMacro(StlVector<int>::Reader, A, 0)
		debug.print() << "Allocate Reader #1" << endl;
		AllocateReaderMacro(StlVector<int>::Reader, B, 1)

		debug.print() << "Allocate Writer #0" << endl;		
		AllocateWriterMacro(StlVector<int>::Writer, result, 0)

		if(!A or !B or !result) return;
		
		unsigned minSize = A->size();
		if(minSize > B->size() ) minSize = B->size();
		if(minSize > result->size() ) minSize = result->size();

		for(unsigned i = 0; i < minSize; ++i)
		{	
			result->at(i) = A->at(i) + B->at(i);
			debug.print() << "i = " << i << " -> "<< result->at(i) <<endl();
		}
		
	}
	
	Resource::Reader* newReader(unsigned index) { return new Reader(0);}
	Resource::Writer* newWriter(unsigned index) { return new Writer(0);}
	bool isReaderCompatible(Resource::portIndex_t inputIndex, Resource::Reader* reader) {return true;}
	bool isWriterCompatible(Resource::portIndex_t inputIndex, Resource::Writer* writer) {return true;}


};


int main()
{

ScopedBlockMacro(s2, "kiwi::Test");

debug.beginBlock("int main() ");

	debug.beginBlock("Allocate the resources");
		StlVector<int> resource1(10);
		StlVector<int> resource2(10);
		StlVector<int> resourceResult(10);

		TestFilter myTest;
	debug.endBlock();

	debug.beginBlock("connect the ports");
		resource1.readerOutputPort(0) >> myTest.readerInputPort(0);
		resource2.readerOutputPort(0) >> myTest.readerInputPort(1);	
		resourceResult.writerOutputPort(0) >> myTest.writerInputPort(0);
	debug.endBlock();

	myTest.process();
	
	
	
debug.endBlock();
	return 0;
}


