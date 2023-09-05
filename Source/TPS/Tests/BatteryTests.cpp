// My game copyright

#if (WITH_DEV_AUTOMATION_TESTS || WITH_PERF_AUTOMATION_TESTS)

#include "BatteryTests.h"
#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "TPS/Items/Battery.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBatteryTests, "TPSGame.Items.Battery",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter  //
        | EAutomationTestFlags::HighPriority);

bool FBatteryTests::RunTest(const FString& Parameters)
{
    using namespace TPS;

    /*
    AddInfo("Battery with default constructor");
    const Battery BatteryDefault;
    TestTrueExpr(FMath::IsNearlyEqual(BatteryDefault.GetPercent(), 1.0f));
    TestTrueExpr(BatteryDefault.GetColor() == FColor::Green);
    TestTrueExpr(BatteryDefault.ToString().Equals("100%"));

    AddInfo("Battery with custom constructor");
    const Battery BatteryObject1{1.0f};
    TestTrueExpr(FMath::IsNearlyEqual(BatteryObject1.GetPercent(), 1.0f));
    TestTrueExpr(BatteryObject1.GetColor() == FColor::Green);
    TestTrueExpr(BatteryObject1.ToString().Equals("100%"));

    const Battery BatteryObject2{0.46f};
    TestTrueExpr(FMath::IsNearlyEqual(BatteryObject2.GetPercent(), 0.46f));
    TestTrueExpr(BatteryObject2.GetColor() == FColor::Yellow);
    TestTrueExpr(BatteryObject2.ToString().Equals("46%"));
    */

    AddInfo("Battery with default constructor");
    const auto BatteryTestFunc = [this](float Percent, const FColor& Color, const FString& PercentString)
    {
        const Battery BatteryObject{Percent};
        TestTrueExpr(FMath::IsNearlyEqual(BatteryObject.GetPercent(), FMath::Clamp(Percent, 0.0f, 1.0f)));
        TestTrueExpr(BatteryObject.GetColor() == Color);
        TestTrueExpr(BatteryObject.ToString().Equals(PercentString));
    };

    BatteryTestFunc(1.0f, FColor::Green, "100%");
    BatteryTestFunc(0.46f, FColor::Yellow, "46%");
    BatteryTestFunc(0.2f, FColor::Red, "20%");
    BatteryTestFunc(3000.0f, FColor::Green, "100%");
    BatteryTestFunc(-3000.0f, FColor::Red, "0%");

    AddInfo("Battery charge / discharge");
    Battery BatteryObject{0.6f};
    TestTrueExpr(FMath::IsNearlyEqual(BatteryObject.GetPercent(), 0.6f));
    BatteryObject.Discharge();
    TestTrueExpr(FMath::IsNearlyEqual(BatteryObject.GetPercent(), 0.5f));
    BatteryObject.Charge();
    TestTrueExpr(FMath::IsNearlyEqual(BatteryObject.GetPercent(), 0.6f));

    AddInfo("Battery charge / discharge. Corner cases");
    for (int32 i = 0; i < 100; ++i)
    {
        BatteryObject.Discharge();
    }
    TestTrueExpr(FMath::IsNearlyEqual(BatteryObject.GetPercent(), 0.0f));

    for (int32 i = 0; i < 100; ++i)
    {
        BatteryObject.Charge();
    }
    //UE_LOG(LogTemp, Warning, TEXT("%f"), BatteryObject.GetPercent());
    TestTrueExpr(FMath::IsNearlyEqual(BatteryObject.GetPercent(), 1.0f));

    AddInfo("Battery comparison");
    const Battery BatteryLow{0.3f};
    const Battery BatteryHigh{0.99f};

    TestTrueExpr(BatteryHigh >= BatteryLow);
    TestTrueExpr(FMath::Max(BatteryHigh, BatteryLow) == BatteryHigh);  // since == operator is overloaded

    AddInfo("Battery in memory comparison");
    TestNotSame("Not the same batteries", BatteryHigh, BatteryLow);
    Battery BatteryHighDuplicate {0.9f};
    TestNotSame("Not the same batteries", BatteryHigh, BatteryHighDuplicate);

    const Battery& BatteryHighRef = BatteryHigh;
    TestSame("Same batteries", BatteryHigh, BatteryHighRef);

    return true;
}

#endif