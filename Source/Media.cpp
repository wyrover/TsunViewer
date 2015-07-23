#include "Media.hpp"

#include "common.hpp"

#include <rapidjson/document.h>

#include <restclient-cpp/restclient.h>

#include <string>

Media::Media(const rapidjson::Value::ConstValueIterator& iter)
{
	RestClient::response imageReq = RestClient::get(
		(*iter)["image"]["image"].GetString()
	);
	path = (*iter)["image"]["url"].GetString();
	path.erase(0, 11);
	path = "Images/" + path;
	if (!fileExists(path)) {
		writeFile(path, imageReq.body);
	}
	
	width = (*iter)["width"].GetInt();
	height = (*iter)["height"].GetInt();
}
