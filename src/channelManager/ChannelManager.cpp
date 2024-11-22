#include "ChannelManager.hpp"
#include <algorithm>
#include <iostream>

ChannelManager::ChannelManager() {}

ChannelManager::ChannelManager(const ChannelManager& other) {
    for (std::vector<Channel*>::const_iterator it = other.channels.begin(); it != other.channels.end(); ++it) {
        channels.push_back(new Channel(**it));
    }
}

ChannelManager& ChannelManager::operator=(const ChannelManager& other) {
    if (this != &other) {
        clear();
        for (std::vector<Channel*>::const_iterator it = other.channels.begin(); it != other.channels.end(); ++it) {
            channels.push_back(new Channel(**it));
        }
    }
    return *this;
}

ChannelManager::~ChannelManager() {
    clear();
}

ChannelManager::ChannelFinder::ChannelFinder(const std::string& name) : name(name) {}

bool ChannelManager::ChannelFinder::operator()(Channel* channel) const {
    return channel->getChannelName() == name;
}

Channel* ChannelManager::findChannel(const std::string& channelName) const {
    std::vector<Channel*>::const_iterator it = std::find_if(
        channels.begin(), channels.end(), ChannelFinder(channelName));

    return (it != channels.end()) ? *it : NULL;
}

bool ChannelManager::addChannel(std::string channelName, Client *userName, std::string password) {
    if (findChannel(channelName)) {
        std::cout << "이미 존재하는 채널 이름: " << channelName << std::endl;
        return false;
    }

   try {
        // 채널 생성 및 추가
        Channel* newChannel = new Channel(channelName, userName, password);
        channels.push_back(newChannel);
        std::cout << "채널 추가: " << channelName << std::endl;
        return true;
    } catch (const std::invalid_argument& e) {
        std::cerr << "채널 생성 실패: " << e.what() << std::endl;
    }
    return false; 
}

bool ChannelManager::deleteChannel(const std::string& channelName) {
    std::vector<Channel*>::iterator it = std::find_if(
        channels.begin(), channels.end(), ChannelFinder(channelName));

    if (it != channels.end()) {
        delete *it;
        channels.erase(it);
        return true;
    }

    std::cout << "해당 채널이 존재하지 않음: " << channelName << std::endl;
    return false;
}

void ChannelManager::clear() {
    for (std::vector<Channel*>::iterator it = channels.begin(); it != channels.end(); ++it) {
        delete *it;
    }
    channels.clear();
}
