#include "pch.h"
#include "CppUnitTest.h"
#include <fstream>
#include <string>
#include "Windows.h"
#include "../12.4/12.4.cpp"
#define _CRT_SECURE_NO_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest124
{
    

    TEST_CLASS(UnitTest124)
    {
    public:

        TEST_METHOD(TestIsValidPhone)
        {
            Assert::IsTrue(isValidPhone("1234567890"));
            Assert::IsTrue(isValidPhone("380501234567"));
            Assert::IsFalse(isValidPhone("12345")); 
            Assert::IsFalse(isValidPhone("abcdefghij")); 
        }

        TEST_METHOD(TestIsValidDate)
        {
            Assert::IsTrue(isValidDate(15, 5, 1995)); 
            Assert::IsTrue(isValidDate(29, 2, 2000)); 
            Assert::IsFalse(isValidDate(31, 2, 2020));
            Assert::IsFalse(isValidDate(32, 1, 1999));
            Assert::IsFalse(isValidDate(15, 13, 1995));
        }
        
    };
}
