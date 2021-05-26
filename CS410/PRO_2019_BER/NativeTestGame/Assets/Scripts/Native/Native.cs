using System.Runtime.InteropServices;

namespace Assets.Scripts.Native
{
    public class Native
    {
        [DllImport("NativePlugin.dll")]
        public static extern float getForce();
    }
}
