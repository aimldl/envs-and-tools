% detect_pitch_and_plot_the_pitch_contour.m

% Source: Speaker Identification Using Pitch and MFCC
%   https://www.mathworks.com/help/audio/examples/speaker-identification-using-pitch-and-mfcc.html

read_in_audio_and_plot_it;

pD  = audiopluginexample.SpeechPitchDetector;
[~,pitch] = process( pD, audioIn );

figure
subplot( 2,1,1 )
plot( timeVector, audioIn );
axis( [twoStartInSec twoStopInSec -1 1] )
ylabel( 'Amplitude' )
xlabel( 'Time (s)' )
title( 'Utterance - Two' )
grid on

subplot(2,1,2)
plot( timeVector, pitch, '*' )
axis( [twoStartInSec twoStopInSec 80 140] )
ylabel( 'Pitch (Hz)' )
xlabel( 'Time (s)' )
title( 'Pitch Contour - Two' )
grid on