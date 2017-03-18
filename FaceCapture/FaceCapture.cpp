
/*
opencv_core243.lib
opencv_core243d.lib
opencv_objdetect243.lib
opencv_objdetect243d.lib
opencv_highgui243.lib
opencv_highgui243d.lib
opencv_imgproc243.lib
opencv_imgproc243d.lib
*/
#include <iostream>
#include <stdio.h>
#include "opencv2/highgui/highgui.hpp"
#include <json/json.h>

#pragma comment(lib,"opencv_core243.lib")
#pragma comment(lib,"opencv_highgui243.lib")

#pragma comment(lib,"json_vc71_libmt.lib")
#include "../FacePlusInterface/FacePlusInterface.h"
#pragma comment(lib,"../Release/FacePlusInterface.lib")
#if defined(_MSC_VER) && _MSC_VER >= 1310
#pragma warning(disable : 4996) // disable fopen deprecation warning
#endif
using namespace std;
using namespace cv;

void GetMsg(Json::Value &Root)
{
	char temp[20 * 1024] = { 0 };
	GetResponseMsg(temp);
	string response = temp;
	Json::Reader reader;
	bool parsingSuccessful = reader.parse(temp, temp + response.length() + 1, Root);
}

int main(int argc, const char** argv)
{
	string GroupName;
	cout << "��������Ҫ����ʶ���Ⱥ����Ϣ, ��Enter����������. " << endl;
	cin >> GroupName;
	CvCapture* capture = 0;
	Mat frame;

	capture = cvCaptureFromCAM(0);
	if (!capture)
		cout << "Capture from CAM  didn't work" << endl;

	if (capture)
	{
		cout << "�豸�Ѵ� ..." << endl;
		cout << "�������ַ�Ϊ . "  << "����P��������ʶ��,  ���루C��Q�˳����� ." << endl << endl << endl;

		for (;;)
		{
			IplImage* iplImg = cvQueryFrame(capture);
			frame = iplImg;
			cv::imshow("result", frame);
			char keyRet = cv::waitKey(10);
			if (keyRet >= 0)
			{
				cout << "�����ַ�Ϊ ��" << keyRet << endl << endl << endl;
				if (keyRet == 'q' || keyRet == 'c' || keyRet == 'C' || keyRet == 'Q')
					break;
				if (keyRet == 'p' || keyRet == 'P')
				{
					cout << "���ڽ�������ʶ�� ... " << endl;
					cv::imwrite("temp.jpg", frame);
					DetectFace("temp.jpg");
					Json::Value root;
					GetMsg(root);
				
					if (root["faces"] != NULL)
					{
						string  faceId = root["faces"][0]["face_token"].asString();
						
						if (!faceId.empty())
						{
							cout << "��ͼƬ��������, FaceId Ϊ: " << faceId.c_str() << endl;
							FaceSearchByFaceId((char*)GroupName.c_str(), (char *)faceId.c_str());
							Json::Value userId;
							GetMsg(userId);
							string confidence = userId["results"][0]["confidence"].asString();
							if (!confidence.empty())
							{
								string userName = userId["results"][0]["user_id"].asString();

								cout << "�ȽϽ��Ϊ: " << endl << endl
									<< "���ƶ�Ϊ: " << confidence.c_str() << endl
									<< "ͼƬ��ʶ����: " << userName.c_str() << endl;
							}
							else
							{
								cout << "�����ȶ�ʧ��,��ȷ��Ⱥ���Ƿ����. " << endl << endl << endl;
							}
						}
						else
						{
							cout << "δ�ҵ�������Ϣ. " << endl;
						}
					}

					//cout << "response \n" << response.c_str() << endl;
				}

			}
		}
		cvReleaseCapture(&capture);
	}
	cv::destroyAllWindows();
	return 0;
}
