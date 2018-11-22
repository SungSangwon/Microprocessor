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

### 온도센서를 위한 함수들
* ### 함수설명에 앞서 I2C 통신에 대해 간단히 설명하겠습니다.

          I2C는 Inter Integrated Cricuit의 줄임말로 TWI(Two Wire Interface)라고도 불립니다. 
          하나의 마스터와 하나이상의 슬레이브로 이루어진 Data 통신방식입니다.
          출처: https://elecs.tistory.com/11 [늦깎이 공대생의 좌충우돌 이야기]
          
* ### void I2C_Init(void);
  I2C 초기화하는 함수. 
  16000000 / (16 + (2x12))*prescaler = 400000Hz = 400kHz로 지정. 
  prescaler = 1로 지정한다.
  
* ### void I2C_start(void);
  I2C 를 시작하는 함수.
* ### void I2C_write(unsigned char data);
  I2C 데이터를 받아오기 시작하는 함수.
* ### unsigned char I2C_read(unsigned char ackVal);
  I2C 데이터를 읽기 시작하는 함수.
* ### void I2c_stop(void);
  I2C 전송을 중단하는 함수.
* ### void temp_init(void);

* ### int temp_read(void);

* ### int int_temp(int value);

### 습도센서를 위한 함수들
* ### unsigned int conversionHumidity (unsigned int x);

* ### void ADCInit();

### Dotmatrix로 출력을 위한 함수들
* ### void Display_Dotmatrix(unsigned int value);

* ### void display_FND(int value);

* ### 실험 결과

![7](https://user-images.githubusercontent.com/44973398/48904166-e5a87280-eea0-11e8-8e71-86fb93c5b83f.PNG)

    온도와 습도를 입력으로 받아 변환된 불쾌지수 수치에따라 8x8 dot matrix에 표현되는 표정이 다름을 알 수 있다.

* ### 참조문헌
    -AVR Microcontroller and Embedded Systems: Pearson New International Edition: Using Assembly and C
    1.1.1. Muhammad Ali Mazidi; Sarmad Naimi; Sepehr Naimi
