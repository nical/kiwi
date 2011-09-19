/++
 + Runtime compatibility policies for kiwi.dynamic.InputPort objects.
 + @author Nicolas Silva
 +/
module kiwi.dynamic.compatibility;

import kiwi.core.all;
import kiwi.dynamic.port;


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

/**
 * Runtime compatibility policy for kiwi.dynamic.InputPort objects, never compatible.
 */
class NeverCompatible : PortCompatibility
{
	override bool isCompatible(OutputPort port) pure
	in
	{
		assert ( port !is null);
	}
	body
	{
		return false;
	}
}
