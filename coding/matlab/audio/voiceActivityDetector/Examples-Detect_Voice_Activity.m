% voiceActivityDetector/Examples-Detect_Voice_Activity.m
% https://www.mathworks.com/help/audio/ref/voiceactivitydetector-system-object.html

% fileReader
% Filename: '/usr/local/MATLAB/R2019a/toolbox/audio/samples/Counting-16-44p1-mono-15secs.wav'
%           PlayCount: 1
%     SamplesPerFrame: 1024
%      OutputDataType: 'double'
%          SampleRate: 44100
%           ReadRange: [1 Inf]

% VAD
%                    InputDomain: 'Time'
%                         Window: 'Hann'
%                      FFTLength: []
%     SilenceToSpeechProbability: 0.2000
%     SpeechToSilenceProbability: 0.1000

% scope
%             NumInputPorts: 2
%                SampleRate: 44100
%            TimeSpanSource: 'Property'
%                  TimeSpan: 3
%     TimeSpanOverrunAction: 'Scroll'
%               AxesScaling: 'Manual'

% deviceWriter
%         Device: 'Default'
%     SampleRate: 44100

clear all; close all;
fileReader = dsp.AudioFileReader('Counting-16-44p1-mono-15secs.wav');
release(fileReader);

fs = fileReader.SampleRate;
fileReader.SamplesPerFrame = ceil(10e-3*fs);  % Change it from 1024 to 441

VAD = voiceActivityDetector;
scope = dsp.TimeScope( ...
    'NumInputPorts',2, ...
    'SampleRate',fs,...
    'TimeSpan',3,...
    'BufferLength',3*fs,...
    'YLimits',[-1.5 1.5],...
    'TimeSpanOverrunAction','Scroll',...
    'ShowLegend',true,...
    'ChannelNames',{'Audio', 'Probability of speech presence'} );
deviceWriter = audioDeviceWriter('SampleRate',fs);

while ~isDone(fileReader)
    audioIn = fileReader();
    probability = VAD( audioIn );
    scope( audioIn, probability*ones( fileReader.SamplesPerFrame,1) )
    deviceWriter( audioIn );
end
