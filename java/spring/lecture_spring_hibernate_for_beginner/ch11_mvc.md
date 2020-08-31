### Spring MVC
- MVC 방식으로 웹 서비스를 구성할 수 있으며, 결국 이들은 beans들을 조합한 결과이다.
![spring_mvc](../../../images/spring_mvc.png)
- front controller는 DispatcherServlet이라고도 알려져있다. Spring Framework의 일부이다.
- 개발자가 개발해야할 것은 Model, View templates, Controller classes이다. (오렌지, 옐로우, 그린)
- view는 JSP로 개발할 수도 있고, 다른 스택들로 개발할 수도 있다.
- controller가 business logic을 담는 부분이다. 요청을 처리하고, 데이터를 저장하거나 읽어온다.
- model은 데이터를 담고 있다. view template로 전달되어진다.
- view template으로 가장 일반적으로 쓰이는 것은 JSP와 JSTL이다. 모델에 담겨진 데이터를 가지고 html을 만들어 사용자에게 보여준다.

### Spring MVC 개발 프로세스
- configuration file 추가 (WEB-INF/web.xml)
  - Spring MVC Dispatcher Servlet 설정
  - Spring MVC Dispatcher Servlet에 URL 맵핑 설정
- Web-INF/spring-mvc-demo-servlet.xml 파일 추가
  - component scanning 설정
  - conversion, formatting, validation 설정
  - resolver 추가

### Spring MVC 개발환경 셋팅
- eclipse에서 perspective를 Java EE로 바꿔준 뒤, New -> Dynamic Web Application을 생성
- WebContent > WEB-INF > lib 아래에 Spring JAR 파일을 넣어준다.
- WebContent > WEB-INF 아래에 web.xml과 spring-mvc-demo-servlet.xml을 생성해준다.

### Controller 작성 과정
1. Controller class 작성
2. Controller method 작성
3. Controller method에 Request Mapping 추가
4. View Name 리턴
5. View Page 개발

### Controller Class 작성
```
@Controller
public class HomeController {
  @RequestMapping("/")
  public String showMyPage() {
    // 여기서 view 이름을 리턴하면 스프링은 자동으로 /WEB-INF/view/main-menu.jsp를 찾는다.
    return "main-menu";
  }
}
```
