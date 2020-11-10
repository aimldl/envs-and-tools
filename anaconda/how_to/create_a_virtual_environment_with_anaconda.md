





```bash
(base) $ conda create -n text_summarization python=3 anaconda
```



```bash
(base) $ conda info -e
# conda environments:
#
base                  *  /home/k8smaster/anaconda3
text_summarization       /home/aimldl/anaconda3/envs/text_summarization
$
```



```bash
(base) $ conda activate text_summarization
(text_summarization) $
```



```bash
(text_summarization) $ jupyter notebook
[I 11:55:04.054 NotebookApp] JupyterLab extension loaded from /home/aimldl/anaconda3/envs/text_summarization/lib/python3.8/site-packages/jupyterlab
  ...    
    To access the notebook, open this file in a browser:
        file:///home/k8smaster/.local/share/jupyter/runtime/nbserver-2913783-open.html
    Or copy and paste one of these URLs:
        http://localhost:8888/?token=90a916cf0beae36746918b917b35f3951fdbf7b6a18d409e
     or http://127.0.0.1:8888/?token=90a916cf0beae36746918b917b35f3951fdbf7b6a18d409e
(text_summarization) $ 
```



```bash
(base) $ conda create -n text_summarization python=3 anaconda
Collecting package metadata (current_repodata.json): done
Solving environment: failed with repodata from current_repodata.json, will retry with next repodata source.
Collecting package metadata (repodata.json): done
Solving environment: done

## Package Plan ##

  environment location: /home/k8smaster/anaconda3/envs/text_summarization

  added / updated specs:
    - anaconda
    - python=3


The following NEW packages will be INSTALLED:

  _libgcc_mutex      pkgs/main/linux-64::_libgcc_mutex-0.1-main
  alabaster          pkgs/main/noarch::alabaster-0.7.12-py_0
  anaconda           pkgs/main/linux-64::anaconda-2020.07-py38_0
  anaconda-client    pkgs/main/linux-64::anaconda-client-1.7.2-py38_0
  anaconda-project   pkgs/main/noarch::anaconda-project-0.8.4-py_0
  argh               pkgs/main/linux-64::argh-0.26.2-py38_0
  asn1crypto         pkgs/main/linux-64::asn1crypto-1.3.0-py38_0
  astroid            pkgs/main/linux-64::astroid-2.4.2-py38_0
  astropy            pkgs/main/linux-64::astropy-4.0.1.post1-py38h7b6447c_1
  atomicwrites       pkgs/main/noarch::atomicwrites-1.4.0-py_0
  attrs              pkgs/main/noarch::attrs-19.3.0-py_0
  autopep8           pkgs/main/noarch::autopep8-1.5.3-py_0
  babel              pkgs/main/noarch::babel-2.8.0-py_0
  backcall           pkgs/main/noarch::backcall-0.2.0-py_0
  backports          pkgs/main/noarch::backports-1.0-py_2
  backports.shutil_~ pkgs/main/linux-64::backports.shutil_get_terminal_size-1.0.0-py38_2
  beautifulsoup4     pkgs/main/linux-64::beautifulsoup4-4.9.1-py38_0
  bitarray           pkgs/main/linux-64::bitarray-1.4.0-py38h7b6447c_0
  bkcharts           pkgs/main/linux-64::bkcharts-0.2-py38_0
  blas               pkgs/main/linux-64::blas-1.0-mkl
  bleach             pkgs/main/noarch::bleach-3.1.5-py_0
  blosc              pkgs/main/linux-64::blosc-1.19.0-hd408876_0
  bokeh              pkgs/main/linux-64::bokeh-2.1.1-py38_0
  boto               pkgs/main/linux-64::boto-2.49.0-py38_0
  bottleneck         pkgs/main/linux-64::bottleneck-1.3.2-py38heb32a55_1
  brotlipy           pkgs/main/linux-64::brotlipy-0.7.0-py38h7b6447c_1000
  bzip2              pkgs/main/linux-64::bzip2-1.0.8-h7b6447c_0
  ca-certificates    pkgs/main/linux-64::ca-certificates-2020.6.24-0
  cairo              pkgs/main/linux-64::cairo-1.14.12-h8948797_3
  certifi            pkgs/main/linux-64::certifi-2020.6.20-py38_0
  cffi               pkgs/main/linux-64::cffi-1.14.0-py38he30daa8_1
  chardet            pkgs/main/linux-64::chardet-3.0.4-py38_1003
  click              pkgs/main/noarch::click-7.1.2-py_0
  cloudpickle        pkgs/main/noarch::cloudpickle-1.5.0-py_0
  clyent             pkgs/main/linux-64::clyent-1.2.2-py38_1
  colorama           pkgs/main/noarch::colorama-0.4.3-py_0
  contextlib2        pkgs/main/noarch::contextlib2-0.6.0.post1-py_0
  cryptography       pkgs/main/linux-64::cryptography-2.9.2-py38h1ba5d50_0
  curl               pkgs/main/linux-64::curl-7.71.1-hbc83047_1
  cycler             pkgs/main/linux-64::cycler-0.10.0-py38_0
  cython             pkgs/main/linux-64::cython-0.29.21-py38he6710b0_0
  cytoolz            pkgs/main/linux-64::cytoolz-0.10.1-py38h7b6447c_0
  dask               pkgs/main/noarch::dask-2.20.0-py_0
  dask-core          pkgs/main/noarch::dask-core-2.20.0-py_0
  dbus               pkgs/main/linux-64::dbus-1.13.16-hb2f20db_0
  decorator          pkgs/main/noarch::decorator-4.4.2-py_0
  defusedxml         pkgs/main/noarch::defusedxml-0.6.0-py_0
  diff-match-patch   pkgs/main/noarch::diff-match-patch-20200713-py_0
  distributed        pkgs/main/linux-64::distributed-2.20.0-py38_0
  docutils           pkgs/main/linux-64::docutils-0.16-py38_1
  entrypoints        pkgs/main/linux-64::entrypoints-0.3-py38_0
  et_xmlfile         pkgs/main/noarch::et_xmlfile-1.0.1-py_1001
  expat              pkgs/main/linux-64::expat-2.2.9-he6710b0_2
  fastcache          pkgs/main/linux-64::fastcache-1.1.0-py38h7b6447c_0
  filelock           pkgs/main/noarch::filelock-3.0.12-py_0
  flake8             pkgs/main/noarch::flake8-3.8.3-py_0
  flask              pkgs/main/noarch::flask-1.1.2-py_0
  fontconfig         pkgs/main/linux-64::fontconfig-2.13.0-h9420a91_0
  freetype           pkgs/main/linux-64::freetype-2.10.2-h5ab3b9f_0
  fribidi            pkgs/main/linux-64::fribidi-1.0.9-h7b6447c_0
  fsspec             pkgs/main/noarch::fsspec-0.7.4-py_0
  future             pkgs/main/linux-64::future-0.18.2-py38_1
  get_terminal_size  pkgs/main/linux-64::get_terminal_size-1.0.0-haa9412d_0
  gevent             pkgs/main/linux-64::gevent-20.6.2-py38h7b6447c_0
  glib               pkgs/main/linux-64::glib-2.65.0-h3eb4bd4_0
  glob2              pkgs/main/noarch::glob2-0.7-py_0
  gmp                pkgs/main/linux-64::gmp-6.1.2-h6c8ec71_1
  gmpy2              pkgs/main/linux-64::gmpy2-2.0.8-py38hd5f6e3b_3
  graphite2          pkgs/main/linux-64::graphite2-1.3.14-h23475e2_0
  greenlet           pkgs/main/linux-64::greenlet-0.4.16-py38h7b6447c_0
  gst-plugins-base   pkgs/main/linux-64::gst-plugins-base-1.14.0-hbbd80ab_1
  gstreamer          pkgs/main/linux-64::gstreamer-1.14.0-hb31296c_0
  h5py               pkgs/main/linux-64::h5py-2.10.0-py38h7918eee_0
  harfbuzz           pkgs/main/linux-64::harfbuzz-2.4.0-hca77d97_1
  hdf5               pkgs/main/linux-64::hdf5-1.10.4-hb1b8bf9_0
  heapdict           pkgs/main/noarch::heapdict-1.0.1-py_0
  html5lib           pkgs/main/noarch::html5lib-1.1-py_0
  icu                pkgs/main/linux-64::icu-58.2-he6710b0_3
  idna               pkgs/main/noarch::idna-2.10-py_0
  imageio            pkgs/main/noarch::imageio-2.9.0-py_0
  imagesize          pkgs/main/noarch::imagesize-1.2.0-py_0
  importlib-metadata pkgs/main/linux-64::importlib-metadata-1.7.0-py38_0
  importlib_metadata pkgs/main/noarch::importlib_metadata-1.7.0-0
  intel-openmp       pkgs/main/linux-64::intel-openmp-2020.1-217
  intervaltree       pkgs/main/noarch::intervaltree-3.0.2-py_1
  ipykernel          pkgs/main/linux-64::ipykernel-5.3.2-py38h5ca1d4c_0
  ipython            pkgs/main/linux-64::ipython-7.16.1-py38h5ca1d4c_0
  ipython_genutils   pkgs/main/linux-64::ipython_genutils-0.2.0-py38_0
  ipywidgets         pkgs/main/noarch::ipywidgets-7.5.1-py_0
  isort              pkgs/main/linux-64::isort-4.3.21-py38_0
  itsdangerous       pkgs/main/noarch::itsdangerous-1.1.0-py_0
  jbig               pkgs/main/linux-64::jbig-2.1-hdba287a_0
  jdcal              pkgs/main/noarch::jdcal-1.4.1-py_0
  jedi               pkgs/main/linux-64::jedi-0.17.1-py38_0
  jeepney            pkgs/main/noarch::jeepney-0.4.3-py_0
  jinja2             pkgs/main/noarch::jinja2-2.11.2-py_0
  joblib             pkgs/main/noarch::joblib-0.16.0-py_0
  jpeg               pkgs/main/linux-64::jpeg-9b-h024ee3a_2
  json5              pkgs/main/noarch::json5-0.9.5-py_0
  jsonschema         pkgs/main/linux-64::jsonschema-3.2.0-py38_0
  jupyter            pkgs/main/linux-64::jupyter-1.0.0-py38_7
  jupyter_client     pkgs/main/noarch::jupyter_client-6.1.6-py_0
  jupyter_console    pkgs/main/noarch::jupyter_console-6.1.0-py_0
  jupyter_core       pkgs/main/linux-64::jupyter_core-4.6.3-py38_0
  jupyterlab         pkgs/main/noarch::jupyterlab-2.1.5-py_0
  jupyterlab_server  pkgs/main/noarch::jupyterlab_server-1.2.0-py_0
  keyring            pkgs/main/linux-64::keyring-21.2.1-py38_0
  kiwisolver         pkgs/main/linux-64::kiwisolver-1.2.0-py38hfd86e86_0
  krb5               pkgs/main/linux-64::krb5-1.18.2-h173b8e3_0
  lazy-object-proxy  pkgs/main/linux-64::lazy-object-proxy-1.4.3-py38h7b6447c_0
  lcms2              pkgs/main/linux-64::lcms2-2.11-h396b838_0
  ld_impl_linux-64   pkgs/main/linux-64::ld_impl_linux-64-2.33.1-h53a641e_7
  libarchive         pkgs/main/linux-64::libarchive-3.4.2-h62408e4_0
  libcurl            pkgs/main/linux-64::libcurl-7.71.1-h20c2e04_1
  libedit            pkgs/main/linux-64::libedit-3.1.20191231-h14c3975_1
  libffi             pkgs/main/linux-64::libffi-3.3-he6710b0_2
  libgcc-ng          pkgs/main/linux-64::libgcc-ng-9.1.0-hdf63c60_0
  libgfortran-ng     pkgs/main/linux-64::libgfortran-ng-7.3.0-hdf63c60_0
  liblief            pkgs/main/linux-64::liblief-0.10.1-he6710b0_0
  libllvm9           pkgs/main/linux-64::libllvm9-9.0.1-h4a3c616_1
  libpng             pkgs/main/linux-64::libpng-1.6.37-hbc83047_0
  libsodium          pkgs/main/linux-64::libsodium-1.0.18-h7b6447c_0
  libspatialindex    pkgs/main/linux-64::libspatialindex-1.9.3-he6710b0_0
  libssh2            pkgs/main/linux-64::libssh2-1.9.0-h1ba5d50_1
  libstdcxx-ng       pkgs/main/linux-64::libstdcxx-ng-9.1.0-hdf63c60_0
  libtiff            pkgs/main/linux-64::libtiff-4.1.0-h2733197_1
  libtool            pkgs/main/linux-64::libtool-2.4.6-h7b6447c_5
  libuuid            pkgs/main/linux-64::libuuid-1.0.3-h1bed415_2
  libxcb             pkgs/main/linux-64::libxcb-1.14-h7b6447c_0
  libxml2            pkgs/main/linux-64::libxml2-2.9.10-he19cac6_1
  libxslt            pkgs/main/linux-64::libxslt-1.1.34-hc22bd24_0
  llvmlite           pkgs/main/linux-64::llvmlite-0.33.0-py38hc6ec683_1
  locket             pkgs/main/linux-64::locket-0.2.0-py38_1
  lxml               pkgs/main/linux-64::lxml-4.5.2-py38hefd8a0e_0
  lz4-c              pkgs/main/linux-64::lz4-c-1.9.2-he6710b0_0
  lzo                pkgs/main/linux-64::lzo-2.10-h7b6447c_2
  markupsafe         pkgs/main/linux-64::markupsafe-1.1.1-py38h7b6447c_0
  matplotlib         pkgs/main/linux-64::matplotlib-3.2.2-0
  matplotlib-base    pkgs/main/linux-64::matplotlib-base-3.2.2-py38hef1b27d_0
  mccabe             pkgs/main/linux-64::mccabe-0.6.1-py38_1
  mistune            pkgs/main/linux-64::mistune-0.8.4-py38h7b6447c_1000
  mkl                pkgs/main/linux-64::mkl-2020.1-217
  mkl-service        pkgs/main/linux-64::mkl-service-2.3.0-py38he904b0f_0
  mkl_fft            pkgs/main/linux-64::mkl_fft-1.1.0-py38h23d657b_0
  mkl_random         pkgs/main/linux-64::mkl_random-1.1.1-py38h0573a6f_0
  mock               pkgs/main/noarch::mock-4.0.2-py_0
  more-itertools     pkgs/main/noarch::more-itertools-8.4.0-py_0
  mpc                pkgs/main/linux-64::mpc-1.1.0-h10f8cd9_1
  mpfr               pkgs/main/linux-64::mpfr-4.0.2-hb69a4c5_1
  mpmath             pkgs/main/linux-64::mpmath-1.1.0-py38_0
  msgpack-python     pkgs/main/linux-64::msgpack-python-1.0.0-py38hfd86e86_1
  multipledispatch   pkgs/main/linux-64::multipledispatch-0.6.0-py38_0
  nbconvert          pkgs/main/linux-64::nbconvert-5.6.1-py38_0
  nbformat           pkgs/main/noarch::nbformat-5.0.7-py_0
  ncurses            pkgs/main/linux-64::ncurses-6.2-he6710b0_1
  networkx           pkgs/main/noarch::networkx-2.4-py_1
  nltk               pkgs/main/noarch::nltk-3.5-py_0
  nose               pkgs/main/linux-64::nose-1.3.7-py38_2
  notebook           pkgs/main/linux-64::notebook-6.0.3-py38_0
  numba              pkgs/main/linux-64::numba-0.50.1-py38h0573a6f_1
  numexpr            pkgs/main/linux-64::numexpr-2.7.1-py38h423224d_0
  numpy              pkgs/main/linux-64::numpy-1.18.5-py38ha1c710e_0
  numpy-base         pkgs/main/linux-64::numpy-base-1.18.5-py38hde5b4d6_0
  numpydoc           pkgs/main/noarch::numpydoc-1.1.0-py_0
  olefile            pkgs/main/noarch::olefile-0.46-py_0
  openpyxl           pkgs/main/noarch::openpyxl-3.0.4-py_0
  openssl            pkgs/main/linux-64::openssl-1.1.1g-h7b6447c_0
  packaging          pkgs/main/noarch::packaging-20.4-py_0
  pandas             pkgs/main/linux-64::pandas-1.0.5-py38h0573a6f_0
  pandoc             pkgs/main/linux-64::pandoc-2.10-0
  pandocfilters      pkgs/main/linux-64::pandocfilters-1.4.2-py38_1
  pango              pkgs/main/linux-64::pango-1.45.3-hd140c19_0
  parso              pkgs/main/noarch::parso-0.7.0-py_0
  partd              pkgs/main/noarch::partd-1.1.0-py_0
  patchelf           pkgs/main/linux-64::patchelf-0.11-he6710b0_0
  path               pkgs/main/linux-64::path-13.1.0-py38_0
  path.py            pkgs/main/noarch::path.py-12.4.0-0
  pathlib2           pkgs/main/linux-64::pathlib2-2.3.5-py38_0
  pathtools          pkgs/main/noarch::pathtools-0.1.2-py_1
  patsy              pkgs/main/linux-64::patsy-0.5.1-py38_0
  pcre               pkgs/main/linux-64::pcre-8.44-he6710b0_0
  pep8               pkgs/main/linux-64::pep8-1.7.1-py38_0
  pexpect            pkgs/main/linux-64::pexpect-4.8.0-py38_0
  pickleshare        pkgs/main/linux-64::pickleshare-0.7.5-py38_1000
  pillow             pkgs/main/linux-64::pillow-7.2.0-py38hb39fc2d_0
  pip                pkgs/main/linux-64::pip-20.1.1-py38_1
  pixman             pkgs/main/linux-64::pixman-0.40.0-h7b6447c_0
  pkginfo            pkgs/main/linux-64::pkginfo-1.5.0.1-py38_0
  pluggy             pkgs/main/linux-64::pluggy-0.13.1-py38_0
  ply                pkgs/main/linux-64::ply-3.11-py38_0
  prometheus_client  pkgs/main/noarch::prometheus_client-0.8.0-py_0
  prompt-toolkit     pkgs/main/noarch::prompt-toolkit-3.0.5-py_0
  prompt_toolkit     pkgs/main/noarch::prompt_toolkit-3.0.5-0
  psutil             pkgs/main/linux-64::psutil-5.7.0-py38h7b6447c_0
  ptyprocess         pkgs/main/linux-64::ptyprocess-0.6.0-py38_0
  py                 pkgs/main/noarch::py-1.9.0-py_0
  py-lief            pkgs/main/linux-64::py-lief-0.10.1-py38h403a769_0
  pycodestyle        pkgs/main/noarch::pycodestyle-2.6.0-py_0
  pycosat            pkgs/main/linux-64::pycosat-0.6.3-py38h7b6447c_1
  pycparser          pkgs/main/noarch::pycparser-2.20-py_2
  pycurl             pkgs/main/linux-64::pycurl-7.43.0.5-py38h1ba5d50_0
  pydocstyle         pkgs/main/noarch::pydocstyle-5.0.2-py_0
  pyflakes           pkgs/main/noarch::pyflakes-2.2.0-py_0
  pygments           pkgs/main/noarch::pygments-2.6.1-py_0
  pylint             pkgs/main/linux-64::pylint-2.5.3-py38_0
  pyodbc             pkgs/main/linux-64::pyodbc-4.0.30-py38he6710b0_0
  pyopenssl          pkgs/main/noarch::pyopenssl-19.1.0-py_1
  pyparsing          pkgs/main/noarch::pyparsing-2.4.7-py_0
  pyqt               pkgs/main/linux-64::pyqt-5.9.2-py38h05f1152_4
  pyrsistent         pkgs/main/linux-64::pyrsistent-0.16.0-py38h7b6447c_0
  pysocks            pkgs/main/linux-64::pysocks-1.7.1-py38_0
  pytables           pkgs/main/linux-64::pytables-3.6.1-py38h9fd0a39_0
  pytest             pkgs/main/linux-64::pytest-5.4.3-py38_0
  python             pkgs/main/linux-64::python-3.8.3-hcff3b4d_2
  python-dateutil    pkgs/main/noarch::python-dateutil-2.8.1-py_0
  python-jsonrpc-se~ pkgs/main/noarch::python-jsonrpc-server-0.3.4-py_1
  python-language-s~ pkgs/main/linux-64::python-language-server-0.34.1-py38_0
  python-libarchive~ pkgs/main/noarch::python-libarchive-c-2.9-py_0
  pytz               pkgs/main/noarch::pytz-2020.1-py_0
  pywavelets         pkgs/main/linux-64::pywavelets-1.1.1-py38h7b6447c_0
  pyxdg              pkgs/main/noarch::pyxdg-0.26-py_0
  pyyaml             pkgs/main/linux-64::pyyaml-5.3.1-py38h7b6447c_1
  pyzmq              pkgs/main/linux-64::pyzmq-19.0.1-py38he6710b0_1
  qdarkstyle         pkgs/main/noarch::qdarkstyle-2.8.1-py_0
  qt                 pkgs/main/linux-64::qt-5.9.7-h5867ecd_1
  qtawesome          pkgs/main/noarch::qtawesome-0.7.2-py_0
  qtconsole          pkgs/main/noarch::qtconsole-4.7.5-py_0
  qtpy               pkgs/main/noarch::qtpy-1.9.0-py_0
  readline           pkgs/main/linux-64::readline-8.0-h7b6447c_0
  regex              pkgs/main/linux-64::regex-2020.6.8-py38h7b6447c_0
  requests           pkgs/main/noarch::requests-2.24.0-py_0
  ripgrep            pkgs/main/linux-64::ripgrep-11.0.2-he32d670_0
  rope               pkgs/main/noarch::rope-0.17.0-py_0
  rtree              pkgs/main/linux-64::rtree-0.9.4-py38_1
  ruamel_yaml        pkgs/main/linux-64::ruamel_yaml-0.15.87-py38h7b6447c_1
  scikit-image       pkgs/main/linux-64::scikit-image-0.16.2-py38h0573a6f_0
  scikit-learn       pkgs/main/linux-64::scikit-learn-0.23.1-py38h423224d_0
  scipy              pkgs/main/linux-64::scipy-1.5.0-py38h0b6359f_0
  seaborn            pkgs/main/noarch::seaborn-0.10.1-py_0
  secretstorage      pkgs/main/linux-64::secretstorage-3.1.2-py38_0
  send2trash         pkgs/main/linux-64::send2trash-1.5.0-py38_0
  setuptools         pkgs/main/linux-64::setuptools-49.2.0-py38_0
  simplegeneric      pkgs/main/linux-64::simplegeneric-0.8.1-py38_2
  singledispatch     pkgs/main/linux-64::singledispatch-3.4.0.3-py38_0
  sip                pkgs/main/linux-64::sip-4.19.13-py38he6710b0_0
  six                pkgs/main/noarch::six-1.15.0-py_0
  snappy             pkgs/main/linux-64::snappy-1.1.8-he6710b0_0
  snowballstemmer    pkgs/main/noarch::snowballstemmer-2.0.0-py_0
  sortedcollections  pkgs/main/noarch::sortedcollections-1.2.1-py_0
  sortedcontainers   pkgs/main/noarch::sortedcontainers-2.2.2-py_0
  soupsieve          pkgs/main/noarch::soupsieve-2.0.1-py_0
  sphinx             pkgs/main/noarch::sphinx-3.1.2-py_0
  sphinxcontrib      pkgs/main/linux-64::sphinxcontrib-1.0-py38_1
  sphinxcontrib-app~ pkgs/main/noarch::sphinxcontrib-applehelp-1.0.2-py_0
  sphinxcontrib-dev~ pkgs/main/noarch::sphinxcontrib-devhelp-1.0.2-py_0
  sphinxcontrib-htm~ pkgs/main/noarch::sphinxcontrib-htmlhelp-1.0.3-py_0
  sphinxcontrib-jsm~ pkgs/main/noarch::sphinxcontrib-jsmath-1.0.1-py_0
  sphinxcontrib-qth~ pkgs/main/noarch::sphinxcontrib-qthelp-1.0.3-py_0
  sphinxcontrib-ser~ pkgs/main/noarch::sphinxcontrib-serializinghtml-1.1.4-py_0
  sphinxcontrib-web~ pkgs/main/noarch::sphinxcontrib-websupport-1.2.3-py_0
  spyder             pkgs/main/linux-64::spyder-4.1.4-py38_0
  spyder-kernels     pkgs/main/linux-64::spyder-kernels-1.9.2-py38_0
  sqlalchemy         pkgs/main/linux-64::sqlalchemy-1.3.18-py38h7b6447c_0
  sqlite             pkgs/main/linux-64::sqlite-3.32.3-h62c20be_0
  statsmodels        pkgs/main/linux-64::statsmodels-0.11.1-py38h7b6447c_0
  sympy              pkgs/main/linux-64::sympy-1.6.1-py38_0
  tbb                pkgs/main/linux-64::tbb-2020.0-hfd86e86_0
  tblib              pkgs/main/noarch::tblib-1.6.0-py_0
  terminado          pkgs/main/linux-64::terminado-0.8.3-py38_0
  testpath           pkgs/main/noarch::testpath-0.4.4-py_0
  threadpoolctl      pkgs/main/noarch::threadpoolctl-2.1.0-pyh5ca1d4c_0
  tk                 pkgs/main/linux-64::tk-8.6.10-hbc83047_0
  toml               pkgs/main/noarch::toml-0.10.1-py_0
  toolz              pkgs/main/noarch::toolz-0.10.0-py_0
  tornado            pkgs/main/linux-64::tornado-6.0.4-py38h7b6447c_1
  tqdm               pkgs/main/noarch::tqdm-4.47.0-py_0
  traitlets          pkgs/main/linux-64::traitlets-4.3.3-py38_0
  typing_extensions  pkgs/main/noarch::typing_extensions-3.7.4.2-py_0
  ujson              pkgs/main/linux-64::ujson-1.35-py38h7b6447c_0
  unicodecsv         pkgs/main/linux-64::unicodecsv-0.14.1-py38_0
  unixodbc           pkgs/main/linux-64::unixodbc-2.3.7-h14c3975_0
  urllib3            pkgs/main/noarch::urllib3-1.25.9-py_0
  watchdog           pkgs/main/linux-64::watchdog-0.10.3-py38_0
  wcwidth            pkgs/main/noarch::wcwidth-0.2.5-py_0
  webencodings       pkgs/main/linux-64::webencodings-0.5.1-py38_1
  werkzeug           pkgs/main/noarch::werkzeug-1.0.1-py_0
  wheel              pkgs/main/linux-64::wheel-0.34.2-py38_0
  widgetsnbextension pkgs/main/linux-64::widgetsnbextension-3.5.1-py38_0
  wrapt              pkgs/main/linux-64::wrapt-1.11.2-py38h7b6447c_0
  wurlitzer          pkgs/main/linux-64::wurlitzer-2.0.1-py38_0
  xlrd               pkgs/main/noarch::xlrd-1.2.0-py_0
  xlsxwriter         pkgs/main/noarch::xlsxwriter-1.2.9-py_0
  xlwt               pkgs/main/linux-64::xlwt-1.3.0-py38_0
  xz                 pkgs/main/linux-64::xz-5.2.5-h7b6447c_0
  yaml               pkgs/main/linux-64::yaml-0.2.5-h7b6447c_0
  yapf               pkgs/main/noarch::yapf-0.30.0-py_0
  zeromq             pkgs/main/linux-64::zeromq-4.3.2-he6710b0_2
  zict               pkgs/main/noarch::zict-2.0.0-py_0
  zipp               pkgs/main/noarch::zipp-3.1.0-py_0
  zlib               pkgs/main/linux-64::zlib-1.2.11-h7b6447c_3
  zope               pkgs/main/linux-64::zope-1.0-py38_1
  zope.event         pkgs/main/linux-64::zope.event-4.4-py38_0
  zope.interface     pkgs/main/linux-64::zope.interface-4.7.1-py38h7b6447c_0
  zstd               pkgs/main/linux-64::zstd-1.4.5-h0b5b093_0


Proceed ([y]/n)? 

Preparing transaction: done
Verifying transaction: done
Executing transaction: done
#
# To activate this environment, use
#
#     $ conda activate text_summarization
#
# To deactivate an active environment, use
#
#     $ conda deactivate

(base) $
```

