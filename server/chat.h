#pragma once
#include <list>

#include <string>
#include <vector>

#include <nlohmann/json.hpp>
#include <mutex>

#include <ctime>
class Message
{
public:
    explicit Message(const std::string &msg, int user_id)
        : user_id(user_id), timestamp(std::time(nullptr)), text(msg){

                                                           };
    ~Message(){};

    int id;
    int user_id;
    std::string text;
    time_t timestamp;
};

class Chat
{
public:
    explicit Chat(){};
    ~Chat(){};

    void add_message(Message message)
    {
        messages.push_back(message);
    };
    void add_user(int user_id)
    {
        users.push_back(user_id);
    };

    std::vector<Message> get_messages()
    {
        return std::vector<Message>{std::begin(messages), std::end(messages)};
    }

    bool has_user(int user_id)
    {
        return std::count(users.begin(), users.end(), user_id);
    }

    std::list<Message> messages;
    std::list<int> users;

private:
    int id;
};

class ChatHandler
{
public:
    explicit ChatHandler(){
        chats.push_back(Chat());
    };

    ~ChatHandler(){};

    void add_chat(Chat chat)
    {
        std::lock_guard<std::mutex> lock(chats_mutex);
        chats.push_back(chat);
    }

    void handle_message(const Message &message, int chat_id)
    {
        std::lock_guard<std::mutex> lock(chats_mutex);
        chats.at(chat_id).add_message(message);
    }

    void handle_user_chat_add(int chat_id, int user_id)
    {
        std::lock_guard<std::mutex> lock(chats_mutex);
        chats.at(chat_id).add_user(user_id);
    }

    std::vector<Message> get_chat_messages(int chat_id)
    {
        std::lock_guard<std::mutex> lock(chats_mutex);
        return chats.at(chat_id).get_messages();
    }

private:
    std::vector<Chat> chats;
    std::mutex chats_mutex;
};
