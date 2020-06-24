## Reference
Read and Write Audio Files, https://www.mathworks.com/help/matlab/import_export/read-and-get-information-about-audio-files.html

# Loading from a sample data
>> load handel.mat

### Check the loaded variables: Fs and y
handel.mat consists of Fs and y.
>> Fs

Fs =

        8192

>> plot(y)

### Check the loaded variables by listening to them.
>> sound(y,Fs)

This is a 8 second music by Handel. A choir sings "Hallelujah" 5 times with accompany of a symphony.

## Write y to a wav file
>> audiowrite('handel.wav',y,Fs)

### Supported audio file formats
WAV, OGG, FLAC,MPEG-4 AAC

### Delete y and Fs to call them later.
>> clear y Fs

## Read from a wav file
>> [y,Fs] = audioread('handel.wav');

### Check the loaded variables: Fs and y
>> Fs

Fs =

        8192
>> t = 0:seconds(1/Fs):seconds(info.Duration);
>> t = t(1:end-1);
>> plot(t,y)
>> xlabel('Time')
>> ylabel('Audio Signal')

### Check the information about the audio file
>> info = audioinfo('handel.wav')

info = 

  struct with fields:

             Filename: '/usr/local/MATLAB/R2019a/bin/handel.wav'
    CompressionMethod: 'Uncompressed'
          NumChannels: 1
           SampleRate: 8192
         TotalSamples: 73113
             Duration: 8.9249
                Title: []
              Comment: []
               Artist: []
        BitsPerSample: 16

>> 
