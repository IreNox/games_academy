using System;
using System.Runtime.InteropServices;

namespace Assets.Scripts.Native
{
    public class Native
    {
        [DllImport("NativePlugin.dll")]
        public static extern float getInputAxisHorizontal();
        [DllImport("NativePlugin.dll")]
        public static extern bool getInputJumpButtonDown();

        public static bool getInputJumpButtonUp()
        {
            return !getInputJumpButtonDown();
        }
    }
}
