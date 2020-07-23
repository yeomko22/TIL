### 고루틴 사용하기
- 함수를 동시에 실행시키는 기능
- 다른 언어의 쓰레드 생성 방법보다 문법이 간단, 스레드보다 리소스를 적게 사용하여 많은 수의 고루틴을 쉽게 생성이 가능
```
func hello(n int) {
  r := rand.Intn(100)
  fmt.Println(n)
}

func main() {
  for i:=0; i<100; i++ {
    go hello()
  }
  fmt.Scanln()
}
```
- go언어는 기본적으로 CPU 코어 1개를 사용, 멀티 코어를 사용하고 싶다면 아래 명령어를 통해 설정 가능
```
runtime.GOMAXPROCS(runtime.NumCPU())
```

### 클로저를 고루틴으로 실행하기
```
func main() {
  s := "Hello World"
  for i:=0; i<100; i++ {
    go func(n int) {
      fmt.Println (n, s)
    }(i)
  }
}
```

### 체널 사용하기
- 체널은 고루틴끼리 데이터를 주고 받고 실행 흐름을 제어하는 기능
- 체널 자체는 값이 아닌 레퍼런스
```
func sum(a, b, c chan int) {
  c <- a + b
}

func main() {
  c := make(chan int)
  go sum(1, 2, c)
  n := <-c
  fmt.Println(n)
}
```
- 체널을 매개변수로 받는 함수는 반드시 go 키워드를 사용하여 고루틴으로 실행해야 함
- c<- (체널에 값을 입력)
- <-c (체널에 들어있는 값을 꺼냄)
- <-c는 체널에 값이 들어올 때까지 대기, 갑싱 들어오면 대기를 끝내고 다음 코드를 시랳ㅇ함
- 따라서 체널은 값을 주고 받는 동시에 동기화 역할까지 수행한다.

### 동기 체널
```
func main() {
  done := make(chan bool)
  count := 3
  
  go func() {
    for i:=0; i< count; i++ {
      done <- true
      fmt.Println("고루틴: ", i)
    }
  }()

  for i:=0; i<count; i++ {
    <-done
    fmt.Println("메인 함수: ", i)
  }
}
```
- make 함수에 자료형만 전달시에는 동기 체널을 생성함
- 동기 체널의 경우 체널에 값을 입력한 경우 해당 값을 꺼내갈 때까지 대기한다.

### 채널 버퍼링
- 버퍼가 가득 차면 값을 꺼내 출력
- 위 소스 코드에서 make(chan bool, 2)와 같이 버퍼 사이즈를 넣어주어 생성
- 비동기 체널이므로 버퍼가 가득 찰 때까지 값을 보냄
- 받는 쪽에서는 버퍼에 값이 없을 경우 대기

### range / close
```
func main() {
  c := make(chan int)
  go func() {
    for i:=0; i<5; i++ {
      c <- i
    }
    close(c)
  }
  for i:= range c {
    fmt.Println(i)
  }
}
```
- range 키워드를 사용하면 체널이 닫힐 때까지 반복하면서 값을 꺼냄
- 체널에 값을 보내는 고루틴은 값을 모두 보낸 이후에는 close 함수로 체널을 닫아줌
- 이미 닫힌 체널에 값을 보내면 패닉이 발생
- 체널을 닫으면 range 루프 종료
- 체널이 열려있고 값이 들어오지 않으면 range는 실행되지 않고 무한히 대기
- 체널에서 값을 꺼낼 때 열려있는지 닫혀있는지 확인이 가능
```
a, ok <- c
```

### 보내기 전용 및 받기 전용 체널
- 함수의 매개변수, 리턴 값 설정 시에 체널을 보내기 전용, 받기 전용으로 설정이 가능
```
func num(a, b int) <-chan int {
  out := make(chan int)
  go func() {
    out <- a
    out <- b
    close(out)
  }()
  return out
}

func sum(c<-chan int) <-chan int {
  out := make(chan int)
  go func() {
    r := 0
    for i:=range c {
      r = r + i
    }
    out <- r
  }()
  return out
}

func main() {
  c := num(1, 2)
  out := sum(c)
  fmt.Println(<-out)
}
```

### 셀렉트 사용
```
select {
  case <- 체널 1:
  // 체널 1에 값이 들어왔을 때 실행할 코드
  case <- 체널 2:
  // 체널 2에 값이 들어왔을 때 실행할 코드
}
```
