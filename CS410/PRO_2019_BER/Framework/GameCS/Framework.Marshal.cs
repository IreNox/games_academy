using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace GameCS
{
    class Framework
    {
        [DllImport(DynamicLibrary.Name, CharSet = CharSet.Ansi, EntryPoint = "conct_controller_get_property")]
        public static extern IntPtr GetProperty(IntPtr handle, IntPtr addressHandle, UInt16 instanceId, [param: MarshalAs(UnmanagedType.LPStr)] string name);
    }
}
