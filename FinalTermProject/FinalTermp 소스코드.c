#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define aTS75_CONFIG_REG 1
#define aTS75_TEMP_REG 0

//온도센서를 위한 함수들
void I2C_Init(void);
void I2C_start(void);
void I2C_write(unsigned char data);
unsigned char I2C_read(unsigned char ackVal);
void I2c_stop(void);
void temp_init(void);
int temp_read(void);
int int_temp(int value);

//습도센서를 위한 함수들
unsigned int conversionHumidity (unsigned int x);
void ADCInit();

//Dotmatrix로 출력을 위한 함수들
void Display_Dotmatrix(unsigned int value);
void display_FND(int value);


int main(void)
{
    int temperature = 0;
	unsigned int humidity =0;
	unsigned int H_Percent =0;
	unsigned int volt=0;
	unsigned int DI=0; //불쾌지수
	int temp=0;
	
	//FMD출력
    DDRC = 0xff; 
	DDRG = 0xff;
	
	//Dotmatrix를 위한 설정
	DDRA = 0xff;
	
    //온도센서설정
	PORTD = 3;
	temp_init();
   
    while (1) 
    {
        temperature = temp_read();
		temp=int_temp(temperature);
		ADCInit();
		ADCSRA |= (1<<ADSC); //ADC 변환 시작
		while(ADCSRA & (1<<ADIF)); //ADIF를 check 해주면서 변환이 완료되었나 확인한다.
		unsigned char low  = ADCL;
		unsigned char high = ADCH;
		
		humidity = low + (high<< 8);    // Humidity 센서를 통해 받아온 analog 값
		volt = (float)humidity*5000/1024;    // [mV] 전압값으로 변환
		//humidity = (high << 8) | low;
		H_Percent=conversionHumidity(volt);
		double H = (double)H_Percent/100.000;
		DI = 1.8*temp-0.55*(1-H)*(1.8*temp-26)+32; //불쾌지수를 변환하는 공식
		Display_Dotmatrix(DI);
		display_FND(DI);
		
		
    } 
}


//I2C 초기화
void I2C_Init(void) {
    TWBR = 12;                            // 16000000 / (16 + (2x12)) x prescaler = 400000Hz = 400kHz
    TWSR = (0<<TWPS1) | (0<<TWPS0);        // prescaler = 1
    TWCR = 0x04;
}

//I2C 시작 
void I2C_start(void) {
    TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
    while (!(TWCR & (1<<TWINT)));
}

//I2C 데이터 쓰기 
void I2C_write(unsigned char data) {
    TWDR = data;
    TWCR = (1<<TWINT) | (1<<TWEN);
    while(!(TWCR & (1<<TWINT)));
} 

//I2C 데이터 읽기
unsigned char I2C_read(unsigned char ackVal) {
    TWCR = (1<<TWINT) | (1<<TWEN) | (ackVal<<TWEA);
    while(!(TWCR & (1<<TWINT)));
    return TWDR;
}

//I2C 전송 Stop
void I2c_stop(void) {
    TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
    for(int k=0; k<100; k++);                    //wait
}

void temp_init(void) {
    I2C_Init();
    I2C_start();
    I2C_write(0b10011000);
    I2C_write(aTS75_CONFIG_REG);        // Configuration Register P1 = 0, P0 = 1
    I2C_write(0x00);
    I2c_stop();
}
int temp_read(void) {
    char high_byte, low_byte;
    I2C_start();
    I2C_write(0b10011000);
    I2C_write(aTS75_TEMP_REG);            // Temperature Register P1, P0 = 0 
    
    I2C_start();
    I2C_write(0b10011000 | 1);            // Address + write (not read)
    high_byte = I2C_read(1);            
    low_byte = I2C_read(0);
    I2c_stop();
    
    return ((high_byte<<8) | low_byte);
}

int int_temp(int value)
{
    char value_int;
    value_int = (char)((value & 0x7f00) >> 8);
	return value_int;
}

