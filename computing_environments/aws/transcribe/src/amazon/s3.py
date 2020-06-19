#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
s3.py
Revision: 2019-11-06 (Wed)
"""

import logging
import boto3
import os
from botocore.exceptions import ClientError
from progress.bar import Bar

import numpy as np
import pandas as pd

class AmazonS3:
    # Constructor
    def __init__( self, verbose=False ):
        self.verbose = verbose
        
    def create_bucket( self, bucket_name, region=None ):
        '''Create an S3 bucket in a specified region
    
        If a region is not specified, the bucket is created in the S3 default
        region (us-east-1).
    
        :param bucket_name: Bucket to create. 
               The name must be unique across all regions of the AWS platform. Otherwise,
               BucketAlreadyExists error occurs.
        :param region: String region to create bucket in, e.g., 'us-west-2'. The bucket can be located in a specific region to minimize latency or to address regulatory requirements.
        :return: True if bucket created, else False
        
        This function is from https://boto3.amazonaws.com/v1/documentation/api/latest/guide/s3-example-creating-buckets.html
        '''
        print(f'Creating a bucket {bucket_name}...' )
        try:
            if region is None:
                s3 = boto3.client( 's3' )
                s3.create_bucket( Bucket=bucket_name )
            else:
                s3       = boto3.client( 's3', region_name=region )
                location = { 'LocationConstraint': region }
                s3.create_bucket( Bucket=bucket_name,
                                        CreateBucketConfiguration=location )
        except ClientError as e:
            if self.verbose:
                print( e )
            logging.error(e)
            return False
        
        print(f'Bucket {bucket_name} has been successfully created.' )
        return True
    
    def list_existing_buckets( self ):
        '''
        This function is from https://boto3.amazonaws.com/v1/documentation/api/latest/guide/s3-example-creating-buckets.html
        '''
        # Retrieve the list of existing buckets
        s3       = boto3.client( 's3' )
        response = s3.list_buckets()
        
        # Output the bucket names
        print( 'Existing buckets:' )
        for bucket in response['Buckets']:
            print(f'  {bucket["Name"]}' )

    def bucket_exists( self, bucket_name ):
        assert isinstance( bucket_name, str ), 'bucket_name must be a string'
        
        s3     = boto3.resource( 's3' )
        bucket = s3.Bucket( bucket_name )
        if bucket.creation_date is None:
            return False
        else:
            return True
    
    def file_exists( self, bucket_name, file_name ):
        assert isinstance( bucket_name, str ), 'bucket_name must be a string'
        assert isinstance( file_name, str ), 'file_name must be a string'
    
        s3 = boto3.resource( service_name='s3' )
        try:
            s3.Object( bucket_name, file_name ).load()  # Usually file_name is refered to as key
        except ClientError as e:
            return int( e.response['Error']['Code'] ) != 404
        return True

    def upload_file( self, file, bucket_name, object_name=None ):
        '''Upload a file to an S3 bucket
    
        :param file: File to upload
        :param bucket: Bucket to upload to
        :param object_name: S3 object name. If not specified then file_name is used
        :return: True if file was uploaded, else False
        
        If object_name is not used, an error occurs
          boto3.exceptions.S3UploadFailedError: Failed to upload 
          ../input/how_is_the_weather_today-Joey.wav to 
          hula-dataset/../input/how_is_the_weather_today-Joey.wav: An error occurred 
          (400) when calling the PutObject operation: Bad Request
        
        This function is from https://boto3.amazonaws.com/v1/documentation/api/latest/guide/s3-uploading-files.html
        '''
        # If S3 object_name was not specified, use file_name
        if object_name is None:
            object_name = file
    
        # Upload the file
        s3 = boto3.client('s3')
        try:
            response = s3.upload_file( file, bucket_name, object_name )
            
        except ClientError as e:
            if self.verbose:
                print( e )
            logging.error(e)
            return False
        return True


    def batch_upload_file( self, df_metadata, dir_upload, bucket_name ):
        
        '''
        batch_upload_file uploads df_metadata from dir_upload to bucket_name.
        df_metadata has a list of file names in dir_upload &
                        a list of bucket name in bucket_name.
        
        It is a wrapper around upload_file.
        All the files with file_extension under directory dir_upload are selected
        one-by-one and fed to upload_file.
        
        Terminology
        A file is a file in the local disk.
        An object is the corresponding file in AWS S3.

        Use of flags        
        Files in the upload file list mostly exists in the local hard disk.
        The corresponding objects mostly don't exist in the target S3 bucket.
        '''
        #bucket_name        = self.config.bucket_name
        #language_code_dict = self.config.language_code_dict
        #dir_input          = self.config.dir_input
        #directory          = dir_input / 'wav_files' / 'training' / language_code_dict[ language ]
                
        file_name_list   = df_metadata[ 'file_name' ].tolist()
        object_name_list = df_metadata[ 'object_name' ].tolist()
        
        # for df_flags
        row_size    = df_metadata.shape[0]
        df_is_local = pd.DataFrame( np.ones( (row_size, 1) ), columns=['is_local'] )
        df_is_s3    = pd.DataFrame( np.zeros( (row_size, 1) ), columns=['is_s3'] )
        df_flags    = pd.concat( [df_is_local,df_is_s3], axis=1 )

        bar = Bar( 'Processing', max=row_size )  # Progress bar
        for index, file_name in enumerate( file_name_list, 0 ):
            #dir_upload  = dir_input / 'wav_files' / 'training' / language_code_dict[ language ]
            file_posix = dir_upload / file_name  # full path to a .wav file

            if file_posix.is_file():  # If file exists on the local disk
                #print(f'{file_posix} ' )  # For debugging
                # object_name is the file name in Amazon S3            
                object_name = object_name_list[ index ]
                if self.file_exists( bucket_name, object_name ):
                    df_flags[ 'is_s3' ][ index ] = 1
                else:  # If this file doesn't exit on the target S3 bucket, upload the file
                    file    = str( file_posix )  # ValueError: Filename must be a string in self.upload_file( file, ...)
                    success = self.upload_file( file, bucket_name, object_name=object_name )
                    if success:
                        df_flags[ 'is_s3' ][ index ] = 1
                        if self.verbose:
                            print(f'Uploaded {file}...' )
            else:
                df_flags[ 'is_local' ][ index ] = 0

            bar.next()  # Progress bar
        bar.finish()    # Progress bar

        df_s3 = pd.concat( [df_metadata, df_flags], axis=1 )

        return df_s3

    # This is for the hula project
    # batch_upload -> batch_upload_file
    #def batch_upload( self, df_metadata, language ):
    def batch_upload( self, dir_upload, df_metadata ):
        
        '''
        batch_upload is a wrapper around upload_file.
        All the files with file_extension under directory dir_upload are selected
        one-by-one and fed to upload_file.
        
        Terminology
        A file is a file in the local disk.
        An object is the corresponding file in AWS S3.

        Use of flags        
        Files in the upload file list mostly exists in the local hard disk.
        The corresponding objects mostly don't exist in the target S3 bucket.
        '''
        bucket_name        = self.config.bucket_name
        #language_code_dict = self.config.language_code_dict
        #dir_input          = self.config.dir_input
        #directory          = dir_input / 'wav_files' / 'training' / language_code_dict[ language ]
                
        file_name_list   = df_metadata[ 'file_name' ].tolist()
        object_name_list = df_metadata[ 'object_name' ].tolist()
        
        # for df_flags
        row_size    = df_metadata.shape[0]
        df_is_local = pd.DataFrame( np.ones( (row_size, 1) ), columns=['is_local'] )
        df_is_s3    = pd.DataFrame( np.zeros( (row_size, 1) ), columns=['is_s3'] )
        df_flags    = pd.concat( [df_is_local,df_is_s3], axis=1 )

        bar = Bar( 'Processing', max=row_size )  # Progress bar
        for index, file_name in enumerate( file_name_list, 0 ):
            #dir_upload  = dir_input / 'wav_files' / 'training' / language_code_dict[ language ]
            file_posix = dir_upload / file_name  # full path to a .wav file

            if file_posix.is_file():  # If file exists on the local disk
                #print(f'{file_posix} ' )  # For debugging
                # object_name is the file name in Amazon S3            
                object_name = object_name_list[ index ]
                if self.file_exists( bucket_name, object_name ):
                    df_flags[ 'is_s3' ][ index ] = 1
                else:  # If this file doesn't exit on the target S3 bucket, upload the file
                    file    = str( file_posix )  # ValueError: Filename must be a string in self.upload_file( file, ...)
                    success = self.upload_file( file, bucket_name, object_name=object_name )
                    if success:
                        df_flags[ 'is_s3' ][ index ] = 1
                        if self.verbose:
                            print(f'Uploaded {file}...' )
            else:
                df_flags[ 'is_local' ][ index ] = 0

            bar.next()  # Progress bar
        bar.finish()    # Progress bar

        df_s3 = pd.concat( [df_metadata, df_flags], axis=1 )

        return df_s3
    # This is for the hula project
#    def batch_upload( self, fads_obj, bucket_name ):
#        '''batch_upload is a wrapper around upload_file.
#        All the files with file_extension under directory dir_upload are selected
#        one-by-one and fed to upload_file.
#        '''
#
#        language_code_dict = { 'english':'en',  'korean':'kr', 'chinese':'zh', 'japanese':'jp' }
#        df_en, df_kr, df_zh, df_jp = fads_obj.run( language_code_dict )
#
#        for language in language_code_dict:             # language = key
#            if language == 'english':
#                df_metadata = df_en
#            elif language == 'korean':
#                df_metadata = df_kr
#            elif language == 'chinese':
#                df_metadata = df_zh
#            elif language == 'japanese':
#                df_metadata = df_jp
#
#            # file = file_in_local_disk, object = file_in_s3
#            file_name_list   = df_metadata[ 'file_name' ].tolist()
#            object_name_list = df_metadata[ 'object_name' ].tolist()
#            
#            '''
#            Files in the upload file list mostly exists in the local hard disk.
#            The corresponding objects mostly don't exist in the target S3 bucket.
#            '''
#            row_size    = df_metadata.shape[0]
#            df_is_local = pd.DataFrame( np.ones( (row_size, 1) ), columns=['is_local'] )
#            df_is_s3    = pd.DataFrame( np.zeros( (row_size, 1) ), columns=['is_s3'] )
#            df_flags    = pd.concat( [df_is_local,df_is_s3], axis=1 )
#
#            for index, file_name in enumerate( file_name_list, 0 ):
#                directory  = fads_obj.dir_input / 'wav_files' / 'training' / language_code_dict[ language]
#                file_posix = directory / file_name
#                file       = str( file_posix )  # ValueError: Filename must be a string in self.upload_file( file, ...)
#    
#                # object_name is the file name in Amazon S3            
#                object_name = object_name_list[ index ]
#                if file_posix.is_file():  # If file exists on the local disk
#
#                    if self.file_exists( bucket_name, object_name ):
#                        df_flags[ 'is_s3' ][ index ] = 1
#                        if self.verbose:
#                            print( '.', end='' )
#                    else:  # If this file doesn't exit on the target S3 bucket, upload the file
#                        if self.verbose:
#                            print(f'Uploading {file}...' )
#                        success = self.upload_file( file, bucket_name, object_name=object_name )
#                        if success:
#                            df_flags[ 'is_s3' ][ index ] = 1
#                else:
#                    df_flags[ 'is_local' ][ index ] = 0
#                    
#            df = pd.concat( [df_metadata, df_flags], axis=1 )
#            df.columns = [ 'file_name', 'transcript', 'old_index', 'is_local', 'is_s3', 'object_name' ]
#
#            if language == 'english':
#                df_en = df
#            elif language == 'korean':
#                df_kr = df
#            elif language == 'chinese':
#                df_zh = df
#            elif language == 'japanese':
#                df_jp = df
#            
#        return df_en, df_kr, df_zh, df_jp
# EOF
        
'''
        self.output_dir_name = '../output/aws_transcribe_results/' 
        self.input_file_name = 'what_is_this_music-Brian.wav'
        self.input_file_root = os.path.splitext( self.input_file_name )[0]
        # TODO: A code to create the output directory if it doesn't exist.

        self.job_name      = 'test-hula-07'
        self.job_uri       = 's3://hula-hunk-labeling/' + self.input_file_name
        self.media_format  = 'wav'
        self.language_code = 'en-US'

        self.output_json_file = self.output_dir_name + self.input_file_root + '.json'
        self.output_csv_file  = self.output_dir_name + self.input_file_root + '.csv'
'''