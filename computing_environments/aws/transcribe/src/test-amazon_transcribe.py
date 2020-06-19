#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
test-amazon_transcribe.py
  is a main script to run transcribe.py.

input: ../input/english-2017.wave

1. Upload the input file to an Amazon S3 bucket.
2.

  It uses a wave file, what_is_this_music-Brian.wav. pre-uploaded to AWS S3
as an input to AWS Transcribe and downloads the transcription result to a JSON file, what_is_this_music-Brian.json,
in the output directory "../output/aws_transcribe_results".

../output/aws_transcribe_results/what_is_this_music-Brian.json
{"jobName":"test-hula-07", ... ,
 "results":{"transcripts":[{"transcript":"What is this music?"}],
 "items":[{"start_time":"0.04","end_time":"0.35","alternatives":[{"confidence":"0.9998","content":"What"}],"type":"pronunciation"},
          {"start_time":"0.35","end_time":"0.53","alternatives":[{"confidence":"0.9998","content":"is"}],"type":"pronunciation"},
          {"start_time":"0.53","end_time":"0.76","alternatives":[{"confidence":"1.0","content":"this"}],"type":"pronunciation"},
          {"start_time":"0.76","end_time":"1.48","alternatives":[{"confidence":"1.0","content":"music"}],"type":"pronunciation"},
          {"alternatives":[{"confidence":"0.0","content":"?"}],"type":"punctuation"}]},"status":"COMPLETED"}

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

bucket_name  = 'test-amazon_transcribe'
s3.create_bucket( bucket_name, region=bucket_region )



"""
# TODO: Summarize pathlib/POSIX vs. os.path
import os
import errno
#import pathlib
from datetime import datetime

from amazon.transcribe import AmazonTranscribe
from amazon.s3 import AmazonS3

def safe_makedirs( directory ):
    '''
    If directory is POSIX, convert it to string by str(directory).
    https://www.tutorialspoint.com/How-can-I-create-a-directory-if-it-does-not-exist-using-Python
    '''
    assert isinstance( directory, str), 'directory must be a string'
    
    if not os.path.exists( directory ):
        try:
            os.makedirs( directory )
        except OSError as e:
            if e.errno != errno.EEXIST:
                raise

if __name__ == '__main__':
    language_code = 'en-US'
    dir_input  = '../input'
    dir_output = '../output'
    file_name  = 'english-2017.wav'

    # Create the output directory if it doesn't exist.
    safe_makedirs( dir_output )

    now = datetime.now().strftime( '%Y%m%d' )

    bucket_region = 'us-west-2'
    bucket_name  = 'amazon-transcribe-test' +'-'+ now
    object_name   = file_name  # object_name can be different from file_name
    
    #------------#
    # Amazon S3  #
    #------------#
    # Prerequisite: the input file must be stored on a S3 bucket.
    # object_name is the file name in Amazon S3
    s3  = AmazonS3()
    
    if s3.bucket_exists( bucket_name ):  # Check if the bucket exists on S3
        print(f'Bucket {bucket_name} already exists in AWS S3.' )
    else:  # If not, create one.
        #s3.list_existing_buckets()  # for debugging
        s3.create_bucket( bucket_name, region=bucket_region )
        #s3.list_existing_buckets()  # for debugging
        
        # If the following error occurs, check the bucket_name.
        #  ERROR:root:An error occurred (InvalidBucketName) when calling the CreateBucket operation: The specified bucket is not valid.
        # bucket_name must be a unique one and should not contain underscore or '_'.

    # Upload the file to the S3 bucket
    file2upload = dir_input +'/'+ file_name  # PosixPath('../input/english-2017.wav')
    #file_posix = pathlib.Path( dir_input ) / file_name  # PosixPath('../input/english-2017.wav')

    # Check if file exists on the local disk
    assert os.path.isfile( file2upload ), '%s does not exist' % file2upload
    #assert file_posix.is_file(), '%s does not exist' % file_posix
    
    # If this file doesn't exit on the target S3 bucket, upload the file
    if s3.file_exists( bucket_name, object_name ):
        print(f's3://{bucket_name}/{object_name} already exists in AWS S3.' )
    else:
        assert isinstance( file2upload, str ), 'file2upload must be a string'
        # Otherwise,
        #   ValueError: Filename must be a string in s3.upload_file( file, ...)
        success = s3.upload_file( file2upload, bucket_name, object_name=object_name )
        if success:
            print(f'Uploaded {file2upload} to s3://{bucket_name}/{object_name}' )
    
    #--------------------#
    # Amazon Transcribe  #
    #--------------------#
    tts = AmazonTranscribe()  # TTS (Text-To-Speech)
    tts.run( language_code, dir_input, file_name, bucket_name, object_name, dir_output )
# EOF
