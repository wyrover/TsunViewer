#include "Post.hpp"

#include "common.hpp"
#include "Media.hpp"

#include <rapidjson/document.h>

Post::Post(const rapidjson::Value::ConstValueIterator& iter)
{
	title = (*iter)["title"].GetString();
	
	iterateJSONArray((*iter)["media"], 
		[&](const rapidjson::Value::ConstValueIterator& iter)
		{
			media.push_back(Media(iter));
		}
	);
}
