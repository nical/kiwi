
#ifndef KIWI_CORE_FILTERWRAPPER_HPP
#define KIWI_CORE_FILTERWRAPPER_HPP


template<typename TFilterType>
class FilterWrapper : public Filter{
public:
  typedef TFilterType FilterType;

  void process() { return filter.process(); }
  void SetupLayout(DynamicNodeLayout& layout) {
    // for i in 0..FilterType::nbReader
    //    layout.createReader( filter._getReaderPtr<i> );
  }
  
  FilterType filter;
protected:
  ReaderPort* _dynReaderPorts[TFilterType::nbReaderPorts];
  WriterPort* _dynWriterPorts[TFilterType::nbWriterPorts];
}


#endif
