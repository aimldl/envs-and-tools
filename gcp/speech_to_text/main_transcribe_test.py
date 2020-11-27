'''
google-cloud_speech_to_text-python_text_script.py
Cloud Speech-to-Text Quickstart: Using client libraries
https://cloud.google.com/speech-to-text/docs/quickstart-client-libraries

## Make an audio transcription request
Now you can use Cloud Speech-to-Text to transcribe an audio file to text. Use the following code to send a recognize request to the Speech-to-Text API.
### PYTHON
Before running the example, make sure you've prepared your environment for Python development.

### Setting up a Python development environment
https://cloud.google.com/python/setup

## Usage
$ gcloud init
$ python google-cloud_speech_to_text-python_text_script.py

'''
import io
import os

# Imports the Google Cloud client library
from google.cloud import speech
from google.cloud.speech import enums
from google.cloud.speech import types

def transcribe_file( speech_file, sampling_rate_hz, language_code ):
    ''' Transcribe the given audio file.
    $ aplay next.wav 
    Playing WAVE 'next.wav' : Signed 16 bit Little Endian, Rate 16000 Hz, Mono

    '''
    print(f'speech_file = {speech_file}' )
    
    # Instantiates a client
    client = speech.SpeechClient()

    # Loads the audio into memory
    with io.open( speech_file, 'rb' ) as audio_file:
        content = audio_file.read()

    audio = types.RecognitionAudio(content=content)
    # >>> content
    #b'RIFF$!\x00\x00WAVEfmt \x10\x00\x00\x00\x01
    #  ...
    # \x02]\x03\xc7\x03\xf8\x00\x1b\x04C\x01'
    # >>> audio
    #content: "RIFF$!\000\000WAVEfmt \020\000\000\000\001\000\001\000\200>\000\000\000}\000\000\002\000\020\00
    # ...
    #\002]\003\307\003\370\000\033\004C\001"

    # LINEAR16	Uncompressed 16-bit signed little-endian samples (Linear PCM).
    # FLAC      enums.RecognitionConfig.AudioEncoding.FLAC
    # audioChannelCount =, # ONLY set this for MULTI-CHANNEL recognition
    # sample_rate_hertz = 16000,
    # language_code     = 'en-US'

    config = types.RecognitionConfig(
                encoding          = enums.RecognitionConfig.AudioEncoding.LINEAR16,
                sample_rate_hertz = sampling_rate_hz,
                language_code     = language_code)

    # Detects speech in the audio file
    response = client.recognize(config, audio)

    print( response )
    # Each result is for a consecutive portion of the audio. Iterate through
    # them to get the transcripts for the entire audio file.
    for result in response.results:
        # The first alternative is the most likely one for this portion.
        print(u'Transcript: {}'.format(result.alternatives[0].transcript) )

if __name__ == '__main__':

    dir = '../input/next-song-please/'
    
    # The name of the audio file to transcribe
    #file_name = os.path.join(
    #    os.path.dirname(__file__),
    #    'resources',
    #    'audio.raw')
    #    os.path.dirname( dirname ),
    #    my_file_name
    #    )

    speech_file      = 'next.wav'
    sampling_rate_hz = 16000
    language_code    = 'en-US'

    transcribe_file( speech_file, sampling_rate_hz, language_code )