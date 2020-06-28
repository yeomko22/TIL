### SSH란?
- Secure Shell의 약자로 암호화 된 네트워크 프로토콜이며 unsecured network 위에서 secured network 접속을 하게 해주는 서비스이다. 어떠한 네트워크 서비스라도 SSH에 의해서 보안을 확보할 수 있다. 주로 원격 접속에 이용된다.
- 클라이언트 서버 구조로 작동한다. 
- SSH는 telnet에 SSL로 암호화를 적용하여 구현한 구현체가 아니다.

### Telnet이란?
- Internet이나 Local area network에서 양방향 인터렉티브 텍스트 커뮤니케이션을 제공하는 어플리케이션 프로토콜이다.
- 이전에 많이 사용되었으나 보안상의 문제로 SSH에 자리를 내주었다.

### Secure Sockets Layer(SSL)이란?
- TLS로도 불렸으나 현재는 SSL로 불리며 암호화 프로토콜이다.
- 네트워크 상의 커뮤니케이션에서 보안을 확보해주는 역할을 수행한다.
- 브라우징, 이메일, 메세징, VoIP 등에서 사용이 가능하다.

### HTTPS란?
- HTTP의 익스텐션으로 TLS 혹은 SSL에 의해서 암호화 된다.
- HTTP over TLS, HTTP over SSL로도 불리운다.
- 중간에 패킷을 낚아채는 공격을 방어한다. 암호화를 적용하여 낚아채가더라도 내용을 해석할 수 없게 한다.

### Reference
- https://opentutorials.org/course/228/4894
