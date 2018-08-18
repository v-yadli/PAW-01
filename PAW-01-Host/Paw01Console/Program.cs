using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using YadliTechnology.PAW01;

namespace Paw01Console
{
    class Program
    {
        static void Main(string[] args)
        {
            Log.LogToStdout = true;
            YadliTechnology.PAW01.PAWHost.Start();
        }
    }
}
