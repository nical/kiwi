
#pragma once
#ifndef UTEST_TESTING_HPP
#define UTEST_TESTING_HPP

#include <assert.h>
#include <list>
#include <string>


#define Assert( exp ) assert(exp);
#define Test(exp, msg) processTest(exp, __FILE__, __LINE__, msg);

namespace utest{

struct Result
{
    int         status;
    std::string file;
    int         line;
    std::string message;
    std::string format();
};

typedef std::list<Result> TestResultList;


void BeginTesting(const std::string& testName, int argc, const char* argv);
int EndTesting();

bool ProcessAssert(bool success, const char* file, int line, const char* msg);
bool ProcessTest(bool success, const char* file, int line, const char* msg);

int TestCount();
int WarningCount();
int ErrorCount();
int SuccessCount();

const TestResultList& GetErrorLogs();
const TestResultList& GetWarningLogs();
const TestResultList& GetSuccessLogs();
const TestResultList& GetLogs();


}//namespace

#endif



#ifdef azertyuiop

if(!skip){
// ...

//------------ Test
}
__addTest();
if(!skip){
ProcessTest( n1.ouput() >> n2.input(), file, line, "Simple connection" );
//------------ Test

p.optimize()

}
#endif


