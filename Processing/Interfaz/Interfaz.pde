import processing.serial.*;

// ************ CONFIGURACIÓN DE PANTALLA ************

int W=1300; 
int H=650;

// ************ COMUNICACIÓN SERIAL ************
Serial Port;
boolean found;
IntList buf1, buf2;
byte con1, con2, con3, con4;

int buffer;

// ************ PINTAR GRID ************
int estado = 1, lastx = 40, lasty = 600, posx = 40, posy, increm = 50; 

// ************ BRÚJULA ************
float Azimuth; 
float Bank; // PARA QUE LA BRUJULA SE MUEVA, POR AHORA. BORRAR
float Pitch; // PARA QUE LA BRUJULA SE MUEVA, POR AHORA. BORRAR
PVector v1, v2; // PARA QUE LA BRUJULA SE MUEVA, POR AHORA. BORRAR
float CompassMagnificationFactor=0.6; 
float SpanAngle=120; 
int NumberOfScaleMajorDivisions; 
int NumberOfScaleMinorDivisions; 

// ************ TERMÓMETRO ************
float ThermometerMagnificationFactor=0.9;

boolean sismo; // PARA SIMULAR UN SISMO, POR AHORA. BORRAR

//   ASCII: + 43, - 45

void setup()
{
    size(800,650);  // TAMAÑO DE VENTANA GRÁFICA.
    //println(Serial.list());
    Port = new Serial(this, Serial.list()[0], 115200);
    Port.buffer(3); // DEBE SER DE TAMAÑO 5 PARA 2 ANALÓGICOS.
    buf1 = new IntList();
    buf2 = new IntList();
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
    
    thermometer();
    GetDegValue();
    Compass(); 
        
    // PARA PINTAR ANALÓGICO 1.
    //if(buf1.size()>=40){      // Tamaño de la lista para comenzar a pintar.
    
      
      /*if(posx < 800){
        posy = buf1.remove(0);   // Obtiene el primer valor de la lista y lo elimina de esta.
        if(posx == 40){    
          //stroke(255);
          //line(lastx, lasty, posx, posy);
          lastx = posx;
          lasty = posy;
          posx += increm;
        } 
        else {
          stroke(0,100,255);
          line(lastx, lasty, posx, posy);
          lastx = posx;
          lasty = posy;
          posx += increm;
        }
        // pintar = false
      } // if() 2
      else {
        posx = 40;
        lastx = 40;
        lasty= 600;
        background(0);
        grid();
        buf1.clear();            // Se vacia la lista.
      } // else */
    //} // if() 1
    
    // PARA PINTAR ANALÓGICO 2.
    /*
    if(buf2.size()>=20){
      if(posx < 840){
        posy = buf1.remove(0);
        line(lastx, lasty, posx, posy);
        lastx = posx;
        lasty = posy;
        posx += increm;
      } else {
        posx = 0;
        lastx = 0;
        lasty= 620;
        background(255);
        buf1.clear();
      }
    }
    */
} // draw()

// Loop infinito.
void serialEvent(Serial Port){
  byte[] in = new byte[3];   // Arreglo de bytes de entrada. DEBE SER DE TAMAÑO 5 PARA DOS ANALÓGICOS.
  Port.readBytes(in);        // Leer paquete de bytes de entrada.
  
  for(int i=0;i<3;i++){   // Localizar la cabecera. CAMBIAR A 5 PARA DOS ANALÓGICOS.
    if(in[i] == -14){   // int8 -14 = HEX F2.
      found = true;  // En caso de haber sido encontrada la cabecera.
    } //if() 2
    if(found){
      switch (estado){
        case 1:           // Parados en la cabecera.
          estado = 2;
          break;
        
        case 2:           // Parados en Byte 1 de Analógico 1.
          con1 = in[i];   // Se obtiene Byte 1.
          //print("Byte 1: ");
          //println(con1);
          // decodificar digitales 1 y 2
          estado = 3;
          break;
          
        case 3:           // Parados en Byte 2 de Analógico 1.
          con2 = in[i];   // Se obtiene Byte 2.
          //print("Byte 2: ");
          //println(con2);
          buffer=decode(con1,con2);
          print("Tiempo1: ");
          println(buffer);
          buf1.append(buffer); // Guardar decodificación de valores en la lista de analógico 1.
          estado = 1;
          break;
          
        case 4:           // Parados en Byte 1 de Analógico 2.
          con3 = in[i];   // Se obtiene Byte 3.
          // decodificar digitales 3 y 4
          estado = 5;
          break;
          
        case 5:           // Parados en Byte 2 de Analógico 2.
          con4 = in[i];   // Se obtiene Byte 4.
          buf2.append(decode(con2,con3)); // Guardar decodificación de valores en la lista de analógico 2.
          estado = 1;
          break;
      } // switch()    
    } // if()

  } // loop for()
  //println(in);
}  // serialEvent();

