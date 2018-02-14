import processing.serial.*;

Serial Port;
boolean found;
IntList buf1, buf2;
int estado = 1, lastx = 40, lasty = 600, posx = 40, posy, increm = 50; 
byte con1, con2, con3, con4;
//   ASCII: + 43, - 45

void setup(){
    size(840,620);  // TAMAÑO DE VENTANA GRÁFICA.
    //println(Serial.list());
    Port = new Serial(this, Serial.list()[0], 115200);
    Port.buffer(3); // DEBE SER DE TAMAÑO 5 PARA 2 ANALÓGICOS.
    buf1 = new IntList();
    buf2 = new IntList();
    background(0);
    grid();
} // setup()

void draw(){
    
    // PARA PINTAR ANALÓGICO 1.
    if(buf1.size()>=40){         // Tamaño de la lista para comenzar a pintar.
      if(posx < 800){
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
      } // if() 2
      else {
        posx = 40;
        lastx = 40;
        lasty= 600;
        background(0);
        grid();
        buf1.clear();            // Se vacia la lista.
      } // else 
    } // if() 1
    
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
          // decodificar digitales 1 y 2
          estado = 3;
          //println(hex(con1));
          break;
          
        case 3:           // Parados en Byte 2 de Analógico 1.
          con2 = in[i];   // Se obtiene Byte 2.
          //println(hex(con2));
          buf1.append(decode(con1,con2)); // Guardar decodificación de valores en la lista de analógico 1.
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

// Interrupciones por teclado.
void keyPressed() {
  if (key == '+') {    // Zoom in.
    if(increm < 100){
      increm += 5;     // Se aumenta el desplazamiento en x.
    }
  }
  if (key == '-') {    // Zoom out.
    if(increm > 0){
      increm -= 5;     // Se disminuye el desplazamiento en x.
    }
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
  
  code = (int)map(code,0,4096,580,60);
  //println(code);
  return code;
} // decode()

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