#include <iostream>
#include <exception>
#include <map>
#include <set>

class Message {
public:
    Message(int id, const std::string &username, const std::string &message) {
        this->id = id;
        this->username = username;
        this->message = message;
    }

    void like(const std::string &username) {
        if (this->likes.find(username) == this->likes.end()) {
            this->likes.insert(username);

            return;
        }

        this->likes.erase(username);
    }

    int get_id() const {
        return this->id;
    }

    friend std::ostream& operator<<(std::ostream &os, const Message &message) {
        os << message.id << ":" << message.username << " (" << message.message << ")";

        if (message.likes.size() > 0) {
            int count {0};

            os << " [";

            for (const std::string &username : message.likes) {
                if (count++ > 0) {
                    os << ", ";
                }

                os << username;
            }

            os << "]";
        }

        return os;
    }

private:
    int id;
    std::string username;
    std::string message;
    std::set<std::string> likes;
};

class Inbox {
public:
    void receive_new(Message *tweet) {
        int tweet_id = tweet->get_id();

        this->all_messages[tweet_id] = tweet;
        this->unread[tweet_id] = tweet;
    }

    void store(Message *tweet) {
        this->all_messages[tweet->get_id()] = tweet;
    }

    std::map<int, Message*>& get_all() {
        this->unread.clear();

        return this->all_messages;
    }

    std::map<int, Message*> get_unread() {
        std::map<int, Message*> unread = this->unread;

        this->unread.clear();

        return unread;
    }

    Message* get_tweet(int tweet_id) {
        std::map<int, Message*>::iterator it = this->all_messages.find(tweet_id);

        if (it != this->all_messages.end()) {
            return it->second;
        }

        return nullptr;
    }
    
    friend std::ostream& operator<<(std::ostream &os, Inbox &inbox) {
        int count {0};

        for (std::pair<const int, Message*> &pair : inbox.get_all()) {
            if (count++ > 0) {
                os << "\n";
            }

            os << *pair.second;
        }

        return os;
    }

private:
    std::map<int, Message*> all_messages;
    std::map<int, Message*> unread;
};

class User {
public:
    User(const std::string &username) {
        this->username = username;
    }

    void follow(User &other) {
        if (this->username == other.username) {
            throw "Você não pode seguir você mesmo!";
        }

        this->following.insert({other.username, &other});
        other.followers[this->username] = this;
    }

    void unfollow(const std::string &username) {
        this->following[username]->followers.erase(this->username);
        this->following.erase(username);
    }

    Inbox& get_inbox() {
        return this->inbox;
    }

    void like(int tweet_id) {
        Message *message = this->inbox.get_tweet(tweet_id);

        if (message == nullptr) {
            throw "Tweet não existe!";
        }

        message->like(this->username);
    }

    void send_tweet(Message *tweet) {
        for (std::pair<const std::string, User*> &pair : this->followers) {
            pair.second->inbox.receive_new(tweet);
        }

        this->inbox.store(tweet);
    }

    friend std::ostream& operator<<(std::ostream &os, const User &user) {
        os << user.username << "\n" << "\tseguindo: [";

        int count {0};

        for (const std::pair<const std::string, User*> &pair : user.following) {
            if (count++ > 0) {
                os << ", ";
            }

            os << pair.first;
        }

        os << "]\n\tseguidores: [";

        count = 0;

        for (const std::pair<const std::string, User*> &pair : user.followers) {
            if (count++ > 0) {
                os << ", ";
            }

            os << pair.first;
        }

        os << "]";

        return os;
    }

private:
    std::string username;
    Inbox inbox;
    std::map<std::string, User*> followers;
    std::map<std::string, User*> following;
};

class Controler {
public:
    Controler() {
        this->next_tweet_id = 0;
    }

    ~Controler() {
        for (std::pair<const int, Message*> &pair : this->tweets) {
            delete pair.second;
        }

        for (std::pair<const std::string, User*> &pair : this->users) {
            delete pair.second;
        }
    }

    void add_user(const std::string &username) {
        this->users[username] = new User(username);
    }

    void send_tweet(const std::string &username, const std::string &user_message) {
        Message *message = new Message(this->next_tweet_id, username, user_message);


        this->users[username]->send_tweet(message);
        this->tweets[this->next_tweet_id++] = message;
    }

    User& get_user(const std::string &username) {
        if (this->users.find(username) == this->users.end()) {
            throw "Nenhum usuário encontrado!";
        }

        return *this->users[username];
    }

    friend std::ostream& operator<<(std::ostream &os, const Controler &controler) {
        int count {0};

        for (const std::pair<const std::string, User*> &pair : controler.users) {
            if (count++ > 0) {
                os << "\n";
            }

            os << *pair.second;
        }

        return os;
    }

private:
    int next_tweet_id;
    std::map<int, Message*> tweets;
    std::map<std::string, User*> users;
};

int main() {

    return 0;
}