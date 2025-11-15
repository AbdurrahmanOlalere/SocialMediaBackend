# include <iostream>
# include <string>
# include <stdexcept>
# include "Post.h"

using std::string, std::vector;

Post::Post(unsigned int postId, string userName, string postText) : postId(postId), userName(userName), postText(postText) {
    if (postId == 0 || userName == "" || postText == "") {
        throw std::invalid_argument("post constructor: invalid parameter values");
    }
}
Post::Post() {
    postId = 0;
    userName = "DefaultUser";
    postText = "DefaultText";
}

unsigned int Post::getPostId() {
    return postId;
}

string Post::getPostUser() {
    return userName;
}

string Post::getPostText() {
    return postText;
}

vector<string> Post::findTags() {
    // TODO: extracts candidate tags based on occurrences of # in the post
    string word;
    vector<string> Twords;
    for (int i = 0; i < postText.size(); i++)
    {
        if (postText[i] == '#')
        {
            while (i < postText.size() && postText[i] != ' ')
            {
                word+=postText[i];
                i++;
            }
            for (int i = word.size()-1; i >= 0; i--)
            {
                if (word[i] != ',' && word[i] != '!' && word[i] != '?'&& word[i] != '.')
                {
                    word = word.substr(0, i+1);
                    break;
                }
                
            }
            
            Twords.push_back(word);
            word.clear();

        }
        
    }
    // debugging Twords;
    // for (int i = 0; i < Twords.size(); i++)
    // {
    //     std::cout << Twords.at(i);
    // }
    for (string& word : Twords)
    {
        for (char& c : word)
        {
            c = tolower(c);
        }
    }



    for (int i = 0; i < Twords.size(); i++)
    {
        for (int j = i+1; j < Twords.size();)
        {
            if (Twords[i] == Twords[j])
            {
                Twords.erase(Twords.begin() + j);
            }
            else{
                ++j;
            }
            
        }
        
    }
    

    
    
    
    return Twords;
    


    
}
