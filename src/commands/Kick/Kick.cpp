#include <sstream>

#include "Kick.hpp"

Kick::Kick() {}

Kick::Kick(const Kick &obj) {}

Kick& Kick::operator=(const Kick &obj) {return *this;}

Kick::~Kick() {}


int Kick::executeCommand(tParams &params, ClientManager &cl, ChannelManager &cn)
{
    Channel* channel = cn.findChannel(params.tokens[1]);
    Client* kicker = cl.find_client(params.client_fd);

    if (params.tokens.size() < 3)
        throw 461;
    //사용자의 모든 정보가 저장되어 명령어를 사용할 수 있는지 확인
    if (!kicker->check_pass_client())
        throw 451;

    //채널 존재 확인 (403)
    if (channel == NULL)
        throw 403;

    //권한 확인
    //채널 참가 확인 (442)
    if (channel->findClient(kicker->get_nickName()) == NULL)
        throw 442;

    //채널 권한 확인 (482)
    if (!channel->isOperator(kicker))
        throw 482;

    Client *kickee = cl.find_client_byNick(params.tokens[2]);
    if(!kickee){ // 해당 닉네임의 클라이언트가 존재하지 않는 경우 (401)
        throw 401; 
    }
    //사용자가 채널에 존재하지 않는 경우 (441)
    if (channel->findClient(kickee->get_nickName()) == NULL)
        throw 441;

    std::vector<Client*> client_list = channel->getParticipants();
    //강퇴하려는 사용자가 본인 && 권한을 가진 사람이 본인 한 명 -> 가장 오래된 사용자에게 권한 위임
    if (kicker->get_nickName() == kickee->get_nickName() && channel->getOperators().size() == 1)
    {
        for (int i = 0; i < client_list.size(); i++)
        {
            if (client_list[i] != kicker)
            {
                channel->addOperator(client_list[i]);
                break;
            }
        }
    }

    //권한에서 사용자 삭제
    if (channel->isOperator(kickee))
        channel->removeOperatorByName(kickee->get_nickName());
    
     // 초대목록에서 사용자 삭제
    if(channel->isInvited(kickee))
        channel->removeinvitedClientsByName(kickee->get_nickName());

    //사용자의 채널 목록에서 채널 삭제
    kickee->kick_client_from_channel(params.tokens[1]);
    
    //강퇴당한 사용자에게 강퇴 메세지 전달
    std::string kick_msg = ":" + kicker->get_nickName() + "!" + kicker->get_userName() + "@" + kicker->get_clientIp()\
                            + " KICK " + channel->getChannelName() + " " + kickee->get_nickName();
    if (params.tokens.size() == 4) //강퇴 사유가 있는 경우
        kick_msg += " " + params.tokens[3];
    kick_msg += "\r\n";
    for (int i = 0; i < client_list.size(); i++)
        client_list[i]->set_writeBuf(kick_msg);

    //채널에서 사용자 삭제
    channel->removeParticipantByName(kickee->get_nickName());

    //채널에 참여자가 아무도 없는 경우, 채널 삭제
    if (channel->getParticipants().size() == 0)
        cn.deleteChannel(channel->getChannelName());

    throw 0;
}