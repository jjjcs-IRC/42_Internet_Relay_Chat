// #include "IrcParser.hpp"
// #include <vector>
// #include <string>
// #include <iostream>

// int main(void)
// {
//     IrcParser test;
    
//     // 테스트 케이스를 벡터에 저장
//     std::vector<std::string> test_cases;
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
