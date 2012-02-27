module kiwi.utils.testing;

import kiwi.utils.log;



class TestFailureException : Exception
{
    this(string msg, string file = null, uint line = 0)
    {
        super("Test failure: "~msg, file, line);
    }
}

struct TestSuite
{
    enum{ NORMAL, CRITICAL };

    static string[] FailedTestSuites;
    
    this( string n )
    {
        _log = kiwi.core.commons.log;
        _name = n;
        _log.writeln( LIGHTBLUE, "[Begin test] ", RESET, BOLD, _name );
        _log.indentation++;
    }

    this( ref LogStream l, string n )
    {
        _log = l;
        _name = n;
        _log.writeln( LIGHTBLUE, "[Begin test] ", RESET, BOLD, _name );
        _log.indentation++;
    }

    ~this()
    {
        auto indicator = GREEN;
        if(_successCount < _testCount)
            indicator = RED;
        _log.indentation--;
        _log.writeln( indicator, "[x] ", RESET, _testCount, " tests | ", _successCount, " success | ", _testCount - _successCount, " errors." );
        _log.writeln( LIGHTBLUE, "[End test]   ", RESET, BOLD, _name );

        if(_successCount < _testCount)
            FailedTestSuites ~= _name;
    }

    @property ref LogStream log(){ return _log; }


    void test(string file = __FILE__, int line = __LINE__)( bool cond, string comment = "", uint flag = NORMAL )
    {
        if( cond )
        {
            _log.writeln( GREEN, "+", RESET, " Test:",_testCount++, "(l",line,") ", GREEN,"passed", RESET," successfully." );
            _successCount++;
        }
        else
        {
            _log.writeln( RED, "-", RESET, " Test:",_testCount++, "(l",line,") ", RED, "failed", RESET,".");
            _log.writeln( "  -> file:", file, " line:", line, " ", comment );
            if( flag == CRITICAL )
                throw new TestFailureException(comment,file,line);
        }
    }

    void testEqual(string file = __FILE__, int line = __LINE__, T)( T a, T b, string comment, flag = NORMAL )
    {
        if ( a == b )
        {
            _log.writeln( GREEN, "+", RESET, " Test:",_testCount++, "(l",line,") ", GREEN,"passed", RESET," successfully." );
            _successCount++;
        }
        else
        {
            _log.writeln( RED, "-", RESET, " Test:",_testCount++, "(l",line,") ", RED, "failed", RESET,".");
            _log.writeln( "  -> file:", file, " line:", line, " ", comment );
            _log.writeln( "  -> (a == b) -> (", a, RED, " == ", RESET, b, ")");
            if ( flag == CRITICAL )
                throw new TestFailureException(comment,file,line);
        }
    }

    void testRange(string file = __FILE__, int line = __LINE__, T)( T val, T lower, T upper, string comment, flag = NORMAL )
    {
        if ( (lower <= val) && (upper >= val) )
        {
            _log.writeln( GREEN, "+", RESET, " Test:",_testCount++, "(l",line,") ", GREEN,"passed", RESET," successfully." );
            _successCount++;
        }
        else
        {
            _log.writeln( RED, "-", RESET, " Test:",_testCount++, "(l",line,") ", RED, "failed", RESET,".");
            _log.writeln( "  -> file:", file, " line:", line, " ", comment );
            _log.writeln( "  -> (lower <= val <= upper) -> (", lower, " <= ", val, " <= ", upper, ")");
            if ( flag == CRITICAL )
                throw new TestFailureException(comment,file,line);
        }
    }

    LogStream   _log;
    string      _name;
    uint        _testCount;
    uint        _successCount;
}
