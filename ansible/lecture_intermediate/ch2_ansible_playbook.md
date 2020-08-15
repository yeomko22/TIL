### Ansible playbook 작성
- tasks라는 필드 아래에 작업들에 대한 명세를 코딩한다.
- yum 명령어를 사용하면 필요한 패키지를 패키지 매니저를 통해서 설치할 수 있다.
```
    - name: Install git
      yum:
        name: git
        state: present
```
- shell 명령어를 통해 커맨드를 실행할 수 있으며, curl과 함께 사용하여 인터넷 상에서 파일을 다운로드 할 수 있다.
```
- name: Download pathogen.vim
      shell: "curl -fLo ~/.vim/autoload/pathogen.vim https://tpo.pe/pathogen.vim"
```
- git 명령어를 사용하면 원격 저장소에서 코드를 받아올 수 있다.
```
    - name: Git clone vim-ansible-yaml
      git:
        repo: 'https://github.com/chase/vim-ansible-yaml'
        dest: /home/vagrant/.vim/bundle/vim-ansible-yaml
```
- lineinfile 명령어를 사용하면 파일 안에 라인을 추가할 수 있다.
```
    - name: Configure vimrc
      lineinfile:
        dest: /home/vagrant/.vimrc
        line: "{{ item }}"
      with_items:
        - "set number"
        - "execute pathogen#infect()"
        - "syntax on"
```

### vagrant provision
- 현재 동작 중인 가상머신에 새롭게 변경된 vagrantfile을 적용하고 싶을 때 아래 명령어를 사용한다.
```bash
$ vagrant provision <호스트 명> 
```

### 앤서블 노드 추가하기
- vagrantfile을 수정하여 노드 2개를 더해줄 것
- add_ssh_auth.sh로 ssh 키를 생성해주는 것까지 자동화시킬 것
- playbook에서는 host들을 등록해주어야 하며, sshpass 패키지도 설치해야함
