
# include <iostream>
# include <fstream>
# include <sstream>
# include <stdexcept>
# include "Network.h"

using std::string, std::vector;

Network::Network() : users({}), posts({}), tags({}) {}

void Network::loadFromFile(string fileName) {
    // TODO: load user and post information from file
    std::ifstream file;
    file.open(fileName);
    if (file.fail())
    {
        throw std::invalid_argument("Failed to open " + fileName);
    }
    string type, post, user;
    string id;
    while (file >> type) {
        if (type == "User") {
            if (file >> user) {
                try {
                    addUser(user);
                } catch (const std::exception& e) {
                    throw std::runtime_error("Caught exception when trying to add User:" + user);
                }
            } else {
                throw std::invalid_argument("Missing Data");
            }
        } else if (type == "Post") {
            if (!(file >> id)) {
                throw std::runtime_error("Invalid post ID");
            }

            if (!(file >> user)) {
                throw std::runtime_error("Invalid post username");
            }
           
                // Creating a Post object and add it to the posts vector
            getline(file >> std::ws, post);
            if (post.empty()) {
            throw std::invalid_argument("Missing post data");
            }
            try {
                int postID = std::stoi(id);
                addPost(postID, user, post);
            } catch (const std::exception& e) {
                throw std::runtime_error("Caught exception when trying to add Posts");
            }
        } else {
            throw std::runtime_error("Unknown entry");
        }
    }

    if (!file.eof() && file.fail()) {
        throw std::invalid_argument("File could not be opened");
    }
}

void Network::addUser(string userName) {
    // TODO: create user and add it to network
    //std::transform(userName.begin(), userName.end(), userName.begin(), [] (unsigned char c){return std::tolower(c);});
    for (char& c : userName)
    {
        c = tolower(c);
    }
    

    //checing if the user already exists
    for (User* existingUser : users) {
        const User& user = *existingUser;
        if (existingUser->getUserName() == userName) {
            throw std::invalid_argument("User with this name already exists");
        }
    }

    //create a new User object
    try {
        users.push_back(new User(userName));
        std::cout << "Added User " << userName << std::endl;
    } catch (const std::exception& e) {
        // throws any exception that occurs during User creation
        std::cout << "Error: " << e.what() << std::endl;
    }
}


void Network::addPost(unsigned int postId, string userName, string postText) {
    // TODO: create post and add it to network
    //checking if the post with ID already exists
    bool postExists = false;
    for (Post* existingPost : posts)
    {
        if (existingPost->getPostId() ==  postId)
        {
            postExists = true;
            break;
        }
        
    }
    if (postExists)
    {
        throw std::invalid_argument("This Post exists");
    }
    

    //finding the user with given name
    User* user = nullptr;
    for (User* existingUser : users) {
        if (existingUser->getUserName() == userName) {
            user = const_cast<User*>(existingUser);
            break;
        }
    }    
    //create a new post object
    if (!user)
    {
        throw std::invalid_argument("User was not Found");
        
        
    }
        
    try{
        Post* newPost = new Post(postId,userName,postText);
        posts.push_back(newPost);
        std::cout << "Added Post " << postId << " by " << userName << std::endl;
        user->addUserPost(newPost);
        //string test = user->getUserPosts();
        //std::cout <<  << std::endl;
        const vector<string>& postTags = newPost->findTags();

        // find each candidate hashtag
        for (const string& tag : postTags) {
            bool tagExists = false;

            //  check if the tag already exists in the collection of tags
            for (Tag* existingTag : tags) {
                if (existingTag->getTagName() == tag) {
                    tagExists = true;
                    existingTag->addTagPost(newPost);
                    break;
                }
            }

            // If the tag does not exist, create a new tag and add it to tags
            if (!tagExists) {
                try {
                    Tag* newTag = new Tag(tag);
                    tags.push_back(newTag);
                    newTag->addTagPost(newPost);
                } catch (const std::exception& e) {
                    // catch the exception thrown by Tag constructor and continue processing
                    continue;
                }
            }
        }
    } catch (const std::exception& e) {
        // catch any exception that occurs during Post creation
        std::cout << "Error creating post: " << e.what() << std::endl;
    }
}



vector<Post*> Network::getPostsByUser(string userName) {
    // TODO: return posts created by the given user
    if (userName.empty()) {
        throw std::invalid_argument("User name is empty");
    }
    //std::cout << "passed first check" <<std::endl;
    User* user = nullptr;
    for (int i = 0; i < users.capacity(); i++) {
        if (users[i]->getUserName() == userName) {
            user = users[i];
            break;
        }
    }
    //std::cout << "passed second check" <<std::endl;

    if (!user) {
        throw std::invalid_argument("User not found");
    }
    
    return user->getUserPosts();
}

vector<Post*> Network::getPostsWithTag(string tagName) {
    // TODO: return posts containing the given tag
    if (tagName.empty()) {
        throw std::invalid_argument("Tag name is empty");
    }

    // Search for the tag with the given tagName
    Tag* tag = nullptr;
    for (Tag* existingTag : tags) {
        if (existingTag->getTagName() == tagName) {
            tag = const_cast<Tag*>(existingTag);
            break;
        }
    }

    // If tag is not found, throw std::invalid_argument
    if (!tag) {
        throw std::invalid_argument("Tag not found");
    }

    // Return the posts associated with the tag
    return tag->getTagPosts();
}

vector<string> Network::getMostPopularHashtag() {
    // TODO: return the tag occurring in most posts
    if (tags.empty()) {
        // no hashtags in the network
        return vector<string>();
    }
    vector<std::string> mostPopularHashtags;
    vector<int> hashtagCounts;

    

     for (Post* post : posts) {
        const vector<string>& postTags = post->findTags();
        for (const string& tag : postTags) {
            bool found = false;

            // Check if already in mostPopularHashtags
            for (size_t i = 0; i < mostPopularHashtags.size(); ++i) {
                if (mostPopularHashtags[i] == tag) {
                    hashtagCounts[i]++;
                    found = true;
                    break;
                }
            }

            //add to mostPopularHashtags and set count to 1 if not found
            if (!found) {
                mostPopularHashtags.push_back(tag);
                hashtagCounts.push_back(1);
            }
        }
    }

    vector<string> result;
    int maxCount = 0;

    for (size_t i = 0; i < mostPopularHashtags.size(); i++) {
        if (hashtagCounts[i] > maxCount) {
            result.clear();
            result.push_back(mostPopularHashtags[i]);
            maxCount = hashtagCounts[i];
        } else if (hashtagCounts[i] == maxCount) {
            result.push_back(mostPopularHashtags[i]);
        }
    }

    return result;

    


}

Network::~Network() {
    for (unsigned int i = 0; i < users.size(); ++i) {
        delete users.at(i);
    }

    for (unsigned int i = 0; i < tags.size(); ++i) {
        delete tags.at(i);
    }
    
    for (unsigned int i = 0; i < posts.size(); ++i) {
        delete posts.at(i);
    }
}