#include "Topic.hpp"

Topic::Topic() {}

Topic::Topic(const Topic &obj) {}

Topic& Topic::operator=(const Topic &obj) {return *this;}

Topic::~Topic() {}

//

int Topic::executeCommand(tParams &params, ClientManager &cl, ChannelManager &cn)
{
    //사용자의 모든 정보가 저장되었는지 확인
    if (!inviter->check_pass_client())
        throw 451;

    //채널 존재 여부 확인 ERR_NOSUCHCHANNEL (403)
    Channel* channel = cn.findChannel(params.tokens[1]);
    if (channel == NULL)
        throw 403;

    Client* client = cl.find_client(params.client_fd);
    // 파라미터가 1개일 경우 (토픽 조회)
    if (params.tokens.size() < 3)
    {
        // 사용자가 채널에 있는지 확인
        // 채널에 없는 경우: ERR_NOTONCHANNEL (442)
        if (channel->findClient(client->get_nickName()) == NULL)
            throw 442;
        // 채널에 있는 경우: 토픽과 토픽 수정 시간 출력
        std::string topic_msg = channel->getChannelName() + " topic: ";
        if (channel->getTopic().length() > 0)
            topic_msg += channel->getTopic();
        client->set_writeBuf(topic_msg);

        // 토픽이 있는 경우: RPL_TOPIC (332) + RPL_TOPICWHOTIME (333) 출력
        // 토픽이 공백인 경우: RPL_NOTOPIC (331) 출력
        if (channel->getTopic().length() > 0)
            throw 332;
        throw 331;
    }

    // 파라미터가 2개일 경우 (토픽 변경)
    // 채널 모드 확인
    // 't' 모드가 아닌 경우: 진행
    // 't' 모드인 경우: 사용자 권한 확인
        // 권한이 없는 경우: ERR_CHANOPRIVSNEEDED (482) 에러 발생
    if (channel->hasMode('t') && !channel->isOperator(client))
        throw 482;

    // 토픽 변경 및 수정 시간 업데이트
    channel->setTopic(params.tokens[2], client);
    // 변경된 토픽 출력(채널에 있는 모든 유저에게)
    std::vector<Client*> list =  channel->getParticipants();
    std::string topic_msg = ":" + client->get_userName() + "!" + client->get_userName() +\
                            "@" + client->get_realName() + " TOPIC " + channel->getChannelName()\
                            + " :" + params.tokens[2];
	for (int i = 0; i < list.size(); i++)
		list[i]->set_writeBuf(topic_msg);
    throw 332;
}