#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
aimldl > aws > transcribe > test_transcribe-jp.py
  is a main script to run transcribe-jp.py which transcribes a .wav file in Japanese.
Input .wav file -> AWS Transcribe -> Transcribed results in JSON file.

Input:
  s3://hula-dataset/japanese-0.wav.
  * The input file must be pre-uploaded to AWS S3.
  * The file name is japanese-0.wav and stored in s3://hula-dataset.

Output:
  ../output/aws_transcribe_results/japanese-0.json

transcribe-jp.py uses the wave file (japanese-0.wav) as an input to AWS Transcribe
  and downloads the transcription result to
  a JSON file (japanese-0.json) in the output directory "../output/aws_transcribe_results".

2019-11-05 (Tue)
==> Well, AWS Transcribe doesn't support Japanese! Pause here.
https://docs.aws.amazon.com/transcribe/latest/dg/what-is-transcribe.html

This file is parsed and each item is stored to a CSV file, what_is_this_music-Brian.csv, in the output directory.

../output/aws_transcribe_results/what_is_this_music-Brian.json
,start_time,end_time,content,confidence
0,0.04,0.35,What,0.9998
1,0.35,0.53,is,0.9998
2,0.53,0.76,this,1.0
3,0.76,1.48,music,1.0

Notice you can use the timestamp information and each word in the transcript.

CONTRIBUTION
As of 2019-09-16, the AWS Transcribe tutorial explains up to the point a JSON file is generated.
This source code goes a little bit further by parsing the download URI and downloading the JSON file automatically.
Additionally, the JSON file (stored as a Python Dictionary) is parsed and each item is saved to a Pandas DataFrame.
The DataFrame is exported to a CSV file. You can do many things from this CSV file.

Last updated: 2019-11-05 (Tue)
First written: 2019-09-16 (Mon)
Written by T. Kim, Ph.D. http://tae.hyung.kim/
"""

from aws.transcribe import Configuration
from aws.transcribe import AwsTranscribe

if __name__ == '__main__':
    config = Configuration()
    tts    = AwsTranscribe( config )  # TTS (Text-To-Speech)
    tts.run()
# EOF
