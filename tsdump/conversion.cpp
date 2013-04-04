#include "common.h"
#include "conversion.h"
#ifdef _MSC_VER
#include <cstdio>
#else
#include <stdio.h>
#endif

namespace ABC
{

template<> void toString<>(std::wstring& str, const UInt8& value)
{
    wchar_t buf[64];
    swprintf(buf, 64,  L"0x%02x (%d)", value, value);
    str = buf;
}

template<> void toString<>(std::wstring& str, const UInt16& value)
{
    wchar_t buf[64];
    swprintf(buf, 64, L"0x%04x (%d)", value, value);
    str = buf;
}

template<> void toString<>(std::wstring& str, const UInt32& value)
{
    wchar_t buf[64];
    swprintf(buf, 64, L"0x%08x (%d)", value, value);
    str = buf;
}

template<> void toString<>(std::wstring& str, const UInt64& value)
{
    // It would appear that swprintf can't deal with __int64
    wchar_t buf[64];
    swprintf(buf, 64, L"0x%08x%08x", (UInt32)(value >> 32), (UInt32) value);
    str = buf;
}

template<> void toString<>(std::wstring& str, const Int8& value)
{
    wchar_t buf[64];
    swprintf(buf, 64, L"0x%02x (%d)", value, value);
    str = buf;
}

template<> void toString<>(std::wstring& str, const Int16& value)
{
    wchar_t buf[64];
    swprintf(buf, 64, L"0x%04x (%d)", value, value);
    str = buf;
}

template<> void toString<>(std::wstring& str, const Int32& value)
{
    wchar_t buf[64];
    swprintf(buf, 64, L"0x%08x (%d)", value, value);
    str = buf;
}

template<> void toString<>(std::wstring& str, const Int64& value)
{
    // It would appear that swprintf can't deal with __int64
    wchar_t buf[64];
    swprintf(buf, 64, L"0x%08x%08x", (Int32)(value >> 32), (UInt32) value);
    str = buf;
}

template<> void toString<>(std::wstring& str, const bool& value)
{
    str = value ? L"true" : L"false";
}

template<> void toString<>(std::wstring& str, const std::wstring& value)
{
    str = value;
}

//template<> void fromString<>(UInt8& value, const std::wstring& str)
//{
//}
//
//template<> void fromString<>(UInt16& value, const std::wstring& str)
//{
//}
//
//template<> void fromString<>(UInt32& value, const std::wstring& str)
//{
//}
//
//template<> void fromString<>(UInt64& value, const std::wstring& str)
//{
//}
//
//template<> void fromString<>(Int8& value, const std::wstring& str)
//{
//}
//
//template<> void fromString<>(Int16& value, const std::wstring& str)
//{
//}
//
//template<> void fromString<>(Int32& value, const std::wstring& str)
//{
//}
//
//template<> void fromString<>(Int64& value, const std::wstring& str)
//{
//}
//
//template<> void fromString<>(bool& value, const std::wstring& str)
//{
//}
//
//template<> void fromString<>(std::wstring& value, const std::wstring& str)
//{
//}

    time_t timeFromMJDUTC(long long mjdutc)
    {
        struct tm tm;
        memset(&tm, 0, sizeof(struct tm));

        // Convert MJD into YMD
        double mjd = (double)(mjdutc >> 24);
        int y = (int)((mjd - 15078.2) / 365.25);
        int m = (int)((mjd - 14956.1 - int(y * 365.25)) / 30.6001);
        tm.tm_mday = (int)(mjd - 14956 - int(y * 365.25) - int(m * 30.6001));
        int k;
        if (m == 14 || m == 15)
            k = 1;
        else
            k = 0;
        tm.tm_year = y + k;
        tm.tm_mon = (m - 1 - k * 12) - 1;

        // Convert BCD encoded time
        tm.tm_hour = 10 * ((mjdutc >> 20) & 15) + ((mjdutc >> 16) & 15);
        tm.tm_min = 10 * ((mjdutc >> 12) & 15) + ((mjdutc >> 8) & 15);
        tm.tm_sec = 10 * ((mjdutc >> 4) & 15) + (mjdutc & 15);

        return timegm(&tm);
    }

} //namespace ABC
