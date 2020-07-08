using System;

namespace client_app_cs
{
	static class Program
	{
		static PlayerActionType doAction(GameState gameState)
		{
			PlayerActionType action = (PlayerActionType)(gameState.round % ((int)PlayerActionType.ShootDownRight + 1));
			return action;
		}

		[STAThread]
		static void Main()
		{
			ClientLibrary.run("MyName", doAction);
		}
	}
}
