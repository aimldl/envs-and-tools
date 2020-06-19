% read_in_audio_and_plot_it.m

% Source: Speaker Identification Using Pitch and MFCC
%   https://www.mathworks.com/help/audio/examples/speaker-identification-using-pitch-and-mfcc.html

% Pitch

clear all; close all;
dir_root = '/home/aimldl/Dropbox/matlab/2-tutorials/8_speaker_identification_using_pitch_and_mfcc';
cd( dir_root );

% Read in the file counting from 1 to 16.
% fs is 44100Hz
[ audioIn, fs ] = audioread( 'Counting-16-44p1-mono-15secs.wav' );

% Two starts from 110k~135 samples
twoStart = 110e3;
twoStop  = 135e3;

% Get only two and play it to check if it's cut correctly.
audioIn = audioIn( twoStart:twoStop );
sound( audioIn, fs);

% Compute time to plot in figure.
twoStartInSec = twoStart/fs;  %  2.4943
twoStopInSec  = twoStop/fs;    % 3.0612
lengthAudioIn = numel( audioIn);  % 25001
timeVector = linspace( twoStartInSec, twoStopInSec,  lengthAudioIn);
%  ...  Columns 24998 through 25001
%  ...  3.0612    3.0612    3.0612    3.0612

% Plot the audio samples
figure;
plot( timeVector, audioIn);
ylabel( 'Amplitude' );
xlabel('Time (s)');
title( 'Utterance - Two')