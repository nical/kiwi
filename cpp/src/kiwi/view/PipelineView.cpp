
#include "kiwi/view/PipelineView.hpp"
#include "kiwi/view/PipelineDisplay.hpp"

namespace kiwi{
namespace view{

bool PipelineView::display() const
{
    return _display->display( *this );
}

}//namespace
}//namespace
