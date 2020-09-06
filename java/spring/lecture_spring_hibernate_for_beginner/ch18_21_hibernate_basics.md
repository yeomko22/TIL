### Hibernate란?
- 원래는 java object를 DB에 저장하는 역할을 수행하는 ORM이다.
- low level SQL을 처리해준다. 그래서 JDBC 코드를 직접 작성할 필요를 줄여준다.
```
Student theStudent = new Student("John", "Doe", "john@lub2code.com");
int theId = (Integer)session.save(theStudent);
// 방법 1. id로 가져오기
Student myStudent = session.get(Student.class, theId);
// 방법 2. query로 가져오기
Query query =- session.createQuery("from Student");
List<Student> students = query.list();
```
- Query로 가져올 때는 Hibernate Qeury Language라는 언어를 사용한다.
- 이를 활용해서 CRUD를 쉽게 짤 수가 있다.

### Hibernate and JDBC
- Hibernate는 데이터베이스와 통신을 할 때 JDBC를 이용한다.
- 때문에 hibernate를 사용하고자 한다면 JDBC도 설치해주어야 한다.

### Hibernate Configuration file
- Hibernate가 JDBC를 이용하기 위한 설정 값들을 모두 담아놓은 파일이다.
- DB url과 user, password 등이 담겨져 있다.
- 그 외에 connection pool size, sql dialect, session context 등을 설정할 수 있다.

### Hibernate를 쓰기 위한 방법
1. XML config file을 사용하기
2. Java annotation을 사용하기
- java를 사용하는 것이 더 현대적인 방법이다.

### Hibernate annotation
```
@Entity
@Table(name="student")
public class Student {
  @Id
  @Column(name="id")
  private int id;

  @Column(name="first_name")
  private String firstName;
}
```
- Entity로 지정하고 테이블을 만든다.
- 클래스 아래에는 컬럼들을 정의한다.
- primary key와 같은 속성도 annotation으로 정의할 수 있다.

### Hibernate CRUD
- SessionFactory: hibernate config 파일을 읽어서 session 객체를 만들어낸다. app에서 한번만 만드는 무거운 객체이다.
- Session: JDBC connection을 감싼 wrapper이다. 실제로 데이터를 읽어오고 저장하는 역할을 수행한다. 수명이 짧으며, SeesionFactory로 만들어낸다.
```
SessionFactory factory = new Configuration()
                        .configure("hibernate.cfg.xml")
                        .addAnnotatedClass(Student.class)
                        .buildSessionFactory();
Session session = factory.getCurrentSession();

try {
  Student tempStudnet = new Student("Paul", "Wall", "paul@luv2code.com");
  session.beginTransaction();
  session.save(tempStudetn);
  session.getTransaction().commit();
} finally {
  factory.close();
}
```
- transaction을 열고, 쓰기 작업을 수행하고, 커밋을 남기는 기본적인 hibernate 패턴

### Hibernate Primary key
```
@Id
@GeneratedValue(strategy=GenerationType.IDENTITY)
@Column(name="id")
private int id;
```
- generation 방식으로 여러가지가 있고, 그 중 선택할 수 있다.
- IDENTITY, SEQUENCE, TABLE 등이 있으나, IDENTITY를 가장 많이 쓴다.

### CRUD
- Create
```
session.beginTransaction();
session.save(tempStudetn);
session.getTransaction().commit();
```
- Read
```
session.beginTransaction();
Student myStudent = session.get(Student.class, 6);
List<Student> theStudents = session.createQuery("from Student s where s.lastName='Wall'").list();
session.getTransaction().commit();
```
- Update
```
session.beginTransaction();
// 방법 1
Student myStudent = session.get(Student.class, 6)
myStudent.setFirstName("Scooby");

// 방법 2
session.createQuery("update Student set email='foo@gmail.com'").executeUpdate();
session.getTransaction().commit();
```
- Delete
```
session.beginTransaction();
// 방법 1
Student myStudent = session.get(Student.class, 6)
sessino.delete(myStudent);

// 방법 2
session.createQuery("delete from Student where id=6").executeUpdate();
session.getTransaction().commit();
```

### Querying
```
```
- createQuery 다음에 원하는 쿼리를 넣어주면 잘 동작한다.
- Hibernate는 read 작업만 수행할 때에도 트랜젝션을 강제한다.
