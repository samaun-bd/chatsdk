using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ChatWrapper;
using Windows.Storage;
using System.IO.IsolatedStorage;
using System.IO;

namespace ChatLibGenerator.ChatMedia
{
    public class InternetCheckerMedium
    {

        private static ManagedInternerChecker _instance;
        private static ManagedInternerChecker Instance
        {
            get
            {
                return _instance = _instance ?? new ManagedInternerChecker(Path.Combine(ApplicationData.Current.LocalFolder.Path, "InternetCheckerSettings.txt"));
            }
        }

        public static bool checkInternetConnection
        {
            get
            {
                return Instance.checkInternetConnection();
            }
        }
    }
}
