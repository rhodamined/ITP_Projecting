# follow-up to wave_plot.py
# generates usable output for the project

# --- REFERENCES --- #
# wav file manipulation tutorial: https://learnpython.com/blog/plot-waveform-in-python/
# peak finding tutorial: https://stackoverflow.com/questions/1713335/peak-finding-algorithm-for-python-scipy


# --- Modules --- #
import wave
import numpy as np
import matplotlib.pyplot as plt
from scipy.signal import find_peaks

# --- Open File - BACKGROUND INFO --- #
# One sound file was recorded by two speakers, Iris and Weber, who never speak simultaneously.
# Iris spoke Chinese and Weber spoke English.
# Because of their volumes and speech cadences were different, a single find_peaks function does not satisfactorily analyze both their speech patterns
# In Premiere, I separated each of their voices into their own track. Each track is the same length.
# Here we open one file at a time to analyze.

# --- Open File - IRIS --- #
file_name = '230918_Iris_Iso_1.wav'
print('Open file name:', file_name)

wav_obj_iris =  wave.open(file_name, 'rb')
sample_freq_iris = wav_obj_iris.getframerate()  # sample rate
n_samples_iris = wav_obj_iris.getnframes() # total number of audio samples
t_audio_iris = n_samples_iris/sample_freq_iris # length of wav file in seconds = total samples / sample rate
wav_bd_iris = wav_obj_iris.getsampwidth() # sample width -- 2 = 16bit, 3 = 24bit >:(
signal_wave_iris = wav_obj_iris.readframes(n_samples_iris)

signal_array_iris = np.frombuffer(signal_wave_iris, dtype=np.int16)
l_channel_iris = signal_array_iris[0::wav_bd_iris] # only using 1 channel for this project

print ('Done processing Iris')

# --- Open File - WEBER --- #
file_name = '230918_Weber_Iso_1.wav'
print('Open file name:', file_name)

wav_obj_weber =  wave.open(file_name, 'rb')
sample_freq_weber = wav_obj_weber.getframerate()  # sample rate
n_samples_weber = wav_obj_weber.getnframes() # total number of audio samples
t_audio_weber = n_samples_weber/sample_freq_weber # length of wav file in seconds = total samples / sample rate
wav_bd_weber = wav_obj_weber.getsampwidth() # sample width -- 2 = 16bit, 3 = 24bit >:(
signal_wave_weber = wav_obj_weber.readframes(n_samples_weber)

signal_array_weber = np.frombuffer(signal_wave_weber, dtype=np.int16)
l_channel_weber = signal_array_weber[0::wav_bd_weber] # only using 1 channel for this project

print ('Done processing Weber')

# --- Data Manipulation --- #
# use numpy functions to get a timestamp for each sample
times_iris = np.linspace(0, n_samples_iris/sample_freq_iris, num=n_samples_iris)
times_weber = np.linspace(0, n_samples_weber/sample_freq_weber, num=n_samples_weber)

# times should theoretically all be the same for Iris and Weber because the track lengths are the same
print('times iris', len(times_iris)) # yes it's the same
print('times weber', len(times_weber))

#reduce size by factor to make matplot happier
div_factor = 10 # looked at factors up to 100 -- 10 looks like it preserves enough data
times_iris = times_iris[0::div_factor]
times_weber = times_weber[0::div_factor]
l_channel_iris = l_channel_iris[0::div_factor]
l_channel_weber = l_channel_weber[0::div_factor]

# --- Calculate Peaks --- #
# use scipy function find_peaks to 
# values for distance, prominance were chosen based on visual analysis of the waveforms when plotted
# most of the futzing around finding a reasonable fit was done in wav_plot.py, which plots 4 subplots in comparison
x = l_channel_weber # weber first speaker
y = l_channel_iris  # iris second speaker
peaks_w, _ = find_peaks(x, distance=1000, prominence = 1000)  # weber
peaks_i, _ = find_peaks(y, distance=1000, prominence = 500)  # iris

# the content of peaks_i and peaks_w are the frame #s of the locations of peaks
print('peaks i', peaks_i)
print('peaks w', peaks_w)

# plot weber
plt.subplot(3, 1, 1) 
plt.plot(times_weber[peaks_w], x[peaks_w], "ob"); plt.plot(times_weber, x); plt.legend(['WEBER p=1000'])

# plot iris
plt.subplot(3, 1, 2)
plt.plot(times_iris[peaks_i], y[peaks_i], "xr"); plt.plot(times_iris, y); plt.legend(['IRIS p=500'])

# plot both overlaid
plt.subplot(3, 1, 3)
plt.plot(times_iris, y)
plt.plot(times_weber, x)
plt.plot(times_weber[peaks_w], x[peaks_w], "ob")
plt.plot(times_iris[peaks_i], y[peaks_i], "xr")
plt.legend(['OVERLAID'])

# show figure
plt.show()


# ---- WRITE TO FILE ---- #
# HARD VALUES AS ARDUINO CODE

# combine two arrays
# peaks_all will contain the frame # of all peaks
# To work on: I don't seem to understand how python manipulates arrays
# or even when it's python and when it's numpy 
peaks_all = []
for e in peaks_w:       
    peaks_all.append(e) 
for e in peaks_i:
    peaks_all.append(e)
        
# sort frame #s in ascending order, which organizes it into 'conversation'
peaks_all = np.sort(peaks_all)   
print(peaks_all)

# do the writing
write = 1           # toggle write on/off 0 = OFF

if write != 0:
    
    open("text.txt", "w").close()       # erase any existing text in file
    f = open("text.txt", "a")           # append to file
    
    low_delay = 20                      # the time between pin HIGH and LOW
    last_ts = 0                         # track timestamp of last peak while looping
    peaks_ref = peaks_all               # silly solution when adapting this code to track current element in peaks_all 
    
    for frame in times_iris[peaks_all]:                 # times_iris and times_weber are the same, but should use whichever is longer probably
        curr_ts = int(frame*1000)                       # times is in SECONDS -- convert to MILLISECONDS
        low_time = curr_ts - last_ts - low_delay     
        if low_time >= low_delay:                       # catch any close peaks that might have come through...
            
            # if timestamp is in weber -- PIN 13
            if peaks_ref[0] in peaks_w:

                f.write("delay(" + str(low_time) + ");\n")  # cast to str for python print concatenation, python won't concat ints
                f.write("digitalWrite(13, HIGH);  // "+str(frame)+"\tWEBER\n")    # comment timestamp in seconds; speaker to help manual analysis
                f.write("delay("+str(low_delay)+");\n")                     # hardcoded value of 40ms between HIGH and LOW, which is a pretty quick strike
                f.write("digitalWrite(13, LOW);\n")
                
            # if timestamp is in iris -- PIN 12
            if peaks_ref[0] in peaks_i:
            
                f.write("delay(" + str(low_time) + ");\n")                      # cast to str for python print concatenation, python won't concat ints
                f.write("digitalWrite(12, HIGH);  // "+str(frame)+"\tIRIS\n")   # comment timestamp in seconds; speaker to help manual analysis
                f.write("delay("+str(low_delay)+");\n")                         # hardcoded value of 40ms between HIGH and LOW, which is a pretty quick strike
                f.write("digitalWrite(12, LOW);\n")
                
            last_ts = curr_ts
            peaks_ref = np.delete(peaks_ref, 0) # fastest way i could think to reference itself; self destruct
        
        else:
            f.write("//proximity too close "+str(low_time)+"\n")    # comment an indicator that a line was skipped
        
    f.close()
    print('write complete')
    print('peaks_all length:', len(peaks_all))
    print('peaks_ref length:', len(peaks_ref))