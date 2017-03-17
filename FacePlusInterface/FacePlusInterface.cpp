// FacePlusInterface.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"


/***************************************************************************
*                                  _   _ ____  _
*  Project                     ___| | | |  _ \| |
*                             / __| | | | |_) | |
*                            | (__| |_| |  _ <| |___
*                             \___|\___/|_| \_\_____|
*
* Copyright (C) 1998 - 2015, Daniel Stenberg, <daniel@haxx.se>, et al.
*
* This software is licensed as described in the file COPYING, which
* you should have received as part of this distribution. The terms
* are also available at https://curl.haxx.se/docs/copyright.html.
*
* You may opt to use, copy, modify, merge, publish, distribute and/or sell
* copies of the Software, and permit persons to whom the Software is
* furnished to do so, under the terms of the COPYING file.
*
* This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
* KIND, either express or implied.
*
***************************************************************************/
/* <DESC>
* Simple HTTPS GET
* </DESC>
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <curl/curl.h>
#include <iostream>
#pragma comment(lib,"libcurldll.a")
#pragma comment(lib,"libcurl.a")

CURL *curl;
CURLcode res;
std::string strResponse;


size_t write_data(void *buffer, size_t size, size_t nmemb, void *stream) {

	std::string* str = dynamic_cast<std::string*>((std::string *)stream);
	if (NULL == str || NULL == buffer)
	{
		return -1;
	}
	char* pData = (char*)buffer;
	str->append(pData, size * nmemb);
	return nmemb;
}
int Init()
{

	curl_global_init(CURL_GLOBAL_DEFAULT);
	return 0;
};

int Fini()
{
	curl_global_cleanup();
	return 0;
};

int GetResponseMsg(char *msg)
{
	memcpy(msg, strResponse.c_str(), strResponse.length()+1);
	strResponse.clear();
	return 0;
}

int DetectFace(char * path)
{
	curl = curl_easy_init();
	if (curl && path!= "") {

		struct curl_httppost *formpost = 0;
		struct curl_httppost *lastptr = 0;
		curl_easy_setopt(curl, CURLOPT_URL, "https://api-cn.faceplusplus.com/facepp/v3/detect");
		
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, true);
		curl_easy_setopt(curl, CURLOPT_CAINFO, "curl-ca-bundle.crt");
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &strResponse);
		curl_formadd(&formpost, &lastptr, CURLFORM_COPYNAME, "api_key", CURLFORM_COPYCONTENTS, "lxtJqlWUVMwoOuzRPQJPOZ15sZa59VlK", CURLFORM_END);
		curl_formadd(&formpost, &lastptr, CURLFORM_COPYNAME, "api_secret", CURLFORM_COPYCONTENTS, "rT7dp9PvuY-JweR57XA4VTPHoJwXtejM", CURLFORM_END);
		curl_formadd(&formpost, &lastptr, CURLFORM_PTRNAME, "image_file", CURLFORM_FILE, path, CURLFORM_END);
		curl_formadd(&formpost, &lastptr, CURLFORM_COPYNAME, "return_landmark", CURLFORM_COPYCONTENTS, "1", CURLFORM_END);
		curl_formadd(&formpost, &lastptr, CURLFORM_COPYNAME, "return_attributes", CURLFORM_COPYCONTENTS, "age", CURLFORM_END);

		curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);

		res = curl_easy_perform(curl);
		if (res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
			curl_easy_strerror(res));
		curl_formfree(formpost);
	}
	curl_easy_cleanup(curl);
	return 0;
}

int CreateFaceSet(char * out_id)
{
	curl = curl_easy_init();
	if (curl && out_id != "") {

		struct curl_httppost *formpost = 0;
		struct curl_httppost *lastptr = 0;
		curl_easy_setopt(curl, CURLOPT_URL, "https://api-cn.faceplusplus.com/facepp/v3/faceset/create");

		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, true);
		curl_easy_setopt(curl, CURLOPT_CAINFO, "curl-ca-bundle.crt");
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &strResponse);
		curl_formadd(&formpost, &lastptr, CURLFORM_COPYNAME, "api_key", CURLFORM_COPYCONTENTS, "lxtJqlWUVMwoOuzRPQJPOZ15sZa59VlK", CURLFORM_END);
		curl_formadd(&formpost, &lastptr, CURLFORM_COPYNAME, "api_secret", CURLFORM_COPYCONTENTS, "rT7dp9PvuY-JweR57XA4VTPHoJwXtejM", CURLFORM_END);
		curl_formadd(&formpost, &lastptr, CURLFORM_COPYNAME, "outer_id", CURLFORM_COPYCONTENTS, out_id, CURLFORM_END);

		curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);

		res = curl_easy_perform(curl);
		if (res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
			curl_easy_strerror(res));
		curl_formfree(formpost);
	}
	curl_easy_cleanup(curl);

	return 0;

}



int DeleteFaceSet(char * out_id)
{
	curl = curl_easy_init();
	if (curl && out_id != "") {

		struct curl_httppost *formpost = 0;
		struct curl_httppost *lastptr = 0;
		curl_easy_setopt(curl, CURLOPT_URL, "https://api-cn.faceplusplus.com/facepp/v3/faceset/delete");

		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, true);
		curl_easy_setopt(curl, CURLOPT_CAINFO, "curl-ca-bundle.crt");
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &strResponse);
		curl_formadd(&formpost, &lastptr, CURLFORM_COPYNAME, "api_key", CURLFORM_COPYCONTENTS, "lxtJqlWUVMwoOuzRPQJPOZ15sZa59VlK", CURLFORM_END);
		curl_formadd(&formpost, &lastptr, CURLFORM_COPYNAME, "api_secret", CURLFORM_COPYCONTENTS, "rT7dp9PvuY-JweR57XA4VTPHoJwXtejM", CURLFORM_END);
		curl_formadd(&formpost, &lastptr, CURLFORM_COPYNAME, "outer_id", CURLFORM_COPYCONTENTS, out_id, CURLFORM_END);

		curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);

		res = curl_easy_perform(curl);
		if (res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
			curl_easy_strerror(res));
		curl_formfree(formpost);
	}
	curl_easy_cleanup(curl);

	return 0;

}


int AddFaceToFaceSet(char*out_id,char * faceToken)
{
	curl = curl_easy_init();
	if (curl && faceToken != "") {

		struct curl_httppost *formpost = 0;
		struct curl_httppost *lastptr = 0;
		curl_easy_setopt(curl, CURLOPT_URL, "https://api-cn.faceplusplus.com/facepp/v3/faceset/addface");

		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, true);
		curl_easy_setopt(curl, CURLOPT_CAINFO, "curl-ca-bundle.crt");
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &strResponse);
		curl_formadd(&formpost, &lastptr, CURLFORM_COPYNAME, "api_key", CURLFORM_COPYCONTENTS, "lxtJqlWUVMwoOuzRPQJPOZ15sZa59VlK", CURLFORM_END);
		curl_formadd(&formpost, &lastptr, CURLFORM_COPYNAME, "api_secret", CURLFORM_COPYCONTENTS, "rT7dp9PvuY-JweR57XA4VTPHoJwXtejM", CURLFORM_END);
		curl_formadd(&formpost, &lastptr, CURLFORM_COPYNAME, "face_tokens", CURLFORM_COPYCONTENTS, faceToken, CURLFORM_END);
		curl_formadd(&formpost, &lastptr, CURLFORM_COPYNAME, "outer_id", CURLFORM_COPYCONTENTS, out_id, CURLFORM_END);

		curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);

		res = curl_easy_perform(curl);
		if (res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
			curl_easy_strerror(res));
		curl_formfree(formpost);
	}
	curl_easy_cleanup(curl);

	return 0;
}


int RemoveFromFaceSet(char *out_id, char * faceToken)
{
	curl = curl_easy_init();
	if (curl && faceToken != "") {

		struct curl_httppost *formpost = 0;
		struct curl_httppost *lastptr = 0;
		curl_easy_setopt(curl, CURLOPT_URL, "https://api-cn.faceplusplus.com/facepp/v3/faceset/removeface");

		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, true);
		curl_easy_setopt(curl, CURLOPT_CAINFO, "curl-ca-bundle.crt");
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &strResponse);
		curl_formadd(&formpost, &lastptr, CURLFORM_COPYNAME, "api_key", CURLFORM_COPYCONTENTS, "lxtJqlWUVMwoOuzRPQJPOZ15sZa59VlK", CURLFORM_END);
		curl_formadd(&formpost, &lastptr, CURLFORM_COPYNAME, "api_secret", CURLFORM_COPYCONTENTS, "rT7dp9PvuY-JweR57XA4VTPHoJwXtejM", CURLFORM_END);
		curl_formadd(&formpost, &lastptr, CURLFORM_COPYNAME, "face_tokens", CURLFORM_COPYCONTENTS, faceToken, CURLFORM_END);
		curl_formadd(&formpost, &lastptr, CURLFORM_COPYNAME, "outer_id", CURLFORM_COPYCONTENTS, out_id, CURLFORM_END);

		curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);

		res = curl_easy_perform(curl);
		if (res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
			curl_easy_strerror(res));
		curl_formfree(formpost);
	}
	curl_easy_cleanup(curl);

	return 0;
}



int FaceSearch(char *out_id, char * path)
{
	curl = curl_easy_init();
	if (curl && path != "") {

		struct curl_httppost *formpost = 0;
		struct curl_httppost *lastptr = 0;
		curl_easy_setopt(curl, CURLOPT_URL, "https://api-cn.faceplusplus.com/facepp/v3/search");

		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, true);
		curl_easy_setopt(curl, CURLOPT_CAINFO, "curl-ca-bundle.crt");
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &strResponse);
		curl_formadd(&formpost, &lastptr, CURLFORM_COPYNAME, "api_key", CURLFORM_COPYCONTENTS, "lxtJqlWUVMwoOuzRPQJPOZ15sZa59VlK", CURLFORM_END);
		curl_formadd(&formpost, &lastptr, CURLFORM_COPYNAME, "api_secret", CURLFORM_COPYCONTENTS, "rT7dp9PvuY-JweR57XA4VTPHoJwXtejM", CURLFORM_END);
		curl_formadd(&formpost, &lastptr, CURLFORM_PTRNAME, "image_file", CURLFORM_FILE, path, CURLFORM_END);
		curl_formadd(&formpost, &lastptr, CURLFORM_COPYNAME, "outer_id", CURLFORM_COPYCONTENTS, out_id, CURLFORM_END);

		curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);

		res = curl_easy_perform(curl);
		if (res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
			curl_easy_strerror(res));
		curl_formfree(formpost);
	}
	curl_easy_cleanup(curl);

	return 0;
}



int SetFaceUserID(char *faceToken, char * userId)
{
	curl = curl_easy_init();
	if (curl && userId != "") {

		struct curl_httppost *formpost = 0;
		struct curl_httppost *lastptr = 0;
		curl_easy_setopt(curl, CURLOPT_URL, "https://api-cn.faceplusplus.com/facepp/v3/face/setuserid");

		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, true);
		curl_easy_setopt(curl, CURLOPT_CAINFO, "curl-ca-bundle.crt");
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &strResponse);
		curl_formadd(&formpost, &lastptr, CURLFORM_COPYNAME, "api_key", CURLFORM_COPYCONTENTS, "lxtJqlWUVMwoOuzRPQJPOZ15sZa59VlK", CURLFORM_END);
		curl_formadd(&formpost, &lastptr, CURLFORM_COPYNAME, "api_secret", CURLFORM_COPYCONTENTS, "rT7dp9PvuY-JweR57XA4VTPHoJwXtejM", CURLFORM_END);
		curl_formadd(&formpost, &lastptr, CURLFORM_COPYNAME, "face_token", CURLFORM_COPYCONTENTS, faceToken, CURLFORM_END);
		curl_formadd(&formpost, &lastptr, CURLFORM_COPYNAME, "userId", CURLFORM_COPYCONTENTS, userId, CURLFORM_END);

		curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);

		res = curl_easy_perform(curl);
		if (res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
			curl_easy_strerror(res));
		curl_formfree(formpost);
	}
	curl_easy_cleanup(curl);

	return 0;
}