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
