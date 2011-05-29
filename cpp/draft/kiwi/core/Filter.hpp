
#ifndef KIWI_CORE_FILTER_HPP
#define KIWI_CORE_FILTER_HPP



namespace kiwi{
namespace core{

class DynamicNodeLayout;

class Filter{
public:
  virtual void process() = 0;

  virtual Node* createNode() { return 0; } 
protected:
  virtual void SetupLayout(DynamicNodeLayout& layout) { }
};


}//namespace
}//namespace

#endif
