TROUBLESHOOTING.md


##### Solution
This error is occurring because of clock skew. This means that the time on your sever differs significantly from the time on the AWS server that is fulfilling your request. The solution to this issue is to ensure that your server has the correct time. This is typically accomplished using something like NTP: http://www.ntp.org/. -Michael
[ERROR/BUG - Signature not yet current](https://forums.aws.amazon.com/thread.jspa?threadID=134543)

##### Problem
aws polly synthesize-speech --output-format pcm --voice-id Aditi --text 'you should wake me up at seven am' you_should_wake_me_up_at_seven_am.pcm-Aditi.pcm
/home/bitnami/.local/lib/python2.7/site-packages/urllib3/util/ssl_.py:354: SNIMissingWarning: An HTTPS request has been made, but the SNI (Server Name Indication) extension to TLS is not available on this platform. This may cause the server to present an incorrect TLS certificate, which can cause validation failures. You can upgrade to a newer version of Python to solve this. For more information, see https://urllib3.readthedocs.io/en/latest/advanced-usage.html#ssl-warnings
  SNIMissingWarning

An error occurred (InvalidSignatureException) when calling the SynthesizeSpeech operation: Signature not yet current: 20191204T142742Z is still later than 20191204T142741Z (20191204T142241Z + 5 min.)
aws polly synthesize-speech --output-format pcm --voice-id Raveena --text 'you should wake me up at seven am' you_should_wake_me_up_at_seven_am.pcm-Raveena.pcm
/home/bitnami/.local/lib/python2.7/site-packages/urllib3/util/ssl_.py:354: SNIMissingWarning: An HTTPS request has been made, but the SNI (Server Name Indication) extension to TLS is not available on this platform. This may cause the server to present an incorrect TLS certificate, which can cause validation failures. You can upgrade to a newer version of Python to solve this. For more information, see https://urllib3.readthedocs.io/en/latest/advanced-usage.html#ssl-warnings
  SNIMissingWarning

An error occurred (InvalidSignatureException) when calling the SynthesizeSpeech operation: Signature not yet current: 20191204T142743Z is still later than 20191204T142742Z (20191204T142242Z + 5 min.)
~/aws_polly/tts_generated_speech_corpus$

The command with error can be run independently to check the error.
~/aws_polly/tts_generated_speech_corpus$ aws polly synthesize-speech --output-format pcm --voice-id Aditi --text 'you should wake me up at seven am' you_should_wake_me_up_at_seven_am.pcm-Aditi.pcm
/home/bitnami/.local/lib/python2.7/site-packages/urllib3/util/ssl_.py:354: SNIMissingWarning: An HTTPS request has been made, but the SNI (Server Name Indication) extension to TLS is not available on this platform. This may cause the server to present an incorrect TLS certificate, which can cause validation failures. You can upgrade to a newer version of Python to solve this. For more information, see https://urllib3.readthedocs.io/en/latest/advanced-usage.html#ssl-warnings
  SNIMissingWarning

An error occurred (InvalidSignatureException) when calling the SynthesizeSpeech operation: Signature not yet current: 20191205T002921Z is still later than 20191205T002919Z (20191205T002419Z + 5 min.)

There're too many files. So
~/aws_polly/tts_generated_speech_corpus$ ls *.txt
filtered_document_list-0.999.txt

~/aws_polly/tts_generated_speech_corpus$ gedit filtered_document_list-0.999.txt
The program 'gedit' is currently not installed. To run 'gedit' please ask your administrator to install the package 'gedit'

~/aws_polly/tts_generated_speech_corpus$ cp filtered_document_list-0.999.txt filtered_document_list-0.999-part.txt
~/aws_polly/tts_generated_speech_corpus$ nano filtered_document_list-0.999-part.txt

When I checked the list, the text is in the last one! So let's double-check the number of files.

$ ls *.pcm | wc -l
14937

Currently, 14937 files are completed. How many texts? 1222.

$ wc -l filtered_document_list-0.999.txt
1222 filtered_document_list-0.999.txt

1222 x number of voices is the expected total number. The number of voices are:

VOICES="Amy Emma Brian Ivy Joanna Kendra Kimberly Salli Joey Justin Matthew Nicole Russell Geraint Aditi$

Watch out with the ending $. The text editor nano tells there'are more text with $.
 Raveena"is hiding behind it!
To put them together,
VOICES="Amy Emma Brian Ivy Joanna Kendra Kimberly Salli Joey Justin Matthew Nicole Russell Geraint Aditi Raveena"

16 voices.

1222x16=19552.

Auditi causes an problem for other files, too?
Hmmm... I can see something's wrong with this.
1222x15=18330


$ ls request_an_emergency_call.pcm-*.pcm | wc -l
16


Is the disk space enough?

~/aws_polly/tts_generated_speech_corpus$ df
Filesystem     1K-blocks    Used Available Use% Mounted on
udev              502932      12    502920   1% /dev
tmpfs             101632    9652     91980  10% /run
/dev/xvda1      10178756 5713272   3946780  60% /
none                   4       0         4   0% /sys/fs/cgroup
none                5120       0      5120   0% /run/lock
none              508140       0    508140   0% /run/shm
none              102400       0    102400   0% /run/user
~/aws_polly/tts_generated_speech_corpus$

Yes.

$ tar zcvf tts_generated_speech_corpus-20191204.tar.gz *.pcm

~/aws_polly/tts_generated_speech_corpus$ mv tts_generated_speech_corpus-20191204.tar.gz ..
~/aws_polly/tts_generated_speech_corpus$ cd ..
~/aws_polly$ ls
aws_polly.tar.gz  make_bona_i       run_polly4rl  test_wt_question_mark.mp3
how_are_you.mp3   make_how_are_you  test          this_is_a_test.mp3
how_are_you.pcm   new               test.mp3      tts_generated_speech_corpus-20191204.tar.gz
iloveyou.mp3      polly4bona        test2.mp3     tts_results
lid_hunk_corpus   run_polly         test3.mp3
aws_polly$

Google search: An error occurred (InvalidSignatureException) when calling the SynthesizeSpeech operation: Signature not yet current: 20191204T142743Z is still later than 20191204T142742Z (20191204T142242Z + 5 min.)

Discussion Forums > Category: AWS Web Site & Resources > Forum: PHP Development >Thread: ERROR/BUG - Signature not yet current
https://forums.aws.amazon.com/thread.jspa?threadID=134543


This error is occurring because of clock skew. This means that the time on your sever differs significantly from the time on the AWS server that is fulfilling your request. The solution to this issue is to ensure that your server has the correct time. This is typically accomplished using something like NTP: http://www.ntp.org/.

-Michael
