#include <iostream>
#include <exception>
#include <unordered_map>
#include <vector>
#include <map>
#include <set>
#include "auxiliar.hpp"

class TwitterException : public std::exception {
public:
    TwitterException(const std::string &message) : message(message) {}

    const char* what() const noexcept override {
        return message.c_str();
    }

private:
    std::string message;
};

class Tweet {
public:
    Tweet(int id, const std::string &username, const std::string &message) : username(username), message(message) {
        this->id = id;
        this->deleted = false;
        this->retweet = nullptr;
    }

    void like(const std::string &username) {
        if (this->deleted) {
            return;
        }

        if (this->likes.find(username) == this->likes.end()) {
            this->likes.insert(username);
        } else {
            this->likes.erase(username);
        }
    }

    int get_id() const {
        return this->id;
    }

    std::string get_username() const {
        return this->username;
    }

    std::string get_message() const {
        return this->message;
    }

    const std::set<std::string>& get_likes() const {
        return this->likes;
    }

    bool is_deleted() const {
        return this->deleted;
    }

    void set_retweet(Tweet *retweet) {
        this->retweet = retweet;
    }

    void set_deleted() {
        this->deleted = true;
        this->username = "Account deleted";
        this->message = "Tweet deleted";
        this->likes.clear();
    }

    friend std::ostream& operator<<(std::ostream &os, const Tweet &tweet) {
        os << "--------Tweet id: " << tweet.id;
        os << "\n\tUser: " << tweet.username << "\n\tTweet: " << tweet.message;

        if (!tweet.deleted) {
            os << "\n\tLikes: [";

            int count {0};

            for (const std::string &username : tweet.likes) {
                if (count++ > 0) {
                    os << ", ";
                }

                os << username;
            }

            os << "]";

            if (tweet.retweet) {
                os << "\n\t↳Retweet:\n" << *tweet.retweet;
            }
        }

        return os;
    }

private:
    int id;
    bool deleted;
    std::string username;
    std::string message;
    std::set<std::string> likes;
    Tweet *retweet;
};

class Timeline {
public:
    Timeline() = default;

    void store_in_timeline(Tweet *tweet) {
        this->user_timeline.insert({tweet->get_id(), tweet});
    }

    void store_in_my_tweets(Tweet *tweet) {
        this->user_tweets.insert({tweet->get_id(), tweet});
    }

    void remove_tweets_from(const std::string &username) {
        std::vector<int> keys_to_delete;

        for (auto &[id, tweet] : this->user_timeline) {
            if (tweet->get_username() == username) {
                keys_to_delete.push_back(id);
            }
        }

        for (int key : keys_to_delete) {
            this->user_timeline.erase(key);
        }
    }

    void delete_tweets() {
        for (auto &[id, tweet] : this->user_tweets) {
            tweet->set_deleted();
        }

        this->user_tweets.clear();
    }

    void delete_timeline() {
        this->user_timeline.clear();
    }

    Tweet* get_tweet(int tweet_id) {
        std::unordered_map<int, Tweet*>::iterator it {this->user_timeline.find(tweet_id)};

        if (it == this->user_timeline.end()) {
            throw TwitterException("Error: tweet not found!");
        }

        return it->second;
    }

    const std::unordered_map<int, Tweet*>& get_timeline() const {
        return this->user_timeline;
    }

    const std::unordered_map<int, Tweet*>& get_my_tweets() const {
        return this->user_tweets;
    }

    friend std::ostream& operator<<(std::ostream &os, const Timeline &timeline) {
        int count {0};

        for (auto &[id, tweet] : timeline.user_timeline) {
            if (count++ > 0) {
                os << "\n\n";
            }

            os << *tweet;
        }

        return os;
    }

private:
    std::unordered_map<int, Tweet*> user_timeline;
    std::unordered_map<int, Tweet*> user_tweets;
};

class User {
public:
    User(const std::string &username) : username(username) {}

    void follow(User *other_user) {
        this->following.insert({other_user->username, other_user});
        other_user->followers.insert({this->username, this});
    }

    void unfollow(const std::string &username) {
        std::map<std::string, User*>::iterator it {this->following.find(username)};

        if (it == this->following.end()) {
            throw TwitterException("Error: you don't follow this person!");
        }

        this->timeline.remove_tweets_from(it->first);
        this->following[username]->followers.erase(this->username);
        this->following.erase(it);
    }

    void send_tweet(Tweet *tweet) {
        this->timeline.store_in_my_tweets(tweet);
        this->timeline.store_in_timeline(tweet);

        for (auto &[name, user] : this->followers) {
            user->timeline.store_in_timeline(tweet);
        }
    }

    void like(int tweet_id) {
        try {
            this->timeline.get_tweet(tweet_id)->like(this->username);
        } catch (const TwitterException &e) {
            std::cout << e.what() << std::endl;
        }
    }

    void delete_account() {
        this->unfollow_all();
        this->reject_all();
        this->timeline.delete_tweets();
    }


    Timeline& get_timeline() {
        return this->timeline;
    }

