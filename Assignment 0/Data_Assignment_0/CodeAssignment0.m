%% ASSIGNMENT 0
% Valentina Condorelli, Annika Delucchi, Ramona Ferrari, Daniele Rialdi

clearvars;

% 1. Load the datasets: data1.mat, data2.mat, and data3.mat
load('data1.mat');
load('data2.mat');
load('data3.mat');

% 2. Plot each dataset with appropriate labels on the axes.
% 4. Roughly estimate the frequency content of each signal (Hint: Plotting the data in time points,
% rather than samples, might assist you in this task

sampling_rate1 = 2000; % Hz
samples1 = length(data1);
time_vector1 = (0:samples1-1) / sampling_rate1;

sampling_rate2 = 166; % Hz
samples2 = length(data2);
time_vector2 = (0:samples2-1) / sampling_rate2;

sampling_rate3 = 250; % Hz
samples3 = length(data3);
time_vector3 = (0:samples3-1) / sampling_rate3;


% 2000 Hz
% The EMG (Electromyography) is a diagnostic test to evaluate the health and the function of
% muscles and nerves that control them.
figure()
subplot(3,1,1)
plot(time_vector1, data1)
title('EMG - Electromyography')
xlabel 'Time [s]';
ylabel 'Muscle response [µV]';
grid on;

% 166 Hz
% The motion data captures the motion, in this case, of two parts, as it is
% possible to see from two different colours
subplot(3,1,2)
plot(time_vector2, data2)
title('Motion data')
xlabel 'Time [s]';
ylabel 'Joint angular velocity [°/s]';
grid on;

% 250 Hz
% The EEG (Electroencephalogram) is a test measuring electrical activity in the brain.
subplot(3,1,3)
plot(time_vector3, data3/1000)
title('EEG - Electroencephalogram')
xlabel 'Time [s]';
ylabel 'Muscle response [mV]';
grid on;


% 3. Based on your plots, try to determine the type of data you are observing: EEG, EMG, or motion
% data

% Our first approach was to collect data and compare our graphs with the
% examples we could find online. 

%% FIRST PLOT
% The amplitude of the EMG signal at any instant in time is stochastic or random.
% We noticed the mean of the graph was close to 0.


%% SECOND PLOT
% In ablebodied humans, the movement is planned based on the task and the most distal part of the arm; 
% yet, the command starts from the most proximal segment. 
% Following this line of reasoning, the plot shows the angular velocity of shoulder and elbow joints of an arm, 
% which often operates at opposite velocities.

%% THIRD PLOT
% Electroencephalography (EEG) is an efficient modality which helps to acquire brain signals corresponds to various states from the scalp surface area. 
% These signals are generally categorized as delta, theta, alpha, beta and gamma 
% based on signal frequencies ranges from 0.1 Hz to more than 100 Hz.