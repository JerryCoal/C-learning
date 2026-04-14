# Arduino 编程

## 概述
    本次采用 ESP32-C3 开发板
    setup()函数在程序启动时仅执行一次，用于完成引脚模式设置、串口初始化，外设配置；
    loop()函数在setup()之后执行其他主要操作

### setup函数
```c
void setup(){
    //设置自己的端口数据
    pinMode(13,OUTPUT); //设置13端口为输出模式
}
```

### loop函数(循环主函数)
```c
void loop(){
    delay(1000);//延时1s
    degitalWrite(13,HIGH);//设置13引脚为高电平

}
```

### Ardiuno的Heloworld
```c
int P10 = 10;
void setup() {
  // put your setup code here, to run once:
  pinMode(P10,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(P10,HIGH);
  delay(1000);
  digitalWrite(P10,LOW);
  delay(1000);

}

```

## 延时函数

### 微秒级（us）
#### micros函数应用实例
```c
const int P10 = 10;

unsigned long last_time =0;//初始化上次时间
bool ledState = false;//led状态

const unsigned long set_time_high = 5;
const unsigned long set_time_low = 50;

void setup() {
  // put your setup code here, to run once:
  pinMode(P10,OUTPUT);
}

//这里是交替不同时间的led串流
void loop() {
  //获取当前时间
  unsigned long pre_time = micros();
  if (ledState){
    if ((pre_time - last_time) >= set_time_high){
      ledState = !ledState;
      //这里写自己的操作
      digitalWrite(P10,ledState);
      last_time = pre_time;
    }
  }else{
    if ((pre_time - last_time) >= set_time_low){
      ledState = !ledState;
      digitalWrite(P10,ledState);
      last_time = pre_time;
    }
  }
}

```

#### delayMicroseconds函数
```c
const int P10 = 10;
const unsigned long set_time_high = 5;
const unsigned long set_time_low = 50;

void setup() {
  // put your setup code here, to run once:
  pinMode(P10,OUTPUT);
}

void loop() {

  delayMicroseconds(set_time_high);
  digitalWrite(P10,LOW);
  delayMicroseconds(set_time_low);
  digitalWrite(P10,HIGH);

}
```
### 毫秒级（ms）
    delay函数和millis()函数
    *注意：millis函数和micros函数都是返回当前时间，都用unsigned int 作为返回值

## 按键消抖

### 基础操作
```c
const int P10 = 10;
const int Button= 9;
unsigned long last_time =0;//初始化上次时间
bool ledState = false;//led状态

const unsigned long set_time_high = 5;
const unsigned long set_time_low = 50;

void setup() {
  // put your setup code here, to run once:
  pinMode(P10,OUTPUT);
  pinMode(Button,INPUT);
}

void loop() {
  if (digitalRead(Button) == HIGH){
    digitalWrite(P10,HIGH);
  }else {
    digitalWrite(P10,LOW);
  }
}

```

### 消抖操作
```c
const int P10 = 10;
const int Button= 9;
const int delay_time = 50;
unsigned long last_time =0;//初始化上次时间
bool ledState = true;//led状态

void setup() {
  // put your setup code here, to run once:
  pinMode(P10,OUTPUT);
  pinMode(Button,INPUT);
}

void loop() {
  if (digitalRead(Button) == HIGH){
    delay(1);
    if (digitalRead(Button) == LOW){
      delay(10);
      if (digitalRead(Button) == LOW){
        ledState = !ledState;
        digitalWrite(P10,ledState);           
      }
   
    }
  }
}

```