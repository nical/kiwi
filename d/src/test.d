#!/usr/bin/rdmd

import kiwi.core.data;
import kiwi.core.interfaces;
import kiwi.core.dynamic;
import kiwi.core.templated;

import kiwi.mpl.Tuple;

import kiwi.utils.io;



class CustomContainerA : AbstractContainer{
public:
  static string className = "A"; // does it override ?
  alias kiwi.core.data.AbstractContainer BaseClass;
  alias Tuple!() SubContainerClasses;
protected:
  
}


void main(string[] args){
  auto console = new OutputStream;
  console.println("hello! ", 42 , " D ", "ROCKS!!");
  with(kiwi.core){ 

    auto cm = new ContainerManager;
    CustomContainerA.BaseClass ac_bc = new CustomContainerA.BaseClass;
    auto ac_id = cm.registerContainer!(AbstractContainer)();
    auto a_id = cm.registerContainer!(CustomContainerA.BaseClass)();

    auto node = new dynamic.Node;
    
  }

}

/*
 *
 * kiwi.core.data
 *    Container
 *    ContainerManager
 *    
 * kiwi.core.node
 *    AbstractNode
 *    DynamicNode
 *    StaticNode
 * 
 * kiwi.core.port.interface
 *    AbstractDataPort
 *    AbstractAccessPort
 * kiwi.core.port.dynamic
 *    DynamicDataPort
 *    DynamicAccessPort
 * kiwi.core.port.static
 *    StaticDataPort
 *    StaticAccessPort
 * --------------------------
 *  kiwi.utils.testing
 *    Test
 *    TestManager
 *  kiwi.utils.io
 *    OutputStream
 *  kiwi.core.data
 *    Container
 *    ContainerManager
 *  kiwi.core.interface
 *    Node
 *    DataPort
 *    AccessPort
 *    NodeGroup
 *  kiwi.core.dynamic
 *    Node
 *    DataPort
 *    AccessPort
 *    Pipeline
 *  kiwi.text.data
 *    TextContainer
 *  kiwi.text.filter.uppercase
 *  kiwi.text.filter.morsecode
 * 
 * 
 *  kiwi.script.lua
 *  kiwi.script.python
 *  kiwi.mpl
 *  kiwi.network.
 *  kiwi.image.data
 *  kiwi.image.filter
 * 
 */ 
