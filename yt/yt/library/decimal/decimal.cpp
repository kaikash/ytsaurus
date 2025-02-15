#include "decimal.h"

#include <yt/yt/core/misc/error.h>

#include <util/generic/ylimits.h>
#include <util/string/hex.h>
#include <util/system/byteorder.h>

#include <type_traits>

namespace NYT::NDecimal {

////////////////////////////////////////////////////////////////////////////////

template <typename T>
constexpr bool ValidDecimalUnderlyingInteger =
    std::is_same_v<T, i32> ||
    std::is_same_v<T, i64> ||
    std::is_same_v<T, i128>;

template <typename T>
struct TDecimalTraits
{
    static_assert(ValidDecimalUnderlyingInteger<T>);

    static constexpr T Nan = std::numeric_limits<T>::max();
    static constexpr T PlusInf = std::numeric_limits<T>::max() - 1;
    static constexpr T MinusInf = -PlusInf;

    static constexpr T MinSpecialValue = PlusInf;
};

////////////////////////////////////////////////////////////////////////////////

constexpr int GetDecimalBinaryValueSize(int precision)
{
    if (precision > 0) {
        if (precision <= 9) {
            return 4;
        } else if (precision <= 18) {
            return 8;
        } else if (precision <= 35) {
            return 16;
        }
    }
    return 0;
}

static constexpr i128 DecimalIntegerMaxValueTable[] = {
    i128{0},  // 0
    i128{9},  // 1
    i128{99},  // 2
    i128{999},  // 3
    i128{9999},  // 4
    i128{99999},  // 5
    i128{999999},  // 6
    i128{9999999},  // 7
    i128{99999999},  // 8
    i128{999999999},  // 9
    i128{9999999999ul},  // 10
    i128{99999999999ul},  // 11
    i128{999999999999ul},  // 12
    i128{9999999999999ul},  // 13
    i128{99999999999999ul},  // 14
    i128{999999999999999ul},  // 15
    i128{9999999999999999ul},  // 16
    i128{99999999999999999ul},  // 17
    i128{999999999999999999ul},  // 18

    // 128 bits
    //
    // Generated by fair Python script:
    //
    //     def print_max_decimal(precision):
    //         max_value = int("9" * precision)
    //         hex_value = hex(max_value)[2:]  # strip 0x
    //         hex_value = hex_value.strip("L")
    //         print("i128{{0x{}ul}} | (i128{{0x{}l}} << 64), // {}".format(
    //             hex_value[-16:],
    //             hex_value[:-16] or "0",
    //             precision))
    //     for i in range(19, 36):
    //         print_max_decimal(i)
    //
    i128{0x8ac7230489e7fffful} | (i128{0x0l} << 64), // 19
    i128{0x6bc75e2d630ffffful} | (i128{0x5l} << 64), // 20
    i128{0x35c9adc5de9ffffful} | (i128{0x36l} << 64), // 21
    i128{0x19e0c9bab23ffffful} | (i128{0x21el} << 64), // 22
    i128{0x02c7e14af67ffffful} | (i128{0x152dl} << 64), // 23
    i128{0x1bcecceda0fffffful} | (i128{0xd3c2l} << 64), // 24
    i128{0x1614014849fffffful} | (i128{0x84595l} << 64), // 25
    i128{0xdcc80cd2e3fffffful} | (i128{0x52b7d2l} << 64), // 26
    i128{0x9fd0803ce7fffffful} | (i128{0x33b2e3cl} << 64), // 27
    i128{0x3e2502610ffffffful} | (i128{0x204fce5el} << 64), // 28
    i128{0x6d7217ca9ffffffful} | (i128{0x1431e0fael} << 64), // 29
    i128{0x4674edea3ffffffful} | (i128{0xc9f2c9cd0l} << 64), // 30
    i128{0xc0914b267ffffffful} | (i128{0x7e37be2022l} << 64), // 31
    i128{0x85acef80fffffffful} | (i128{0x4ee2d6d415bl} << 64), // 32
    i128{0x38c15b09fffffffful} | (i128{0x314dc6448d93l} << 64), // 33
    i128{0x378d8e63fffffffful} | (i128{0x1ed09bead87c0l} << 64), // 34
    i128{0x2b878fe7fffffffful} | (i128{0x13426172c74d82l} << 64), // 35
};

template<typename T>
Y_FORCE_INLINE constexpr T GetDecimalMaxIntegerValue(int precision)
{
    static_assert(ValidDecimalUnderlyingInteger<T>);

    if (TDecimal::GetValueBinarySize(precision) <= sizeof(T)) {
        return DecimalIntegerMaxValueTable[precision];
    } else {
        YT_ABORT();
    }
}

template <typename T>
Y_FORCE_INLINE constexpr auto DecimalIntegerToUnsigned(T value)
{
    static_assert(ValidDecimalUnderlyingInteger<T>);

    if constexpr (std::is_same_v<T, i128>) {
        return ui128(value);
    } else {
        using TU = std::make_unsigned_t<T>;
        return static_cast<TU>(value);
    }
}

template <typename T>
static Y_FORCE_INLINE T DecimalHostToInet(T value)
{
    if constexpr (std::is_same_v<T, i128> || std::is_same_v<T, ui128>) {
        return T(::HostToInet(GetLow(value)), ::HostToInet(GetHigh(value)));
    } else {
        return ::HostToInet(value);
    }
}

template <typename T>
static Y_FORCE_INLINE T DecimalInetToHost(T value)
{
    if constexpr (std::is_same_v<T, i128> || std::is_same_v<T, ui128>) {
        return T(::InetToHost(GetLow(value)), ::InetToHost(GetHigh(value)));
    } else {
        return ::InetToHost(value);
    }
}

template <typename T>
static T DecimalBinaryToIntegerUnchecked(TStringBuf binaryValue)
{
    T result;
    memcpy(&result, binaryValue.Data(), sizeof(result));
    result = DecimalInetToHost(result);

    constexpr auto one = DecimalIntegerToUnsigned(T{1});
    result = static_cast<T>(DecimalIntegerToUnsigned(result) ^ (one << (sizeof(T) * 8 - 1)));

    return result;
}

template<typename T>
static void DecimalIntegerToBinaryUnchecked(T decodedValue, void* buf)
{
    auto unsignedValue = DecimalIntegerToUnsigned(decodedValue);
    constexpr auto one = DecimalIntegerToUnsigned(T{1});
    unsignedValue ^= (one << (sizeof(T) * 8 - 1));
    unsignedValue = DecimalHostToInet(unsignedValue);
    memcpy(buf, &unsignedValue, sizeof(unsignedValue));
}

static void CheckDecimalValueSize(TStringBuf value, int precision, int scale)
{
    int expectedSize = TDecimal::GetValueBinarySize(precision);
    if (std::ssize(value) != expectedSize) {
        THROW_ERROR_EXCEPTION(
            "Decimal<%v,%v> binary value representation has invalid length: actual %v, expected %v",
            precision,
            scale,
            value.Size(),
            expectedSize);
    }
}

static Y_FORCE_INLINE TStringBuf PlaceOnBuffer(TStringBuf value, char* buffer)
{
    memcpy(buffer, value.Data(), value.Size());
    return TStringBuf(buffer, value.Size());
}

// TODO(ermolovd): make it FASTER (check NYT::WriteDecIntToBufferBackwards)
template<typename T>
static TStringBuf WriteTextDecimalUnchecked(T decodedValue, int scale, char* buffer)
{
    i8 digits[std::numeric_limits<T>::digits + 1] = {0,};
    static constexpr auto ten = DecimalIntegerToUnsigned(T{10});

    const bool negative = decodedValue < 0;
    auto absValue = DecimalIntegerToUnsigned(negative ? -decodedValue : decodedValue);

    if (decodedValue == TDecimalTraits<T>::MinusInf) {
        static constexpr TStringBuf minusInf = "-inf";
        return PlaceOnBuffer(minusInf, buffer);
    } else if (decodedValue == TDecimalTraits<T>::PlusInf) {
        static constexpr TStringBuf inf = "inf";
        return PlaceOnBuffer(inf, buffer);
    } else if (decodedValue == TDecimalTraits<T>::Nan) {
        static constexpr TStringBuf nan = "nan";
        return PlaceOnBuffer(nan, buffer);
    }

    auto* curDigit = digits;
    while (absValue > 0) {
        *curDigit = static_cast<int>(absValue % ten);
        absValue = absValue / ten;
        curDigit++;
    }
    YT_VERIFY(curDigit <= digits + std::size(digits));

    if (curDigit - digits <= scale) {
        curDigit = digits + scale + 1;
    }

    char* bufferPosition = buffer;
    if (negative) {
        *bufferPosition = '-';
        ++bufferPosition;
    }
    while (curDigit > digits + scale) {
        --curDigit;
        *bufferPosition = '0' + *curDigit;
        ++bufferPosition;
    }
    if (scale > 0) {
        *bufferPosition = '.';
        ++bufferPosition;
        while (curDigit > digits) {
            --curDigit;
            *bufferPosition = '0' + *curDigit;
            ++bufferPosition;
        }
    }
    return TStringBuf(buffer, bufferPosition - buffer);
}

void ThrowInvalidDecimal(TStringBuf value, int precision, int scale, const char* reason = nullptr)
{
    if (reason == nullptr) {
        THROW_ERROR_EXCEPTION(
            "String %Qv is not valid Decimal<%v,%v> representation",
            value,
            precision,
            scale);
    } else {
        THROW_ERROR_EXCEPTION(
            "String %Qv is not valid Decimal<%v,%v> representation: %v",
            value,
            precision,
            scale,
            reason);
    }
}

template<typename T>
T DecimalTextToInteger(TStringBuf textValue, int precision, int scale)
{
    if (textValue.empty()) {
        ThrowInvalidDecimal(textValue, precision, scale);
    }

    auto cur = textValue.cbegin();
    auto end = textValue.end();

    bool negative = false;
    switch (*cur) {
        case '-':
            negative = true;
            [[fallthrough]]; // AUTOGENERATED_FALLTHROUGH_FIXME
        case '+':
            ++cur;
            break;
    }
    if (cur == end) {
        ThrowInvalidDecimal(textValue, precision, scale);
    }

    switch (*cur) {
        case 'i':
        case 'I':
            if (cur + 3 == end) {
                ++cur;
                if (*cur == 'n' || *cur == 'N') {
                    ++cur;
                    if (*cur == 'f' || *cur == 'F') {
                        return negative ? TDecimalTraits<T>::MinusInf : TDecimalTraits<T>::PlusInf;
                    }
                }
            }
            ThrowInvalidDecimal(textValue, precision, scale);
            [[fallthrough]]; // AUTOGENERATED_FALLTHROUGH_FIXME
        case 'n':
        case 'N':
            if (!negative && cur + 3 == end) {
                ++cur;
                if (*cur == 'a' || *cur == 'A') {
                    ++cur;
                    if (*cur == 'n' || *cur == 'N') {
                        return TDecimalTraits<T>::Nan;
                    }
                }
            }
            ThrowInvalidDecimal(textValue, precision, scale);
            break;
    }

    T result = 0;
    int beforePoint = 0;
    int afterPoint = 0;
    for (; cur != end; ++cur) {
        if (*cur == '.') {
            ++cur;
            for (; cur != end; ++cur) {
                int currentDigit = *cur - '0';
                result *= 10;
                result += currentDigit;
                ++afterPoint;
                if (currentDigit < 0 || currentDigit > 9) {
                    ThrowInvalidDecimal(textValue, precision, scale);
                }
            }
            break;
        }

        int currentDigit = *cur - '0';
        result *= 10;
        result += currentDigit;
        ++beforePoint;
        if (currentDigit < 0 || currentDigit > 9) {
            ThrowInvalidDecimal(textValue, precision, scale);
        }
    }

    for (; afterPoint < scale; ++afterPoint) {
        result *= 10;
    }

    if (afterPoint > scale) {
        ThrowInvalidDecimal(textValue, precision, scale, "too many digits after decimal point");
    }

    if (beforePoint + scale > precision) {
        ThrowInvalidDecimal(textValue, precision, scale, "too many digits before decimal point");
    }

    return negative ? -result : result;
}

template<typename T>
Y_FORCE_INLINE TStringBuf DecimalBinaryToTextUncheckedImpl(TStringBuf value, int scale, char* buffer)
{
    T decoded = DecimalBinaryToIntegerUnchecked<T>(value);
    return WriteTextDecimalUnchecked(decoded, scale, buffer);
}

TStringBuf TDecimal::BinaryToText(TStringBuf binaryDecimal, int precision, int scale, char* buffer, size_t bufferSize)
{
    ValidatePrecisionAndScale(precision, scale);

    YT_VERIFY(bufferSize >= MaxTextSize);
    switch (binaryDecimal.Size()) {
        case 4:
            return DecimalBinaryToTextUncheckedImpl<i32>(binaryDecimal, scale, buffer);
        case 8:
            return DecimalBinaryToTextUncheckedImpl<i64>(binaryDecimal, scale, buffer);
        case 16:
            return DecimalBinaryToTextUncheckedImpl<i128>(binaryDecimal, scale, buffer);
    }
    CheckDecimalValueSize(binaryDecimal, precision, scale);
    YT_ABORT();
}

TString TDecimal::BinaryToText(TStringBuf binaryDecimal, int precision, int scale)
{
    TString result;
    result.ReserveAndResize(MaxTextSize);
    auto resultSize = BinaryToText(binaryDecimal, precision, scale, result.Detach(), result.size()).size();
    result.resize(resultSize);
    return result;
}

template<typename T>
TStringBuf TextToBinaryImpl(TStringBuf textDecimal, int precision, int scale, char* buffer)
{
    T decoded = DecimalTextToInteger<T>(textDecimal, precision, scale);
    DecimalIntegerToBinaryUnchecked(decoded, buffer);
    return TStringBuf(buffer, TDecimal::GetValueBinarySize(precision));
}

TStringBuf TDecimal::TextToBinary(TStringBuf textValue, int precision, int scale, char* buffer, size_t bufferSize)
{
    ValidatePrecisionAndScale(precision, scale);

    YT_VERIFY(bufferSize >= static_cast<size_t>(TDecimal::GetValueBinarySize(precision)));

    int byteSize = TDecimal::GetValueBinarySize(precision);
    switch (byteSize) {
        case 4:
            return TextToBinaryImpl<i32>(textValue, precision, scale, buffer);
        case 8:
            return TextToBinaryImpl<i64>(textValue, precision, scale, buffer);
        case 16:
            return TextToBinaryImpl<i128>(textValue, precision, scale, buffer);
        default:
            static_assert(GetDecimalBinaryValueSize(TDecimal::MaxPrecision) == 16);
            YT_ABORT();
    }
}

TString TDecimal::TextToBinary(TStringBuf textValue, int precision, int scale)
{
    TString result;
    result.ReserveAndResize(MaxBinarySize);
    auto resultSize = TextToBinary(textValue, precision, scale, result.Detach(), result.size()).size();
    result.resize(resultSize);
    return result;
}

void TDecimal::ValidatePrecisionAndScale(int precision, int scale)
{
    if (precision <= 0 || precision > MaxPrecision) {
        THROW_ERROR_EXCEPTION("Invalid decimal precision %Qlv, precision must be in range [1, %v]",
            precision,
            MaxPrecision);

    } else if (scale < 0 || scale > precision) {
        THROW_ERROR_EXCEPTION("Invalid decimal scale %v (precision: %v); decimal scale must be in range [0, PRECISION]",
            scale,
            precision);
    }
}

template <typename T>
static void ValidateDecimalBinaryValueImpl(TStringBuf binaryDecimal, int precision, int scale)
{
    T decoded = DecimalBinaryToIntegerUnchecked<T>(binaryDecimal);

    const T maxValue = static_cast<T>(DecimalIntegerMaxValueTable[precision]);

    if (-maxValue <= decoded && decoded <= maxValue) {
        return;
    }

    if (decoded == TDecimalTraits<T>::MinusInf ||
        decoded == TDecimalTraits<T>::PlusInf ||
        decoded == TDecimalTraits<T>::Nan)
    {
        return;
    }

    char textBuffer[TDecimal::MaxTextSize];
    auto textDecimal = WriteTextDecimalUnchecked<T>(decoded, scale, textBuffer);

    THROW_ERROR_EXCEPTION(
        "Decimal<%v,%v> does not have enough precision to represent %Qv",
        precision,
        scale,
        textDecimal)
        << TErrorAttribute("binary_value", HexEncode(binaryDecimal));
}

void TDecimal::ValidateBinaryValue(TStringBuf binaryDecimal, int precision, int scale)
{
    CheckDecimalValueSize(binaryDecimal, precision, scale);
    switch (binaryDecimal.Size()) {
        case 4:
            return ValidateDecimalBinaryValueImpl<i32>(binaryDecimal, precision, scale);
        case 8:
            return ValidateDecimalBinaryValueImpl<i64>(binaryDecimal, precision, scale);
        case 16:
            return ValidateDecimalBinaryValueImpl<i128>(binaryDecimal, precision, scale);
        default:
            static_assert(GetDecimalBinaryValueSize(TDecimal::MaxPrecision) == 16);
            YT_ABORT();
    }
}
template <typename T>
Y_FORCE_INLINE void CheckDecimalIntBits(int precision)
{
    const auto expectedSize = TDecimal::GetValueBinarySize(precision);
    if (expectedSize != sizeof(T)) {
        const int bitCount = sizeof(T) * 8;
        THROW_ERROR_EXCEPTION("Decimal<%v, ?> cannot be represented as int%v",
            precision,
            bitCount);
    }
}

int TDecimal::GetValueBinarySize(int precision)
{
    const auto result = GetDecimalBinaryValueSize(precision);
    if (result <= 0) {
        ValidatePrecisionAndScale(precision, 0);
        YT_ABORT();
    }
    return result;
}

TStringBuf TDecimal::WriteBinary32(int precision, i32 value, char* buffer, size_t bufferLength)
{
    const size_t resultLength = GetValueBinarySize(precision);
    CheckDecimalIntBits<i32>(precision);
    YT_VERIFY(bufferLength >= resultLength);

    DecimalIntegerToBinaryUnchecked(value, buffer);
    return TStringBuf{buffer, sizeof(value)};
}

TStringBuf TDecimal::WriteBinary64(int precision, i64 value, char* buffer, size_t bufferLength)
{
    const size_t resultLength = GetValueBinarySize(precision);
    CheckDecimalIntBits<i64>(precision);
    YT_VERIFY(bufferLength >= resultLength);

    DecimalIntegerToBinaryUnchecked(value, buffer);
    return TStringBuf{buffer, sizeof(value)};
}

TStringBuf TDecimal::WriteBinary128(int precision, TValue128 value, char* buffer, size_t bufferLength)
{
    const size_t resultLength = GetValueBinarySize(precision);
    CheckDecimalIntBits<TValue128>(precision);
    YT_VERIFY(bufferLength >= resultLength);

    DecimalIntegerToBinaryUnchecked(i128(value.High, value.Low), buffer);
    return TStringBuf{buffer, sizeof(TValue128)};
}

template <typename T>
Y_FORCE_INLINE void CheckBufferLength(int precision, size_t bufferLength)
{
    CheckDecimalIntBits<T>(precision);
    if (sizeof(T) != bufferLength) {
        THROW_ERROR_EXCEPTION("Decimal<%v, ?> has unexpected length: expected %v, actual %v",
            precision,
            sizeof(T),
            bufferLength);
    }
}

i32 TDecimal::ParseBinary32(int precision, TStringBuf buffer)
{
    CheckBufferLength<i32>(precision, buffer.Size());
    return DecimalBinaryToIntegerUnchecked<i32>(buffer);
}

i64 TDecimal::ParseBinary64(int precision, TStringBuf buffer)
{
    CheckBufferLength<i64>(precision, buffer.Size());
    return DecimalBinaryToIntegerUnchecked<i64>(buffer);
}

TDecimal::TValue128 TDecimal::ParseBinary128(int precision, TStringBuf buffer)
{
    CheckBufferLength<i128>(precision, buffer.Size());
    auto result = DecimalBinaryToIntegerUnchecked<i128>(buffer);
    return {GetLow(result), static_cast<i64>(GetHigh(result))};
}

////////////////////////////////////////////////////////////////////////////////

} // namespace NYT::NDecimal
