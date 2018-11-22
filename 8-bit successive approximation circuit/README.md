* ### 목적

     -입력 값을 추정하며 찾아 출력하는 FSM(Finite State Machine)을 구현 하는 것이 Term Project의 목적입니다.
     
* ### Detail Project Description 
    입력 값을 넣으면 정해진 상태에 따른 결과값과 그 결과값을 다시 입력 값으로 넣어
    근사치를 연속적으로 추정하여 값을 일치시키는 FSM(Finite State Machine)을 구현하는 것이
    이번 project의 목적입니다. 
    원래는 아날로그 값을 받아 출력을 찾는 것이 마땅하지만, 
    이 project에서는 입력 값을 임의의 8bit값으로 정하여 사용하겠습니다. 
    어셈블리어로 converter함수를 구현하여 입력과 출력의 값을 비교하고, 
    반복작업을 통해 입력 값을 찾고 그 입력 값을 LED로 출력하는 FSM으로 작동하는 DigitalCircuit을 구현하겠습니다.  



* ### 하드웨어블록 및 다이어그램설계
 
 ![1](https://user-images.githubusercontent.com/44973398/48902198-2f8e5a00-ee9b-11e8-813f-8bcceca5d105.PNG)
 
    -Approximation 할 input값과 정해진 상수 INPUT값(constant)를
    뺄셈 연산하였을 때의 OUTPUT상태에 따라 INPUT(Approximation)값을 
    비트를 하나씩 확정해줌으로써 digital circuit을 거칠 때 마다 INPUT(constant)값에
    점점 다가가게 하여 최종적으로 result를 출력해 줄 수 있도록 하였습니다.
    두 INPUT값은 Term Project시에는 정해진 상수를 사용했으므로 INPUT PIN을 
    굳이 설정해주지는 않았으며 PORTA로 출력 값을 담아 LED로 출력해주는 방법으로 설계했습니다.


* ### 소프트웨어 설계

* ### 플로우 차트

![2](https://user-images.githubusercontent.com/44973398/48902322-93b11e00-ee9b-11e8-98db-789ddee3730d.PNG)


* ### Functions used in code
-Converter : R20(입력 값)과 R17(출력 값)을 Subtract연산 해준 뒤 발생하는 carry를 가지고 대소 판별을 해준다.
그래서 두 값이 Greater 이면 PORTB.0을 set, equal 이면 PORTD.0 을 set, 그리고 less 이면 PORTC.0 을 set 해준다

* ### Lable used in code
1. L1: R16을 LSR 해주고, R17과 OR을 해주어 R17의 다음bit를 1로만들어주는 기능을 한다. (출력이 입력 값을 찾아가는 것임)

2. L2: R16과 R17을 XOR해주어, 1로만들었던 R17의 bit를 원래상태인 0으로 되돌린후, LSR한 R16을 다시 OR해줌으로써 다음bit 1로만들어준다.

3. LED_OUT: 입력값을 추정한 값인 R17을 PORTA로 보내서 LED로 출력한다.

4. C1: R20>R17 이면 즉, greater이면 PORTB.0 을 1로 만들어 줌

5. C2: R20<R17 이면 즉, less이면 PORTC.0을 1로 만들어 줌

6. C3: R20=R17 이면 즉, equal이면 PORTD.0을 1로 만들어 줌


* ### 실험 결과

![3](https://user-images.githubusercontent.com/44973398/48902369-bc391800-ee9b-11e8-8de8-ce33b61bf8ac.PNG)

    입력을 0x1F로 주었을 때, 스위치를 누른 뒤 출력이 입력 값을 찾아냈음을 알 수 있다.

![4](https://user-images.githubusercontent.com/44973398/48902370-bcd1ae80-ee9b-11e8-9e60-234003229830.PNG)

    입력을 0xAA로 주었을 때, 스위치를 누른 뒤 Digital Circuit이 입력을 찾아 출력하였다.

* ### 참조문헌
    -AVR Microcontroller and Embedded Systems: Pearson New International Edition: Using Assembly and C
    1.1.1. Muhammad Ali Mazidi; Sarmad Naimi; Sepehr Naimi