//Vout 값을 습도값으로 변환
unsigned int conversionHumidity (unsigned int x){
	unsigned int HumidityPercent =0;
	if(x<758)
	HumidityPercent = 5;
	else if(x<1022)
	HumidityPercent = 10;
	else if(x<1243)
	HumidityPercent = 15;
	else if(x<1430)
	HumidityPercent = 20;
	else if(x<1591)
	HumidityPercent = 25;
	else if(x<1734)
	HumidityPercent = 30;
	else if(x<1862)
	HumidityPercent = 35;
	else if(x<1983)
	HumidityPercent = 40;
	else if(x<2098)
	HumidityPercent = 45;
	else if(x<2213)
	HumidityPercent = 50;
	else if(x<2328)
	HumidityPercent = 55;
	else if(x<2446)
	HumidityPercent = 60;
	else if(x<2566)
	HumidityPercent = 65;
	else if(x<2688)
	HumidityPercent = 70;
	else if(x<2811)
	HumidityPercent = 75;
	else if(x<2932)
	HumidityPercent = 80;
	else if(x<3048)
	HumidityPercent = 85;
	else if(x<3155)
	HumidityPercent = 90;
	else if(x<3248)
	HumidityPercent = 95;
	else if(x<3321)
	HumidityPercent = 100;
	else
	HumidityPercent = 100;
	
	return HumidityPercent;
}

void ADCInit(){
	//ADC init
	ADMUX |= (0<<REFS1 | 0<<REFS0); //기준전압으로 AREF 사용
	//ADC 입력채널 선택  ADC1(PF0)
	ADMUX &= ~( (1<<MUX4) | (1<<MUX3) | (1<<MUX2) | (1<<MUX1)|(1<<MUX0));
	ADCSRA |= (1<<ADEN|(0<<ADFR)); //ADC 기능 활성화, singleconversion mode
	// 16Mhz/128 = 125Khz, ADC의 입력 클록 주파수
	ADCSRA |= ((1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0));
}

void Display_Dotmatrix(unsigned int value){
		DDRA =0xff;
		DDRE = 0xff;
	//웃는표정
	if(value<75){
	const char IMAGES[]= {
		0B00000000,
		0B00000000,
		0B01100110,
		0B01100110,
		0B00000000,
		0B01000010,
		0B00111100,
		0B00000000
	};
	
		for(int i=0; i<8;i++){
			PORTA = IMAGES[i];
			if (i==2||i==3||i==5||i==6)
			PORTE = ~(1<<i);
			else
			PORTE = 0xff;
			_delay_ms(2);
			}
	}
	
	//무표정
	else if(value<79)
	{
		const char IMAGES[] = {
		
		0B00000000,
		0B00000000,
		0B01100110,
		0B01100110,
		0B00000000,
		0B00000000,
		0B00111100,
		0B00000000
	};
	
		for(int i=0; i<8;i++){
			PORTA = IMAGES[i];
			if (i==2||i==3||i==6)
			PORTE = ~(1<<i);
			else
			PORTE = 0xff;
			_delay_ms(2);
		}
	}
	
	//화난표정
	else
	{
	const char IMAGES[] = {
		
		0B00000000,
		0B10000001,
		0B11000011,
		0B01100110,
		0B00000000,
		0B00111100,
		0B01000010,
		0B00000000
	};
	
		for(int i=0; i<8;i++){
			PORTA = IMAGES[i];
			if (i==1||i==2||i==3||i==5||i==6)
			PORTE = ~(1<<i);
			else
			PORTE = 0xff;
			_delay_ms(2);
				}
			}
}

//불쾌지수 DI값을 받아와서 FND로 출력
void display_FND(int value)
{
	char digit[12] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7c, 0x07, 0x7f, 0x67, 0x40, 0x00};
	char fnd_sel[4] = {0x01, 0x02, 0x04, 0x00};
	char num[4];
	int i;
	
	num[2] = (value / 10) % 10;
	num[1] = value % 10;
	num[0] = 0;
	num[3] =0;
	for(i=0; i<4; i++)
	{
		PORTG = fnd_sel[i];
		PORTC = digit[num[i]];
		
		if(i==1)
		PORTC |= 0x80;
		_delay_ms(2);
	}
}