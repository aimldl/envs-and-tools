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

# Instantiates a client
client = speech.SpeechClient()

dirname = '../input/next-song-please/'
my_file_name = 'next.wav'
sample_rate_hertz = 16000
language_code = 'en-US'

#$ aplay next.wav 
#Playing WAVE 'next.wav' : Signed 16 bit Little Endian, Rate 16000 Hz, Mono

# The name of the audio file to transcribe
file_name = os.path.join(
#    os.path.dirname(__file__),
#    'resources',
#    'audio.raw')
    os.path.dirname( dirname ),
    my_file_name
    )

print(f'file_name = {file_name}')

# Loads the audio into memory
with io.open(file_name, 'rb') as audio_file:
    content = audio_file.read()
    audio = types.RecognitionAudio(content=content)
# >>> content
#b'RIFF$!\x00\x00WAVEfmt \x10\x00\x00\x00\x01\x00\x01\x00\x80>\x00\x00\x00}\x00\x00\x02\x00\x10\x00data\x00!\x00
#  ...
# \x02]\x03\xc7\x03\xf8\x00\x1b\x04C\x01'
# >>> audio
#content: "RIFF$!\000\000WAVEfmt \020\000\000\000\001\000\001\000\200>\000\000\000}\000\000\002\000\020\00
# ...
#\002]\003\307\003\370\000\033\004C\001"
config = types.RecognitionConfig(
    encoding=enums.RecognitionConfig.AudioEncoding.LINEAR16,
    # LINEAR16	Uncompressed 16-bit signed little-endian samples (Linear PCM).
    sample_rate_hertz=sample_rate_hertz,
    # audioChannelCount=, # ONLY set this for MULTI-CHANNEL recognition
    language_code=language_code)
#    sample_rate_hertz=16000,
#    language_code='en-US')

# Detects speech in the audio file
response = client.recognize(config, audio)

print( response )
# Each result is for a consecutive portion of the audio. Iterate through
# them to get the transcripts for the entire audio file.

for result in response.results:
    # The first alternative is the most likely one for this portion.
    print('Transcript: {}'.format(result.alternatives[0].transcript))


