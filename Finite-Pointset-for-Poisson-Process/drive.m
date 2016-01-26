close all;
clear all;
clc;

load 'Point_fin.txt';
load 'solver.txt';

plot3(Point_fin(:,2),Point_fin(:,3),solver,'*');