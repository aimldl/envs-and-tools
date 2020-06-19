% voiceActivityDetector/Examples-Determine_Pitch_Contour_using_pitch_and_voiceActivityDetector.m
% https://www.mathworks.com/help/audio/ref/voiceactivitydetector-system-object.html

% I modified the code slightly to compare the two figures.
% Additionally, I've added the original waveform to compare the two
% figures.
% TODO: 1. Fix the scale of the waveform
% TODO: 2. Add the VAD plot onto the waveform.
% TODO: 3. Compare the cepstral coefficients. i.e. Put all the features
% into one figure.

clear all; close all;
filename = 'Counting-16-44p1-mono-15secs.wav'
[audio, fs] = audioread( filename );

windowLength = round(0.05*fs);      % 50ms frame, windowLength = samplesPerFrame
overlapLength = round(0.04*fs);      % 40ms overlap, overlapLength = samplesPerHop
hopLength = windowLength - overlapLength;  % hopLength = samplesPerOverlap

figure
subplot(3,1,1)
plot(audio)
ylabel('Amplitude')
xlabel('Time (s)')
title(['Waveform from ', filename])
axis([0 length(audio) -1.5 1.5])


subplot(3,1,2)
[f0,loc] = pitch(audio, fs,...
    'WindowLength',windowLength,...
    'OverlapLength',overlapLength,...
    'Range',[50 150], ...
    'MedianFilterLength',3);
plot(loc/fs,f0)
ylabel('Fundamental Frequency (Hz)')
xlabel('Time (s)')
title('Pitch of frames from the full samples')

buffer = dsp.AsyncBuffer( numel(audio) );
write(buffer, audio);
VAD = voiceActivityDetector;

n = 1;
probVector = zeros( numel(loc), 1 );
while buffer.NumUnreadSamples >= hopLength

    % Read the samples from buffer as much as the windowLength
    if n==1
        % If enough samples to read exist and this is at the beginning,
        % read the buffer as much as the window length.
        x = read(buffer,windowLength);
    else
        x = read(buffer,windowLength,overlapLength);
    end
    
    % Given the samples in this window, get the result of VAD
    % or the probability that this frame contains speech.
    probVector(n) = VAD(x);
    n = n+1;
end
% Note n (or n+1) is equal to the total number of windows.

% Delete samples below 0.99 of probability
validIdx = probVector>0.99;
loc(~validIdx) = nan;
f0(~validIdx) = nan;

subplot(3,1,3)
plot(loc/fs,f0,'r')
ylabel('Fundamental Frequency (Hz)')
xlabel('Time(s)')
title('Samples with p>0.99')
