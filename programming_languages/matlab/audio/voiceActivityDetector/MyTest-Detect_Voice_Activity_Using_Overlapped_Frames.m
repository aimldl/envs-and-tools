% voiceActivityDetector/MyTest-Detect_Voice_Activity_Using_Overlapped_Frames.m
% https://www.mathworks.com/help/audio/ref/voiceactivitydetector-system-object.html

clear all; close all;
AFR = dsp.AudioFileReader('please_clean_my_room-Aditi.wav');
fs = AFR.SampleRate;

frameSize = ceil(20e-3*fs);
overlapSize = ceil(0.75*frameSize);
hopSize = frameSize - overlapSize;
AFR.SamplesPerFrame = hopSize;

inputBuffer = dsp.AsyncBuffer('Capacity',frameSize);

VAD = voiceActivityDetector('FFTLength',1024);
%VAD = voiceActivityDetector('FFTLength',1024,'Window','Hann','SpeechToSilenceProbability', 0.9, 'SpeechToSilenceProbability',0.4);
%VAD = voiceActivityDetector('FFTLength',512,'Window','Chebyshev','SpeechToSilenceProbability', 0.9, 'SpeechToSilenceProbability',0.4);
%VAD = voiceActivityDetector('FFTLength',1024,'Window','Flat Top','SpeechToSilenceProbability', 0.9, 'SpeechToSilenceProbability',0.4);
%VAD = voiceActivityDetector('FFTLength',1024,'Window','Hamming','SpeechToSilenceProbability', 0.9, 'SpeechToSilenceProbability',0.4);
%VAD = voiceActivityDetector('FFTLength',1024,'Window','Kaiser','SpeechToSilenceProbability', 0.9, 'SpeechToSilenceProbability',0.4);
%VAD = voiceActivityDetector('FFTLength',1024,'Window','Rectangular','SpeechToSilenceProbability', 0.9, 'SpeechToSilenceProbability',0.4);

scope = dsp.TimeScope( ...
    'NumInputPorts',2, ...
    'SampleRate',fs,...
    'TimeSpan',1.4,...
    'BufferLength',3*fs,...
    'YLimits',[-1.5 1.5],...
    'TimeSpanOverrunAction','Scroll',...
    'ShowLegend',true,...
    'ChannelNames',{'Audio', 'Probability of speech presence'} );
player = audioDeviceWriter('SampleRate',fs);

pHold = ones(hopSize,1);
while ~isDone(AFR)
    x = AFR();
    n = write( inputBuffer, x );
    
    overlappedInput = read(inputBuffer,frameSize,overlapSize);
    p = VAD(overlappedInput);
    
    pHold(end) = p;
    scope(x,pHold)
    player(x);
    pHold(:) = p;
end
release( player )
