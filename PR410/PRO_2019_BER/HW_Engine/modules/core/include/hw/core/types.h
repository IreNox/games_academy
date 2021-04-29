#pragma once

namespace hw
{
#if defined( HW_WINDOWS )
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