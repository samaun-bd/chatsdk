using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ChatWrapper;

namespace ChatLibGenerator.ChatMedia
{
    public class DataEncryptionMedium
    {
        private static ManagedDataEncryption _instance;
        public static ManagedDataEncryption Instance
        {
            get
            {
                return _instance ?? new ManagedDataEncryption();
            }
        }

        public static string getSessionlessKey(string ipAddress, Int64 ringId)
        {
            return Instance.getSessionlessKey(ipAddress, ringId);
        }

        public static byte[] encryptMessage(byte[] data, byte[] key, int startIndex = 0)
        {
            return Instance.encryptMessage(data, key, startIndex) ?? new byte[] { };
        }

        public static byte[] decryptMessage(byte[] data, byte[] key, int startIndex = 0)
        {
            return Instance.decryptMessage(data, key, startIndex) ?? new byte[] { };
        }
    }
}
