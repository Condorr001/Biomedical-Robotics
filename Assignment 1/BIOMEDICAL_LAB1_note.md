# BIOMEDICAL LAB1.

1. *Load the dataset:*

```matlab
load ES1_emg.mat
```

I load a struct 1x1.

*2. Filter the raw EMG signal (band pass filter, 30-450 Hz). It's recommended to use an FIR filter. To compensate for the phase delay, utilize the “filtfilt” function:*

```matlab
Fs = 2000 
f1 = 30 
f2 = 450
n = 50 % order of the filter
time_axis = (0:length(Es1_emg.matrix(:,1))-1)/Fs;
```

In time axis I take all the samples and I divide by the frequency: I obtain ms.
Then I normalize the frequencies by Nyquist frequency:

```matlab
w_p = [ f1 f2 ] / (Fs/2)
```

<mark>**Nyquist Theorem:** </mark>states the minimum frequency to campionate an analogic signal without losing information. The signal should be band limited. 
The minimum frequency   >= 2*Fmax.

So, I can create the the **band pass filter** and apply it:

```matlab
bpfilt = fir1(n, w_p)
y_filtered = filtfilt(bpfilt,1, Es1_emg.matrix(:,1);
```

<mark>Why n is so?</mark> 

3. *Rectify the signal:*

```matlab
y_rectified = abs(y_filtered)
```

<mark>Rectify the signal</mark> means

4. Compute the envelope  (low pass filter 3-6 Hz):
   I create the **low pass filter** with its parameters

```matlab
lpf_order = 4;
lpf_cutoff = 4;
lpf_cutoff_norm = lpf_cutoff / (Fs/2);
[num, denom] = butter(lpf_order, lpf_cutoff_norm);
```

I apply the filter to the signal:

```matlab
envelope = filtfilt(num, denom, y_rectified);
```

4. *Down-sample the signal*:
   I have to find the optimal downscaling factor and check if it satisfies Nyquist requirement.

```matlab
div_factor = 2;
f_max = 450;
new_fs = Fs/div_factor;


if new_fs > 2*f_max
    y_ds = downsample(evelope, div_factor);
end 
```

<mark>Why?</mark>

## Plot:

1. *Raw EMG signal overlaid with the filtered signal, plotted in a different color*

```matlab
figure;
subplot(3, 1, 1);
plot(time_axis, Es1_emg.matrix(:, 1), 'b', time_axis, y_filtered, 'r');
title('Raw EMG (b) vs Filtered Signal with BPF (r)');
xlabel('Sample Index');
xlim([0 65])
ylabel('Amplitude');
```

2. *Rectified EMG signal overlaid with the envelope, plotted in a different color.*

```matlab
normalized_evelope = envelope/max(envelope);
subplot(3, 1, 2);
plot(time_axis, y_rectified, 'b', time_axis, envelope, 'r');
title('Rectified signal vs envelope');
xlabel('Sample Index');
xlim([0 65])
ylabel('Amplitude');


```

3. *Movement signal overlaid with the envelope signal*
   In this case I want to plot also the movement signal, so the acceleration. We have the accelerations in x, y, z axis; for this reason I compute the squared norm and I compute the final vector of them. 

```matlab
% I extract the accelerations
accelerations = Es1_emg.matrix(:,2:4);
normalized_accelerations = sqrt((accelerations(:,1).^2)  + 
                                (accelerations(:,2).^2)) +
                                (accelerations(:,3).^2)  ;
```

For plotting I have also to rescale the time axis:

```matlab
time_envelope = (0:length(envelope)-1) / Fs;
time_ds = downsample(time_envelope, div_factor);
```

Then I can plot:

```matlab
subplot(3, 1, 3);
plot(time_axis, normalized_acceleration-max(normalized_accelerations), 'b', time_ds, y_ds/max(y_ds), 'r');
xlabel('Time (ms)');
ylabel('Signal');
xlim([0 65])
title('Movement Signal and Envelope');
```

<mark>Why - ?</mark>


















