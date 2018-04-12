import processing.serial.*;

// ************ CONFIGURACIÓN DE PANTALLA ************

int W=1300; 
int H=650;

// ************ COMUNICACIÓN SERIAL ************
Serial Port;
boolean found;
//IntList buf1, buf2, buf3;
byte con1, con2, con3, con4, con5, con6;

float buffer1, buffer2, buffer3, buffer4 = 0;
int j, k, l;
int estado = 1; 
float bufferAux1[], bufferAux2[];

// ************ ANEMÓMETRO ************

float distance = 0.26;
float time = 0.000758, time1 = 0.0007, time2 = 0.0008; 
float v, vx, vy, angle, sound, temperature;

// ************ BRÚJULA ************
float CompassMagnificationFactor=0.6; 
float SpanAngle=120; 
int NumberOfScaleMajorDivisions; 
int NumberOfScaleMinorDivisions; 

// ************ TERMÓMETRO ************
float ThermometerMagnificationFactor=0.9;
float sumBuffer1=0, sumBuffer2=0;
int countProm=0;

// ************ SISMO ************
boolean sismo;

void setup()
{
    size(800,650);  // TAMAÑO DE VENTANA GRÁFICA.
    Port = new Serial(this, Serial.list()[0], 115200);
    Port.buffer(7); // DEBE SER DE TAMAÑO 5 PARA 2 ANALÓGICOS.
    //buf1 = new IntList();
    //buf2 = new IntList();
} // setup()

void draw(){
    
    background(0);
    if(sismo){
      backgroudRed();
    }else
    {
      backgroudBlue();
    }
    fill(255);
    textSize(30);
    text("Estación Meteorológica", 230, 35);    
    //parameters(time, buffer1, time2);
    thermometer();
    Compass(); 
        
} // draw()

// Loop infinito.
void serialEvent(Serial Port){
  byte[] in = new byte[6];   // Arreglo de bytes de entrada. DEBE SER DE TAMAÑO 5 PARA DOS ANALÓGICOS.
  byte[] dummy = new byte[1];
  
 
  do{
     Port.readBytes(dummy);
  }while(dummy[0]!=-14);
  
  Port.readBytes(in);        // Leer paquete de bytes de entrada.
 

          con1 = in[0];   // Se obtiene Byte 1.
          con2 = in[1];   // Se obtiene Byte 2.
          buffer1 = (256*con1)+con2;
          buffer1 = (buffer1*59/1000)/1000000;
          /*for(k=0;k<11;k++){
            bufferAux1[k]=buffer1;
            if(k==10){
              for(l=0;l<11;l++){
                buffer4 = buffer4 + bufferAux1[l];
   
              }
            }  
          }*/
          print("Tiempo1: ");
          println(buffer1);
          con3 = in[2];   // Se obtiene Byte 3.
          con4 = in[3];   // Se obtiene Byte 4.
          buffer2 = (256*con3)+con4;
          buffer2 = (buffer2*59/1000)/1000000;
          //if(buffer2 > 300 && buffer2<2800){
            sumBuffer1 = sumBuffer1+buffer1;
            sumBuffer2 = sumBuffer2+buffer2;
          //if(buffer2 > 0.0009 || buffer2<0.001){
            countProm++;
          if(countProm>=30){
            print("Tiempo2: ");
            println(buffer2);
            buffer1 = sumBuffer1/30;
            buffer2 = sumBuffer2/30;
            parameters(time, time1, time2);
            sumBuffer1=0;
            sumBuffer2=0;
            countProm=0;
          }
          //}
          
          con5 = in[4];   // Se obtiene Byte 3.
          con6 = in[5];   // Se obtiene Byte 4.
          buffer3=decode(con5,con6);
          //println(buffer3);
          if(buffer3<2300 || buffer3>3000){
            sismo=true;
          }            
    //} // if()

}  // serialEvent();

// Decodificar protocolo.
int decode(byte con1, byte con2){
  int aux1, aux2, aux3, aux4, code;
  
  aux1 = con1 & 0x1F;
  aux2 = con2 << 1;
  aux3 = aux1 << 8;
  aux4 = aux2 & 0x00FF;
  aux4 = aux3 | aux4;
  code = aux4 >> 1;
  
  return code;
} // decode()

