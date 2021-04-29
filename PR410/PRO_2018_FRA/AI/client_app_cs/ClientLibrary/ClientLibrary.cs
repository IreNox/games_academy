using System;
using System.Runtime.InteropServices;

namespace client_app_cs
{
	public delegate PlayerActionType DoActionDelegate(GameState gameState, byte myPlayerId);

	class ClientLibrary
	{
		private delegate byte DoActionNativeDelegate(IntPtr gameState, byte myPlayerId, IntPtr userData);

		[DllImport("client_library.dll", EntryPoint = "runClient")]
		private static extern void runClient( [param: MarshalAs(UnmanagedType.LPStr)] string username, IntPtr callback, IntPtr userData);

		public static void run( String username, DoActionDelegate callback )
		{
			DoActionNativeDelegate managedCallback = delegate(IntPtr gameStatePtr, byte myPlayerId, IntPtr userData) {
				GameState gameState = Marshal.PtrToStructure<GameState>(gameStatePtr);
				return (byte)callback(gameState, myPlayerId);
			};

			IntPtr nativeCallback = Marshal.GetFunctionPointerForDelegate(managedCallback);

			runClient(username, nativeCallback, IntPtr.Zero);

			nativeCallback = IntPtr.Zero;
			managedCallback = null;
		}
	}
}
