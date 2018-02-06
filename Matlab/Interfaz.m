clc
clear all
close all

sensor = ADCComunication();

len=length(sensor);

isensor = uint16(sensor);

sd=isensor(1:2:len-1)*255+isensor(2:2:len);

conver=sd;

t=0:1:length(conver)-1;

plot(conver(1:40),'*'); title('Medición'); xlabel('Tiempo'); ylabel('Voltaje'); grid on;
