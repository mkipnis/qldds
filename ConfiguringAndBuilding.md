# Configuring and Building QLDDS #

## Dependencies: ##
| **Dependency** | **Version** |
|:---------------|:------------|
| [OpenDDS](http://www.opendds.org/) | 3.4.1 or later |
| [QuantLib](http://quantlib.org)  | 1.2.1 or later |
| [ObjectHandler](http://quantlib.org/objecthandler/) | 1.2.0 |
| [Gensrc](http://quantlib.org/gensrc/) | 1.2.0 |
| [QuantLibAddin for C++](http://quantlib.org/quantlibaddin/) | 1.2.0 |

[Building dependencies on Unix platform](BuildUnixDeps.md)


### Unix: ###
OpenDDS needs to be compiled; QuantLib, ObjectHandler, Gensrc, QuantLibAddin for C++ need to be compiled and installed(**make install**) prior to configuring and building QLDDS.

### Windows: ###
All QuantLib dependences have to be compiled and linked with **dynamic run-time libraries support(_gd_).**


---


## Configuring QLDDS ##
**configure.py** creates an environment file which needs to be sourced before building the project.

### Unix: ###
Assuming OpenDDS was compiled under $HOME and QuantLib and it's dependencies were installed under $HOME (prefix=$HOME, exec-prefix=$HOME)

```
$ python configure.py --dds_dir=$HOME/DDS --boost_dir=$HOME --quantlib_dir=$HOME --oh_dir=$HOME --qladdin_dir=$HOME
```

### Windows: ###
Assuming OpenDDS was compiled on C:\ and QuantLib and it's dependencies were compiled in their default locations.

**From Visual Studio Command Prompt!**

```
C:\qldds>python configure.py --dds_dir=c:\DDS --boost_dir=c:\progra~1\boost\boost_1_51 --quantlib_dir=c:\QuantLib-1.2.1 --oh_dir=c:\build_ql_1_2_0\ObjectHandler  --qladdin_dir=c:\build_ql_1_2_0\QuantLibAddin
```

Upon the successful execution of the configuration script the following file with environment variables will be created in the root directory of the package:  **Windows - qldds\_env.bat**, **Unix - qldds\_env.sh** .  This file should be sourced before building other components of the package.


---


## Building QLDDS: ##
Source created by configure.py environment file and run build.py

### Unix: ###
```
$ . ./qldds_env.sh 
$ python build.py
```

### Windows: ###
```
> call qldds_env.bat 
> python build.py
```