# 검색해서 찾은 소스 코드
# 직접 짠 코드는 O(N^2)이라서 퍼포먼스 테스트를 통과 못했음
# 에라토스테네스의 체를 이용해서 O(nlogn)으로 줄였다는데 슈밤 이걸 어떻게 생각해 낼 까 싶다.
def solution(A):
    A_max = max(A)
  
    count = {}
    for element in A:
        if element not in count:
            count[element] = 1
        else:
            count[element] += 1
  
    divisors = {}
    for element in A:
        divisors[element] = set([1, element])
  
    # start the Sieve of Eratosthenes
    divisor = 2
    while divisor*divisor <= A_max:
        element_candidate = divisor
        while element_candidate  <= A_max:
            if element_candidate in divisors and not divisor in divisors[element_candidate]:
                divisors[element_candidate].add(divisor)
                divisors[element_candidate].add(element_candidate//divisor)
            element_candidate += divisor
        divisor += 1
  
    result = [0] * len(A)
    for idx, element in enumerate(A):
        result[idx] = (len(A)-sum([count.get(divisor,0) for divisor in divisors[element]]))
  
    return result
