#pragma once
#include <vector>
#include <string>
#include <nlohmann/json.hpp>

class Message{
public:
    explicit Message(nlohmann::json msg);
    ~Message(){};

    int id;
    int user_id;
    std::string text;
    long long int timestamp;
};

class Chat
{
public:
    explicit Chat(){};
    ~Chat(){};

    void add_message(Message message);
    void add_user(int user_id);

    std::vector<Message> get_messages(){
        return messages;
    }

    std::vector<Message> messages;
    std::vector<int> users;
private:
    int id;
};

class ChatHandler{
public:
    explicit ChatHandler(){};
    ~ChatHandler(){};

    void handle_message(const Message& message){
        chats.at(message.id).add_message(message);
    }
    
    void handle_user_chat_add(int chat_id, int user_id){
        chats.at(chat_id).add_user(user_id);
    }

    void get_chat_messages(int chat_id){
        chats.at(chat_id).get_messages();
    }

    std::vector<Chat> chats;
};


