### Validation
- required values
- valid number in rage
- valid format
- 이러한 유효성 검사를 하기 위해서 Bean Validation API를 사용한다.

### Validation tags
- @NotNull
- @Min, @Max
- @Size
- @Pattern
- @Future / @ Past

### Hibernate
- 원래는 ORM 프로젝트였다. 
- 그러나 최근에는 ORM이나 데이터 베이스에 구속되지 않고 validation 기능도 제공한다.

### Validation 추가하기 
- 먼저 모델로 사용할 class에 validation을 적용할 필드 값 위에 validation 태그를 추가한다.
- validation 태그들은 javax.validation.constraints에 포함된 태그들이다.
```
public class Customer {
  private String firstName;
  @NotNull(message="isrequired")
  @Size(min=1, message="is required")
  private String lastName;
}
```
- 다음으로 jsp로 이동해서 validation이 실패했을 경우를 대비한 html 코드를 추가해준다.
```
<form:errors path="lastName" cssClass="error" />
```
- 컨르롤러로 이동해서 이제 validation과 model을 연결해주어야 한다.
- @Valid를 추가해주는 것이 큰 특징이다.
```
@ReuqestMapping("/processForm")
public Stgring processForm(@Valid @ModelAttribute("customer") Customer theCustomer, BindingResult the BindingResult) {
  if (theBindingResult.hasErrors()) {
    return "customer-form";
  } else {
    return "customer-confirmation";
  }
}
```
- 그런데 그냥 공백을 넣으면 길이 검사 validation을 통과해버린다. 그러므로 validation을 통과하기 이전에 trim을 적용해주어야한다.
- @InitBinder를 통해서 pre-processor를 구현할 수 있다.
```
@InitBinder
public void initBinder(WebDataBinder dataBinder) {
  StirngTrimmerEditor stringTrimmerEditor = new StringTrimmerEditor(true);
  dataBinder.registerCustomEditor(String.class, stringTrimmerEditor);
}
```
- 이렇게 만들어놓으면 모든 form data에 포함된 문자열이 validation 적용하기 이전에 전처리 과정을 거친다.

### Regex 사용해서 validation하기
```
@Pattern(regexp="^[a-zA-Z0-9]{5}", message="only 5 chars/digits")
private String postalCode;
```

### int value를 required 값으로 만들기
- @NotNull 태그를 추가해주면 required 설정을 해줄 수 있다.
- 단, 이 경우 int로 설정하면 타입 에러가 나므로 String 타입과 동적으로 변환이 가능하도록 Integer 타입으로 만들어주고 getter와 setter를 업데이트 해준다.

### Custom Messages
- /src/resources/message.properties라는 파일을 만들고, custom errormessage를 적어준다.
```
typeMismatch.customer.freePasses=Invalid number
```
