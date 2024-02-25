#include <mega128a.h>
#include <delay.h>

#define U8 unsigned char
#define U16 unsigned short
#define U32 unsigned int
#define S16 signed short

unsigned char numbers[16] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x67, 0x77, 0x7C, 0x58, 0x5E, 0x79, 0x71};
unsigned char menu_prompt[] = "Hello!\rPlease write the number among 4~7\r";
unsigned char wrong_number[] = "wrong number.\rAgain.\r";

unsigned char *pStr = 0;          //UART 기본 통신용 변수들
unsigned char menuonce = 0;       //메뉴 출력 통제용 변수
unsigned short failonce = 0;      //UART 오류 메시지 통제용 변수

U8 extint4_on = 0;                //인터럽트 관련 변수
U8 extint5_on = 0;
U8 extint6_on = 0;
U8 extint7_on = 0;
U8 tim1on = 0;
U8 tim2on = 0;
U8 tim0on = 0;

U8 forx = 0, fory = 0;            //for반복문용 변수

U32 tem_count = 0;                //tim2 반복용 변수
U16 adc_value = 0;                //온도의 7seg변환용
U16 adc_result = 0;
U16 tim0x = 0, tim0sec = 0;       //tim0 반복용 변수

U16 ctc_value = 0;                //전압의 UART 송신용
U16 ctc_result;

U8 seg_mod = 0;                   //표시모드 변경용 변수
U8 N1000 = 0, N100 = 0;           //7seg 출력 자릿수 변수
U8 N10 = 0, N1 = 0;
U16 buf = 0;

U8 A100, A10, A1, Arest = 0;      //UART용 자릿수 변수
                                  //함수 선언
void asciify(U16 adata);          //데이터 아스키코드화
U16 adc_resultify(U16 tdata);     //온도, 전압 변환
void seg_write(U16 data);         //7-Seg 표기
void uartsend_volt(void);         //UART 전압 전송
void uartsend_menu(void);         

