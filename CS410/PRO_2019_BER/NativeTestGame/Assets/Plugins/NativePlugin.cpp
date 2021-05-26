#include <math.h>

#include <windows.h>
#include <Xinput.h>

extern "C"
{
	float __declspec(dllexport) getInputAxisHorizontal()
	{
		XINPUT_STATE state;
		XInputGetState( 0u, &state );

		SHORT value = state.Gamepad.sThumbLX;
		if( abs( value ) < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE )
		{
			value = 0u;
		}

		return float( value ) / 32767.0f;
	}

	bool __declspec(dllexport) getInputJumpButtonDown()
	{
		XINPUT_STATE state;
		XInputGetState( 0u, &state );

		return (state.Gamepad.wButtons & XINPUT_GAMEPAD_A) != 0u;
	}
}