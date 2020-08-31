### Annotation이란?
- metadata를 추가해주는 역할을 수행
- @Override와 같이 앞에 골뱅이가 붙은 것을 annotation이라 부른다.
- compile 타임에서 annotation을 검사한다.
- Spring 설정을 annotation을 통해 수행 가능하다.
- xml을 사용할 경우, 프로젝트의 규모가 커질 수록 xml 파일 자체를 감당할 수 없다.
- annotation을 사용해서 xml configuration을 최소화할 수 있다.

### Spring Annotation
- Spring이 java class들을 스캔해서 annotation들을 인식한다.
- 자동으로 Spring Container에 bean들을 등록해준다.

### Annotation을 이용한 개발 과정
- Spring config file에서 component scanning을 enable한다.
- @Component annotation을 java class들에 추가해준다.
- bean을 가져와서 사용한다.
```
// 시작 지점부터 재귀적으로 java class들을 검사한다.
<context:component-scan base-package="com.lub2code.springdemo" />

// bean id로 쓸 이름을 @Component와 함께 annotation으로 작성해주면 끝
@Component("<bean id>")
public class TennisCoach implemets Coach {...}
```

### Default Component Names
- @Component 태그를 달아줄 때 이름을 전달하지 않으면 기본 이름이 설정된다.
- 기본 이름은 Class 이름의 맨 앞글자를 소문자로 바꿔준 값이다.

### Annotation - Dependency Injection
- auto wiring을 사용하여 annotation으로 의존성 주입을 사용할 수 있다.
- Spring은 Component를 스캔하여 자동으로 주입해준다.
- Constructor Injection, Setter Injection, Field Injection 세 가지 유형이 있다.

### auto-wire 작성 순서
- 의존성을 가진 인터페이스와 클래스를 작성한다.
- 의존성 주입을 위한 클래스 생성자를 작성한다.
- @Autowired annotation을 추가해서 의존성 주입을 설정한다.
```
private FortuneService fortuneService;

@Autowired
public TennisCoach(FortuneService theFortuneService) {
  fortuneService = theFortuneService;
}
```
- 생성자를 만들어주고 @Autowired 어노테이션을 달아준다. Spring file은 건드릴 필요가 없다. 
- Spring이 자동으로 FortuneService를 구현한 bean을 찾아서 연결해준다.
- 원래는 Spring file에서 bean constructor-arg에 FortuneService를 넣어주어야만 했다.
- 만일 해당 인터페이스를 구현한 클래스가 여러개 있다면? Spring은 이러한 상황을 @Qualifier를 통해서 해결하며, 나중에 강의에서 다룸 

### Setter Injection
- 마찬가지로 setter method를 만들어주고 @Autowired 태그를 붙여주면 된다.
```
@Autowired
public void setFortuneService(FortuneService fortuneService) {
  this.fortuneService = fortuneService;
}
```

### Method Injection
- 어떤 메서드라도 @Autowired 태그를 붙여줄 수 있다. 굳이 set 어쩌고 하지 않아도 된다.
- constructor의 경우에는 @Autowired를 생략할 수 있지만, Method Injection 방식에서는 @Autowired 생략하지 말자. 그리고 생성자의 경우에도 @Autowired를 생략하는 방식은 그다지 권장되어지지 않는다.

### Field Injection
- field value를 이용해서 의존성을 주입한다. java reflection을 이용하는 기능이다.
- setter method도 필요없이 곧바로 field에 값을 주입할 수 있다.
```
@Autowired
private FortuneService fortuneService;
```

### which injection type to use?
- constructor injection, setter injection, field injection 가운데 뭘 써야하는가?
- 프로젝트 내에서만 일관성을 유지하면 뭘 쓰던 큰 상관이 없다.

### Qualifier
- @Autowired를 사용하면 Spring은 @Component들 가운데 해당 인터페이스를 구현한 것을 찾는다.
- 만일 인터페이스를 구현한 클래스가 많다면 Qualifier의 도움을 받아야한다.
```
@Autowired
@Qualifier("happyFortuneService")
private FortuneService fortuneService;
```
- Qualifier에 bean id를 전달해줘서 해결이 가능하다.

### properties file injection with annotation
- 먼저 Spring file에서 파일을 읽어온 다음 @Value 태그를 이용하여 환경변수를 사용하듯이 쓰면 된다.
```
<context:property-placeholder location="classpath:sport.properties"/>
@Value("${foo.email}")
private String email;
```
