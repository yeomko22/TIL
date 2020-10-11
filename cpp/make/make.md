### make 파일 기본 사용법
- 참고 자료: https://bowbowbow.tistory.com/12
```
1 CC = g++
2 CFLAGS = -std=c++14
3 TARGET = diary_exe
4 OBJECTS = memo.o main.o calendar.o
5
7 $(TARGET): $(OBJECTS)
8     $(CC) $(CFLAGS) -o $@ $^
9
10 clean:
11     rm *.o diary_exe
```

### cmake란?
- 플랫폼에 독립적으로 플랫폼 종속적인 native makefile을 생성할 수 있는 빌드 도구
- makefile을 만들어주는 도구를 cmake라고 보면 된다.
- 직접 makefile을 작성해서 관리하지 않는다. 이 cmake를 통해서 makefile을 만들어 관리하는 것이다.
