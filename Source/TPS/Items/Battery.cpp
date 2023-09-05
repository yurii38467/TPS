// My game copyright

#include "Items/Battery.h"

constexpr float ChargeAmount = 0.1f;

using namespace TPS;

TPS::Battery::Battery(float PercentIn)
{
    SetPercent(PercentIn);
}

void TPS::Battery::Charge()
{
    SetPercent(Percent + ChargeAmount);
}

void TPS::Battery::Discharge()
{
    SetPercent(Percent - ChargeAmount);
}

float TPS::Battery::GetPercent() const
{
    return Percent;
}

FColor TPS::Battery::GetColor() const
{
    return Percent > 0.8f ? FColor::Green : (Percent > 0.3f ? FColor::Yellow : FColor::Red);
}

FString TPS::Battery::ToString() const
{
    return FString::Printf(TEXT("%i%%"), FMath::RoundToInt(Percent * 100));
}

void TPS::Battery::SetPercent(float PercentIn)
{
    Percent = FMath::Clamp(PercentIn, 0.0f, 1.0f);
}
