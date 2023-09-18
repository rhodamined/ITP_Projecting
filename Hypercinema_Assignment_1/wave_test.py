# wav file manipulation tutorial: https://learnpython.com/blog/plot-waveform-in-python/
import wave

# what we learned here is that 24bit sound is too hefty to plot using this method 
# I am not sure what exactly the data we are even planning is....
# there's probably an easy math transformation to make it less hefty -- but I do not know how lol

#file_name = 'countman.wav'
#file_name = 'HC-RecTest_2a_16bit.wav'
#file_name = 'HC-RecTest_3_16bit.wav'
file_name = 'HC-RecTest_4_16bit.wav'
print('File name:', file_name)

wav_obj =  wave.open(file_name, 'rb')
sample_freq = wav_obj.getframerate()  # sample rate
n_samples = wav_obj.getnframes() # total number of audio samples
t_audio = n_samples/sample_freq # length of wav file in seconds = total samples / sample rate
wav_params = wav_obj.getparams() # named tuple -- needed bc of BIT DEPTH ARGH
wav_bd = wav_obj.getsampwidth() # sample width -- 2 = 16bit, 3 = 24bit >:(

# print results
print('t_audio', t_audio)
print('params:', wav_params)
print('sampwidth', wav_bd)

# readframes() takes 1 argument 'n', which defines the # of frames to read
# this returns a 'bytes' object, with which we must use numpy
signal_wave = wav_obj.readframes(n_samples)

print('Length of signal_wave:', len(signal_wave))
#print(signal_wave)
# print ('signal_wave', signal_wave)  <-- don't print this, it encodes tooo much. or do, it's fun.

import numpy as np

# the following returns all data as a 1-D array
signal_array = np.frombuffer(signal_wave, dtype=np.int16)

# slice into left and right channels
# python slicing: https://www.freecodecamp.org/news/python-slicing-how-to-slice-an-array/
# python slicing syntax: [start:end:step]
# so [0::2] indicates start at 0; end at END; step 2, which would get all Ls
l_channel = signal_array[0::wav_bd]
r_channel = signal_array[1::wav_bd]
print ('Length of signal_array:',len(signal_array))
print ('Length of l_channel:', len(l_channel))

for i in range(0,len(l_channel)):
  print(l_channel[i])
  if i == 300:
    break

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
print ('Length of l_channel:', len(l_channel))

import matplotlib.pyplot as plt

plt.figure(figsize=(15,5))
plt.plot(times, l_channel)
plt.title('Left Channel')
plt.ylabel('Signal Value')
plt.xlabel('Time (s)')
plt.xlim(0, t_audio)
plt.show()

# define local max -- max 1
# -- keep highest value
# define local min
# -- needs to be defined by when numbers begin trending upwards again -- need a max 2
# compare local min to max 1 -- 
# -- if local min is less than 25% different from max 1 -- 
# 