#pragma once
#include "pch.hpp"

namespace Utils
{
    unsigned long long GetTimestampLong() { return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count(); }
    std::string GetTimestampStr() { return std::to_string(GetTimestampLong()); }

    FProductInstanceID IntToProductInstanceID(int64_t Value)
    {
        FProductInstanceID ID;
        ID.UpperBits = static_cast<uint64_t>(Value >> 32);
        ID.LowerBits = static_cast<uint64_t>(Value & 0xffffffff);
        return ID;
    }

    FProductInstanceID HexStringToProductInstanceID(const std::string& HexString)
    {
        uint64_t Value = std::stoull(HexString, nullptr, 16);

        return IntToProductInstanceID(Value);
    }

    std::string ProductInstanceIDToHexString(const FProductInstanceID& ID)
    {
        uint64_t Value = (ID.UpperBits << 32) | ID.LowerBits;

        std::stringstream stream;
        stream << std::setfill('0') << std::setw(sizeof(uint64_t) * 2) << std::hex << Value;

        return stream.str();
    }

    int64_t ProductInstanceIDToInt(const FProductInstanceID& ID)
    {
        uint64_t Value = (ID.UpperBits << 32) | ID.LowerBits;

        return static_cast<int64_t>(Value);
    }

    FProductInstanceID GeneratePIID(int Product)
    {
        return IntToProductInstanceID(GetTimestampLong() + Product * rand());
    }

    std::string GeneratePIIDstr(int Product)
    {
        return ProductInstanceIDToHexString(GeneratePIID(Product));
    }
}