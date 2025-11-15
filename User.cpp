# include <string>
# include <stdexcept>
# include "User.h"

using std::string, std::vector;

User::User(string userName) : userName(userName) {
    // TODO: implement constructor checks
    if (userName.empty())
    {
        throw std::invalid_argument("Username is empty!");
    }
    
    if (userName.at(0) < 'a' || userName.at(0) > 'z' )
    {
        throw std::invalid_argument("Username doesn't start with lowercase letter");
    }
    
    for (char c : userName)
    {
        if ((c < 'a' || c > 'z'))
        {
            throw std::invalid_argument("Only lowercase Letters allowed");
        }
        
    }
    
}
User::User() {
    userName = "Default UserName";
}

string User::getUserName() {
    // TODO: implement getter
    return userName;
}

vector<Post*>& User::getUserPosts() {
    // TODO: implement getter
    return userPosts;
    
}

void User::addUserPost(Post* post) {
    // TODO: add post to user posts
    if (post == nullptr)
    {
        throw std::invalid_argument("There is no post here");
    }
    userPosts.push_back(post);// not sure if this the right way to do this but ill try this for lnow
}
