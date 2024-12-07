#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
transcribe.py

CAUTION:
Ensure to use a new job_name for every single job request. Otherwise an error occurs:
    botocore.errorfactory.ConflictException: An error occurred
    (ConflictException) when calling the StartTranscriptionJob operation:
    The requested job name already exists. Use a different job name.

To play an audio file on Linux, you may use the aplay command:
  $ aplay file_name
  Signed 16 bit Little Endian, Rate 16000 Hz, Mono
  $

Last updated: 2019-09-16 (Mon)
First written: 2019-09-16 (Mon)
Written by T. Kim, Ph.D. http://tae.hyung.kim/
"""

import time
import json
import wget

import os.path
import pandas as pd


from datetime import datetime
from progress.bar import Bar

import boto3

from amazon.s3 import AmazonS3
#import threading  # TODO: change a multiple files to use threading.

class AmazonTranscribe:
    # Constructor
    def __init__( self, verbose=False ):
        # transcribe was changed to boto3_transcribe because there is function transcribe.
        self.boto3_transcribe = boto3.client('transcribe')
        self.verbose    = verbose
        self.sleep_time = 40

        '''
        StartTranscriptionJob, (as of 2019-11-06)
          https://docs.aws.amazon.com/transcribe/latest/dg/API_StartTranscriptionJob.html
          LanguageCode
            [ar-AE, en-US, ta-IN, en-IN, ar-SA, zh-CN, gd-GB, id-ID, nl-NL, es-ES, pt-PT, 
             ru-RU, it-IT, fr-FR, de-DE, ga-IE, af-ZA, ko-KR, de-CH, hi-IN, cy-GB, ms-MY,
             he-IL, da-DK, en-AU, pt-BR, ja-JP, es-US, en-GB, fr-CA]
          MediaFormat
            mp3 | mp4 | wav | flac

        '''    
        self.supported_language_code_list = ['ar-AE', 'en-US', 'ta-IN', 'en-IN', 
                                             'ar-SA', 'zh-CN', 'gd-GB', 'id-ID', 
                                             'nl-NL', 'es-ES', 'pt-PT', 'ru-RU', 
                                             'it-IT', 'fr-FR', 'de-DE', 'ga-IE', 
                                             'af-ZA', 'ko-KR', 'de-CH', 'hi-IN', 
                                             'cy-GB', 'ms-MY', 'he-IL', 'da-DK',
                                             'en-AU', 'pt-BR', 'ja-JP', 'es-US',
                                             'en-GB', 'fr-CA']
        self.supported_media_format_list = ['mp3', 'mp4', 'wav', 'flac']

    def validate_params( self, language_code, media_format ):

        # Check language_code
        assert language_code in self.supported_language_code_list, '%s is not a supported language_code' %language_code
        
        # Check audio format
        assert media_format in self.supported_media_format_list, '%s is not a supported media_format' %media_format
    
    def run( self, language_code, dir_input, file_name, bucket_name, object_name, dir_output ):
        '''
        If it runs successfully, the returned 'status' looks like below.
            {'TranscriptionJob': {'TranscriptionJobName': 'test-amazon_transcribe-20191106-154153',
             'TranscriptionJobStatus': 'COMPLETED', 'LanguageCode': 'en-US',
             'MediaSampleRateHertz': 22050, 'MediaFormat': 'wav', 'Media':
             {'MediaFileUri': 's3://test-amazon_transcribe/english-0.wav'},
             'Transcript': {'TranscriptFileUri': ... , 'RetryAttempts': 0}}
        '''
        # Amazon Transcribe
        job_name      = bucket_name + datetime.now().strftime( '-%H%M%S' )
        job_uri       = 's3://' + bucket_name + '/' + object_name

        # file_name  # 'english-0.wav'
        input_file_root      = os.path.splitext( file_name )[0]      # english-0
        input_file_extension = os.path.splitext( file_name )[1][1:]  # wav
        media_format         = input_file_extension  # 'wav'
        
        self.validate_params( language_code, media_format )
        
        # dir_output = '../output/'
        output_json_file = dir_output +'/'+ input_file_root + '.json'
        output_csv_file  = dir_output +'/'+ input_file_root + '.csv'

        file_exists = os.path.isfile( output_json_file )
        if file_exists:
            print(f'Transcription result exists! Retrieving the result from {output_json_file}')
        else:
            status_dict     = self.transcribe( job_name, job_uri, media_format, language_code )
            if self.verbose:
                print( status_dict )
            # if status is a success
            self.result_uri = status_dict['TranscriptionJob']['Transcript']['TranscriptFileUri']
            wget.download( self.result_uri, output_json_file )

        self.json_dict  = self.load_result( output_json_file )
        if self.verbose:
            print( self.json_dict )

        if self.verbose:
            self.print_transcripts( self.json_dict )

        self.df_result = self.parse_transcripts( self.json_dict )
        self.df_result.to_csv( output_csv_file )        

    def transcribe( self, job_name, job_uri, media_format, language_code ):
        
        print(f'Transcribing {job_uri}...' )
        
        self.boto3_transcribe.start_transcription_job(
          TranscriptionJobName = job_name,
          Media                = {'MediaFileUri': job_uri},
          MediaFormat          = media_format,
          LanguageCode         = language_code
        )

        while True:
            status_dict = self.boto3_transcribe.get_transcription_job( TranscriptionJobName=job_name )
            if status_dict['TranscriptionJob']['TranscriptionJobStatus'] in ['COMPLETED', 'FAILED']:
                break
            print("Not ready yet. Waiting for another minute...")
            time.sleep( self.sleep_time )

        return status_dict

    def load_result( self, file ):
        #file = '../output/test_transcribe_result-asrOutput.json'
        with open( file, 'r' ) as f:
            json_dict = json.load( f )

        return json_dict

    def parse_transcripts( self, json_dict ):
        '''
        word #0: content = What, start_time = 0.04, end_time = 0.35
        word #1: content = is, start_time = 0.35, end_time = 0.53
        word #2: content = this, start_time = 0.53, end_time = 0.76
        word #3: content = music, start_time = 0.76, end_time = 1.48
        word #4: content = ?
        '''
        #results = json_dict['results']

        transcripts_list = json_dict['results']['transcripts']
        print( "Result='", transcripts_list[0]['transcript'],"'" )

        word_list = []
        speech    = []

        items_list = json_dict['results']['items']
        for i, item in enumerate( items_list ):
            print(f'word #{i}: ', end='')
            if item['type'] == 'pronunciation':
                start_time = item['start_time']
                end_time   = item['end_time']
                content    = item['alternatives'][0]['content']
                confidence = item['alternatives'][0]['confidence']  # floating number
                word_list = [ start_time, end_time, content, confidence ]
                speech.append( word_list )

        df = pd.DataFrame( speech, columns=['start_time','end_time','content','confidence'] )
        # Note item for punctuation may be removed.

        return df

    def print_transcripts( self, json_dict ):
        print( json_dict['jobName'] )
        print( json_dict['accountId'] )
        print( json_dict['results'] )
        print( json_dict['status'] )

        print( json_dict['results']['transcripts'] )  # results['transcripts']
        print( json_dict['results']['items'] )        # results['items']

        print( json_dict['results']['transcripts'][0]['transcript'] )  # transcripts_list[0]['transcript']

        items_list = json_dict['results']['items']
        for i, item in enumerate( items_list ):
            print(f'word #{i}: ', end='')
            if item['type'] == 'pronunciation':
                print( 'content =', item['alternatives'][0]['content'], end='' )
                print( ', start_time =', item['start_time'], end='' )
                print( ', end_time =', item['end_time'] )
            elif item['type'] == 'punctuation':
                print( 'content =', item['alternatives'][0]['content'] )        

    def save2json( self, data, file ):
        '''
        Two dictionaries exist in data: ResponseMetadata & TranscriptionJob.
        I'm not interested in ResponseMetadata because this is about the HTTP connection.
        So only TranscriptionJob will be saved.
        
        with open( file, 'w') as f:
            json.dump( data, f )
        will give TypeError.
        TypeError: Object of type datetime is not JSON serializable
        '''
        df = pd.DataFrame.from_dict( data )
        df.to_json( file )
        
    def parse( self, json_dict ):
        '''
        word #0: content = What, start_time = 0.04, end_time = 0.35
        word #1: content = is, start_time = 0.35, end_time = 0.53
        word #2: content = this, start_time = 0.53, end_time = 0.76
        word #3: content = music, start_time = 0.76, end_time = 1.48
        word #4: content = ?
        '''
        #results = json_dict['results']
        transcript = json_dict['results']['transcripts'][0]['transcript']
        #print( transcripts_list[0]['transcript'] )
        #transcript_list = json_dict['results']['transcripts'][0]['transcript']
        
        word_list   = []
        speech_list = []
        
        items_list = json_dict['results']['items']
        for i, item in enumerate( items_list ):
            #print(f'word #{i}: ', end='')
            if item['type'] == 'pronunciation':
                start_time = item['start_time']
                end_time   = item['end_time']
                content    = item['alternatives'][0]['content']
                confidence = item['alternatives'][0]['confidence']  # floating number
                #word_list = ' :: '.join( [ start_time, end_time, content, confidence ] )
                word_list = [ start_time, end_time, content, confidence ]
                speech_list.append( word_list )

        # Note item for punctuation may be removed.
        # speech, columns=['start_time','end_time','content','confidence']
        return ( transcript , speech_list )

    # This is for the hula project
#    # TODO: The code from here is not working. Work on that.
#    def multi_transcribe( self, df_s3, language ):
#        '''
#        batch_transcribe is a wrapper around ...
#        
#        All the .wav files are assumed to be uploaded to an AWS S3 bucket.
#        This information is stored in df_s3 and passed to this function.
#        Each .wav file is transcribed one-by-one.
#        '''
#        # creating a lock 
#        lock = threading.Lock() 
#
#        # creating threads 
#
#        t2 = threading.Thread( target=thread_task, args=(lock,) )
#  
#        # start threads 
#        t1.start() 
#        t2.start() 
#      
#        # wait until threads finish their job 
#        t1.join() 
#        t2.join() 
#    
#            maxthreads = 5
#            sema = threading.Semaphore(value=maxthreads)
#            threads = list()
#            
#            def task(i):
#                sema.acquire()
#                print "start %s" % (i,)
#                time.sleep(2)
#                sema.release()
#            
#            for i in range(10):
#                thread = threading.Thread(target=task,args=(str(i)))
#                threads.append(thread)
#                thread.start()
#    
#
#
#        media_format     = self.config.media_format  # 'wav'
#        s3_language_code    = self.config.s3_language_code_dict[ language ]
#        bucket_name      = self.config.bucket_name
#        now              = datetime.now()
#        # ../output/json_files/en or /jp or /kr or /zh
#        dir_output = self.config.dir_output / 'json_files' / self.config.language_code_dict[ language ]
#       
#        transcripts_list = []
#        words_list       = []
#        
#        row_size         = df_s3.shape[0]
#        bar              = Bar( 'Processing', max=row_size )  # Progress bar
#        object_name_list = df_s3[ 'object_name' ].tolist()
#        for index, object_name in enumerate( object_name_list, 0 ):
#            file_root = os.path.splitext( object_name )[0]
#            file_name = file_root + '.json'
#            file_json = dir_output / file_name
#            
#            status_file_name = 'status-' + file_root + '.json'
#            status_file_json = dir_output / status_file_name
#
#            if not file_json.is_file():
#                time        = now.strftime( '%Y%m%d-%H%M%S' )
#                job_name    = bucket_name + '-' + file_root + '-' + time
#                job_uri     = 's3://' + bucket_name + '/' + object_name
#                
#                if self.config.debug:
#                    print(f'Requesting to transcribe {job_uri} ...' )
#                status_dict = self.boto3_transcribe( job_name, job_uri, media_format, s3_language_code )
#                
#                t1 = threading.Thread( target=transcribe, args=( job_name, job_uri, media_format, s3_language_code,) )
#                
#                
#                
#                result_uri  = status_dict['TranscriptionJob']['Transcript']['TranscriptFileUri']
#                self.save2json( status_dict, status_file_json )
#                
#                if self.config.debug:
#                    print(f'Downloading {result_uri} ...' )
#                wget.download( result_uri, str( file_json ) )
#
#            json_dict   = self.load_result( file_json )
#            (transcript, word_list) = self.parse( json_dict )  # Error
#            transcripts_list.append( transcript )
#            words_list.append( word_list )
#
#            bar.next()  # Progress bar
#        bar.finish()    # Progress bar
#
#        df_transcripts = pd.DataFrame( transcripts_list, columns=['transcribe_transcript'] )
#        df_words       = pd.DataFrame( words_list, columns=['transcribe_words'] )
#        df_transcribe  = pd.concat( [df_transcripts, df_words], axis=1 )
#
#        return df_transcribe
#
#    # For multithreading
#    def transcribe( job_name, job_uri, media_format, s3_language_code ):
#
#        self.boto3_transcribe.start_transcription_job(
#          TranscriptionJobName = job_name,
#          Media                = {'MediaFileUri': job_uri},
#          MediaFormat          = media_format,
#          LanguageCode         = language_code
#        )
#        
#        while True:
#            status_dict = self.boto3_transcribe.get_transcription_job( TranscriptionJobName=job_name )
#            if status_dict['TranscriptionJob']['TranscriptionJobStatus'] in ['COMPLETED', 'FAILED']:
#                break
#            #print("Not ready yet...")
#            time.sleep( self.sleep_time )
#
#        return status_dict
#
#
#
## global variable x 
#x = 0
#  
#def increment(): 
#    """ 
#    function to increment global variable x 
#    """
#    global x 
#    x += 1
#  
#def thread_task(lock): 
#    """ 
#    task for thread 
#    calls increment function 100000 times. 
#    """
#    for _ in range(100000): 
#        lock.acquire() 
#        increment() 
#        lock.release() 
#  
#def main_task(): 
#    global x 
#    # setting global variable x as 0 
#    x = 0
#  
#    # creating a lock 
#    lock = threading.Lock() 
#  
#    # creating threads 
#    t1 = threading.Thread(target=thread_task, args=(lock,)) 
#    t2 = threading.Thread(target=thread_task, args=(lock,)) 
#  
#    # start threads 
#    t1.start() 
#    t2.start() 
#  
#    # wait until threads finish their job 
#    t1.join() 
#    t2.join() 

# EOF
