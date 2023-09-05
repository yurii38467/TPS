// My game copyright

#if (WITH_DEV_AUTOMATION_TESTS || WITH_PERF_AUTOMATION_TESTS)

#include "Tests/SandboxTests.h"
#include "Tests/TestUtils.h"
#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FMathMaxInt, "TPSGame.Math.MaxInt",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter  //
        | EAutomationTestFlags::HighPriority);

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FMathSqrt, "TPSGame.Math.Sqrt",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter  //
        | EAutomationTestFlags::HighPriority);

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FMathSin, "TPSGame.Math.Sin",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter  //
        | EAutomationTestFlags::HighPriority);

using namespace TPSGame;

bool FMathMaxInt::RunTest(const FString& Parameters)
{
    AddInfo("Max [int] func testing");

    typedef TArray<TestPayload<TInterval<int32>, int32>> MaxIntTestPayload;

    const MaxIntTestPayload TestData{
        {{13, 25}, 25}, {{25, 25}, 25}, {{0, 25}, 25}, {{0, 0}, 0}, {{-25, 0}, 0}, {{-25, -13}, -13}, {{-25, -25}, -25}, {{-25, 25}, 25}};

    for (const auto Data : TestData)
    {
        TestTrueExpr(FMath::Max(Data.TestValue.Min, Data.TestValue.Max) == Data.ExpectedValue);
    }

    /*
    TestTrue("2 different positive numbers", FMath::Max(13, 25) == 25);
    TestEqual("2 equal positive numbers", FMath::Max(25, 25), 25);
    TestTrueExpr(FMath::Max(0, 25) == 25);
    TestTrue("2 zeroes", FMath::Max(0, 0) == 0);
    TestTrue("negative number and zero", FMath::Max(-13, 0) == 0);
    TestTrue("2 different negative numbers", FMath::Max(-13, -25) == -13);
    TestTrue("2 equal negative numbers", FMath::Max(-25, -25) == -25);
    TestTrue("negative and positive numbers", FMath::Max(13, -25) == 13);
    */

    return true;
}

bool FMathSqrt::RunTest(const FString& Parameters)
{
    AddInfo("Sqrt func testing");

    typedef TArray<TestPayload<float, float>> SqrtTestPayload;

    const SqrtTestPayload TestData{{4.0f, 2.0f}, {3.0f, 1.7f, 0.1f}, {3.0f, 1.73f, 0.01f}, {3.0f, 1.73205f, 1.e-5f}};

    for (const auto Data : TestData)
    {
        const bool IsEqual = FMath::IsNearlyEqual(FMath::Sqrt(Data.TestValue), Data.ExpectedValue, Data.Tolerance);
        TestTrueExpr(IsEqual);
    }

    /*
    TestEqual("Sqrt(4) [0]", FMath::Sqrt(4.0f), 2.0f);
    // TestEqual("Sqrt(3) [1]", FMath::Sqrt(3.0f), 1.7f); // wrong tolerance, by default it is 0.0001f
    TestEqual("Sqrt(3) [1]", FMath::Sqrt(3.0f), 1.7f, 0.1f);
    TestEqual("Sqrt(3) [1]", FMath::Sqrt(3.0f), 1.73205f, 1.e-5f);
    */

    return true;
}

bool FMathSin::RunTest(const FString& Parameters)
{
    AddInfo("Sin func testing");

    typedef float Degrees;
    typedef TArray<TestPayload<Degrees, float>> SinTestPayload;

    const SinTestPayload TestData{
        {Degrees{0.00f}, 0.0f}, {Degrees{30.0f}, 0.5f}, {Degrees{45.0f}, 0.707f}, {Degrees{60.0f}, 0.866f}, {Degrees{90.0f}, 1.0f}};

    for (const auto Data : TestData)
    {
        const float Rad = FMath::DegreesToRadians(Data.TestValue);

        TestTrueExpr(FMath::IsNearlyEqual(FMath::Sin(Rad), Data.ExpectedValue, 0.001f));
    }

    return true;
}

#endif
