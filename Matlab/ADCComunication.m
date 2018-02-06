function [sen] = ADCComunication()

clc
clear all

s = serial('COM3');
set(s,'BaudRate',115200);

fopen(s);

sen=fgetl(s);
sen=unicode2native(sen);

fprintf(s,'*IDN?')
out = fscanf(s);

fclose(s)
delete(s)
clear s

end