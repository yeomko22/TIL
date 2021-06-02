## 2. ROS Filesystem
### concept
- package: 라이브러리, 실행 파일, 스크립트 등을 묶어놓은 ROS 코드 집합
- Manifasts(packages.xml): 패키지에 대한 설명


### 주요 명령어
```
// 패키지 위치 출력
$ rospack find [package name]

// 패키지 위치로 곧바로 이동
$ roscd [package name] 

// ROS log가 저장되는 위치로 바로 이동
$ roscd log

// 특정 패키지 내 파일 목록 조회
$ rosls [package name]

```

## 3. Creating Package
- catkin 패키지로 여겨지려면 아래 조건을 충족해야함
    - package.xml 포함할 것
    - catkin을 사용하는 CMakeLists.txt을 포함할 것
- catkin package는 catkin_workspace 안에서 사용할 것을 권장
~~~
workspace
    src/
        CMakeLists.txt
        package_1/
            CMakeLists.txt
            package.xml
        ...
        package_n/
            CMakeLists.txt
            package.xml
~~~
~~~
$ catkin_create_pkg [패키지명] [의존 패키지 1] [의존 패키지 2] ...
$ cd ~/catkin_ws
$ catkin_make

// ros package 직접 의존성 확인
$ rospack depends1 [package name]

// ros package 전체 의존성 확인
$ rospack depend [package name]
~~~

