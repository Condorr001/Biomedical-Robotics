clear;
close all;
clc;

% Load the EMG data
load ES2_emg.mat

%% Data
% Sampling frequency
Fs = 1000;
% Low cutoff frequency
f1 = 30;
% High cutoff frequency
f2 = 450;

% Filter order
n = 50; 
% Nyquist for the computation of w_n
w_n = [f1, f2]/(Fs/2);
% Extracting toime vector from struct ES2_emg
time = ES2_emg.time;
% Initializing envelope_matrix
envelope_matrix = zeros(size(time,1), size(ES2_emg.signals,2));

%% Loop to treat the data for all 4 muscles

for i = 1:size(ES2_emg.signals,2)
    % Extracting the data for the muscle in consideration
    EMG_data =  ES2_emg.signals(:,i);
    
    % FIR bandpass filter coefficient
    b = fir1(n, w_n, 'bandpass');
    
    % Filter the data using filtfilt for zero-phase filtering
    filtered_data = filtfilt(b, 1, EMG_data);

    % Rectify the data
    rectified_data = abs(filtered_data);
    % Cutoff of the filter
    lp_cutoff_norm = 4/(Fs/2);
    % IIR butterworth filter
    [a, b] = butter(4, lp_cutoff_norm);
    % Filter the data using filtfilt to get the envelope
    envelope_data = filtfilt(a, b, rectified_data);
    % Matrix of the values of the envelope data normalized
    envelope_matrix(:,i) = (envelope_data - min(envelope_data))./(max(envelope_data) - min(envelope_data));


    % Plotting the data before and after filtering (suggested to be
    % commented to fasten the computations)

    % figure;
    % subplot(2, 1, 1);
    % plot(time, EMG_data);
    % hold on; plot(time, filtered_data);
    % title('Raw EMG Data vs Filtered EMG data');
    % xlabel('Time (s)');
    % ylabel('Amplitude');
    % legend('Raw EMG data', 'Filtered EMG data')
    % grid on;
    % xlim([0, 30])  

    % subplot(2, 1, 2);
    % plot(time, rectified_data);
    % hold on; plot(time, envelope_data, 'LineWidth', 1); 
    % title('Rectified vs Envelope');
    % xlabel('Time (s)');
    % ylabel('Amplitude');
    % legend('Rectified', 'Envelope')
    % grid on;
    % xlim([0, 30])
    % hold off;
end

%% Data interpretation
% 1 Bicep right     --> Est
% 2 Bicep left      --> West
% 3 Trapezius right --> North
% 4 Trapezius left  --> South

% ¡WARNING! Simulink can do 1 simulation and then it freezes in Matlab2024b
% To run multiple simulations it is suggested to close simulink and reopen
% it for every execution.
