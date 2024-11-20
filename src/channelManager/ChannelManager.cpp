#include "ChannelManager.hpp"

ChannelManager::ChannelManager() {}

ChannelManager::ChannelManager(const ChannelManager& other) {
    for (Channel* channel : other.channels) {
        channels.push_back(new Channel(*channel));
    }
}

ChannelManager& ChannelManager::operator=(const ChannelManager& other) {
    if (this != &other) {
        clear();
        for (Channel* channel : other.channels) {
            channels.push_back(new Channel(*channel));
        }
    }
    return *this;
}

ChannelManager::~ChannelManager() {
    clear();
}

Channel* ChannelManager::findChannel(const std::string& channelName) const {
    auto it = std::find_if(channels.begin(), channels.end(),
        [&channelName](Channel* channel) {
            return channel->getChannelName() == channelName;
        });

    return (it != channels.end()) ? *it : NULL;
}

bool ChannelManager::addChannel(Channel* newChannel) {
    if (!newChannel) return false;

    if (findChannel(newChannel->getChannelName())) {
        std::cout << "이미 존재하는 채널 이름: " << newChannel->getChannelName() << std::endl; // 에러 확인하기 위해 추가
        return false;
    }

    channels.push_back(newChannel);
    return true;
}

bool ChannelManager::deleteChannel(const std::string& channelName) {
    auto it = std::find_if(channels.begin(), channels.end(),
        [&channelName](Channel* channel) {
            return channel->getChannelName() == channelName;
        });

    if (it != channels.end()) {
        delete *it;
        channels.erase(it);
        return true;
    }

    std::cout << "해당 채널이 존재하지 않음: " << channelName << std::endl; // 에러 확인하기 위해 추가
    return false;
}

void ChannelManager::clear() {
    for (Channel* channel : channels) {
        delete channel;
    }
    channels.clear();
}
