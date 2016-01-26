clear all;
clc;
close all;

load 'shock.txt';
density = zeros(size(shock,1));
pressure = zeros(size(shock,1));
x_coordinate = zeros(size(shock,1));
energy = zeros(size(shock,1));
velocity = zeros(size(shock,1));
for i = 1:size(shock,1)
    x_coordinate(i) = shock(i,1);
    pressure(i) = shock(i,2);
    density(i) = shock(i,3);
    velocity(i) = shock(i,4);
    energy(i) = shock(i,5);
end
figure(4);
subplot(2,2,1);
plot(x_coordinate,pressure);
xlabel('x');
ylabel('pressure');

subplot(2,2,2);
plot(x_coordinate,density);
xlabel('x');
ylabel('density');

subplot(2,2,3);
plot(x_coordinate,velocity);
xlabel('x');
ylabel('velocity');

subplot(2,2,4);
plot(x_coordinate,energy);
xlabel('x');
ylabel('energy');

suptitle('Shock Tube');