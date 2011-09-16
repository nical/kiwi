module kiwi.core.nodetree;

import kiwi.core.commons;
import kiwi.core.base;

interface NodeTree
{
    @property
    {
        NodeTree[] children();
        NodeTree parent();
        
    }
} 