    friend std::ostream& operator<<(std::ostream &os, const User &user) {
        os << user.username << "\n\t↳Following: [";

        int count {0};

        for (auto &[name, user] : user.following) {
            if (count++ > 0) {
                os << ", ";
            }

            os << name;
        }

        count = 0;

        os << "]\n\t↳Followers: [";

        for (auto &[name, user] : user.followers) {
            if (count++ > 0) {
                os << ", ";
            }

            os << name;
        }        

        os << "]";

        return os;
    }

private:
    std::string username;
    Timeline timeline;
    std::map<std::string, User*> followers;
    std::map<std::string, User*> following;

    void unfollow_all() {
        std::vector<std::string> keys_to_delete;

        for (auto &[name, user] : this->following) {
            keys_to_delete.push_back(name);
        }

        for (const std::string &key : keys_to_delete) {
            this->unfollow(key);
        }
    }

    void reject_all() {
        std::vector<User*> users_to_unfollow;

        for (auto &[name, user] : this->followers) {
            users_to_unfollow.push_back(user);
        }

        for (User *user : users_to_unfollow) {
            user->unfollow(this->username);
        }
    }
};

class Controller {
public:
    Controller() {
        this->next_tweet_id = 0;
    }

    ~Controller() {
        for (auto &[username, user] : this->users) {
            delete user;
        }

        for (auto &[id, tweet] : this->tweets) {
            delete tweet;
        }
    }

    void add_user(const std::string &username) {
        User *new_user {new User(username)};
        
        auto &&[it, added] = this->users.insert({username, new_user});

        if (!added) {
            delete new_user;

            throw TwitterException("Error: this username is already in use!");
        }
    }

    void send_tweet(const std::string &username, const std::string &message) {
        try {
            User *user {this->get_user(username)};
            Tweet *new_tweet {this->create_tweet(username, message)};

            this->tweets.insert({new_tweet->get_id(), new_tweet});
            user->send_tweet(new_tweet);
        } catch (const TwitterException &e) {
            std::cout << e.what() << std::endl;
        }
    }

    void send_retweet(const std::string &username, int tweet_id, const std::string &retweet_message) {
        try {
            User *user {this->get_user(username)};
            Tweet *tweet {user->get_timeline().get_tweet(tweet_id)}, *new_tweet {this->create_tweet(username, retweet_message)};

            new_tweet->set_retweet(tweet);

            this->tweets.insert({new_tweet->get_id(), new_tweet});
            user->send_tweet(new_tweet);
        } catch (const TwitterException &e) {
            std::cout << e.what() << std::endl;
        }
    }

    User* get_user(const std::string &username) {
        std::map<std::string, User*>::iterator it {this->users.find(username)};

        if (it == this->users.end()) {
            throw TwitterException("Error: user not found!");
        }
        
        return this->users[username];
    }

    void remove_user(const std::string &username) {
        try {
            User *user {this->get_user(username)};

            user->delete_account();

            this->users.erase(username);

            delete user;
        } catch(const TwitterException &e) {
            std::cout << e.what() << std::endl;
        }
    }

    friend std::ostream& operator<<(std::ostream &os, const Controller &controller) {
        for (auto &[username, user] : controller.users) {
            os << *user << std::endl;
        }

        return os;
    }

private:
    int next_tweet_id;
    std::map<std::string, User*> users;
    std::map<int, Tweet*> tweets;

    Tweet* create_tweet(const std::string &username, const std::string &message) {
        return new Tweet(this->next_tweet_id++, username, message);
    }
};

int main(){
    Controller system;

    while(true) {
        std::cout << "$";

        std::vector<std::string> parameters {aux::get_cmd()};

        try {
            std::string cmd {parameters.at(0)};

            if (cmd == "end") {
                break;
            } else if (cmd == "add") {
                system.add_user(parameters.at(1));
            } else if (cmd == "rm") {
                system.remove_user(parameters.at(1));
            } else if (cmd == "follow") {
                system.get_user(parameters.at(1))->follow(system.get_user(parameters.at(2)));
            } else if (cmd == "unfollow") {
                system.get_user(parameters.at(1))->unfollow(parameters.at(2));
            } else if (cmd == "tweet") {
                std::string tweet_message {aux::join(aux::slice(parameters, 2), " ")};

                system.send_tweet(parameters.at(1), tweet_message);
            } else if (cmd == "like") {
                system.get_user(parameters.at(1))->like(std::stoi(parameters.at(2)));
            } else if (cmd == "timeline") {
                Timeline timeline {system.get_user(parameters.at(1))->get_timeline()};

                std::cout << timeline << std::endl;
            } else if (cmd == "retweet") {
                std::string tweet_message {aux::join(aux::slice(parameters, 3), " ")};

                system.send_retweet(parameters.at(1), std::stoi(parameters.at(2)), tweet_message);
            } else if (cmd == "show") {
                std::cout << system << '\n';
            } else {
                std::cout << "Error: your command doesn't exist!" << std::endl;
            }
        } catch (const TwitterException &e) {
            std::cout << e.what() << std::endl;
        } catch (...) {
            std::cout << "Error: bad command!" << std::endl;
        }
    }

    return 0;
}