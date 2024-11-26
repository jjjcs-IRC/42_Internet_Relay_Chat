# 42_Internet_Relay_Chat
# first Parser::


#feat/#20/ParserClass - 2024/11/21 Update
<Irctype.hpp> update:
define CMD_Numbers
- JOIN
- KICK
- INVITE
- TOPIC
- MODE

Newly created:
<JoinParser.hpp & JoinParser.cpp>
<KickParser.hpp & KickParser.cpp>
<InviteParser.hpp & InviteParser.cpp>
<InviteParser.hpp & InviteParser.cpp>

Modified function:
SuperParser	*IrcParser::NewClassPtr()