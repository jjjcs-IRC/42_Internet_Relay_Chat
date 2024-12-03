// #include "IrcParser.hpp"
// #include <vector>
// #include <string>
// #include <iostream>

// int main(void)
// {
//     IrcParser test;
    
//     std::vector<std::string> test_cases;
// 	// PASS
// 	test_cases.push_back("PASS secretpassword");
// 	test_cases.push_back("PASS anotherpassword123");
// 	test_cases.push_back("PASS");
// 	test_cases.push_back("PASS ");
// 	test_cases.push_back("PASS invalid password with spaces");
// 	// NICK
// 	test_cases.push_back("NICK user123");
// 	test_cases.push_back("NICK another_user");
// 	test_cases.push_back("NICK _nickname");
// 	test_cases.push_back("NICK user!@#$");
// 	test_cases.push_back("NICK");

// 	//USER
// 	test_cases.push_back("USER username 0 * :Real Name");
// 	test_cases.push_back("USER guest 8 * :Guest User");
// 	test_cases.push_back("USER bot_user 0 * :Bot Account");
// 	test_cases.push_back("USER ");
// 	test_cases.push_back("USER user_with_missing_info 0 *");

// 	// JOIN
// 	test_cases.push_back("JOIN #general");
// 	test_cases.push_back("JOIN &private_channel");
// 	test_cases.push_back("JOIN #channel password123");
// 	test_cases.push_back("JOIN 0");
// 	test_cases.push_back("JOIN #channel1,#channel2,#channel3");

// 	//KICK
// 	test_cases.push_back("KICK #general user123 :Breaking the rules");
// 	test_cases.push_back("KICK #channel user456");
// 	test_cases.push_back("KICK #private user789 :Spamming");
// 	test_cases.push_back("KICK #general");
// 	test_cases.push_back("KICK");

// 	// INVITE
// 	test_cases.push_back("INVITE user123 #channel");
// 	test_cases.push_back("INVITE user456 &private_channel");
// 	test_cases.push_back("INVITE user789 #channel_with_no_permission");
// 	test_cases.push_back("INVITE");
// 	test_cases.push_back("INVITE user_only");

// 	// TOPIC
// 	test_cases.push_back("TOPIC #general :New Topic");
// 	test_cases.push_back("TOPIC #channel_with_no_topic");
// 	test_cases.push_back("TOPIC #private_channel :Confidential");
// 	test_cases.push_back("TOPIC #channel :");
// 	test_cases.push_back("TOPIC #channel_with_long_topic :This is a very long topic text for testing.");

// 	// PRIVMSG
// 	test_cases.push_back("PRIVMSG user123 :Hello!");
// 	test_cases.push_back("PRIVMSG #general :Welcome to the channel.");
// 	test_cases.push_back("PRIVMSG user456 :How are you?");
// 	test_cases.push_back("PRIVMSG #channel_with_special_chars :@here!");
// 	test_cases.push_back("PRIVMSG #general");

// 	// PING
// 	test_cases.push_back("PING");
// 	test_cases.push_back("PING :server1");
// 	test_cases.push_back("PING :127.0.0.1");
// 	test_cases.push_back("PING :long_ping_data_for_testing");
// 	test_cases.push_back("PING :missing_colon");

// 	// PONG
// 	test_cases.push_back("PONG");
// 	test_cases.push_back("PONG :server1");
// 	test_cases.push_back("PONG :127.0.0.1");
// 	test_cases.push_back("PONG :invalid_response");
// 	test_cases.push_back("PONG");

//     // mode;
//     test_cases.push_back("MODE #channel +i");
//     test_cases.push_back("MODE #channel +t");
//     test_cases.push_back("MODE #channel +k password123");
//     test_cases.push_back("MODE #channel +l 50");
//     test_cases.push_back("MODE #channel +o user1");
//     test_cases.push_back("MODE #channel -o user2");

//     // 복합 테스트 명령어
//     test_cases.push_back("MODE #channel +it");
//     test_cases.push_back("MODE #channel +l 30 +o user3");
//     test_cases.push_back("MODE #channel +k password123 +t");
//     test_cases.push_back("MODE #channel -o user3 -l");
//     test_cases.push_back("MODE #channel +k password123 -k");

//     // 잘못된 매개변수 처리
//     test_cases.push_back("MODE #channel +k"); // throw 475
//     test_cases.push_back("MODE #channel +l invalid_number");
//     test_cases.push_back("MODE #channel -k extra_argument");
//     test_cases.push_back("MODE #channel +o");

//     // 비정상적인 입력 테스트
//     test_cases.push_back("MODE #channel +x");
//     test_cases.push_back("MODE #channel +o+k invalid_argument");
//     test_cases.push_back("MODE #channel -z");
//     test_cases.push_back("MODE #channel -k +o user5 +l 10"); // ??
//     test_cases.push_back("MODE #channel +k password123 -t");
//     test_cases.push_back("MODE #channel -o user6 +t");
//     test_cases.push_back("MODE #channel +k verylongpasswordthatexceedslimits");
//     test_cases.push_back("MODE #channel +l 1000000000");

//     // 벡터를 순회하며 테스트
// 	int i = 1;
//     for (std::vector<std::string>::iterator it = test_cases.begin(); it != test_cases.end(); ++it) {
//         tParams res;
//         std::cout << "Testing input["<< i++ <<"]: " << *it << std::endl;
//         try {
//             // 파싱 호출
//             res = test.IrcParsing(3, *it);
//             test.ShowParams(); // 파싱 결과 출력
//         } catch (int error_code) {
//             // 오류 처리
//             std::cerr << "Parsing error (" << error_code << ") for input: " << *it << std::endl;
//         }

//         std::cout << "---------------------------------------" << std::endl;
//     }

//     return 0;
// }
