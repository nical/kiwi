#pragma once

#ifndef KIWI_UTILS_MODULO_HPP
#define KIWI_UTILS_MODULO_HPP

#include <math.h>

namespace kiwi
{
namespace utils
{	


template <typename T>
T modulo(T inValue, T modulo)
{
	T value; //result
		
	if(inValue >= modulo)
	{
		kiwi::int32_t division = floor(static_cast<float>( (inValue - modulo ) / (modulo - 0) ) ); //>0
		value = 0 + (inValue - modulo) -  division*(modulo - 0 );	
	}
	else if (inValue < 0)
	{
		int division = floor(static_cast<float>( (0 - inValue) / (modulo - 0) ) ); //>0
		value = modulo + (inValue - 0) +  division*(modulo - 0 );
	}	
	else
	{
		value = static_cast<T>(inValue);
	}
	//Debug::print() << "modulo("<<inValue<<", "<<modulo<<") = " << value << endl();
	return value;			
}

/*
// TODO, see how this might help
int fastModulo(int edge) // modulo 3
{
     return ((edge&1)<<1) | ((~(edge+1)&2) >>1);
}
*/

} // namespace
} // namespace



/*

IT inValue = *inDataPtr;
			OT value;
	
			if(CastType == CIRCULAR_CAST )
			{
				if(inValue > _sup)
				{
					int division = floor(static_cast<float>( (inValue - _sup ) / (_sup - _inf) ) ); //>0
					value = _inf + (inValue - _sup) -  division*(_sup - _inf );	
				}
				else if (inValue < _inf)
				{
					int division = floor(static_cast<float>( (_inf - inValue) / (_sup - _inf) ) ); //>0
					value = _sup + (inValue - _inf) +  division*(_sup - _inf );

				}	
				else
				{
					value = static_cast<OT>(inValue);
				}
				
			}
			else
			{
				if(inValue > _sup )
				{
					value = static_cast<OT>(_sup);
				}
				else if(inValue < _inf )
				{
					value = static_cast<OT>(_inf);
				}
				else
				{
					value = static_cast<OT>(inValue);
				}
			}

*/

#endif
