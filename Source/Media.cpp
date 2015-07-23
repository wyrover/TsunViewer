#include "Media.hpp"

#include "common.hpp"

#include <rapidjson/document.h>

#include <restclient-cpp/restclient.h>

#include <string>

Media::Media(const rapidjson::Value::ConstValueIterator& iter)
{
	iterateJSONArray((*iter)["image"]["thumbnails"], 
		[&](const rapidjson::Value::ConstValueIterator& thumbIter)
		{
			std::string label = (*thumbIter)["label"].GetString();
			if (label == "preview") {
				RestClient::response imageReq = RestClient::get(
					(*thumbIter)["image"].GetString()
				);
				path = (*thumbIter)["url"].GetString();
				path.erase(0, 11);
				path = "Images/" + path;
				if (!fileExists(path)) {
					writeFile(path, imageReq.body);
				}
				
				width = (*thumbIter)["width"].GetInt();
				height = (*thumbIter)["height"].GetInt();
			}
		}
	);
}