// Calculo de parámetros.
void parameters(float tiempo, float tiempo1, float tiempo2){
  
  // Para cálculo de la velocidad del viento.
  vx = (distance*(tiempo1-tiempo))/(2*tiempo1*tiempo);
  vy = (distance*(tiempo2-tiempo))/(2*tiempo2*tiempo);
  v = sqrt(pow(vx,2)+pow(vy,2));
  
  // Para cálculo de la dirección del viento.
  if(tiempo1>tiempo && tiempo2<tiempo){
    angle = ((180*(atan(vy/vx)))/PI) + 180;
  }
  if(tiempo1<tiempo && tiempo2>tiempo){
    angle = ((180*(atan(vy/vx)))/PI);  
  }
  if(tiempo1>tiempo && tiempo2>tiempo){
    angle = ((180*(atan(vy/vx)))/PI) + 180;  
  }
  if(tiempo1<tiempo && tiempo2<tiempo){
    angle = ((180*(atan(vy/vx)))/PI);
  }
  if(tiempo1>tiempo){
    angle = ((180*(atan(vy/vx)))/PI) + 180;
  }
  if(tiempo1<tiempo){
    angle = ((180*(atan(vy/vx)))/PI);
  }else{
    angle = ((180*(atan(vy/vx)))/PI) + 180;
  }  
  
  // Para el cálculo de la temperatura.
  temperature = (pow((distance*(tiempo1+tiempo))/(40*tiempo1*tiempo),2)) - 273;
  
  // Para el cálculo de la velocidad del sonido.
  sound = (distance*(tiempo1+tiempo))/(2*tiempo1*tiempo);
} // parameters()

void backgroudBlue()
{
  for (int k=255;k>0;k=k-1) 
  { 
    noStroke(); 
    fill(0, 0, 255-k); 
    ellipse(400, 310, 3.5*k, 3.5*k); 
  } 
}

void backgroudRed(){
    for (int k=255;k>0;k=k-1) 
  { 
    noStroke(); 
    fill(255-k, 0, 0); 
    ellipse(400, 310, 3.5*k, 3.5*k); 
    
    fill(255);
    textSize(40);
    text("HA OCURRIDO UN SISMO",160,640);
    
    sismo = false;
  } 
}

// ************ BRÚJULA ************

void Compass() 
{ 
  rectMode(CENTER); 
  smooth(); 
  translate(W/4, H/2); 
  scale(CompassMagnificationFactor); 
  noFill(); 
  stroke(100); 
  strokeWeight(80); 
  ellipse(0, 0, 750, 750); 
  strokeWeight(50); 
  stroke(50); 
  fill(0, 0, 40); 
  ellipse(0, 0, 610, 610); 
  for (int k=255;k>0;k=k-5) 
  { 
    noStroke(); 
    fill(0, 0, 255-k); 
    ellipse(0, 0, 2*k, 2*k); 
  } 
  strokeWeight(20); 
  NumberOfScaleMajorDivisions=18; 
  NumberOfScaleMinorDivisions=36;  
  SpanAngle=180; 
  CircularScale(); 
  rotate(PI); 
  SpanAngle=180; 
  CircularScale(); 
  rotate(-PI); 
  fill(255); 
  textSize(60); 
  textAlign(CENTER); 
  text("W", -375, 0, 100, 80); 
  text("E", 370, 0, 100, 80); 
  text("N", 0, -365, 100, 80); 
  text("S", 0, 375, 100, 80); 
  textSize(30); 
  text("Wind Direction", 0, -130, 500, 80); 
  rotate(PI/4); 
  textSize(40); 
  text("NW", -370, 0, 100, 50); 
  text("SE", 365, 0, 100, 50); 
  text("NE", 0, -355, 100, 50); 
  text("SW", 0, 365, 100, 50); 
  rotate(-PI/4); 
  //parameters(time, buffer1, time2);
  CompassPointer(); 
  showDegreesB(); 
  
}

void CompassPointer() 
{ 
  rotate(PI+radians(angle));  
  stroke(0); 
  strokeWeight(4); 
  fill(100, 255, 100); 
  triangle(-20, -210, 20, -210, 0, 270); 
  triangle(-15, 210, 15, 210, 0, 270); 
  ellipse(0, 0, 45, 45);   
  fill(0, 0, 50); 
  noStroke(); 
  ellipse(0, 0, 10, 10); 
  triangle(-20, -213, 20, -213, 0, -190); 
  triangle(-15, -215, 15, -215, 0, -200); 
  rotate(-PI-radians(angle)); 
}

