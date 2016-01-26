clear all;
clc;
close all;

load 'Points.txt';
figure;
hold on;
for i = 1:size(Points,1)
if (Points(i,3) == 1)
plot(Points(i,1),Points(i,2),'*');
else
    plot(Points(i,1),Points(i,2),'+');
end
end
