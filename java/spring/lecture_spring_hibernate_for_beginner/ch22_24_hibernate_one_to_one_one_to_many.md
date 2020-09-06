### Hibernate Advanced
- one to one
- one to many, many to one
- many to many
- 이러한 관계들도 hibernate로 mapping할 수 있다.

### Database Concepts
- foreign key, cascade
- Eager loading, lazy loading. lazy는 데이터가 필요한 시점에서야 읽어오는 것
- uni directional, bi directional

### Hibernate One to One mapping
- instructor - instructor detail
- one to one, unidirectional
- 각각의 테이블을 만든 뒤, Foreign key로 사용할 필드를 annotation을 통해 알려준다.
```
@Entity
@Table(name="instructor")
public class Instructor {
  @OneToOne(cascade=CascadeType.ALL)
  @JoinColumn(name="instructor_detail_id")
  private InstructorDetail instructorDetail
}
// 뿌야!
```
- 그러니까, 참조하는 엔티티에서 @OneToOne, @JoinColumn 태그를 이용해서 참조되는 측의 필드 값을 가리키면 된다.
- cascade를 따로 설정안하면 어떠한 operation도 cascade되어 적용되지 않는다.
```
// create the object
Instructor tempInstructor = new Instructor("Chand", "Darby", "darby@lub2code.com");
InstructorDetail tempInstructorDetail = 
    new InstructorDetail(
        "http://www.luv2code.com/youtube",
        "Luv 2 code !!!");
// associate the objects
tempInstructor.setInstructorDetail(tempInstructorDetail);

// start a transaction
session.beginTransaction();
session.save(tempInstructor);

// end a transaction
session.getTransaction().commit();
```
- 먼저 참조하는 객체와 참조되는 객체를 만들어 준 다음, setter 메서드를 이용해서 연결해준다.
- 그 다음 참조하는 객체만 save를 해주면 참조되는 객체도 cascade가 적용되어서 함께 저장이 되는 것을 확인할 수 있다.
- 마찬가지로 참조하는 객체를 지우면 cascade가 적용되어 참조되는 객체도 지워진다.

### Bi-directional relationship
- 참조되는 객체에서 역으로 @OneToOne을 지정하고 참고하는 객체를 엮어주면 된다.
```
@OneToOne(mappedBy="instructorDetail", cascade=CascadeType.ALL)
private Instructor instructor;
```
- @OneToOne 안에 원래 참조하는 객체에서 참조를 위해 사용하는 필드명을 넣어주어야만 한다.
- 이렇게 엮어주면 cascade를 양방향으로 적용할 수 있다.
- 만일 delete cascade를 적용하기 싫다면 cascade type에서 remove를 제외하고 설정해주면 된다.

### code refactoring
```
try {
  // start a transaction
  session.beginTransaction();
  int theId = 3;
  InstructorDetail theInsturctorDetail = 
      session.get(InstructorDetail.class, theId);
  System.out.println(theInsturctorDetail);
  System.out.println(theInsturctorDetail.getInstructor());
  // end a transaction
  session.getTransaction().commit();
} 
catch (Exception exc) {
  exc.printStackTrace();
} 
finally {
  session.close();
  factory.close();
}
```
- catch에서는 null pointer exception을 잡아낸다.
- finally에서는 factory와 session을 닫아주어 memory leak을 방지한다.

### One to many
- one to many 관계에서 cascade delete는 조심스럽게 구현해야한다.
```
@Entity
@Table(name="instructor")
public class instructor {
  @OneToMany(mappedBy="instructor", 
             casacde={CascadeType.PERSIST, CascadeType.MERGE, 
                      CascadeType.DETACH, CascadeType.REFRESH})
  private List<Course> courses;
}
```
- One에 해당하는 Entity에서는 one to many로 foreign key로 지정할 필드 값을 명시한다. 
- 즉, Course Entity는 instructor라는 필드 값으로 instructor를 참조한다.
```
@Entity
@Table(name="Course")
public class Course {
  @ManyToOne(casacde={CascadeType.PERSIST, CascadeType.MERGE, 
                      CascadeType.DETACH, CascadeType.REFRESH})
  @JoinColumn(name="instructor_id")
  private Instructor instructor;
}
```
- Many에 해당하는 Entity에서는 ManyToOne 태그와 JoinColumn으로 참조할 대상의 필드 값을 명시

```
public class Instructor {
  public void add(Course tempCourse) {
    if (courses == null) {
      courses = new ArrayList<>();
    }
    courses.add(tempCourse);
    tempCourse.setInstructor(this);
  }
}
```
- bi-directional link를 걸어주어야 한다.
- 새로운 course를 추가할 때, 반드시 tempCourse.setInstructor 함수를 통해서 참조 관계를 걸어주어야 한다.
```
session.beginTransaction();
int theId = 1;
Instructor tmpInstructor = session.get(Instructor.class, theId);
Course tempCourse1 = new Course("Air Guitar - The Ultimate Guide");
Course tempCourse2 = new Course("Pinball Masterclass");

tmpInstructor.add(tempCourse1);
tmpInstructor.add(tempCourse2);

session.save(tempCourse1);
session.save(tempCourse2);

// end a transaction
session.getTransaction().commit();
```
- 여기서 주목해야할 라인은 tmpInstructor.add(tempCourse1)과 그 아랫 라인이다.
- 참조하는 대상에 Course를 추가해주는 add 함수를 호출한다. add 함수는 그 안에서 다시 Course 객체의 setInstructor 함수를 호출한다.
- 이를 통해서 두 객체 간의 bi-directional한 관계를 형성해 줄 수 있으며, 해당 키 값을 자동으로 저장한다.
