* Draft:  2019-12-06 (Fri)
# sed (Stream EDitor)
sed is a Unix/Linux command to parse and transform text. For the basics, refer to [Linux sed command](https://www.computerhope.com/unix/used.htm),  [Sed Command in Linux/Unix with examples](https://www.geeksforgeeks.org/sed-command-in-linux-unix-with-examples/) and [sed, a stream editor](https://www.gnu.org/software/sed/manual/sed.html).

## Examples

### s for Substitute

`sample_file.txt`

```text
This is the sample file.
An example sentence is below.
"Take the medicine an hour before a meal."
After applying the sed command, check the text in this file.
Pay attention to what happens beforehand.
Does the meaning change? Yes? :-)

Some more words for the sake of practice.
before Before BEFORE bEFORE
after  After  AFTER  aFTER
```

#### Number of occurrence
##### Substitute "before" to "after" (all the occurrences)
```bash
$ sed 's/before/after/' sample_file.txt
```
> "Take the medicine an hour ***after*** a meal."
> Pay attention to what happens ***after***hand.
> ***after*** Before BEFORE bEFORE

##### Substitute the n-th occurrence

```bash
$ sed 's/before/after/3' sample_file.txt
```
TODO: Fix this. /1 is the same as /, but /2 or /3 doesn't change anything.

##### Substitute  or global.

```bash
$ sed 's/before/after/g' sample_file.txt
```
> "Take the medicine an hour ***after*** a meal."
> Pay attention to what happens ***after***hand.
> ***after*** Before BEFORE bEFORE

#### Specify a specific line number

Limit the scope to the n-th line and substitute before to after if there is a match. 

```bash
$ sed 'n s/before/after/' sample_file.txt
```

##### Examples

```bash
$ sed '3 s/before/after/' sample_file.txt
```

> "Take the medicine an hour ***after*** a meal."

```bash
$ sed '5 s/before/after/' sample_file.txt
```

> Pay attention to what happens ***after***hand.

```bash
$ sed '9 s/before/after/' sample_file.txt
```

> ***after*** Before BEFORE bEFORE

### Options

#### -i or --in-place

The -i or --in-place option edits files in-place. In effect, this option is like `--quiet` for other commands. (Be careful with the `--quiet` option for sed because this option may not behave as you expected.)

The -i or --in-place option is explained more in detail below. So far the changes are printed to the standard output. In other words, the changes are displayed on the terminal. For example, 

```bash
$ sed '9 s/before/after/' sample_file.txt
This is the sample file.
An example sentense is below.
"Take the medicine an hour before a meal."
After applying the sed command, check the text in this file.
Pay attention to what happens beforehand.
Does the meaning change? Yes? :-)

Some more words for the sake of practice.
after Before BEFORE bEFORE
after  After  AFTER  aFTER
$
```

The -i or --in-place option doesn't display the output. Instead the file itself is edited.

```bash
$ sed -i '9 s/before/after/' sample_file.txt
$
```

Let's check the file with the tail command.

```bash
$ tail sample_file.txt 
This is the sample file.
An example sentense is below.
"Take the medicine an hour before a meal."
After applying the sed command, check the text in this file.
Pay attention to what happens beforehand.
Does the meaning change? Yes? :-)

Some more words for the sake of practice.
after Before BEFORE bEFORE
after  After  AFTER  aFTER
$
```

"before" in the 9th line is changed to "after" resulting in:

> ***after*** Before BEFORE bEFORE

#### Before moving to the next step

Reset the change. That is, revert the change so that `sample_file.txt` is the same as the beginning.

```bash
$ sed -i '9 s/after/before/' sample_file.txt
```

To verify, 

> $ tail sample_file.txt 
> This is the sample file.
> An example sentense is below.
> "Take the medicine an hour before a meal."
> After applying the sed command, check the text in this file.
> Pay attention to what happens beforehand.
> Does the meaning change? Yes? :-)
>
> Some more words for the sake of practice.
> ***before*** Before BEFORE bEFORE
> after  After  AFTER  aFTER
>
> $

#### -i`SUFFIX` or --in-place`=SUFFIX`

