## Auto generation of DDS data types  and data readers ##

[$QLDDS\_HOME/gensrc/qldds\_gensrc.py](https://code.google.com/p/qldds/source/browse/gensrc/qldds_gensrc.py) is a python script that converts QuantLibAddin for C++ XML function definitions to [DDS Data Types](DDSDataTypes.md) and creates default implementation of DataReaders for converted types.  This script requires locations of source directories of ObjectHander, GenSrc and QuantLibAddin that can be passed as command arguments.

### Usage: ###

Unix(assuming all dependences are located at $HOME):
```
$ python qldds_gensrc.py --oh_dir=$HOME/ObjectHandler-1.2.0 --gensrc_dir=$HOME/gensrc-1.2.0 --qladdin_dir=$HOME/QuantLibAddin-1.2.0
```

Windows:
```
C:\qldds\gensrc>python qldds_gensrc.py --oh_dir=C:\build_ql_1_2_0\ObjectHandler --gensrc_dir=c:\build_ql_1_2_0\gensrc --qladdin_dir=c:\build_ql_1_2_0\QuantLibAddin
```