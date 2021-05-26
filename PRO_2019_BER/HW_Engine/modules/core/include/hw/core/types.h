#pragma once

#define HW_ON	2
#define HW_OFF	1

#define HW_ENABLED( val ) ( ( 0 + val ) == 2 )
#define HW_DISABLED( val ) ( ( 0 + val ) != 2 )

#if defined( HW_WINDOWS )
#	define HW_PLATFORM_WINDOWS	HW_ON
#else
#	define HW_PLATFORM_WINDOWS	HW_OFF
#endif

namespace hw
{

#if HW_ENABLED( HW_PLATFORM_WINDOWS )
	using uint8 = unsigned __int8;
	using uint16 = unsigned __int16;
	using uint32 = unsigned __int32;
	using uint64 = unsigned __int64;

	using int8 = __int8;
	using int16 = __int16;
	using int32 = __int32;
	using int64 = __int64;

	using size_t = unsigned __int64;
	using ssize_t = __int64;
#else
#	error Platform not implemented
#endif

	static constexpr size_t DefaultAlignment = 16u;

	static constexpr float DefaultEpsilon = 1.0e-20f;
}