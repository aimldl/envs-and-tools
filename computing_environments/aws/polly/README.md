##### aimldl > aws > polly > README.md
* Rev.1: 2019-11-28 (Thu)
* Draft: 2018-12-18 (Tue)


#### Supported output format
<img src="images/Amazon_Polly-SynthesizeSpeech-OutputFormat.png" height=373
 width=584 >
source: [SynthesizeSpeech](https://docs.aws.amazon.com/polly/latest/dg/API_SynthesizeSpeech.html) > OutputFormat

* Tip to get a wav file
To change the output format to wav, you should do it in two steps. Amazon Polly doesn't support wav. Instead, pcm is supported. So get the Polly's output in pcm and then convert the pcm file to a wav file. Refer to [pcm2wav](https://github.com/aimldl/computing_environments/blob/70f412adceec4f3364ec0546a5e749bdef3de6f5/bash/scripts/pcm2wav) to convert the format.

#### Available Voices
Voices available for Chinese, English, Japanese, and Korean languages are below (as of 2019-12-17).

<img src="images/amazon_polly-voices.png">

Refer to [Voices in Amazon Polly](https://docs.aws.amazon.com/polly/latest/dg/voicelist.html) for the entire list of available voices.
