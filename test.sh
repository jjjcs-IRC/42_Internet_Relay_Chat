#!/bin/bash

# 함수: 사용법 출력
usage() {
    echo "사용법:"
    echo "  $0 <포트> <패스워드> <닉네임> (localhost 접속)"
    echo "  $0 <닉네임> (irc.ubuntu.com 접속)"
    exit 1
}

# 인자 개수 확인
if [ $# -eq 0 ] || [ $# -eq 2 ] || [ $# -gt 3 ]; then
    usage
fi

# localhost 모드
if [ $# -eq 3 ]; then
    PORT=$1
    PASSWORD=$2
    NICK=$3
    SERVER="localhost"

    # 포트 번호 유효성 검사
    if ! [[ "$PORT" =~ ^[0-9]+$ ]] || [ "$PORT" -lt 1 ] || [ "$PORT" -gt 65535 ]; then
        echo "오류: 유효하지 않은 포트 번호입니다."
        exit 1
    fi

    echo "localhost의 $PORT 포트로 접속합니다. 닉네임: $NICK"
    irssi -c $SERVER -p $PORT -w $PASSWORD -n $NICK

# irc.ubuntu.com 모드
elif [ $# -eq 1 ]; then
    NICK=$1
    SERVER="irc.ubuntu.com"
    PORT=6667

    echo "irc.ubuntu.com의 6667 포트로 접속합니다. 닉네임: $NICK"
    irssi -c $SERVER -p $PORT -n $NICK

else
    usage
fi