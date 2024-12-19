# 📧 📩 📤 42_Internet_Relay_Chat  📥 📮 💌 💬

| 항목 | 내용 |
| --- | --- |
| **개발 기간** | 2024.11 - 2024.12 |
| **개발 언어** | C++ 98 |
| **멤버** | 팀 jjjcs_irc ([jjhang](https://github.com/jjhang42), [jimchoi](https://github.com/jimchoi9), [jeakim](https://github.com/jeayoungKim529), [choolee](https://github.com/MatSalt), [seonghmo](https://github.com/seong-hui)) |

<br/>

## 📌 목차
- [✏️ IRC 프로젝트 설명](#%EF%B8%8F-irc-프로젝트-설명)
- [🛠️ 프로젝트 구조도](#%EF%B8%8F-프로젝트-구조도)
- [✅ 구현한 명령어](#-구현한-명령어)
- [🏃🏻‍♂️ 실행하기](#%EF%B8%8F-실행하기)
- [📚 참고 자료](#-참고자료)

  <br/>

## ✏️ IRC 프로젝트 설명
해당 프로젝트는 **IRC 서버의 기능**들을 부분적으로 제공하는 프로그램입니다. <br/>
42서울 과제인 ft_irc에서 요구하는 사항들을 바탕으로 만들어졌습니다.
> IRC 정의
: `IRC(Internet Relay Chat)`는 **인터넷 기반 실시간 텍스트 통신 프로토콜**로, 사용자들이 채팅방(채널)을 통해 대화를 나누거나 1:1 개인 메시지를 보낼 수 있게 해주는 시스템입니다.

- 참조 클라이언트: [irssi](https://irssi.org/)
- 참조 서버: [inspircd](https://www.inspircd.org/), [libera server](https://libera.chat/)


<br/>

### 프로젝트 요구 사항

- 본 과제는 C++ 98로 IRC 서버를 만들어야 합니다.
- 서버간 통신과 클라이언트는 구현하지 않아도 됩니다.
- 프로그램을 실행하기 위한 코드는 다음과 같습니다.  `./ircserv <port> <password>`
- 해당 서버는 동시에 여러 클라이언트와 통신이 되어야 합니다.
- 모든 입출력은 논블럭으로 처리되어야 합니다.
- 오직 하나의 `poll()` (또는 동등한 것)을 사용하여야 합니다.
- 해당 서버가 제공해야하는 기능들
    - 인증과정, 닉네임과 유저네임 변경, 채널 입장,  개인 메세지를 주고 받는 기능
    - 채널에 속해 있는 모든 클라이언트에게 메세지를 보내는 기능
    - 구현해야할 명령어
        - KICK
        - INVITE
        - TOPIC
        - MODE
            - MODE 명령어는 i, t, k, o, l 옵션을 받을 수 있어야 합니다.
         
  <br/>

## 🛠️ 프로젝트 구조도

### ▫️ 서버 구조
> jjjcs_irc의 소켓 연결은 서버의 시스템 콜 함수인 socket(), bind(), listen(), accept()를 사용하여 클라이언트와 연결합니다.
<br/>사용된 멀티플렉싱 기법은 kqueue입니다.
읽기 이벤트는 클라이언트가 접속함과 동시에 해당 클라이언트의 읽기 이벤트가 kqueue에 등록이 됩니다.<br/>
쓰기 이벤트는 특정 클라이언트의 쓰기 버퍼가 채워지면, 해당 클라이언트의 쓰기 이벤트가 kqueue에 등록이 되고, write()를 실행함과 동시에 쓰기 버퍼를 초기화 시켜 줍니다.

<img src="https://github.com/user-attachments/assets/66ba7b82-a44c-47df-b4bb-438452391f9b" alt="IRC 서버 구조" width="500"/>

 ### ▫️ 채널과 클라이언트
> IRC 상용 클라이언트가 IRC 서버에 연결되면, 서버는 ClientManager를 통해 Client 객체 정보를, ChannelManager를 통해 Channel 객체 정보를 관리하며, 클라이언트와 채널 간의 연결 및 상호작용을 중재합니다.
<img width="600" alt="irc (1)" src="https://github.com/user-attachments/assets/5ad8afe7-daa1-4f15-9901-4997fa110607" />

 ### ▫️ 커맨드 실행 구조
> IRC 서버는 수신한 커맨드를 검증한 후 각 커맨드 타입에 맞는 처리 과정을 거쳐 실행합니다.

<img width="600" alt="irc (1)" src="https://github.com/user-attachments/assets/0bfb7010-3293-44fd-8745-4ee30ecebc4a" />

## ✅ 구현한 명령어 
| 명령어 | 설명 |
| --- | --- |
| PASS | `PASS` 명령은 '연결 비밀번호'를 설정하는 데 사용됩니다. 비밀번호가 설정된 경우, 연결 등록 시도 전에 설정되어야 합니다. |
| NICK | `NICK` 명령은 클라이언트에게 닉네임을 지정하거나 기존 닉네임을 변경하는 데 사용됩니다. |
| USER | `USER` 명령은 새 사용자의 사용자 이름과 실제 이름을 지정하기 위해 연결 초기 단계에서 사용됩니다. |
| JOIN | `JOIN` 명령은 클라이언트가 지정된 채널에 참가하고자 할 때 사용됩니다. |
| PRIVMSG | `PRIVMSG` 명령은 사용자 간에 개인 메시지를 전송하거나 채널에 메시지를 전송하는 데 사용됩니다. |
| MODE | `MODE` 명령은 채널의 모드를 설정하거나 제거하는 데 사용됩니다. 모드 추가는 `+`로, 제거는 `-`로 표시합니다.<br> **채널 모드 설명:**<br> - `i` (Invite-only): 초대받은 사용자만 채널에 참가할 수 있습니다.<br> - `t` (Topic-protected): 채널의 주제는 오퍼레이터만 변경할 수 있습니다.<br> - `k` (Key-protected): 참가하려면 특정 키(비밀번호)가 필요합니다.<br> - `o` (Operator): 채널 오퍼레이터 권한을 부여하거나 제거합니다.<br> - `l` (Limit): 채널의 최대 참가자 수를 제한합니다. |
| INVITE | `INVITE` 명령은 사용자를 채널에 초대하는 데 사용됩니다. |
| TOPIC | `TOPIC` 명령은 특정 채널의 주제를 변경하거나 조회하는 데 사용됩니다. |
| KICK | `KICK` 명령은 특정 사용자를 강제로 채널에서 제거하도록 요청할 때 사용됩니다. |
| PART | `PART` 명령은 클라이언트를 지정된 채널에서 나가게 하는 데 사용됩니다. |
| PONG | `PONG` 명령은 클라이언트의 `PING` 요청에 대한 응답으로 사용됩니다.|

<br/>

## 🏃🏻‍♂️ 실행하기

해당 레파지토리를 clone하기

```
git clone //github.com/jjjcs-IRC/42_Internet_Relay_Chat.git
```

src 폴더 들어가기

```
cd src
```

Makefile 실행하기

```
make
```

ircserv 실행하기

```
./ircserv <port> <password>
```
irssi 클라이언트로 로컬 irc서버 접속하기

```
irssi
/connect -nocap localhost <port> <password>
```

nc 로컬 irc서버 접속하기
```
nc -c 127.0.0.1 <port> <password>
```
```
PASS <password>
NICK <nickname>
USER <username> 0 * <realname>
```
&nbsp;


## 📚 참고자료

- [RFC 1459 - Internet Relay Chat Protocol](https://datatracker.ietf.org/doc/html/rfc1459)
- [RFC 2812 - Internet Relay Chat: Client Protocol](https://datatracker.ietf.org/doc/html/rfc2812)
- https://modern.ircdocs.horse/
- https://1d1cblog.tistory.com/319
- https://80000coding.oopy.io/a8507af9-f9f7-4f50-b3a2-26bff492c8c6#a8507af9-f9f7-4f50-b3a2-26bff492c8c6
- https://medium.com/@afatir.ahmedfatir/small-irc-server-ft-irc-42-network-7cee848de6f9
- https://jiiiiind.github.io/42Seoul/5Circle/ft_irc/
- [https://velog.io/@sihkang/IRC서버-메시지-처리](https://velog.io/@sihkang/IRC%EC%84%9C%EB%B2%84-%EB%A9%94%EC%8B%9C%EC%A7%80-%EC%B2%98%EB%A6%AC)
- [https://velog.io/@rockaria/ftirc-3.-IRC-프로토콜](https://velog.io/@rockaria/ftirc-3.-IRC-%ED%94%84%EB%A1%9C%ED%86%A0%EC%BD%9C)
- https://80000coding.oopy.io/48994d58-5d68-4639-9982-e7d31c61e66f#48994d58-5d68-4639-9982-e7d31c61e66f
- [https://velog.io/@jen133/Ftirc-irc-커맨드](https://velog.io/@jen133/Ftirc-irc-%EC%BB%A4%EB%A7%A8%EB%93%9C)
