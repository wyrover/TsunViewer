#include "Media.hpp"

#include "common.hpp"

#include <rapidjson/document.h>

#include <restclient-cpp/restclient.h>

#include <iostream>
#include <string>

Media::Media(const rapidjson::Value::ConstValueIterator& iter)
{
	iterateJsonArray((*iter)["image"]["thumbnails"], 
		[&](const auto& thumbIter)
		{
			std::string label = (*thumbIter)["label"].GetString();
			if (label == "preview") {				
				url = (*thumbIter)["image"].GetString();
				
				path = (*thumbIter)["url"].GetString();
				path.erase(0, 11);
				path = "Images/" + path;
				
				width = (*thumbIter)["width"].GetInt();
				height = (*thumbIter)["height"].GetInt();				
				
				return true;
			}
			return false;
		}
	);
	loaded = fileExists(path);
}

void Media::load()
{	
	if (!loaded) {
		RestClient::response imageReq = RestClient::get(url);
		writeFile(path, imageReq.body);
		loaded = true;
	}
} 