Using the -i option is a great way to substitute a file in-place. The drawback is the original file is lost. What if a mistake is made? It's the best to keep the original and save the substitutes in a separate file. Add a suffix after `i` without a space to back up the original file. For example,

```bash
$ sed -i'.bak' '9 s/before/after/' sample_file.txt
```

List the file and `sample_file.txt.bak` is created as well as `sample_file.txt`. 

```bash
$ ls
sample_file.txt  sample_file.txt.bak
$
```

The change is saved in `sample_file.txt`.

```bash
$ tail sample_file.txt
```

> This is the sample file.
> An example sentense is below.
> "Take the medicine an hour before a meal."
> After applying the sed command, check the text in this file.
> Pay attention to what happens beforehand.
> Does the meaning change? Yes? :-)
>
> Some more words for the sake of practice.
> after Before BEFORE bEFORE
> after  After  AFTER  aFTER

The back up is saved to `sample_file.txt.bak`.

```bash
$ tail sample_file.txt.bak 
```

> This is the sample file.
> An example sentense is below.
> "Take the medicine an hour before a meal."
> After applying the sed command, check the text in this file.
> Pay attention to what happens beforehand.
> Does the meaning change? Yes? :-)
>
> Some more words for the sake of practice.
> before Before BEFORE bEFORE
> after  After  AFTER  aFTER

#### -r

TODO: add an explanation
```bash
$ grep "current-context" ~/.kube/config | sed -r 's/:|@|\./ /g'
```

```bash
function get_eks_cluster_name() {

  # Kubeflow's configuration file is ~/.kube/config.
  # Get the line with "current-context:" and
  #   extract the cluster name.

  CURRENT_CONTEXT=`grep "current-context" ~/.kube/config | sed -r 's/:|@|\./ /g'`
  # current-context: aimldl@ridiculous-sheepdog-1587095845.us-west-2.eksctl.io
  # current-context  aimldl ridiculous-sheepdog-1587095845 us-west-2 eksctl io
  # $1               $2     $3                             $4        $5     $6

  EKS_CLUSTER_NAME=`echo ${CURRENT_CONTEXT} | awk '{ print $3; }'`
  echo ${EKS_CLUSTER_NAME}
}
```

#### Example 1
##### Problem
The file names are wrong. There're ".wav" in the middle in 14937 files.

$ ls | wc -l
14937

$ ls
air_con.wav-Aditi.wav
air_con.wav-Brian.wav
  ...
you_should_wake_me_up_at_seven_am.wav-Russell.wav
you_should_wake_me_up_at_seven_am.wav-Salli.wav

##### Solution
Use "sed" to change the file names. The following command replaces ".wav-" to "-" globally or at all occurences.
$ ls | sed 's/\.wav-/-/g'
air_con-Aditi.wav
air_con-Brian.wav
  ...
you_should_wake_me_up_at_seven_am-Russell.wav
you_should_wake_me_up_at_seven_am-Salli.wav

Note the follogin command replaces all occurences of ".wav-" to nothing globally. In other words, delete all ".wav-"
$ ls | sed 's/\.wav-//g'
air_conAditi.wav
air_conBrian.wav
  ...
you_should_wake_me_up_at_seven_amRussell.wav
you_should_wake_me_up_at_seven_amSalli.wav

#### Example 2

Rename the existing directories in benchmark_results. For example, klue-ynat is changed to klue_ynat. Apply this change to all sub-directory names the benchmark_results directory. 

```bash
cd benchmark_results && for dir in klue-*; do if [ -d "$dir" ]; then new_name=$(echo "$dir" | sed 's/klue-/klue_/g'); echo "Renaming $dir to $new_name"; mv "$dir" "$new_name"; fi; done
```

Before
```bash
$ tree -d benchmark_results/
benchmark_results/
├── klue-dp
├── klue-mrc
├── klue-ner
├── klue-nli
├── klue-re
├── klue-sts
├── klue-wos
└── klue-ynat

9 directories
$
```

After
```bash
$ tree -d benchmark_results/
benchmark_results/
├── klue_dp
├── klue_mrc
├── klue_ner
├── klue_nli
├── klue_re
├── klue_sts
├── klue_wos
└── klue_ynat

9 directories
$
```
