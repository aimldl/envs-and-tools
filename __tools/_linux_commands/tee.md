# tee
- The tee command reads from standard input and writes to both standard output and one or more files. 
- The name comes from its function, which is similar to a T-splitter in plumbing, splitting the flow into two directions.

## Syntax
`tee` splits the flow into two directions:
- standard output and
- one or more files.

```bash
command | tee file_name
```
The output of command is sent to tee, which then simultaneously 
- displays it on the screen (standard output) and
- writes it to the specified file.

`tee -a` appends the new output to the end of the existing content.

- By default, tee overwrites the file if it already exists.
- The -a option appends instead of overwriting the file.

## Example
```bash
#!/bin/bash

# Initialize flags
DRY_RUN=false

MODEL_NAME="gemini-2.5-flash"
OUTPUT_LOG="output.log"
CMD="python example.py"

# Write the starting messages to the log file using 'tee' to both display and write
echo "Sign into Google Cloud first. Run:" | tee "$OUTPUT_LOG"
echo "  $ gcloud auth application-default login" | tee -a "$OUTPUT_LOG"
echo "" | tee -a "$OUTPUT_LOG"

echo "To view the log, run:" | tee -a "$OUTPUT_LOG"
echo "  $ tail -f $OUTPUT_LOG" | tee -a "$OUTPUT_LOG"
echo "" | tee -a "$OUTPUT_LOG"
echo "$CMD" | tee -a "$OUTPUT_LOG"

if [ "$DRY_RUN" = false ]; then
  # Append the command output to the log file
  eval "$CMD" &>> "$OUTPUT_LOG"

  TIME_FINISHED=$(date +"%m-%d %H:%M:%S")
  echo "" >> "$OUTPUT_LOG"
  echo "Execution finished at $TIME_FINISHED" >> "$OUTPUT_LOG"
fi
```
