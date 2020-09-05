### Form Tags and Data Binding
- jsp 파일 내에서 일반 html 태그 사이에 Spring MVC 태그를 끼워넣을 수 있다.
```
<%@ taglib prefix="form" uri="http://www.springframwork.org/tags/form" %>
```

### Text Field
- model을 사용해서 데이터를 집어넣고, data binding을 사용한다.
```
@RequestMapping("/showForm")
pbulic String showForm(Model theModel) {
  theModel.addAttribute("student", new Student());
  return "student-form";
}
```
```
<form:form action="processForm" modelAttribute="student">
  First name: <form:input path="firstName" />
  <br><br>
  Last name: <form:input path="LastName" />
  <br><br>
  <input type="submit" value="Submit" />
</form:form>
```
- 이제 이 form을 통해서 입력된 정보들은 student라는 모델에 매핑된다.
- 그리고 path로 지정한 경로를 메서드 명으로 써서 데이터를 읽어올 수 있다.
- getter가 있으면 setter도 있다. 
```
student.getFirstName();
student.setFirstName();
student.getLastName();
student.setLastName();
```
- Controller 측에서는 @ModelAttribute 태그를 이용해서 데이터 바인딩을 사용할 수 있다.
```
@RequestMapping("/processForm")
public String processForm(@ModelAttribute("student") Student theStudent) {
  System.out.println("theStudent: ", theStudent.getLastName());
  return "student-confirmation";
}
```

### model attribute
- 먼저 form을 보여주는 컨트롤러 측에서 model.addAttribute로 객체를 모델의 attribute로 넣어줘야 한다.
```
@RequestMapping("/showForm")
public String showForm(Model theModel) {
  Student theStudent = new Student();
  theModel.addAttribute("student", theStudent);
  return "student-form";
}
```
- form jsp 상에서는 modelAttribute를 적어놓고 값을 입력해서 전송하면, 컨트롤러 쪽에서 자동으로 데이터가 바인딩이 된다.
```
<form:form action="processForm" modelAttribute="student">
  First name: <form:input path="firstName" />
  <br><br>
  Last name: <form:input path="lastName" />
  <br><br>
  <input type="submit" value="Submit" />
</form:form>
```
- form 결과를 수신하는 컨느롤러 측에서는 @ModelAttribute를 이용해서 곧바로 데이터를 읽어올 수 있다.
```
@RequestMapping("/processForm")
public String processForm(@ModelAttribute("student") Student theStudent) {
  System.out.println("the Student: " + theStudent.getFirstName()+ " " + theStudent.getLastName());
  return "student-confirmation";
}
```
- form 결과를 렌더링하는 jsp는 다음과 같이 $ 기호를 통해서 모델에 접근해서 데이터를 읽어온다.
```
The student is confirmed: ${student.firstName} ${student.lastName}
```

### Dropdown
- Spring form tag를 사용해서 select문을 구현할 수 있다.
- 이 때 주의할 점은 모델 클래스에 필드 값을 추가하고 getter와 setter 함수도 추가해 놓아야 한다.
```
<form:select path="country">
  <form:option value="Brazil" label="Brazil" />
  <form:option value="France" label="France" />
  <form:option value="Germany" label="Germany" />
  <form:option value="India" label="India" />
</form:select>
```

- select에 사용할 option 값을 LinkedhashMap에 미리 자바 코드로 정의한 다음, 전달할 수도 있다. 
```
private LinkedHashMap<String, String> countryOptions;
public Student() {
  countryOptions = new LinkedHashMap<>();
  countryOptions.put("BR", "Brazil");
  countryOptions.put("FR", "France");
  countryOptions.put("GE", "Germany");
  countryOptions.put("IN", "India");
}
```
```
<form:select path="country">
  <form:options items="${student.coutryOptions}" />
</form:select>
```

### Radiobutton
```
Java <form:radiobutton path="favoriteLanguage" value="Java" />
C# <form:radiobutton path="favoriteLanguage" value="C#" />
PHP <form:radiobutton path="favoriteLanguage" value="PHP" />
Ruby <form:radiobutton path="favoriteLanguage" value="Ruby" />
```

### Checkbox
- radiobox와 사용법은 거의 동일하다.
- 그러나 차이점은 checkbox의 경우 여러개의 선택지를 고를 수 있다는 것이다. 때문에 모델에 해당 필드의 데이터 타입을 String Array로 만들어줘야 한다.
```
Linux <form:checkobx path="operatingSystems" value="Linux" />
Mac <form:checkobx path="operatingSystems" value="Mac" />
Windows <form:checkobx path="operatingSystems" value="Windows" />	
```
- 그리고 confirmation 페이지에서 배열 형태의 변수를 렌더링 하기 위해서는 아래와 같이 코딩을 해야한다.
```
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>
Operating Systems:
<ul>
  <c:forEach var="temp" items="${student.operatingSystems}">
    <li> ${temp} </li>
  </c:forEach>
</ul>
```
