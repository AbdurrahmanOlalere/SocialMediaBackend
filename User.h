# ifndef _USER_H
# define _USER_H

# include <string>
# include <vector>
# include "Post.h"

class User {
    private:
        std::string userName;
        std::vector<Post*> userPosts;
    
    public:
        User(std::string userName);
        User();
        std::string getUserName();
        std::vector<Post*>& getUserPosts();
        void addUserPost(Post* post);
};

# endif
