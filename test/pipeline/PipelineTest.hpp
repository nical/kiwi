
#include "core/Commons.hpp"

#include "core/Filter.hpp"
#include "core/Pipeline.hpp"

#include <vector>

#include <boost/scoped_ptr.hpp>


using namespace kiwi::core;
using namespace kiwi;

template <typename ValueType>
class StlVectorReader : public Reader
{
public:
	StlVectorReader(std::vector<ValueType>* data) : _data(data){}
	inline ValueType at(unsigned pos){return (*_data)[pos];}
	inline unsigned size() {return _data->size();}
protected:
	std::vector<ValueType>* _data;
};

template <typename ValueType>
class StlVectorWriter : public Writer
{
public:
	StlVectorWriter(std::vector<ValueType>* data) : _data(data){}
	inline ValueType& at(unsigned pos){return (*_data)[pos];}
	inline unsigned size() {return _data->size();}
protected:
	std::vector<ValueType>* _data;
};

template <typename ValueType>
class StlVector : public Resource
{
public:
	
	Reader* newReader(unsigned index) { return new StlVectorReader<ValueType>(&_data);}
	Writer* newWriter(unsigned index) { return new StlVectorWriter<ValueType>(&_data);}
	
	StlVector(unsigned initialSize)
	: Resource()
	{
		_data.resize(initialSize);
		for(unsigned i = 0; i < initialSize; ++i) _data[i] = 1;
		addReaderOutputPort("Read");
		addWriterOutputPort("Read/Write");
	}
	bool isReaderCompatible(Resource::portIndex_t inputIndex, Reader* reader) const {return false;}
	bool isWriterCompatible(Resource::portIndex_t inputIndex, Writer* writer) const {return false;}


	inline unsigned int size() {return _data.size();}
	
protected:
	std::vector<ValueType> _data;
};

class TestReader : public Reader
{
	public:
	TestReader(int a) {}
};

class TestWriter : public Writer
{
	public:
	TestWriter(int a) {}
};

class TestFilter : public Filter
{
public:
	

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
		AllocateReaderMacro(StlVectorReader<int>, A, 0)
		debug.print() << "Allocate Reader #1" << endl;
		AllocateReaderMacro(StlVectorReader<int>, B, 1)

		debug.print() << "Allocate Writer #0" << endl;		
		AllocateWriterMacro(StlVectorWriter<int>, result, 0)

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
	
	Reader* newReader(unsigned index) { return new TestReader(0);}
	Writer* newWriter(unsigned index) { return new TestWriter(0);}
	bool isReaderCompatible(Resource::portIndex_t inputIndex, Reader* reader) const {return true;}
	bool isWriterCompatible(Resource::portIndex_t inputIndex, Writer* writer) const {return true;}

	bool isReady()
	{
		return (readerInputPort(0).isConnected()
			&& readerInputPort(1).isConnected()
			&& writerInputPort(0).isConnected() );
	}

};


int main()
{

ScopedBlockMacro(s2, "kiwi::Test -- Pipeline");

debug.beginBlock("int main() ");

	debug.beginBlock("Allocate the resources");
		Pipeline Pl;
	
		StlVector<int> resource1(10);
		StlVector<int> resource2(10);
		StlVector<int> resourceResult(10);

		TestFilter myTest;
		TestFilter myTest2;
	debug.endBlock();

	debug.beginBlock("connect the ports");
		Pl.add(&myTest);
		Pl.add(&myTest2);
		Pl.add(&resource1);
		Pl.add(&resource2);
	
		resource1.readerOutputPort(0) >> myTest.readerInputPort(0);
		resource2.readerOutputPort(0) >> myTest.readerInputPort(1);	
		resourceResult.writerOutputPort(0) >> myTest.writerInputPort(0);
		
		Pl.update();
	debug.endBlock();


	Pl.process();
	
	
	
debug.endBlock();
	return 0;
}


