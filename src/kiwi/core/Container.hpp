// Copyright (c) 2010 Nicolas Silva
// All rights reserved.
//      Redistribution and use in source and binary forms, with or without
//      modification, are permitted provided that the following conditions are
//      met:
//
//      * Redistributions of source code must retain the above copyright
//        notice, this list of conditions and the following disclaimer.
//      * Redistributions in binary form must reproduce the above
//        copyright notice, this list of conditions and the following disclaimer
//        in the documentation and/or other materials provided with the
//        distribution.
//      * Neither the name of the  nor the names of its
//        contributors may be used to endorse or promote products derived from
//        this software without specific prior written permission.
//
//      THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
//      "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
//      LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
//      A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
//      OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
//      SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
//      LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//      DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//      THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//      (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
//      OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


#pragma once

#ifndef KIWI_RESOURCE_HPP
#define KIWI_RESOURCE_HPP

#include "kiwi/core/Node.hpp"
#include "kiwi/utils/Factory.hpp"

namespace kiwi{
namespace core{

/**
 * @brief The base class for containers.
 *
 */
class Container
{
public:
	static const uint32_t UNAVAILABLE = 0;
  enum { READ = 1, WRITE = 2, READ_WRITE = READ | WRITE };
  
  /**
   * @brief A method intended to prepare the container before access when needed.
   *
   * Some libraries -cairo for example- need to make some function calls before
   * and after working on their data structures. These pre-process calls
   * should be placed here.
   * This is important because some kiwi containers use abstraction layers so as
   * to work with non library-specific data, which means that the child containers
   * should override this method if any pre-treatment is required. 
   */
   virtual void begin( int flags = READ_WRITE ) { }
   /**
   * @brief A method intended to prepare the container before access when needed.
   *
   * Some libraries -cairo for example- need to make some function calls before
   * and after working on their data structures. These post-process calls
   * should be placed here.
   * This is important because some kiwi containers use abstraction layers so as
   * to work with non library-specific data, which means that the child containers
   * should override this method if any post-treatment is required. 
   */
   virtual void end( int flags = READ_WRITE ) { }

	/**
	 * @brief Returns an estimation of the memory consumed by the container.
	 */ 
	virtual kiwi::uint32_t memoryEstimation() const { return UNAVAILABLE; }

	/**
	 * @brief Returns the number of scalar elements in the container.
   * @todo This method should be moved to a child class
	 */ 
	virtual kiwi::uint32_t size() const { return 0; }

	/**
	 * @brief Returns this container's tags used for runtime compatibility check.
	 */ 
	virtual kiwi::Tags tags() const { return kiwi::Tags(); }

	/**
	 * @brief Returns true if the container is composed of sub-containers.
	 */ 
	virtual bool isComposite() const { return false; }

	/**
	 * @brief Returns the number of sub-containers (if any)
	 */ 
	virtual kiwi::uint32_t nbSubContainers() const { return 0; }

	/**
	 * @brief Returns the nth subContrainer, or a nil pointer if it does not exist.
	 */ 
	virtual Container* subContainer(kiwi::uint32_t index = 0){ return 0; }


	/**
	 * @brief Register the Container to the ContainerFactory
	 */
	 virtual bool registerToFactory(const kiwi::utils::NodeFactory& factory) {return false;}
};


/**
 * @brief helper macro that produces typedef classType ReaderType;
 *
 * Some filters that have template a parameter on the (Container) input type need
 * to know at compilation time the Container's Reader type to instanciate it
 * correctly. This macro should be used in the public part of every Container class
 * declaration.
 */
#define ReaderTypeMacro(classType) typedef classType ReaderType;

/**
 * @brief helper macro that produces typedef classType WriterType;
 *
 * Some filters that have a template parameter on the (Container) input type need
 * to know at compilation time the Container's Writer type to instanciate it
 * correctly. This macro should be used in the public part of every Container class
 * declaration.
 */
#define WriterTypeMacro(classType) typedef classType WriterType;

/**
 * @brief helper macro that produces typedef classType ReaderType;
 *
 * Some filters that have template a parameter on the (Container) input type need
 * to know at compilation time the Container's Reader type to instanciate it
 * correctly. This macro should be used in the public part of every class
 * declaration of containers that are iterable.
 */
#define IteratorTypeMacro(classType) typedef classType IteratorType;



} //namespace
} //namespace

#endif
