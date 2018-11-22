# FinalTermProject (온습도 센서를 활용한 불쾌지수 판별기)

* ### 목적

          -온도와 습도만을 가지고는 바깥에서 느끼는 날씨가 어떤지 감을 잘 잡을 수가 없습니다.
          따라서 아날로그 신호인 온도와 습도를 외부센서로 받아 불쾌지수를 계산하여 
          8x8 dotmatrix로 불쾌지수에따른 표정을 출력하는 시스템을 구현하였습니다.
 
* ### 사용된 부품

![8](https://user-images.githubusercontent.com/44973398/48904583-31a7e700-eea2-11e8-8f01-8834432acb42.PNG)
                   
                 -EPXFDNH3 정전용량방식 습도센서 :습도센서. 
                  BVD-8518SG1: 표정출력을 위한 8x8 dotmatrix. 
                  aTS75 : 온도측정센서


* ### 하드웨어블록 및 다이어그램설계
 
 ![5](https://user-images.githubusercontent.com/44973398/48904087-abd76c00-eea0-11e8-84a6-837363728a25.png)
         
         -Input으로 온도와 습도를 받습니다.(입력) 
         그 후 ADC converter를 이용하여 Digital Data로 바꾸어줍니다.(처리)
         변환된 Data를 가지고 불쾌지수를 계산하여 8x8 dotmatrix에 표정을 출력하여 줍니다.(출력)

* ### 소프트웨어 설계

* ### 플로우 차트

![6](https://user-images.githubusercontent.com/44973398/48904089-ac700280-eea0-11e8-9ef5-d4cbf0773415.PNG)

    -먼저 온도센서를 이용하여 온도를 측정합니다. 
    그 후 ADC(Analogue-Digital Converter)를 사용하기 위해 ADC1 포트에 습도센서를 연결합니다. 
    Interrupt를 사용하여 온도 및 습도 DATA를 전달 받으면 
    그 Data를 가지고 불쾌지수를 계산하여 기준값에 따라 8x8 dotmatrix에 표정을 출력합니다.
    
* ### Functions used in code

* ### 실험 결과

![7](https://user-images.githubusercontent.com/44973398/48904166-e5a87280-eea0-11e8-8e71-86fb93c5b83f.PNG)

    온도와 습도를 입력으로 받아 변환된 불쾌지수 수치에따라 8x8 dot matrix에 표현되는 표정이 다름을 알 수 있다.

* ### 참조문헌
    -AVR Microcontroller and Embedded Systems: Pearson New International Edition: Using Assembly and C
    1.1.1. Muhammad Ali Mazidi; Sarmad Naimi; Sepehr Naimi
