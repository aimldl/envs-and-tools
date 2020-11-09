##### aimldl > matlab > audio> voiceActivityDetector > README.md

* Revision:
* Draft: Some time ago

* Detect presence of speech in audio signal
* Source: https://www.mathworks.com/help/audio/ref/voiceactivitydetector-system-object.html
## Syntax
  [probability,noiseEstimate] = VAD(audioIn)

## Algorithms
The voiceActivityDetector implements the algorithm described in [1].
If InputDomain is specified as 'Time', the input signal is windowed and then converted to the frequency domain according to the Window, SidelobeAttenuation, and FFTLength properties. If InputDomain is specified as frequency, the input is assumed to be a windowed discrete time Fourier transform (DTFT) of an audio signal. The signal is then converted to the power domain. Noise variance is estimated according to [2]. The posterior and prior SNR are estimated according to the Minimum Mean-Square Error (MMSE) formula described in [3]. A log likelihood ratio test and Hidden Markov Model (HMM)-based hang-over scheme determine the probability that the current frame contains speech, according to [1].

## References
* [1] Sohn, Jongseo., Nam Soo Kim, and Wonyong Sung. "A Statistical Model-Based Voice Activity Detection." Signal Processing Letters IEEE. Vol. 6, No. 1, 1999.
* [2] Martin, R. "Noise Power Spectral Density Estimation Based on Optimal Smoothing and Minimum Statistics." IEEE Transactions on Speech and Audio Processing. Vol. 9, No. 5, 2001, pp. 504–512.
* [3] Ephraim, Y., and D. Malah. "Speech Enhancement Using a Minimum Mean-Square Error Short-Time Spectral Amplitude Estimator." IEEE Transactions on Acoustics, Speech, and Signal Processing. Vol. 32, No. 6, 1984, pp. 1109–1121.

## Examples
### Detect Voice Activity
### Detect Voice Activity Using Overlapped Frames
### Frequency-Domain Voice Activity Detection and Cepstral Feature Extraction
### Determine Pitch Contour using pitch and voiceActivityDetector
