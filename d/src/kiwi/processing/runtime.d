module kiwi.processing.runtime;

import kiwi.core.context;
import kiwi.core.pipeline;
import kiwi.core.commons;

/+
class ProcessingRuntime
{
    bool update(PipelineID pid, uint hints = 0)
    {
        return _context.pipeline(pid).update(hints);
    }
    
    bool updateStep(PipelineID pid, PipelineState ps, uint hints = 0)
    {
        return false;
        //return _context.pipeline(pid).updateStep(ps, hints);
    }
    
private:    
    Context _context;
    PipelineState _currentState;
}
+/
/+
class ProcessingPipelineState : PipelineState
{
    @property
    {
        uint hash()
        {
            NotImplemented("ProcessingPipelineState.hash");
            return 0;
        }
        
        bool finished()
        {
            NotImplemented("ProcessingPipelineState.finished");
            return false;
        }
    }
    // nextStep
}
+/

struct ProcessingRequest
{
    enum { CONNECT, DISCONNECT, RUN, RUNSTEP };
    union 
    {
        ConnectionRequest   connection;
        ConnectionRequest   disconnection;
        RunRequest          run;
        RunStepRequest      runStep;
    }
}

struct RunRequest
{
    PipelineID pipeline;
    void delegate(bool) onCompletion;
}

struct RunStepRequest
{
    PipelineID pipeline;
    uint nbSteps;
    void delegate(bool) onCompletion;
}

struct ConnectionRequest
{
    NodeID n1;
    NodeID n2;
    void delegate(bool) onCompletion;
}
