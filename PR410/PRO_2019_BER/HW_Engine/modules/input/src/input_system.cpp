#include "Input.h"

#include "Graphics.h"

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

#include <Xinput.h>

namespace GA
{
	static const uint8_t s_keyboardMapping[] =
	{
		DIK_ESCAPE,
		DIK_SPACE,
		DIK_LSHIFT,
		DIK_W,
		DIK_A,
		DIK_S,
		DIK_D,
		DIK_LEFT,
		DIK_RIGHT,
		DIK_UP,
		DIK_DOWN
	};

	struct InputState
	{
		POINT			mousePosition;
		DIMOUSESTATE2	lastMouseState;
		DIMOUSESTATE2	currentMouseState;

		XINPUT_STATE	lastGamepadState;
		XINPUT_STATE	currentGamepadState;

		uint8_t			lastKeyboardState[ 256u ];
		uint8_t			currentKeyboardState[ 256u ];
	};

	bool Input::create( Graphics& graphics )
	{
		m_pGraphics	= &graphics;
		m_pState	= new InputState();

		const HINSTANCE hInstance = GetModuleHandle( nullptr );

		HRESULT result = DirectInput8Create( hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInputDevice, nullptr );
		if( FAILED( result ) || m_pInputDevice == nullptr )
		{
			destroy();
			return false;
		}

		bool mouseOk = false;
		result = m_pInputDevice->CreateDevice( GUID_SysMouse, &m_pMouse, nullptr );
		if( SUCCEEDED( result ) )
		{
			result = m_pMouse->SetDataFormat( &c_dfDIMouse2 );
			if( SUCCEEDED( result ) )
			{
				result = m_pMouse->SetCooperativeLevel( graphics.getHandle(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE );
				if( SUCCEEDED( result ) )
				{
					mouseOk = true;
				}
			}
		}

		bool keybaordOk = false;
		result = m_pInputDevice->CreateDevice( GUID_SysKeyboard, &m_pKeyboard, nullptr );
		if( SUCCEEDED( result ) )
		{
			if( SUCCEEDED( m_pKeyboard->SetDataFormat( &c_dfDIKeyboard ) ) )
			{
				result = m_pKeyboard->SetCooperativeLevel( graphics.getHandle(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE );
				if( SUCCEEDED( result ) )
				{
					keybaordOk = true;
				}
			}
		}

		if( !mouseOk || !keybaordOk )
		{
			destroy();
			return false;
		}

		return true;
	}

	void Input::destroy()
	{
		if( m_pState != nullptr )
		{
			delete m_pState;
			m_pState = nullptr;
		}

		if( m_pKeyboard != nullptr )
		{
			m_pKeyboard->Unacquire();

			m_pKeyboard->Release();
			m_pKeyboard = nullptr;
		}

		if( m_pMouse != nullptr )
		{
			m_pMouse->Unacquire();

			m_pMouse->Release();
			m_pMouse = nullptr;
		}

		if( m_pInputDevice != nullptr )
		{
			m_pInputDevice->Release();
			m_pInputDevice = nullptr;
		}
	}

	void Input::update()
	{
		m_pState->lastMouseState = m_pState->currentMouseState;

		for( size_t i = 0u; i < ARRAY_COUNT( m_pState->currentKeyboardState ); ++i )
		{
			m_pState->lastKeyboardState[ i ] = m_pState->currentKeyboardState[ i ];
		}

		HRESULT result = m_pMouse->GetDeviceState( sizeof( m_pState->currentMouseState ), &m_pState->currentMouseState );
		if( FAILED( result ) &&
			(result == DIERR_INPUTLOST || result == DIERR_NOTACQUIRED) )
		{
			m_pMouse->Acquire();
		}

		result = m_pKeyboard->GetDeviceState( sizeof( m_pState->currentKeyboardState ), m_pState->currentKeyboardState );
		if( FAILED( result ) &&
			(result == DIERR_INPUTLOST || result == DIERR_NOTACQUIRED) )
		{
			m_pKeyboard->Acquire();
		}

		GetCursorPos( &m_pState->mousePosition );
		ScreenToClient( m_pGraphics->getHandle(), &m_pState->mousePosition );

		m_pState->lastGamepadState = m_pState->currentGamepadState;
		XInputGetState( 0u, &m_pState->currentGamepadState );
	}

	float Input::getMouseDeltaX() const
	{
		return float( m_pState->currentMouseState.lX );
	}

	float Input::getMouseDeltaY() const
	{
		return float( m_pState->currentMouseState.lY );
	}

	float Input::getMousePositionX() const
	{
		return float( m_pState->mousePosition.x );
	}

	float Input::getMousePositionY() const
	{
		return float( m_pState->mousePosition.y );
	}

	bool Input::isMouseButtonDown( InputMouseButton button ) const
	{
		return m_pState->currentMouseState.rgbButtons[ (uint8_t)button ] != 0u;
	}

	bool Input::isMouseButtonUp( InputMouseButton button ) const
	{
		return m_pState->currentMouseState.rgbButtons[ (uint8_t)button ] == 0u;
	}

	bool Input::wasMouseButtonPressed( InputMouseButton button ) const
	{
		return m_pState->lastMouseState.rgbButtons[ (uint8_t)button ] == 0u && m_pState->currentMouseState.rgbButtons[ (uint8_t)button ] != 0u;
	}

	bool Input::wasMouseButtonReleased( InputMouseButton button ) const
	{
		return m_pState->lastMouseState.rgbButtons[ (uint8_t)button ] != 0u && m_pState->currentMouseState.rgbButtons[ (uint8_t)button ] == 0u;
	}

	bool Input::isKeyboardKeyDown( InputKeyboardKey key ) const
	{
		return (m_pState->currentKeyboardState[ s_keyboardMapping[ (uint8_t)key ] ] & 0x80u) != 0u;
	}

	bool Input::isKeyboardKeyUp( InputKeyboardKey key ) const
	{
		return (m_pState->currentKeyboardState[ s_keyboardMapping[ (uint8_t)key ] ] & 0x80u) == 0u;
	}

	bool Input::wasKeyboardKeyPressed( InputKeyboardKey key ) const
	{
		return (m_pState->currentKeyboardState[ s_keyboardMapping[ (uint8_t)key ] ] & 0x80u) != 0u && (m_pState->lastKeyboardState[ s_keyboardMapping[ (uint8_t)key ] ] & 0x80u) == 0u;
	}

	bool Input::wasKeyboardKeyReleased( InputKeyboardKey key ) const
	{
		return (m_pState->currentKeyboardState[ s_keyboardMapping[ (uint8_t)key ] ] & 0x80u) == 0u && (m_pState->lastKeyboardState[ s_keyboardMapping[ (uint8_t)key ] ] & 0x80u) != 0u;
	}

	float Input::getGamepadAxis( InputGamepadAxis axis ) const
	{
		SHORT value = 0;
		SHORT deadZone = 0;
		float maxValue = 0.0f;
		switch( axis )
		{
		case InputGamepadAxis::LeftX:			value = m_pState->currentGamepadState.Gamepad.sThumbLX; deadZone = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE; maxValue = 32767.0f; break;
		case InputGamepadAxis::LeftY:			value = m_pState->currentGamepadState.Gamepad.sThumbLY; deadZone = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE; maxValue = 32767.0f; break;
		case InputGamepadAxis::RightX:			value = m_pState->currentGamepadState.Gamepad.sThumbRX; deadZone = XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE; maxValue = 32767.0f; break;
		case InputGamepadAxis::RightY:			value = m_pState->currentGamepadState.Gamepad.sThumbRY; deadZone = XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE; maxValue = 32767.0f; break;
		case InputGamepadAxis::TriggerLeft:		value = m_pState->currentGamepadState.Gamepad.bLeftTrigger; deadZone = XINPUT_GAMEPAD_TRIGGER_THRESHOLD; maxValue = 255.0f; break;
		case InputGamepadAxis::TriggerRight:	value = m_pState->currentGamepadState.Gamepad.bRightTrigger; deadZone = XINPUT_GAMEPAD_TRIGGER_THRESHOLD; maxValue = 255.0f; break;
		}

		if( abs( value ) < deadZone )
		{
			value = 0u;
		}

		return float( value ) / maxValue;
	}

	bool Input::isGamepadButtonDown( InputGamepadButton button ) const
	{
		const DWORD buttonMask = 1u << (DWORD)button;
		return (m_pState->currentGamepadState.Gamepad.wButtons & buttonMask) != 0u;
	}

	bool Input::isGamepadButtonUp( InputGamepadButton button ) const
	{
		const DWORD buttonMask = 1u << (DWORD)button;
		return (m_pState->currentGamepadState.Gamepad.wButtons & buttonMask) == 0u;
	}

	bool Input::wasGamepadButtonPressed( InputGamepadButton button ) const
	{
		const DWORD buttonMask = 1u << (DWORD)button;
		return  (m_pState->currentGamepadState.Gamepad.wButtons & buttonMask) != 0u && (m_pState->lastGamepadState.Gamepad.wButtons & buttonMask) == 0u;
	}

	bool Input::wasGamepadButtonReleased( InputGamepadButton button ) const
	{
		const DWORD buttonMask = 1u << (DWORD)button;
		return  (m_pState->currentGamepadState.Gamepad.wButtons & buttonMask) == 0u && (m_pState->lastGamepadState.Gamepad.wButtons & buttonMask) != 0u;
	}
}