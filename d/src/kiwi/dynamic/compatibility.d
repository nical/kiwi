/++
 + Runtime compatibility policies for kiwi.dynamic.InputPort objects.
 +/
module kiwi.dynamic.compatibility;

import kiwi.commons;
import kiwi.data 			: DataTypeInfo;
import kiwi.core 			: OutputPort;
import kiwi.dynamic.port 	: PortCompatibility;


/++
 + Runtime compatibility policy for kiwi.dynamic.InputPort objects, based on DataTypeInfo.
 +/
class DataTypeCompatibility : PortCompatibility
{
	this(DataTypeInfo[] compatibleTypes)
	{
		_compatibleTypes = compatibleTypes;
	}
	this(DataTypeInfo compatibleType)
	{
		_compatibleTypes ~= compatibleType;
	}

	override bool isCompatible(OutputPort port) pure
	in
	{
		assert ( port !is null);
	}
	body
	{		
		foreach ( typeInfo ; _compatibleTypes )
		{
			if (port.dataType is typeInfo)
				return true;
		}
		return false;
	}

private:
	DataTypeInfo[] _compatibleTypes;
}


/**
 * Runtime compatibility policy for kiwi.dynamic.InputPort objects, always compatible.
 */
class AlwaysCompatible : PortCompatibility
{
	override bool isCompatible(OutputPort port) pure
	in
	{
		assert ( port !is null);
	}
	body
	{
		return true;	
	}
}
