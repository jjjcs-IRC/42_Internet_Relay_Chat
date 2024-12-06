#include "Part.hpp"

Part::Part() {}

Part::Part(const Part &obj) {}

Part& Part::operator=(const Part &obj) {return *this;}

Part::~Part() {}

//

int Part::executeCommand(tParams &params, ClientManager &cl, ChannelManager &cn)
{
    Client *client = cl.find_client(params.client_fd);

    std::cout << "part : " << std::endl;
    //사용자의 모든 정보가 저장되어 명령어를 사용할 수 있는지 확인
    if (!client->check_pass_client())
        throw 451;

    std::cout << "part : 451" << std::endl;
    // 명령의 인자가 부족한 경우
    if (params.tokens.size() < 2)
        throw 461;
    std::cout << "part : 461" << std::endl;

    
    Channel *channel = cn.findChannel(params.tokens[1]);
    std::cout << "part : channel" << std::endl;

    //채널 존재 확인 (403)
    if (channel == NULL)
        throw 403;
    std::cout << "part : channel 403" << std::endl;

    // 채널에 참여하지 않은 경우
    if (channel->findClient(client->get_nickName()) == NULL)
        throw 442;
    std::cout << "part : channel 442" << std::endl;
    
    std::vector<Client*> client_list = channel->getParticipants();
    //권한을 가진 사람이 본인 한 명 -> 가장 오래된 사용자에게 권한 위임
    if (channel->getOperators().size() == 1 && channel->getOperators()[0] == client)
    {
        for (int i = 0; i < client_list.size(); i++)
        {
            if (client_list[i] != client)
            {
                channel->addOperator(client_list[i]);
                break;
            }
        }
    }
    std::cout << "part : channel oper" << std::endl;


    //채널에서 사용자 삭제
    channel->removeParticipantByName(client->get_nickName());
    
    //권한에서 사용자 삭제
    if (channel->isOperator(client))
        channel->removeOperatorByName(client->get_nickName());
    std::cout << "part : channel oper del" << std::endl;


    //사용자의 채널 목록에서 채널 삭제
    client->kick_client_from_channel(channel->getChannelName());
    std::cout << "part : channel  del" << std::endl;


    //채널에 사용자가 나갔다고 알림
    std::string part_msg = ":" + client->get_userName() + "!" + client->get_userName() + "@" + client->get_clientIp() \
                            + " PART " + channel->getChannelName() + " ";
    if (params.tokens.size() == 3)
        part_msg += params.tokens[2];
    else
        part_msg += ":good bye!";
    part_msg += "\r\n";
    for (int i = 0; i < client_list.size(); i++)
        client_list[i]->set_writeBuf(part_msg);

    std::cout << "part : msg" << std::endl;



    std::cout << "part : del" << std::endl;


    //채널에 참여자가 아무도 없는 경우, 채널 삭제
    if (channel->getParticipants().size() == 0)
        cn.deleteChannel(channel->getChannelName());

    std::cout << "part : channel del" << std::endl;


    throw 0;
}