#include "Invite.hpp"

Invite::Invite() {}

Invite::Invite(const Invite &obj) 
{
    (void)obj;
}

Invite& Invite::operator=(const Invite &obj) 
{
    (void)obj;
    return *this;
}

Invite::~Invite() {}

//

int Invite::executeCommand(tParams &params, ClientManager &cl, ChannelManager &cn)
{
    Channel *channel = cn.findChannel(params.tokens[2]);
    Client* inviter = cl.find_client(params.client_fd);
    Client* invitee = cl.find_client_byNick(params.tokens[1]);

    if (params.tokens.size() < 3)
        throw 461;
    //사용자의 모든 정보가 저장되어 명령어를 사용할 수 있는지 확인
    if (!inviter->check_pass_client())
        throw 451;

    //개인 존재 유무 확인 (401)
    if (cl.find_client_byNick(params.tokens[1]) == NULL)
        throw 401;

    //채널 존재 유무 확인 (403)
    if (channel == NULL)
        throw 461;

    //실행자(초대자)가 채널에 있는지 확인 (442)
    if (channel->findClient(inviter->get_nickName()) == NULL)
        throw 442;

    //채널 모드 확인 및 초대자의 운영자 권한 확인
    //초대 제한 모드이고 초대자가 운영자가 아닌 경우: ERR_CHANOPRIVSNEEDED (482)
    if (!channel->isOperator(inviter))
        throw 482;

    //대상자가 이미 채널에 있는지 확인 (443)
    if (channel->findClient(params.tokens[1]) != NULL)
        throw 443;

    //초대 처리
    //대상자에게 PRIVMSG로 초대 메시지 전송 -> 명령어 불러오지 않고 임의로 처리
    std::string invite_msg = ":" + inviter->get_nickName() + "!" + inviter->get_userName() + "@"\
                             + inviter->get_realName() + " INVITE " + invitee->get_clientIp() + " :"\
                             + channel->getChannelName() + "\n";
    cl.find_client_byNick(params.tokens[1])->set_writeBuf(invite_msg);
    //채널의 초대 리스트에 대상자 추가
    channel->inviteClient(invitee);
    //초대자에게 RPL_INVITING (341) 전송
    throw 341;
}