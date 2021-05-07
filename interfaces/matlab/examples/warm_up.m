%% Run a simple warm up problem
% Clean up and load libraries
clear all; clc; close all; 

% Simple QP 
Q = [2 0; 0 2];
g = [-2; -2];
L = [1 0];
R = [0 1];

% Run solver
LCQParrot(Q, g, L, R);

% Algorithm parameters
params.x0 = [1; 1];
params.R0 = 1;
params.storeSteps = true;
params.useInitializationStruct = false;
params.solveZeroPenaltyFirst = false;
params.printStats = true;
params.penaltyUpdater = @(R) R*2;

% Direct call (for valgrind debug)
% LCQPanther([2 0; 0 2], [-2; -2], [1 0], [0 1]);
