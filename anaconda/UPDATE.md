# Update conda
* Created: 2019-12-18 (Wed)
* Updated: 2025-02-22 (Sat)

## Update all
```bash
(base) $ conda update --all -y
```

## With the -y option,
```bash
$ conda update -n base -c defaults -y conda
```
name is base and the channel is defaults. The -y says "Yes" automatically.

## Without the -y option,

```bash
$ conda update -n base -c defaults conda
```

The full message is below.
```bash
$ conda update -n base -c defaults conda
Collecting package metadata (current_repodata.json): done
Solving environment: done

## Package Plan ##

  environment location: /home/aimldl/anaconda3

  added / updated specs:
    - conda


The following packages will be downloaded:

    package                    |            build
    ---------------------------|-----------------
    backports.functools_lru_cache-1.6.1|             py_0          11 KB
    conda-4.8.0                |           py37_1         2.8 MB
    ------------------------------------------------------------
                                           Total:         2.8 MB

The following packages will be UPDATED:

  backports.functoo~                               1.5-py_2 --> 1.6.1-py_0
  conda                                       4.7.12-py37_0 --> 4.8.0-py37_1


Proceed ([y]/n)? y


Downloading and Extracting Packages
backports.functools_ | 11 KB     | ############################################################## | 100%
conda-4.8.0          | 2.8 MB    | ############################################################## | 100%
Preparing transaction: done
Verifying transaction: done
Executing transaction: done
$
```