void main(void){
    DDRG = 0x0F;
    DDRB = 0xF0;
    DDRD = 0xF0;
    DDRC = 0xFF;
    PORTC = 0xFF;       
    
    SREG = 0x80;
    /*UCSR0A = 0x00;
    UCSR0B = 0x18;                  //송수신 ON
    UCSR0C = 0x06;
    UBRR0H = 0;
    UBRR0L = 103;*/                 //baud rate 9600
    
    for (forx = 0; forx <100; forx++){   //7seg 생년 출력
        PORTB &= 0x7F;
        seg_write(1997);
        PORTB &= 0x7F;
    }
     

    
    while(1){
        uartsend_menu();
        
        if (extint4_on == 1){     //7번 스위치 입력
            extint4_on = 0;
            TIMSK = 0x40;         //OVF 모드
            TCCR2 = 0x04;         //256분주
            TCNT2 = 6;            //4msec으로 1305번 (5220ms)
            ADMUX = 0x07;         //ADC7 이용
            ADCSRA = 0x84;        //Interrupt Off, 16분주
            seg_mod = 2;          //표시모드 = 온도
            forx = 0;             //for문 반복용 변수 초기화
        }
        if (tim2on == 1){
            tim2on = 0;
            tem_count++;          //4msec마다 변수값 증가
        }
        if(tem_count >= 1305){    //5220ms 도달 시
            tem_count = 0;
            ADCSRA |= 0x40;       //ADC 변환 시작
            while((ADCSRA & 0x10) == 0);   //ADC Int 확인
            adc_value = (short)ADCL + ((short)ADCH << 8);       //변환 값 저장
            if (adc_value < 100) adc_value = adc_value * 100;   //변환 값을 4자리로 만들기
            else if (adc_value > 100 && adc_value < 1000) adc_value = adc_value * 10;
            adc_result = adc_resultify(adc_value);              //정수형 온도값 계산 -> L176
            forx++;
            if (forx >=9){        //10번 반복 시
                TIMSK &= 0xBF;
                TCCR2 &= 0xFB;
                ADCSRA &= 0xBF;
                seg_mod = 1;      //종료 후 생일 표시로 복귀
            }
        }
        //인터럽트 4번 체인 끝
        
        if (extint5_on == 1){     //6번 스위치 입력
            extint5_on = 0;
            TIMSK = 0x10;         //CTC A 인터럽트 켜기
            TCCR1A = 0x0;
            TCCR1B = 0x0B;        //CTC, 64분주
            TCCR1C = 0x0;
            OCR1AH = 0xC3;        //0.2sec로 52200ms 주기
            OCR1AL = 0x4F;
            ADMUX = 0x06;         //ADC6 이용
            ADCSRA = 0x84;        //ADC 켜기, 16분주
            seg_mod = 1;
            fory = 0;
        }
        if (tim1on == 1){
            tim1on = 0;
            ADCSRA |= 0x40;       //ADC 변환 시작
            while((ADCSRA & 0x10) == 0);                    //ADC Int 확인
            ctc_value = (short)ADCL + ((short)ADCH << 8);   //변환 값 저장
            ctc_result = adc_resultify(ctc_value);          //정수형 전압값 계산
            asciify(ctc_result);                            //UART 통신 위해 아스키화
            uartsend_volt();
            fory++;
            if (fory >= 8){       //8번 반복 시
                ADCSRA &= 0xBF;
                TIMSK &= 0xEF;
                TCCR1B &= 0xF4;   //통신 종료
                menuonce = 0;     //메뉴 표시
            }
        }
        //인터럽트 5번 체인 끝 
        
        if (extint6_on == 1){     //5번 스위치 입력 시
            extint6_on = 0;
            TCCR3A = 0x82;        //OC3A핀, OCR까지 high 
            TCCR3B = 0x0B;        //F-PWM, 9bit, 64분주
            TCCR3C = 0x0;
            OCR3AH = 0;
            OCR3AL = 112;         //22퍼센트
            DDRE |= 0x08;         //E포트 출력
            TIMSK = 0x01;         //tim0 OVF
            TCNT0 = 6;            
            TCCR0 = 0x06;         //256분주
            tim0x = 0;            //tim0 반복변수 초기화
            tim0sec++;
        }
        if (tim0on == 1){         //4ms마다
            tim0on = 0;
            tim0x++;              //1증가
        }
        if (tim0x >= 250){        //1초마다
            tim0x = 0;
            tim0sec++;            //1증가
        }
            
        if (TCCR3B == 0x0B && tim0sec >= 7){   //Int6 + 7초 경과
            tim0sec = 0;
            TCCR3A &= 0x7D;       //Int6의 변화 초기화
            TCCR3B &= 0xF4;
            DDRE &= 0xF7;
            TIMSK &= 0xFE;    
        }
        if (extint7_on == 1){
            extint7_on = 0;
            TCCR3A = 0x82;        //OC3A핀, OCR까지 high
            TCCR3B = 0x03;        //PC-PWM, 9bit, 64분주
            TCCR3C = 0x0;
            OCR3AH = 0;
            OCR3AL = 112;         //22퍼센트
            DDRE |= 0x08;         //E포트 출력
            TIMSK = 0x01;         //tim0 OVF
            TCNT0 = 6;
            TCCR0 = 0x06;         //256분주
            tim0x = 0;            //tim0 반복변수 초기화
            tim0sec++;
        }
        if (TCCR3B == 0x03 && tim0sec >= 8){   //Int7 + 8초 경과
            tim0sec = 0;
            PORTC = 0x00;         //Int7의 변화 초기화
            TCCR3A &= 0x7D;
            TCCR3B &= 0xFC;
            DDRE &= 0xF7;
            TIMSK &= 0xFE;       
        }
        switch(seg_mod){
            case 1:seg_write(5022);   //기본 모드, 생일 표시
            break;
            case 2:seg_write(adc_result);    //인터럽트 발생 시, 온도 표시
            break;
            default:seg_mod = 1;
        }
    }
}
void uartsend_menu(void){               //UART 기본 함수
    if (menuonce == 255) menuonce = 2;  //메뉴 중복 출력 방지 구문
    menuonce++;
    UCSR0A = 0x00;
    UCSR0C = 0x06;
    UBRR0H = 0;
    UBRR0L = 103;                       //baud rate 9600
    
    if (menuonce == 1){                 //메뉴 송신 구문
        pStr = menu_prompt;             
        UCSR0B = 0x08;                  //송신 ON
        while(*pStr != 0){
            while((UCSR0A & 0x20) == 0x0); 
            UDR0 = *pStr++;
        }
    }
    if (failonce == 1){                 //오류 메시지 출력 구문
        pStr = wrong_number;
        UCSR0B = 0x08;                  //송신 ON
        while(*pStr != 0){
            while((UCSR0A & 0x20) == 0x0); 
            UDR0 = *pStr++;
        }
        failonce = 0;
    }
    while((UCSR0A & 0x20) == 0x0);
    UCSR0B = 0x10;                      //수신 ON
    switch (UDR0){                      //수신 값 확인
        case '4':
            EIMSK |= 0x10;              //4번 인터럽트 On, 여타 인터럽트는 건드리지 않음
            EICRB |= 0x03;
            menuonce = 0;               //메뉴 재출력
            break;
        case '5':
            EIMSK |= 0x20;              //5번 인터럽트 On, 여타 인터럽트는 건드리지 않음
            EICRB |= 0x08;
            menuonce = 0;
            break;
        case '6':
            EIMSK |= 0x40;              //6번 인터럽트 On, 여타 인터럽트는 건드리지 않음
            EICRB |= 0x30;
            menuonce = 0;
            break;          
        case '7':
            EIMSK |= 0x80;              //7번 인터럽트 On, 여타 인터럽트는 건드리지 않음
            EICRB |= 0x80;
            menuonce = 0;
            break;
        default:    
            if(UDR0 !=4 && UDR0 != 5 && UDR0 != 6 && UDR0 != 7 && UDR0 != 0x00) failonce = 1;  //미입력 시에도 출력되는 걸 방지하고자 NULL문자 포함
            break;
    }      
}
U16 adc_resultify(U16 tdata){           //전압, 온도 변환 함수
    float fdata = 0;
    U16 idata = 0;
    
    fdata = (float)(tdata) * 5.0 / 1024.0;
    idata = (short)(fdata * 100.0);
    
    return idata;    
}
void asciify(U16 adata){                //UART 통신용 아스키화 함수
    A100 = (adata / 100) + 0x30;
    Arest = adata % 100;
    A10 = (Arest / 10) + 0x30;
    A1 = (Arest % 10) + 0x30;
}
void uartsend_volt(void){               //UART, 전압 송신용 함수
    UCSR0A = 0x00;
    UCSR0B = 0x08;
    UCSR0C = 0x06;
    UBRR0H = 0;
    UBRR0L = 103;     //baud rate 9600
    
    while((UCSR0A & 0x20) == 0x0);
    UDR0 = A100;
    while((UCSR0A & 0x20) == 0x0);
    UDR0 = '.';
    while((UCSR0A & 0x20) == 0x0);
    UDR0 = A10; 
    while((UCSR0A & 0x20) == 0x0);
    UDR0 = A1; 
    while((UCSR0A & 0x20) == 0x0);
    UDR0 = 'V';
    while((UCSR0A & 0x20) == 0x0);
    UDR0 = ' ';  
}
void seg_write(U16 data){                    //7-Seg 입력용 함수
    N1000 = data / 1000;
    buf = data % 1000;
    
    N100 = buf / 100;
    buf = buf % 100;
    
    N10 = buf / 10;
    N1 = buf % 10;

    PORTG = 0x01;
    PORTD = ((numbers[N1000] & 0x0F) << 4) | (PORTD & 0x0F);
    PORTB = (numbers[N1000] & 0x70) | (PORTB & 0x0F);
    delay_ms(1);
    
    PORTG = 0x02;
    PORTD = ((numbers[N100] & 0x0F) << 4) | (PORTD & 0x0F);
    PORTB = (numbers[N100] & 0x70) | (PORTB & 0x0F);
    if (seg_mod == 2) PORTB |= 0x80;
    delay_ms(1);
    
    PORTG = 0x04;
    PORTD = ((numbers[N10] & 0x0F) << 4) | (PORTD & 0x0F);
    PORTB = (numbers[N10] & 0x70) | (PORTB & 0x0F);
    delay_ms(1);
    
    PORTG = 0x08;
    PORTD = ((numbers[N1] & 0x0F) << 4) | (PORTD & 0x0F);
    PORTB = (numbers[N1] & 0x70) | (PORTB & 0x0F);
    delay_ms(1);
}
interrupt [EXT_INT4] void EXTINT4ON(void){   //스위치 7
    SREG &= 0x7F;
    extint4_on = 1;
    SREG |= 0x80;
}
interrupt [EXT_INT5] void EXTINT5ON(void){   //스위치 6
    SREG &= 0x7F;
    extint5_on = 1;
    SREG |= 0x80;
}
interrupt [EXT_INT6] void EXTINT6ON(void){   //스위치 5
    SREG &= 0x7F;
    extint6_on = 1;
    SREG |= 0x80;
}
interrupt [EXT_INT7] void EXTINT7ON(void){   //스위치 4
    SREG &= 0x7F;
    extint7_on = 1;
    SREG |= 0x80;
}
interrupt [TIM1_COMPA] void TIM1COMPAON(void){
    SREG &= 0x7F;
    tim1on = 1;
    SREG |= 0x80;
}
interrupt [TIM2_OVF] void TIM2OVFON(void){
    SREG &= 0x7F;
    tim2on = 1;
    SREG |= 0x80;
}
interrupt [TIM0_OVF] void ADCOMPLETE(void){
    SREG &= 0x7F;
    tim0on = 1;
    SREG |= 0x80;
}
interrupt [ADC_INT] void AAADDDCCCINTER(void){
    SREG &= 0x7F;
    SREG |= 0x80;
}