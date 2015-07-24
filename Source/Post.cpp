#include "Post.hpp"

#include "common.hpp"
#include "Media.hpp"

#include <rapidjson/document.h>

Post::Post(const rapidjson::Value::ConstValueIterator& iter)
{
	title = (*iter)["title"].GetString();
	
	iterateJsonArray((*iter)["media"], 
		[&](const auto& iter)
		{
			media.push_back(Media(iter));
			return false;
		}
	);
}
