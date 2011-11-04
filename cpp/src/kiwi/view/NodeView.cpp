
#include "kiwi/view/NodeView.hpp"
#include "kiwi/view/NodeDisplay.hpp"


namespace kiwi{
namespace view{


void NodeView::display() const
{
    _display->display( *this );
}


}//namespace
}//namespace
