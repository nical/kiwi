module kiwi.image.data;

import kiwi.core.commons;
import kiwi.core.interfaces;
import kiwi.core.data;

class ImageContainer(T) : DataInterface {
    alias T ValueType;
    enum{ R, G, B, A };
    
    T opIndex(size_t x, size_t y){
        return _data[x*dim*(1+y*_width)];
    }
    
    override bool isSerializable(){ return true; }

    override bool serialize( DataStream stream ){
      return false;
    }

    override bool deSerialize( const DataStream ){
      return false;
    }

    override const(DataInterface[]) subData() @property{ return _subData; }

    /++
     + SubData
     +/
    class ImageChannel : DataInterface {
      this(uint index){
        _index = index;
      }
      T opIndex(size_t x, size_t y){
        return _data[_index + x*_stride*(1+y*_width)];
      }
      override bool isSerializable(){ return false; }//TODO
      override bool serialize( DataStream stream ){ return false; }
      override bool deSerialize( const DataStream ){ return false; }
      override const(DataInterface[]) subData() @property{
        DataInterface[] empty;
        return empty;
      }
    private:
      uint _index;
    }

    
private:
    DataInterface[] _subData;
    ValueType[] _data;
    u32 _width;
    u32 _height;
}


struct ColorFragment(T,uint dim){
  alias T ValueType;
  enum{ Dimension = dim };
  T opIndex(size_t index){
    return _data[index];
  }
  @property{
    T r() { return _data[0]; }
    T g() { return _data[1]; }
    T b() { return _data[2]; }    
    void r(T val) { _data[0] = val; }
    void g(T val) { _data[1] = val; }
    void b(T val) { _data[2] = val; }
    static if (dim >= 3){
      T a() { return _data[3]; }
      void a(T val) { _data[3] = val; }
    }
  }
private:
  T[dim] _data;
}


