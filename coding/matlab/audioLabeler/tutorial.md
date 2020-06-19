
Ref. Doc.: Label Audio Using Audio Labeler, https://www.mathworks.com/help/audio/ug/audio-labeler-walkthrough.html

## Load unlabeled data
>> audioLabeler
>> fullfile( matlabroot, 'toolbox', 'audio', 'samples')

ans =

    '/usr/local/MATLAB/R2019a/toolbox/audio/samples'

where
>> matlabroot

ans =

    '/usr/local/MATLAB/R2019a'

## Create label definitions
Two types of labels for the audio files: file-level labels and region-level labels.
### File-level labels
  Label Name=Content, Data Type=categorical, categories={music, speech, ambience, unknown}
  If unknown is the default, all the files are automatically labeled as unknown.
### Region-level labels
  Label Name=SpeechActivity, Data Type=logical, Default Value=true
  Label Name=VUV, Data Type=categorical, categories={voiced, unvoiced}

## Label definition
### Export
Export > Label Definitions > To File
### Import
Import > Label Definitions > From File

### Labeled audio data
### Export
Export > Labels > To Workspace

>> labeledSet_155217

labeledSet_155217 = 

  labeledSignalSet with properties:

             Source: {25×1 cell}
         NumMembers: 25
    TimeInformation: "inherent"
             Labels: [25×3 table]
        Description: ""

 Use labelDefinitionsHierarchy to see a list of labels and sublabels.
 Use setLabelValue to add data to the set.

>> labeledSet_155217.Source
    /usr/local/MATLAB/R2019a/toolbox/audio/samples/Ambiance-16-44p1-mono-12secs.wav                                              unknown     [0×2 table]      [0×2 table]
      ...
    /usr/local/MATLAB/R2019a/toolbox/audio/samples/WaveGuideLoopOne-24-96-stereo-10secs.aif                                      unknown     [0×2 table]      [0×2 table]

>> labeledSet_155217.Labels

## Prepare audio datastore for deep learning workflow

>> ADS = audioDatastore(labeledSet_155217.Source, 'Labels', labeledSet_155217.Labels)

ADS = 

  audioDatastore with properties:

                       Files: {
                              ' .../MATLAB/R2019a/toolbox/audio/samples/Ambiance-16-44p1-mono-12secs.wav';
                              ' .../R2019a/toolbox/audio/samples/AudioArray-16-16-4channels-20secs.wav';
                              ' .../toolbox/audio/samples/ChurchImpulseResponse-16-44p1-mono-5secs.wav'
                               ... and 22 more
                              }
                      Labels: 25-by-3 table
    AlternateFileSystemRoots: {}
              OutputDataType: 'double'

>> countEachLabel(ADS,'TableVariable','Content')
Error using audioDatastore/countEachLabel (line 28)

 TableVariable must be a valid character array of a variable name in the Labels Table.
 
>> countEachLabel(ADS,'TableVariable','Content')
Error using audioDatastore/countEachLabel (line 28)

 TableVariable must be a valid character array of a variable name in the Labels Table.
 
>>
