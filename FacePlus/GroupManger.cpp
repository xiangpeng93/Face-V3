#include "GroupManger.h"

//std::string CreateRequest = "/v2/group/create?api_key=c499b2943a96babe258e8d4ed8098061&api_secret=hHbxdSmNwgvCwWURtjweTRyGR5V_TmWH&tag=created_by_Alice&group_name=";
//std::string DeleteRequest = "/v2/group/delete?api_key=c499b2943a96babe258e8d4ed8098061&api_secret=hHbxdSmNwgvCwWURtjweTRyGR5V_TmWH&tag=created_by_Alice&group_name=";

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

int CGroupManger::_createGroup(char *outId){
	
	curl_global_init(CURL_GLOBAL_DEFAULT);
	curl = curl_easy_init();

	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, true);
	curl_easy_setopt(curl, CURLOPT_CAINFO, "curl-ca-bundle.crt");
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &strResponse);

	curl_easy_setopt(curl, CURLOPT_URL, "https://api-cn.faceplusplus.com/facepp/v3/faceset/create");

	curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);

	curl_formadd(&formpost, &lastptr, CURLFORM_COPYNAME, "api_key", CURLFORM_COPYCONTENTS, "lxtJqlWUVMwoOuzRPQJPOZ15sZa59VlK", CURLFORM_END);

	curl_formadd(&formpost, &lastptr, CURLFORM_COPYNAME, "api_secret", CURLFORM_COPYCONTENTS, "rT7dp9PvuY-JweR57XA4VTPHoJwXtejM", CURLFORM_END);

	curl_formadd(&formpost, &lastptr, CURLFORM_COPYNAME, "outer_id", CURLFORM_COPYCONTENTS, "xp", CURLFORM_END);


	res = curl_easy_perform(curl);
	if (res != CURLE_OK)
		fprintf(stderr, "curl_easy_perform() failed: %s\n",
		curl_easy_strerror(res));

	curl_easy_cleanup(curl);
	curl_global_cleanup();

	m_recvMessage = strResponse;
	MessageBoxA(NULL, m_recvMessage.c_str(), NULL, NULL);

	return 0;
}

int CGroupManger::_deleteGroup(char *outId){

	struct curl_httppost *formpost = NULL;
	struct curl_httppost *lastptr = NULL;
	SetUrl("https://api-cn.faceplusplus.com/facepp/v3/faceset/delete");

	AddElememt( "outer_id", outId);
	SendToDst();

	curl_formfree(lastptr);
	curl_formfree(formpost);

	m_recvMessage = strResponse;
	return 0;
}