void CircularScale() 
{ 
  float GaugeWidth=800;  
  textSize(GaugeWidth/30); 
  float StrokeWidth=1; 
  float an; 
  float DivxPhasorCloser; 
  float DivxPhasorDistal; 
  float DivyPhasorCloser; 
  float DivyPhasorDistal; 
  strokeWeight(2*StrokeWidth); 
  stroke(255);
  float DivCloserPhasorLenght=GaugeWidth/2-GaugeWidth/9-StrokeWidth; 
  float DivDistalPhasorLenght=GaugeWidth/2-GaugeWidth/7.5-StrokeWidth;
  for (int Division=0;Division<NumberOfScaleMinorDivisions+1;Division++) 
  { 
    an=SpanAngle/2+Division*SpanAngle/NumberOfScaleMinorDivisions;  
    DivxPhasorCloser=DivCloserPhasorLenght*cos(radians(an)); 
    DivxPhasorDistal=DivDistalPhasorLenght*cos(radians(an)); 
    DivyPhasorCloser=DivCloserPhasorLenght*sin(radians(an)); 
    DivyPhasorDistal=DivDistalPhasorLenght*sin(radians(an));   
    line(DivxPhasorCloser, DivyPhasorCloser, DivxPhasorDistal, DivyPhasorDistal); 
  }
  DivCloserPhasorLenght=GaugeWidth/2-GaugeWidth/10-StrokeWidth; 
  DivDistalPhasorLenght=GaugeWidth/2-GaugeWidth/7.4-StrokeWidth;
  for (int Division=0;Division<NumberOfScaleMajorDivisions+1;Division++) 
  { 
    an=SpanAngle/2+Division*SpanAngle/NumberOfScaleMajorDivisions;  
    DivxPhasorCloser=DivCloserPhasorLenght*cos(radians(an)); 
    DivxPhasorDistal=DivDistalPhasorLenght*cos(radians(an)); 
    DivyPhasorCloser=DivCloserPhasorLenght*sin(radians(an)); 
    DivyPhasorDistal=DivDistalPhasorLenght*sin(radians(an)); 
    if (Division==NumberOfScaleMajorDivisions/2|Division==0|Division==NumberOfScaleMajorDivisions) 
    { 
      strokeWeight(15); 
      stroke(0); 
      line(DivxPhasorCloser, DivyPhasorCloser, DivxPhasorDistal, DivyPhasorDistal); 
      strokeWeight(8); 
      stroke(100, 255, 100); 
      line(DivxPhasorCloser, DivyPhasorCloser, DivxPhasorDistal, DivyPhasorDistal); 
    } 
    else 
    { 
      strokeWeight(3); 
      stroke(255); 
      line(DivxPhasorCloser, DivyPhasorCloser, DivxPhasorDistal, DivyPhasorDistal); 
    } 
  } 
}

void showDegreesB() 
{ 
  int angle1=round(angle); 
  textAlign(CORNER); 
  textSize(35); 
  fill(255); 
  text("Degrees:  "+angle1+"°", 90, 477, 500, 60); 
  text("Wind Speed: "+v+" m/s", 90, 520, 500, 60);
  text("Sound Speed: "+sound+" m/s", 90, 570, 500, 60);
}

// ************ TERMOMETRO ************

// Interfaz del termómetro.
void thermometer()
{
 int i;
 int N = (int)map(temperature,-59,86,380,0);
 
 scale(ThermometerMagnificationFactor); 

 // Relleno de gris
 fill (120,120,120);

 // Creación del termostato.
 rectMode(CORNER);
 rect(680, 60, 70, 392);
 ellipse (715, 500, 120, 120);
  
 // Reservorio de color azul.
 fill(0, 0, 100);
 ellipse (715, 500, 100, 100);
 rect(690,450,50,10); // RELLENO
 
 // Reservorio a llenarse dependiendo de los grados.
 rect(690, 70+N, 50, 380-N);  // PINTA EL VALOR EN GRADOS.
 
 // Lineas de medida. 
 fill(0);
 for(i=1;i<=13;i++){
   rect(700,(i*30+40),40,3); // RELLENO
 }
 
 ShowDegreesT();
}

// Valor a mostrar debajo del termómetro en °C
void ShowDegreesT() 
{ 
  int temperature1=round(temperature); 
  textAlign(CORNER);   
  textSize(21); 
  fill(255); 
  text("Degrees:  "+temperature1+"°C", 650, 575, 500, 60); 
}
  
