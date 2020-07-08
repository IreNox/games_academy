using System;
using System.Runtime.InteropServices;

namespace client_app_cs
{
	public delegate PlayerActionType DoActionDelegate(GameState gameState);

	class ClientLibrary
	{
		private delegate byte DoActionNativeDelegate(IntPtr gameState);

		[DllImport("client_library.dll", EntryPoint = "runClient")]
		private static extern void runClient( [param: MarshalAs(UnmanagedType.LPStr)] string username, IntPtr callback );

		public static void run( String username, DoActionDelegate callback )
		{
			DoActionNativeDelegate managedCallback = delegate(IntPtr gameStatePtr) {
				GameState gameState = Marshal.PtrToStructure<GameState>(gameStatePtr);
				return (byte)callback(gameState);
			};

			IntPtr nativeCallback = Marshal.GetFunctionPointerForDelegate(managedCallback);

			runClient(username, nativeCallback);

			nativeCallback = IntPtr.Zero;
			managedCallback = null;
		}
	}
}
