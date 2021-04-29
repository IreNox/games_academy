using System;
using System.Runtime.InteropServices;

namespace client_app_cs
{
	[StructLayout(LayoutKind.Sequential)]
	public struct PlayerState
	{
		public byte playerId;
		public byte positionX;
		public byte positionY;
	};

	[StructLayout(LayoutKind.Sequential)]
	public struct ShootState
	{
		public byte playerId;
		public byte startPositionX;
		public byte startPositionY;
		public byte endPositionX;
		public byte endPositionY;
	};

	[StructLayout(LayoutKind.Sequential)]
	public struct GameState
	{
		public UInt32 round;
		[MarshalAs(UnmanagedType.ByValArray, ArraySubType = UnmanagedType.Struct, SizeConst = 8)]
		public PlayerState[] players;
		public byte playerCount;
		[MarshalAs(UnmanagedType.ByValArray, ArraySubType = UnmanagedType.Struct, SizeConst = 8)]
		public ShootState[] shoots;
		public byte shootCount;
	};

	public enum PlayerActionType
	{
		Invalid,
		MoveUp,
		MoveDown,
		MoveLeft,
		MoveRight,
		ShootUpLeft,
		ShootUpRight,
		ShootDownLeft,
		ShootDownRight
	};
}
