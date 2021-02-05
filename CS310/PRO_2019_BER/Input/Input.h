#pragma once

#include <stdint.h>

struct IDirectInputA;
struct IDirectInputDeviceA;

namespace GA
{
	class Graphics;
	struct InputState;

	enum class InputMouseButton : uint8_t
	{
		Left,
		Right,
		Middle
	};

	enum class InputKeyboardKey : uint8_t
	{
		Escape,
		Space,
		Shift,
		W,
		A,
		S,
		D,
		Left,
		Right,
		Up,
		Down,

		Count
	};

	enum class InputGamepadAxis : uint8_t
	{
		LeftX,
		LeftY,
		RightX,
		RightY,
		TriggerLeft,
		TriggerRight
	};

	enum class InputGamepadButton : uint8_t
	{
		DPadUp,
		DPadDown,
		DPadLeft,
		DPadRight,
		Start,
		Back,
		LeftThumb,
		RightThumb,
		LeftShoulder,
		RightShoulder,
		A,
		B,
		X,
		Y
	};

	class Input
	{
	public:

		bool					create( Graphics& graphics );
		void					destroy();

		void					update();

		float					getMouseDeltaX() const;
		float					getMouseDeltaY() const;
		float					getMousePositionX() const;
		float					getMousePositionY() const;

		bool					isMouseButtonDown( InputMouseButton button ) const;
		bool					isMouseButtonUp( InputMouseButton button ) const;
		bool					wasMouseButtonPressed( InputMouseButton button ) const;
		bool					wasMouseButtonReleased( InputMouseButton button ) const;

		bool					isKeyboardKeyDown( InputKeyboardKey key ) const;
		bool					isKeyboardKeyUp( InputKeyboardKey key ) const;
		bool					wasKeyboardKeyPressed( InputKeyboardKey key ) const;
		bool					wasKeyboardKeyReleased( InputKeyboardKey key ) const;

		float					getGamepadAxis( InputGamepadAxis axis ) const;

		bool					isGamepadButtonDown( InputGamepadButton button ) const;
		bool					isGamepadButtonUp( InputGamepadButton button ) const;
		bool					wasGamepadButtonPressed( InputGamepadButton button ) const;
		bool					wasGamepadButtonReleased( InputGamepadButton button ) const;

	private:

		Graphics*				m_pGraphics		= nullptr;

		IDirectInputA*			m_pInputDevice	= nullptr;
		IDirectInputDeviceA*	m_pMouse		= nullptr;
		IDirectInputDeviceA*	m_pKeyboard		= nullptr;

		InputState*				m_pState		= nullptr;
	};
}
