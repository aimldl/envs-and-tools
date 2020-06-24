% voiceActivityDetector/MyTest-Frequency-Domain_Voice_Activity_Detection_and_Cepstral_Feature_Extraction.m
% https://www.mathworks.com/help/audio/ref/voiceactivitydetector-system-object.html

% I modified the code slightly to show the TimeScope obtained from the FFT
% results.

clear all; close all;
AFR = dsp.AudioFileReader('please_clean_my_room-Aditi.wav');
fs = AFR.SampleRate;

samplesPerFrame = ceil(0.03*fs);  % 30ms frame, frameSize = samplesPerFrame
samplesPerHop = ceil(0.01*fs);      % hopSize = samplesPerHop
samplesPerOverlap = samplesPerFrame - samplesPerHop;

AFR.SamplesPerFrame = samplesPerHop;
buffer = dsp.AsyncBuffer;

VAD = voiceActivityDetector('InputDomain','Frequency');
cepFeatures = cepstralFeatureExtractor('InputDomain','Frequency','SampleRate',fs,'LogEnergy','Replace');
sink = dsp.SignalSink;

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

threshold = 0.75;
nanVector = nan(1,13);

pHold = ones(samplesPerHop,1);
while ~isDone(AFR)
  audioIn = AFR();
  write(buffer, audioIn);
  
  overlappedAudio = read(buffer,samplesPerFrame,samplesPerOverlap);
  X = fft(overlappedAudio,2048);
  %X = fft(overlappedAudio,1024);
  %X = fft(overlappedAudio,512);
  
  probOfSpeech = VAD(X);
  
  pHold(end) = probOfSpeech;
  %scope(X,pHold)
  scope(audioIn,pHold)
  player(audioIn);
  pHold(:) = probOfSpeech;
  
  if probOfSpeech > threshold
      xFeatures = cepFeatures(X);
      sink(xFeatures')
  else
      sink(nanVector)
  end
end

timeVector = linspace(0,15,size(sink.Buffer,1));
plot(timeVector,sink.Buffer)
xlabel('Time(s)')
ylabel('MFCC Amplitude')
legend('Log-Energy','c1','c2','c3','c4','c5','c6','c7','c8','c9','c10','c11','c12')
