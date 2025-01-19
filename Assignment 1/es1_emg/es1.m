clear;
close all;
clc;

% Load the EMG data
load ES1_emg.mat

%% Data

% Sampling frequency
Fs = 2000;
% Low cutoff frequency
f1 = 30; 
% High cutoff frequency
f2 = 450;

% We take the data of the EMG
EMG_data =  Es1_emg.matrix(:,1);

%% Design the FIR bandpass filter using fir1

% Filter order
n = 50;
% Nyquist for the computation of w_n
w_n = [f1, f2]/(Fs/2);
% FIR bandpass filter coefficients
b = fir1(n, w_n, 'bandpass'); 

% Filter the data using filtfilt for zero-phase filtering
filtered_data = filtfilt(b, 1, EMG_data);

% Create time vector based on the sample rate
time = (0:length(EMG_data)-1) / Fs;
% Rectified data
rectified_data = abs(filtered_data);

%% Butterworth filter

% Cutoff of the filter
lp_cutoff_norm = 3/(Fs/2);
% IIR butterworth filter
[a, b] = butter(4, lp_cutoff_norm);
% Filter the data using filtfilt to get the envelope
envelope_data = filtfilt(a, b, rectified_data);

%% Downsampling

% Check if the downscaling factor satisfies the Nyquist requirement
downcscaling_factor = 2;
new_fs = Fs / downcscaling_factor;

if new_fs > 2*f2
    data_final = downsample(envelope_data, downcscaling_factor);
end

% Normalization
data_final = data_final./max(data_final);

%% Extracting accelerations and computing their norm

X_accel = Es1_emg.matrix(:,2);
Y_accel = Es1_emg.matrix(:,3);
Z_accel = Es1_emg.matrix(:,4);

norm_accelerations = sqrt(X_accel.^2 + Y_accel.^2 + Z_accel.^2);

%% Plotting the results

% Plotting the data before and after filtering
figure;
subplot(3, 1, 1);
plot(time, EMG_data);
hold on; plot(time, filtered_data);
title('Raw EMG Data vs Filtered EMG data');
xlabel('Time (s)');
ylabel('Amplitude (mV)');
legend('Raw EMG data', 'Filtered EMG data')
grid on;
xlim([0, 65])

subplot(3, 1, 2);
plot(time, rectified_data);
hold on; plot(time, envelope_data, 'LineWidth', 1);
title('Rectified vs Envelope');
xlabel('Time (s)');
ylabel('Amplitude (mV)');
legend('Rectified', 'Envelope')
grid on;
xlim([0, 65])

subplot(3, 1, 3);
plot(time, envelope_data/max(envelope_data), 'LineWidth', 1);
hold on; plot(time, norm_accelerations - max(norm_accelerations), 'LineWidth', 1);
title('Envelope vs Accelerations');
xlabel('Time (s)');
ylabel('Signals comparison');
xlim([0, 65])
legend('Normalized envelope', 'Accelerations')
grid on;