// INTERRUPCIONES POR TECLADO
void keyPressed() {
  if (key == '+') {    // Zoom in.
    if(increm < 800){
      increm += 20;     // Se aumenta el desplazamiento en x.
    }
  }
  if (key == '-') {    // Zoom out.
    if(increm > 0){
      increm -= 20;     // Se disminuye el desplazamiento en x.
      if(increm == 0){
        text("Zoom out no disponible",500,10);
        increm = 20;
      }      
    }
  }
  if(key == ' '){
    sismo=true;
  }  
} // keyPressed

// Decodificar protocolo.
int decode(byte con1, byte con2){
  int aux1, aux2, aux3, aux4, code;
  
  aux1 = con1 & 0x1F;
  aux2 = con2 << 1;
  aux3 = aux1 << 8;
  aux4 = aux2 & 0x00FF;
  aux4 = aux3 | aux4;
  code = aux4 >> 1;
  
  //code = (int)map(code,0,4096,580,60);
  //println(code);
  return code;
} // decode()

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
    text("HA OCURRIDO UN SISMO",160,620);
    
    sismo = false;
  } 
}

// ************ PINTAR GRID ************
void grid(){
  float x = 40, y = 60;
  
  stroke(255);
  
  while(x < width){
    float i = 3.3, m = 60;
    text("SEÑAL DE ENTRADA", 350, 50);
    while(m <= 580){
    text(i, 5, m);
      i = i - 0.253846;
      m = m + 40;
    }
    line(x, 60, x, height-40);
    x = x + 40;    
  }
  
  while(y < height){
    line(40, y, width-40, y);
    y = y + 40;    
  }  
}

// ************ BRÚJULA ************

void GetDegValue()
{
  v2= new PVector(); 
  v1= new PVector(W/2, H/2); 
  v2.x=mouseX; 
  v2.y=mouseY; 
  Bank = PVector.angleBetween(v1, v2); 
  Pitch=mouseY-H/2; 
  Azimuth=(180/PI*10*Bank)%360; // ************ VALOR DE LA DIRECCIÓN ************
}  

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
  CompassPointer(); 
  showDegreesB(); 
}

void CompassPointer() 
{ 
  rotate(PI+radians(Azimuth));  
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
  rotate(-PI-radians(Azimuth)); 
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
  int Azimuth1=round(Azimuth); 
  textAlign(CORNER); 
  textSize(35); 
  fill(255); 
  text("Degrees:  "+Azimuth1+"°", 90, 477, 500, 60); 
  text("Wind Speed: "+Azimuth1+" m/s", 90, 520, 500, 60);
}

// ************ TERMOMETRO ************

void thermometer()
{
 int i;
 int N=round(Azimuth);   // VALOR DE 0 A 380.
 scale(ThermometerMagnificationFactor); 

 //fill background in gray
 fill (120,120,120);

 //build thermostat
 rectMode(CORNER);
 rect(680, 60, 70, 392);
 ellipse (715, 500, 120, 120);
  
 //build quicksilver reservoir
 fill(0, 0, 100);
 ellipse (715, 500, 100, 100);
 rect(690,450,50,10); // RELLENO
 
 //quicksilver
 rect(690, 70+N, 50, 380-N);
 
 fill(0);
 for(i=1;i<=13;i++){
   rect(700,(i*30+40),40,3); // RELLENO
 }

 ShowDegreesT();
 //define stroke
 //stroke (255,0,0);
 //strokeWeight(2);
  
}

void ShowDegreesT() 
{ 
  int Azimuth1=round(Azimuth); 
  textAlign(CORNER);   
  textSize(21); 
  fill(255); 
  text("Degrees:  "+Azimuth1+"°C", 600, 575, 500, 60); 
}
  
