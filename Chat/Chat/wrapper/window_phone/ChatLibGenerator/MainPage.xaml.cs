using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Navigation;
using Microsoft.Phone.Controls;
using Microsoft.Phone.Shell;
using ChatLibGenerator.Resources;
using ChatLibGenerator.ChatMedia;
using System.IO.IsolatedStorage;
using Windows.Storage;
using Microsoft.Phone;
using System.IO;
using System.Windows.Media.Imaging;
using System.Threading.Tasks;

namespace ChatLibGenerator
{
    public partial class MainPage : PhoneApplicationPage
    {
        // Constructor
        public MainPage()
        {
            InitializeComponent();

            //ChatPacketSender.IMPacketSender.RegisterEventHandler("2110023445", "Russell", "38.127.68.55", 1200, "", 0, 4, "450500710648902832110020631", 140, 0);
        }

        //string filePath = "";



        private static string GetAbsolutePath(string filename)
        {
            IsolatedStorageFile isoStore = IsolatedStorageFile.GetUserStoreForApplication();

            string absoulutePath = null;

            if (isoStore.FileExists(filename))
            {
                IsolatedStorageFileStream output = new IsolatedStorageFileStream(filename, FileMode.Open, isoStore);
                absoulutePath = output.Name;

                output.Close();
                output = null;
            }

            return absoulutePath;
        }

        private async void saveFileToIso()
        {
            string fileName = "SampleImgISO.jpg";

            var uri = new Uri("Assets/SampleImg.jpg", UriKind.Relative);
            var sri = Application.GetResourceStream(uri);
            var data = sri.Stream;

            using (IsolatedStorageFile storage = IsolatedStorageFile.GetUserStoreForApplication())
            {
                if (storage.FileExists(fileName))
                    return;
                    //storage.DeleteFile(fileName);

                using (IsolatedStorageFileStream stream = storage.CreateFile(fileName))
                {
                    data.CopyTo(stream);
                }
            }
        }






        public async Task<string> DownloadFileFromWeb() //string fileName)
        {
            string savedPath = "";
            string fileName = "SampleImgISO.jpg";
           
            var isf = IsolatedStorageFile.GetUserStoreForApplication();

            var storageFile = await StorageFile.GetFileFromPathAsync("C:\\Data\\Users\\Public\\Pictures\\ringID\\edccad9c-847c-11e6-0000-000000000028.jpg");
            if (storageFile != null)
            {
                using (var fileStream = await storageFile.OpenAsync(FileAccessMode.Read))
                {
                    var wb = PictureDecoder.DecodeJpeg(fileStream.AsStream(), 1480, 1480);
                    using (var isoStream = isf.CreateFile(fileName))
                    {
                        wb.SaveJpeg(isoStream, wb.PixelWidth, wb.PixelHeight, 0, 100);
                        isoStream.Close();
                    }

                }
            }

            return "";
        }

        private static string sendingFilePacketId = "";
        private void sendImg_clicked(object sender, RoutedEventArgs e)
        {
            ChatPacketSender.IMPacketSender.GetConversationList("20376", 1, 0, 20, "");

            //ChatPacketSender.IMPacketSender.GetConversationList("578", 3, 0, 20, "");


            //bool check = InternetCheckerMedium.checkInternetConnection;

            //string sampleString = "dipalIsABoss";
            //string sampleKey = "dipalIsABossAgain";

            //byte[] StringArr = System.Text.Encoding.UTF8.GetBytes(sampleString.ToArray());
            //byte[] keyArr = System.Text.Encoding.UTF8.GetBytes(sampleKey.ToArray());

            //var encryptedData = DataEncryptionMedium.encryptMessage(StringArr, keyArr);
            //var decryptedData = DataEncryptionMedium.decryptMessage(encryptedData, keyArr);

            //string finalOutput = System.Text.Encoding.UTF8.GetString(decryptedData, 0, decryptedData.Length);

            //return;



            ////ChatPacketSender.IMPacketSender.downloadFriendChatMedia(691, "d34f2828-f65d-11e6-0000-0000000002b3", "cloudShared/691/chatContents-148/6615581487482505381_d34f2828-f65d-11e6-0000-0000000002b3.g729", 8, 0);

            //saveFileToIso();
            //sendingFilePacketId = !string.IsNullOrEmpty(sendingFilePacketId) ? sendingFilePacketId : ChatPacketSender.service.generatePacketId().PacketID;
            //string filePath = GetAbsolutePath("SampleImgISO.jpg");
            //ChatPacketSender.IMPacketSender.sendFriendChatMedia(40, sendingFilePacketId, 7, filePath, "zzz", 350, 200, 0, 459646887654, true);
        }

        private void cancel_clicked(object sender, RoutedEventArgs e)
        {
            ChatPacketSender.IMPacketSender.cancelChatMediaTransfer(sendingFilePacketId);
        }

    }
}