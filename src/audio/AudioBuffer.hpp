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

#ifndef KIWI_AUDIOBUFFER_HPP
#define KIWI_AUDIOBUFFER_HPP

#include "generic/ArrayContainer.hpp"

namespace kiwi
{
namespace audio
{


template< typename TValueType >
class AudioBuffer : public generic::ArrayContainer<TValueType, 1>
{
public:

	typedef TValueType ValueType;
	
	/**
	 * @brief constructor
	 */ 
	AudioBuffer( unsigned size,  portIndex_t nbBuffer = 1 );
	
	/**
	 * @brief constructor
	 */
	AudioBuffer(ValueType* dataPtr, unsigned size, portIndex_t nbBuffer = 1);

	/**
	 * @brief destructor
	 */
	~AudioBuffer();
	
};



} // namespace
} // namespace

#include "audio/AudioBuffer.ih"

#endif
