#include <sstream>

#include "Kick.hpp"

Kick::Kick() {}

Kick::Kick(const Kick &obj) {}

Kick& Kick::operator=(const Kick &obj) {return *this;}

Kick::~Kick() {}

//

int Kick::executeCommand(tParams &params, ClientManager &cl, ChannelManager &cn)
{
    Channel* channel = cn.findChannel(params.tokens[1]);
    Client* kicker = cl.find_client(params.client_fd);
    //채널 존재 확인 (403)
    if (channel == NULL)
        return 403;

    //권한 확인
    //채널 참가 확인 (442)
    if (channel->findClient(kicker->get_nickName()) == NULL)
        return 442;
    //채널 권한 확인 (482)
    if (channel->hasMode('i'))
        return 482;

    std::istringstream ss(params.tokens[2]);
    std::string tmp;
    int res = 0;
    while (getline(ss, tmp, ',')) //','로 구분
    {
        Client *client = cl.find_client_byNick(tmp);
        //사용자가 채널에 존재하지 않는 경우 (441)
        if (channel->findClient(client->get_nickName()) == NULL)
        {
            res = 441;
            continue;
        }
        //채널에서 사용자 삭제
        channel->removeParticipantByName(client->get_nickName());
        //사용자의 채널 목록에서 채널 삭제
        client->kick_client_from_channel(params.tokens[1]);
        //강퇴당한 사용자에게 강퇴 메세지 전달
        std::string kick_msg = ":" + kicker->get_nickName() + "!" + kicker->get_userName() + "@" + \
                                kicker->get_realName() + " KICK " + params.tokens[1] + \
                                " " + tmp + " :" + params.tokens[3];
        client->set_writeBuf(kick_msg);
    }
    return res;
}