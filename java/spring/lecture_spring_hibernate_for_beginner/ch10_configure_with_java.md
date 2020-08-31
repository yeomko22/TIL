### Java Configuration
- XML을 사용하는 대신 java 코드를 사용할 수 있다.
- Spring Container를 설정하는 방식으로 3가지가 있다.
  - XML 파일 하나에 다 기재하는 방식
  - XML을 최소화하고 Annotation을 사용, Component Scan을 하는 방식
  - XML 없이 java 코드 상에서 설정을 진행하는 방식

### @Configuration
- 설정을 담당할 클래스를 생성하고 @Configuration 어노테이션을 달아준다.
- @ComponentScan 어노테이션과 함께 패키지 명을 입력해준다.
- AnnotationConfigAplicationContext로 Spring Configuration을 읽어온다.
```
@Configuration
@ComponentScan("com.luv2code.springdemo")
public class SportConfig {...}

// 이전에는 ClassPathXMLApplicationContext를 이용해서 설정을 읽어왔으나,
// 이제 java 코드를 활용하여 설정을 하므로 AnnotationConfigApplicationContext를 사용한다.
AnnotationConfigApplicationContext contexts = new AnnotationConfigApplicationContext(SportConfig.class)
```

### Define Bean with java code
- annotation을 사용하기 이전에 xml 파일에서 bean을 정의할 수 있었다.
- 이제 java 코드가 xml을 대체할 수 있게 되었으니, 마찬가지로 configuration 클래스 안에서 bean을 정의할 수 있게 되었다.
- 이렇게 하면 Component Scan 없이 bean을 생성할 수 있다.
- 다른 bean을 생성자 안에 넣어줌으로써 의존성 주입이 가능하다.
```
@Bean
public FortuneService happyFortuneService() {
  reutnr new HappyFortuneService();
}

@Bean
public Coach swimCoach() {
  SwimCoach mySwimCoach = new SwimCoach(happyFortuneService());
  return mySwimCoach;
}
```

### inject values from files
- properties file을 만들고 java code에서 읽어온다. 
- 마찬가지로 환경 변수를 사용하듯 사용하면 된다.
```
@Configuration
@PropertySource("classpath:sport.properties")
public class SportConfig {...}

// bean class에서 사용
public class SwimCoach implements Coach {
  @Value("${foo.email}")
  private String email;

  @Value("${foo.team}")
  private String team;
}
```

