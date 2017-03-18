using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using Newtonsoft.Json;
using System.IO;

namespace Setup
{
	/// <summary>
	/// MainWindow.xaml 的交互逻辑
	/// </summary>
	public partial class MainWindow : Window
	{
		/*
		FACEPLUS_API int testInt();
		FACEPLUS_API int testString(char *message);

		FACEPLUS_API int groupManger(int cmd, char * groupName);
		FACEPLUS_API int personManger(int cmd, char * personName, char* groupName, char * faceId);
		FACEPLUS_API int detectManger(char * url, char *result);
		FACEPLUS_API int trainManger(int cmd,char *name);
		FACEPLUS_API int recManger(int cmd, char *url, char *group, char *result);
		FACEPLUS_API int getMessage(char *message);
		 * enum CMDLIST
		{
			_CREATE,
			_DELETE,
			_ADD,
			_REMOVE,
			_PERSON,
			_GROUP
		};
		 */
		[DllImport("FacePlusInterface.dll", EntryPoint = "Init", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
		static extern Int32 Init();

		[DllImport("FacePlusInterface.dll", EntryPoint = "DetectFace", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
		static extern Int32 DetectFace(string path);

		[DllImport("FacePlusInterface.dll", EntryPoint = "CreateFaceSet", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
		static extern Int32 CreateFaceSet(string groupName);

		[DllImport("FacePlusInterface.dll", EntryPoint = "DeleteFaceSet", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
		static extern Int32 DeleteFaceSet(string groupName);

		[DllImport("FacePlusInterface.dll", EntryPoint = "GetResponseMsg", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
		static extern Int32 GetResponseMsg(StringBuilder message);

		[DllImport("FacePlusInterface.dll", EntryPoint = "AddFaceToFaceSet", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
		static extern Int32 AddFaceToFaceSet(string groupName, string message);
		[DllImport("FacePlusInterface.dll", EntryPoint = "RemoveFromFaceSet", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
		static extern Int32 RemoveFromFaceSet(string groupName, string message);
		[DllImport("FacePlusInterface.dll", EntryPoint = "FaceSearch", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
		static extern Int32 FaceSearch(string groupName, string path);
		[DllImport("FacePlusInterface.dll", EntryPoint = "SetFaceUserID", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
		static extern Int32 SetFaceUserID(string faceToken, string userId);


		public MainWindow()
		{
			InitializeComponent();
		}

		private void AddGroup_Click(object sender, RoutedEventArgs e)
		{
			StringBuilder message = new StringBuilder(10 * 1024);
			CreateFaceSet(value_group_box.Text);
			GetResponseMsg(message);
			message_box.Text = message.ToString();
		}

		private void DeleteGroup_Click(object sender, RoutedEventArgs e)
		{
			StringBuilder message = new StringBuilder(10 * 1024);
			DeleteFaceSet(value_group_box.Text);
			GetResponseMsg(message);
			message_box.Text = message.ToString();
		}

		private void DetectFace_Click(object sender, RoutedEventArgs e)
		{
			StringBuilder message = new StringBuilder(50 * 1024);
			DetectFace(url_box.Text);
			GetResponseMsg(message);
			message_box.Text = message.ToString();

            JsonTextReader reader = new JsonTextReader(new StringReader(message_box.Text));
            bool isFindToken = false;
            while (reader.Read())
            {
                if(reader.Value != null)
                {
                    if (isFindToken && reader.TokenType.ToString().Equals("String"))
                    {
                        Console.WriteLine("Token: {0}, Value: {1}", reader.TokenType, reader.Value);
                        ReslutDetect.Text = reader.Value.ToString();
                        value_faceId_box.Text = reader.Value.ToString();
                        break;
                    }
                    if (reader.Value.Equals("face_token"))
                    {
                        Console.WriteLine("Token: {0}, Value: {1}", reader.TokenType, reader.Value);
                        isFindToken = true;
                    }
                }
               
            }

		}


		private void RecoFace_Click(object sender, RoutedEventArgs e)
		{
			StringBuilder message = new StringBuilder(10 * 1024);
			FaceSearch(value_group_box.Text, url_box.Text);
			GetResponseMsg(message);
			message_box.Text = message.ToString();
		}


		private void AddGropFace_Click(object sender, RoutedEventArgs e)
		{
			StringBuilder message = new StringBuilder(10 * 1024);
			AddFaceToFaceSet(value_group_box.Text, value_faceId_box.Text);
			GetResponseMsg(message);
			message_box.Text = message.ToString();
		}

		private void DeleteGroupFace_Click(object sender, RoutedEventArgs e)
		{
			StringBuilder message = new StringBuilder(10 * 1024);
            RemoveFromFaceSet(value_group_box.Text, value_faceId_box.Text);
			GetResponseMsg(message);
			message_box.Text = message.ToString();
		}

		private void SetFaceUser_Click(object sender, RoutedEventArgs e)
		{
			StringBuilder message = new StringBuilder(10 * 1024);
			SetFaceUserID(value_faceId_box.Text, value_person_box.Text);
			GetResponseMsg(message);
			message_box.Text = message.ToString();

		}
	}
}
