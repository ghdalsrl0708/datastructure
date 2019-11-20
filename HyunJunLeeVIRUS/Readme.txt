-코드에 대한 간단 설명
-Simple explanation about the code.

0. system을 이용한 정말 간단한 방법 입니다. sysremprocess.c 는.
1. Ps.c 파일은 컴퓨터 내 pid와 프로세스 위치를 알아내어 ps.txt파일에 저장하는 코드입니다.
2. delprocess.c 파일은 pid 값을 입력하면 종료를 하는 코드입니다.
3. execv.c 파일은 처음에 pid 값과 등등을 구할려고 한 Ps.c와 유사하지만 txt파일에 저장은 못합니다. 'ps-al' 의 결과 값을 볼수있습니다.

0. By using systme you can use the linux code in c. Easy way to get ps.
1. Ps.c file is the code that get computer's pid and cmdLine and save them in ps.txt file.
2. delprocess.c is the code that if you write down the pid then this program keep kill the process.
3. execv.c is the code that I tried to get the same result as Ps.c you may try to use this to get the similar result.
