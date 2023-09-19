# follow-up to wave_test.py
# find peaks in addition to plotting wave forms
# wav file manipulation tutorial: https://learnpython.com/blog/plot-waveform-in-python/
# peak finding tutorial: https://stackoverflow.com/questions/1713335/peak-finding-algorithm-for-python-scipy
import wave

#file_name = '230918_Weber_1_Denoised.wav'
# file_name = '230918_Weber&Iris_1_Denoised.wav'
# file_name = '230918_Weber&Iris_1_Denoised_Compressed.wav'
# file_name = '230918_Weber_Iso_1.wav'
file_name = '230918_Iris_Iso_1.wav'
print('File name:', file_name)

wav_obj =  wave.open(file_name, 'rb')
sample_freq = wav_obj.getframerate()  # sample rate
n_samples = wav_obj.getnframes() # total number of audio samples
t_audio = n_samples/sample_freq # length of wav file in seconds = total samples / sample rate
wav_params = wav_obj.getparams() # named tuple -- needed bc of BIT DEPTH ARGH
wav_bd = wav_obj.getsampwidth() # sample width -- 2 = 16bit, 3 = 24bit >:(

signal_wave = wav_obj.readframes(n_samples)

# ---- USE NUMPY ----
# -- plot frequency
import numpy as np

# the following returns all data as a 1-D array
signal_array = np.frombuffer(signal_wave, dtype=np.int16)

# slice into left and right channels
# python slicing: https://www.freecodecamp.org/news/python-slicing-how-to-slice-an-array/
# python slicing syntax: [start:end:step]
# so [0::2] indicates start at 0; end at END; step 2, which would get all Ls
l_channel = signal_array[0::wav_bd]
r_channel = signal_array[1::wav_bd]

# array of times at which a sample is taken == length in seconds of track / # of samples
# numpy linspace https://numpy.org/doc/stable/reference/generated/numpy.linspace.html
# (start, stop, num), returns num evenly spaced samples over interval
# (start at 0, stop at time=length of track, num=#samples)
times = np.linspace(0, n_samples/sample_freq, num=n_samples)

#reduce size by factor to make matplot happier
div_factor = 10 # looked at factors up to 100 -- 10 looks like it preserves enough data
times = times[0::div_factor]
l_channel = l_channel[0::div_factor]
r_channel = r_channel[0::div_factor]
print ('Length of l_channel, post div_factor:', len(l_channel))


# ---- USE MATPLOTLIB and SCIPY
# ---- to PLOT WAVEFORMS -- matplotlib -- thank god
# ---- and to IDENTIFY PEAKS! -- scipy -- very nifty
# code adapted from: https://stackoverflow.com/questions/1713335/peak-finding-algorithm-for-python-scipy

import matplotlib.pyplot as plt
from scipy.signal import find_peaks
  
# Compare 4 different peak paths, very helpful for fitting to peaks
x = l_channel
peaks, _ = find_peaks(x, distance=1000, prominence = 500)          # prominence parameter too close
peaks2, _ = find_peaks(x, distance=1000, prominence = 1000)         # this one looks the best for countman.wav
peaks3, _ = find_peaks(x, distance=1000, prominence = 1500)        # this one bypasses peaks i'd like to keep
peaks4, _ = find_peaks(x, distance=1000, prominence = 2000)        # ditto
plt.subplot(2, 2, 1) 
plt.plot(times[peaks], x[peaks], "xr"); plt.plot(times, x); plt.legend(['p=500'])
plt.subplot(2, 2, 2)
plt.plot(times[peaks2], x[peaks2], "ob"); plt.plot(times, x); plt.legend(['p=1000'])
plt.subplot(2, 2, 3)
plt.plot(times[peaks3], x[peaks3], "vg"); plt.plot(times, x); plt.legend(['p=1500'])
plt.subplot(2, 2, 4)
plt.plot(times[peaks4], x[peaks4], "xk"); plt.plot(times, x); plt.legend(['p=2000'])
plt.show()

# just one at a time
# x = l_channel
# peaks, _ = find_peaks(x, distance=500, prominence = 1000)          # prominence parameter too close
# plt.plot(times[peaks], x[peaks], "xr"); plt.plot(times, x); plt.legend(['p=1000'])
# plt.show()


# ---- PRINT OUT HARD VALUES AS ARDUINO CODE

# last_ts = 0                                     # track the last value
# low_delay = 20
# for i in times[peaks]:                          # if using compare-4 -- make sure using correct array
#     curr_ts = int(i*1000)                       # times is in SECONDS -- convert to MILLISECONDS
#     low_time = curr_ts - last_ts - low_delay     
#     if low_time >= low_delay:                   # catch any close peaks that might have come through...
#         print("delay(" + str(low_time) + ");")  # cast to str for python print concatenation, python won't concat ints
#         print("digitalWrite(13, HIGH);  // "+str(i))    # comment timestamp in seconds to help manual analysis
#         print("delay("+str(low_delay)+")")                     # hardcoded value of 40ms between HIGH and LOW, which is a pretty quick strike
#         print("digitalWrite(13, LOW);")
#         last_ts = curr_ts
        
        
# ---- WRITE TO FILE--  HARD VALUES AS ARDUINO CODE

write = 0

if write != 0:
    
    f = open("weber.txt", "a")
    last_ts = 0                                     # track the last value
    low_delay = 20
    for i in times[peaks]:                          # if using compare-4 -- make sure using correct array
        curr_ts = int(i*1000)                       # times is in SECONDS -- convert to MILLISECONDS
        low_time = curr_ts - last_ts - low_delay     
        if low_time >= low_delay:                   # catch any close peaks that might have come through...
            f.write("delay(" + str(low_time) + ");\n")  # cast to str for python print concatenation, python won't concat ints
            f.write("digitalWrite(13, HIGH);  // "+str(i)+"\n")    # comment timestamp in seconds to help manual analysis
            f.write("delay("+str(low_delay)+");\n")                     # hardcoded value of 40ms between HIGH and LOW, which is a pretty quick strike
            f.write("digitalWrite(13, LOW);\n")
            last_ts = curr_ts
    f.close()
    print('write complete')
