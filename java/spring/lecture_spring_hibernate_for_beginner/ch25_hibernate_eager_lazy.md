### Eager vs Lazy
- Eager: 요청이 왔을 때, 모든 데이터를 읽어온다. 즉, foreign key로 걸려있는 데이터도 모두 디비에서 읽어옴
- Lazy: 요청이 올 때까지 데이터를 읽어오는 것을 미룬다.
- Eager Loading은 성능 저하의 원인이 될 수 있다. 떄문에 Lazy loading을 사용해야 한다.
```
@OneToMany(fetch=FetchType.LAZY, mappedBy="instructor")
private List<Course> courses;
```

### Default Fetch Types
- @OneToOne: Eager
- @OneToMany: Lazy
- @ManyToOne: Eager
- @ManyToMany: Lazy

### Lazy Loading
- 필요한 시점에 데이터를 읽어오지만 그러기 위해서는 hibernate session이 필요하다.
- 따라서 lazy loading을 위한 패턴을 사용해야한다.

### Eager Fetching
```
int theId = 1;
Instructor tmepInstructor = session.get(Instructor.class, theId);
System.out.println("luv2code: Instructor: " + tmepInstructor);
System.out.println("luv2code: Courses: " + tmepInstructor.getCourses());
```
- Eager 모드로 실행하면 처음부터 instructor와 courses를 모두 읽어온다.
- Lazy 모드로 실행하면 getCourse 함수를 실행하는 시점에 courses를 읽어온다.

### Resolv lazy fetching exception
- 세션이 살아있을 때, 변수에 한번 접근해서 읽어오면 세션이 닫히고 나서 데이터를 읽어올 떄 발생하는 예외를 예방할 수 있다.

### HQL로 데이터 읽어오기
```
Query<Instructor> query = 
					session.createQuery("select i from Instructor i "
								+ "JOIN FETCH i.courses "
								+ "where i.id=:theInstructorId", 
							Instructor.class);
query.setParameter("theInstructorId", theId);
Instructor tempInstructor = query.getSingleResult();
System.out.println("luv2code: Instructor: " + tempInstructor);
```
- JOIN FETCH를 하면 EAGER loading 처럼 한꺼번에 참조하는 객체까지 읽어온다.
- 그냥 select from where로 HQL을 작성하면 lazy loading이 된다.

### One To Many Uni Directional
- course 하나에 여려 리뷰가 달려있는 상황
- course가 지워지면 자연스레 리뷰도 지워져야 한다.
- 그러므로 delete cascade를 지원해야한다.

### Many to Many
- course에 여러 학생들이 등록할 수 있고, 또 학생 한명이 여러 course를 수강할 수 있는 상황
- 이럴 때는 중간에 Join Table이라는 것을 두어 관리한다.
- 각 테이블에대한 foreign key들을 가지며 mapping 관계를 정의한다.
- 즉, course id와 student id를 매핑해서 가지고 있는 별도의 테이블을 만들어주면 된다.

### Join Table
```
@Entity
@Table(name="course")
public class Course {
  @ManyToMany
  @JoinTable(
    name="course_student",
    joinColumns=@JoinColumn(name="course_id"),
    inverseJoinColumns=@JoinColumn(name="student_id")
  )
  private List<Student> students;
}

@Entity
@Table(name="student")
public class Student {
  @ManyToMany
  @JoinTable(
    name="course_student",
    joinColumns=@JoinColumn(name="student_id"),
    inverseJoinColumns=@JoinColumn(name="course_id")
  )
  private List<Course> courses;
}
```
- 그리고 이러한 양방향 Many to Many 관계에서는 delete cascade를 적용하면 안된다.
- 이렇게 두 엔티티 클래스에 관계만 설정해주면 JoinTable에 둘 사이 레코드 매핑을 나타내는 레코드가 자동으로 저장된다.
