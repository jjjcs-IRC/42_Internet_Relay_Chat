#include "Mode.hpp"

// 토큰을 만드는 헬퍼 함수: flag(모드), 부호(+/-), 파라미터를 조합해 문자열 생성
// 예: 'o', '+', "nickname" -> "o:+:nickname"
static std::string	MakeToken( char flag, char sign, std::string param )
{
	return (std::string(1, flag) + ":" + std::string(1, sign) + ":" + param);
}


// 문자열이 '+' 또는 '-'로 시작하는지 확인하는 함수
// MODE 명령어의 부호를 체크
static inline bool	IsSignString( std::string &str )
{
	char	c;

	c = str.at(0);
	if (c == '+' || c == '-')
		return (true);
	return (false);
}

// 플래그 문자열의 유효성을 검사하고 필요한 파라미터 개수를 반환
// o: operator 변경은 항상 파라미터 필요
// l: limit 설정(+)시에만 파라미터 필요
// k: key 설정(+)시에만 파라미터 필요


bool	IsDigit( std::string str )
{
	std::string::iterator	start = str.begin();
	std::string::iterator	end = str.end();

	for ( ; start != end ; ++start )
	{
		if (!std::isdigit(*start))
			return (false);
	}
	return (true);
}

std::vector<std::string>	Mode::Parser( std::vector<std::string>	&tokens )
{

		std::vector<std::string>	result;

		result.push_back("MODE");
		if (tokens.size() > 1)
			result.push_back(tokens[1]); // #channel

	/* sorting strings(flag and parameters ) */
	std::vector<std::string>	flag;
	std::vector<std::string>	params;
	{
		std::vector<std::string>::iterator	it = tokens.begin() + 2;
		bool cycle = true;
		(void)cycle;

		while(it != tokens.end()) {
			if (IsSignString(*it)) {
				flag.push_back(*it);
			} else {
				params.push_back(*it);
			}
			it++;
		}

	//파라미터 순서대로
	std::vector<std::string>::iterator paramIt = params.begin();
	// 각 플래그 그룹 처리
	for(std::vector<std::string>::iterator flagIt = flag.begin(); flagIt != flag.end(); ++flagIt) {
		char sign = (*flagIt)[0];
        
        // 각 플래그 처리
        for (size_t i = 1; i < flagIt->length(); ++i) {
            char flag = (*flagIt)[i];
            
            // 파라미터가 필요없는 플래그
            if (flag == 'i' || flag == 't' || (sign == '-' && flag != 'o')) {
                result.push_back(MakeToken(sign, flag, ""));
                continue;
            }
            
            // 파라미터가 필요한 플래그
            if (paramIt != params.end()) {
                // limit 모드는 숫자 검증 필요
                if (sign == '+' && flag == 'l') {
                    if (IsDigit(*paramIt)) {
                        result.push_back(MakeToken(sign, flag, *paramIt));
                        ++paramIt;
                    }
                    continue;
                }
				if (flag == 'o' || flag == 'k') {
					result.push_back(MakeToken(sign, flag, *paramIt));
					++paramIt;
				}
            }
        }
	}
}

	return (result);
}
