## pvc storage 요구량 확인하기
~~~bahs
$ k get pvc -o custom-columns='name:{.metadata.name},storage:{.spec.resources.requests.storage}' -n kubeflow
~~~
