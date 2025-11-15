# include <string>
# include <stdexcept>
# include "Tag.h"

using std::string, std::vector;

Tag::Tag(string tagName) : tagName(tagName) {
    // TODO: implement constructor checks
    if (tagName.length() < 2)
    {
        throw std::invalid_argument("tagName is less than 2");
    }

    if (tagName[0] != '#')
    {
        throw std::invalid_argument("tagName doesn't start with #");
    }
    if (tagName[1] < 'a' || tagName[1] > 'z')
    {
        throw std::invalid_argument("tagName's second char isn't between a - z");
    }

    vector<char> chcks;
    chcks.push_back('!');
    chcks.push_back(',');
    chcks.push_back('.');
    chcks.push_back('?');

    for (int i = 0; i < chcks.size(); i++)
    {
        if (tagName[-1] == chcks.at(i))//finds the last char in string against the vector of certain chars
        {
            for (int j = 0; i < chcks.size(); j++)//finds the second to last char and checks if if also contains thos chars.
            {
                if (tagName[-2]== chcks.at(j))
                {
                    throw std::invalid_argument("Invalid format for Tags");
                }
                
            }
            
        }
    }
    
    

    
    
    
}

string Tag::getTagName() {
    // TODO: implement getter
    return tagName;
}

vector<Post*>& Tag::getTagPosts() {
    // TODO: implement getter
    return tagPosts;
}

void Tag::addTagPost(Post* post) {
    // TODO: add post to tag posts
    if (post == nullptr)
    {
        throw std::invalid_argument("Invalid Argument for Tag");
    }
    // need to add posts to the vector
    //
    tagPosts.push_back(post);
    
}
