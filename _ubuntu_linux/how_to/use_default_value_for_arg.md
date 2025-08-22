# Default Value for Arguments.

```bash
"${variable:-default_value}"
```

For example,
```bash
    # Set variables with defaults that can be overridden by command-line arguments.
    local model="${1:-meta-llama/Meta-Llama-3.1-8B-Instruct}"
    local output_base_dir="${2:-results}"
    local model_type="${3:-vllm}"
```
