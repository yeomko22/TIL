### goroutine 누수 가능성
- go 런타임은 고루틴을 임의의 수의 운영체제 스레드로 다중화(multiplexing)한다.
- 한번 실행된 고루틴이 종료가 되기 위해서는 몇 가지 방법이 있다.
  - 작업이 완료됐을 때
  - 복구할 수 없는 에러로 인해 더 이상 작업을 진행할 수 없을 때
  - 작업을 중단하라는 요청을 받았을 때
- 앞의 두가지 케이스는 별다른 노력 없이 구현 가능하다. 그러나 중간에 작업을 중단하라는 명령을 보내는 것이 어렵다.
- 왜냐면 고루틴들은 파이프라인 등을 통해서 다른 고루틴들과 긴밀하게 연결되어 작업을 수행하기 때문이다.
- 따라서 전체 문맥에 대한 지식을 가진 부모 고루틴(보통은 main 고루틴)이 자식 고루틴에게 종료하라고 말할 수 있어야한다.
```
func memoryLeak() {
	doWork := func(strings <-chan string) <-chan interface{} {
		completed := make(chan interface{})
		go func() {
			defer fmt.Println("doWork exited.")
			defer close(completed)
			for s := range strings {
				fmt.Println(s)
			}
		}()
		return completed
	}
	doWork(nil)
	time.Sleep(5 * time.Second)
	fmt.Println("Done.")
}
```
- 위 코드에서 doWork goroutine에 nil이 전달되었다. 따라서 doWork 함수 내에서 실행되는 고루틴은 아무런 작업을 수행하지 않는다.
- 그렇다면 해당 고루틴이 종료되어야 하는데 종료되지 않고 메인 고루틴이 종료될 때까지 남아있다. doWork exited가 출력되지 않는것으로 이를 알 수 있다.
```
func preventMemoryLeak() {
	doWork := func(done <-chan interface{}, strings <-chan string) <-chan interface{} {
		completed := make(chan interface{})
		go func() {
			defer fmt.Println("doWork exited.")
			defer close(completed)
			for {
				select {
				case s := <-strings:
					fmt.Println(s)
				case <-done:
					return
				}
			}
		}()
		return completed
	}
	done := make(chan interface{})
	completed := doWork(done, nil)

	go func() {
		time.Sleep(1 * time.Second)
		fmt.Println("Canceling doWork goroutine...")
		close(done)
	}()
	<-completed
	fmt.Println("Done.")
}
```
- main 고루틴에서 자식 고루틴을 실행시킬 때 done이라는 체널을 추가하여 전달한다.
- 자식 고루틴은 내부에서 for-select 문을 실행시키며 입력 체널과 done 체널의 입력 값을 읽어온다.
- 부모 고루틴에서 done 체널을 닫아줄 경우, select 문의 <-done 이벤트가 발생하면서 for 루프가 종료되고 고루틴이 종료되게 된다.
- 즉, 부모 고루틴의 입자에서 자식 고루틴의 동작을 멈출 수 있게 되었다.
