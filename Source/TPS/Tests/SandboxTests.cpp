// My game copyright

#include "Tests/SandboxTests.h"
#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FMathMaxInt, "TPSGame.Math.MaxInt",
    EAutomationTestFlags::ApplicationContextMask  //
        | EAutomationTestFlags::ProductFilter     //
        | EAutomationTestFlags::HighPriority);

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FMathSqrt, "TPSGame.Math.Sqrt",
    EAutomationTestFlags::ApplicationContextMask  //
        | EAutomationTestFlags::ProductFilter     //
        | EAutomationTestFlags::HighPriority);

bool FMathMaxInt::RunTest(const FString& Parameters)
{
    AddInfo("Max [int] func testing");

    TestTrue("2 different positive numbers", FMath::Max(13, 25) == 25);
    TestEqual("2 equal positive numbers", FMath::Max(25, 25), 25);
    TestTrueExpr(FMath::Max(0, 25) == 25);
    TestTrue("2 zeroes", FMath::Max(0, 0) == 0);
    TestTrue("negative number and zero", FMath::Max(-13, 0) == 0);
    TestTrue("2 different negative numbers", FMath::Max(-13, -25) == -13);
    TestTrue("2 equal negative numbers", FMath::Max(-25, -25) == -25);
    TestTrue("negative and positive numbers", FMath::Max(13, -25) == 13);

    return true;
}

bool FMathSqrt::RunTest(const FString& Parameters) 
{
    AddInfo("Sqrt func testing");

    TestEqual("Sqrt(4) [0]", FMath::Sqrt(4.0f), 2.0f);
    //TestEqual("Sqrt(3) [1]", FMath::Sqrt(3.0f), 1.7f); // wrong tolerance, by default it is 0.0001f
    TestEqual("Sqrt(3) [1]", FMath::Sqrt(3.0f), 1.7f, 0.1f);
    TestEqual("Sqrt(3) [1]", FMath::Sqrt(3.0f), 1.73205f, 1.e-5f);

    return true;
}