### 동기화 객체 사용
- go 언어는 체널 이외에도 고루틴의 실행 흐름을 제어하는 동기화 객체를 제공
- Mutex: 여러 고루틴에서 공유되는 데이터를 보호할 때 사용
- RWMutex: 읽기 쓰기 동작을 나누어서 락을 걸 수 있음
- Cond: 대기하고 있는 객체를 깨울수도 있고, 동시에 여러개를 꺠울 수도 있음
- Once: 특정 함수를 딱 한번 실행할 때 사용
- Pool: 멀티 스레드에서 사용할 수 있는 객체 풀, 자주 사용하는 객체를 풀에 보관했다가 사용이 가능
- WaitGroup: 고루틴이 모두 끝날 때까지 기다리는 기능
- Atomic: 더 이상 쪼갤 수 없는 연산, 안전하게 값을 연산하는 기능

### 뮤텍스 사용하기
```
var data = []int{}
go func() {
  for i:=0; i<1000; i++ {
    mutex.Lock()
    data = append(data, 1)
    mutex.Unlock()
    runtime.Gosched()
  }
}
go func() {
  for i:=0; i<1000; i++ {
    mutex.Lock()
    data = append(data, 1)
    mutex.Unlock()
    runtime.Gosched()
  }
}
```

### RWMutex 사용하기
```
var data int = 0
go func() {
  for i:=0; i<3; i++ {
    rwMutex.Lock()
    data += 1
    fmt.Println("write: ", data)
    rwMutex.Unlock()
  }
}()

go func() {
  for i:=0; i<3; i++ {
    rwMutex.RLock()
    fmt.Println("read 1: ", data)
    rwMutex.RUnlock()
  }
}()

go func() {
  for i:=0; i<3; i++ {
    rwMutex.RLock()
    fmt.Println("read 2: ", data)
    rwMutex.RUnlock()
  }
}()
```

### Cond 사용하기
- Wait: 고루틴 실행을 멈추고 대기를
- Signal: 대기하고 있는 고루틴 하나만 깨움
- Broadcast: 대기하고 있는 모든 고루틴을 깨움
```
func main() {
  var mutex = new(sync.Mutex)
  var cond = sync.NewCond(mutex)
  c := make(chan bool, 3)
  for i:= 0; i<3; i++ {
    go func (n int) {
      mutex.Lock()
      c <- true
      fmt.Println("wait begin: ", n)
      cond.Wait()
      fmt.Println("wait end: ", n)
      mutex.Unlock()
    } 
  }

  for i:=0; i<3; i++ {
    <-c
  }

  for i:=0; i<3; i++ {
    mutex.Lock()
    fmt.Println("signal: ", i)
    cond.Signal()
    mutex.Unlock()
  }
  fmt.Scanln()
}
```
- cond.Signal()로 wait 중인 3개의 고루틴 가운데 하나만 깨움
- cond.Broadcast()를 사용하면 3개의 고루틴 모두 깨움

### Once, Pool
- 여러 고루틴이 특정 함수를 호출 할 때 Once를 사용하면 한번만 호출할 수 있음
- 풀 이란 객체를 사용한 후 보과해두었다가 다시 사용할 수 있게 해주는 기능

### WaitGroup
```
func main() {
  wg := new(sync.WaitGroup)
  for i:=0; i<10; i++ {
    wg.Add(1)
    go func(n int) {
      fmt.Println(n)
      wg.Done()
    }(i)
  }
  wg.Wait()
}
```
- wg를 생성하고 wg.Add(1)로 고루틴의 개수를 늘려줌
- 고루틴이 모든 작업을 마치면 wg.Done()을 호출하여 개수를 줄여줌
- defer wg.Done()을 이용하여 호출도 가능

### Atomic 사용하기
- 서로 영향을 받지 않고 안전하게 연산이 가능
- 별다른 동기화 객체 사용하지 않고 atomic.AddInt32(&data, 1) 같은 문법으로 적용 가능
